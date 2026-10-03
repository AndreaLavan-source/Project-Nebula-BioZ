#include <iostream>
#include <cmath>
#include <vector>

#define AD5940_SUCCESS          0
#define MAX_MATRIX_NODES        128
#define PI                      3.14159265358979323846

struct ComplexImpedance {
    double real_ohms;
    double imaginary_ohms;
    double impedance_magnitude;
    double phase_angle;
};

class Layer2DSPPipeline {
private:
    double current_clamping_threshold_ua;
    
    // Physical Zero-Ohm Baseline Correction Storage Variables
    double zero_ohm_offset_real;
    double zero_ohm_offset_imag;
    bool is_calibrated;

public:
    Layer2DSPPipeline() {
        current_clamping_threshold_ua = 10.0;
        zero_ohm_offset_real = 0.0;
        zero_ohm_offset_imag = 0.0;
        is_calibrated = false;
    }

    /**
     * COMMAND: Capture 0-Ohm System Short-Circuit Calibration Profile.
     * Call this when you have placed the shorting link between Breadboard Rows 5 & 10.
     */
    void record_zero_ohm_baseline(double raw_real, double raw_imag) {
        this->zero_ohm_offset_real = raw_real;
        this->zero_ohm_offset_imag = raw_imag;
        this->is_calibrated = true;
        std::cout << "\n[CALIBRATION] Succeeded! 0-Ohm Wire Baseline Matrix Recorded:\n";
        std::cout << "              -> Offset Real Vector: " << zero_ohm_offset_real << "\n";
        std::cout << "              -> Offset Imag Vector: " << zero_ohm_offset_imag << "\n\n";
    }

    /**
     * INGESTION PIPELINE: Subtracts baseline noise and scales raw digital signals.
     */
    ComplexImpedance process_hardware_dft_codes(double raw_real, double raw_imag) {
        ComplexImpedance calibrated;
        const double RCAL_VALUE = 10000.0; // 10k reference resistor
        const double SYSTEM_GAIN = 5800.0; // Hardware amplification factor

        // Subtract the 0-Ohm calibration offsets if recording is complete
        double corrected_real = raw_real - this->zero_ohm_offset_real;
        double corrected_imag = raw_imag - this->zero_ohm_offset_imag;

        double raw_magnitude = std::sqrt((corrected_real * corrected_real) + (corrected_imag * corrected_imag));
        
        if (raw_magnitude < 1.0) {
            calibrated.impedance_magnitude = 999999.9;
            calibrated.phase_angle = 0.0;
            return calibrated;
        }

        // Compute actual system impedance magnitude in Ohms (Z)
        calibrated.impedance_magnitude = (RCAL_VALUE / raw_magnitude) * SYSTEM_GAIN;
        
        // Calculate the physical raw phase shift
        double raw_phase_deg = std::atan2(corrected_imag, corrected_real) * (180.0 / PI);
        
        // Correct vector phase layout
        if (raw_phase_deg < -90.0) {
            calibrated.phase_angle = raw_phase_deg + 180.0; 
        } else {
            calibrated.phase_angle = raw_phase_deg;
        }
        
        calibrated.real_ohms = calibrated.impedance_magnitude * std::cos(calibrated.phase_angle * (PI / 180.0));
        calibrated.imaginary_ohms = calibrated.impedance_magnitude * std::sin(calibrated.phase_angle * (PI / 180.0));
        
        return calibrated;
    }

    void process_live_matrix_sweep(const std::vector<std::pair<double, double>>& live_hardware_stream) {
        std::cout << "[FIRMWARE] Streaming Layer 2 High-Density Multi-Channel Sweep Data...\n";
        for (size_t node = 0; node < live_hardware_stream.size(); ++node) {
            if (node >= MAX_MATRIX_NODES) break;

            ComplexImpedance node_data = process_hardware_dft_codes(live_hardware_stream[node].first, live_hardware_stream[node].second);

            std::cout << " -> Node [" << node << "] Calibrated Impedance: " 
                      << node_data.impedance_magnitude << " Ohms | Phase Delay: " 
                      << node_data.phase_angle << "°\n";
        }
    }
};

int main() { 
    Layer2DSPPipeline dsp_engine; 

    // =========================================================================
    // STEP 1: ZERO-OHM SHORT CIRCUIT INITIALIZATION
    // Put a solid jumper wire between row 5 and row 10, then pass raw line inputs below:
    // =========================================================================
    double hardware_short_real = 131420.0; // Insert the active real channel trace code here
    double hardware_short_imag = -4200.0;  // Insert the active imaginary channel trace code here
    
    dsp_engine.record_zero_ohm_baseline(hardware_short_real, hardware_short_imag);

    // =========================================================================
    // STEP 2: LIVE METRIC RUNWAY
    // Place components back on Rows 5 & 10. The system will evaluate them cleanly.
    // =========================================================================
    std::vector<std::pair<double, double>> active_adc_stream = { 
        {131881.0, -4500.0}, // Live Matrix Node 0
        {131420.0, -4200.0}, // Live Matrix Node 1
    };

    dsp_engine.process_live_matrix_sweep(active_adc_stream); 
    return 0;
}
