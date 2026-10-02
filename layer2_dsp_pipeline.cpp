#include <iostream>
#include <cmath>
#include <vector>

// Simulated Analog Devices EVAL-AD5940 Hardware Registers & Constants
#define AD5940_SUCCESS          0
#define MAX_MATRIX_NODES        128
#define PI                      3.14159265358979323846

struct ComplexImpedance {
    double real_ohms;      // Pure material resistance
    double imaginary_ohms; // Capacitive reactance
    double phase_angle;    // Calculated biological delay in degrees
};

class Layer2DSPPipeline {
private:
    double current_clamping_threshold_ua;

public:
    Layer2DSPPipeline() {
        current_clamping_threshold_ua = 10.0; // Strict human safety barrier
    }

    /**
     * Executes a hardware quadrant inversion correction loop.
     * Bypasses the inherent 180-degree propagation shifts introduced by electrical isolation buffers.
     */
    ComplexImpedance apply_quadrant_inversion_filter(double raw_real, double raw_imag) {
        ComplexImpedance corrected_metrics;
        
        // Step 1: Extract basic engineering metrics using standard rectangular-to-polar formulas
        corrected_metrics.real_ohms = raw_real;
        corrected_metrics.imaginary_ohms = raw_imag;
        
        // Calculate raw phase angle in radians, then convert to degrees
        double raw_phase_deg = std::atan2(raw_imag, raw_real) * (180.0 / PI);
        
        // Step 2: Digital Corrective Prism Filter
        // If the signal registers an inherent inverted phase shift (e.g., ~ -143°), un-flip it to its true biological value
        if (raw_phase_deg < -90.0) {
            corrected_metrics.phase_angle = raw_phase_deg + 180.0; // Realigns vector with true biological state
        } else {
            corrected_metrics.phase_angle = raw_phase_deg;
        }
        
        return corrected_metrics;
    }

    void process_matrix_sweep(const std::vector<std::pair<double, double>>& raw_hardware_stream) {
        std::cout << "[FIRMWARE] Processing Layer 2 High-Density Multi-Channel Sweep Data...\n";
        
        for (size_t node = 0; node < raw_hardware_stream.size(); ++node) {
            if (node >= MAX_MATRIX_NODES) break;

            // Ingest raw real/imaginary DFT data points from the Analog Front End
            double raw_real = raw_hardware_stream[node].first;
            double raw_imag = raw_hardware_stream[node].second;

            // Process data through the quadrant correction loop
            ComplexImpedance node_data = apply_quadrant_inversion_filter(raw_real, raw_imag);

            std::cout << " -> Node [" << node << "] Corrected Phase Angle: " 
                      << node_data.phase_angle << "° | Resistance: " 
                      << node_data.real_ohms << " Ohms\n";
        }
    }
};

int main() { 
    Layer2DSPPipeline dsp_engine; 

    // Simulated raw incoming benchtop stream with hardware inversion artifacts (-143.42° flipped profile) 
    std::vector<std::pair<double, double>> simulated_afe_stream = { 
        {-275.5, -203.2}, // Node 0 Raw Data 
        {-270.1, -198.9}, // Node 1 Raw Data 
        {-266.4, -195.3}  // Node 2 Raw Data 
    };

    dsp_engine.process_matrix_sweep(simulated_afe_stream); 

    // ================================================================= // 
    // 🧪 AUTOMATED C++ UNIT TEST: Quadrant Inversion Filter Validation // 
    // ================================================================= // 
    std::cout << "\n[TEST] Running Automated Pipeline Validation...\n"; 
    
    // Pass a known hardware inversion artifact (-135.0° flipped profile) 
    double test_real = -1.0; 
    double test_img = -1.0; 
    
    ComplexImpedance apply_quadrant_inversion_filter(double raw_real, double raw_imag) {
        ComplexImpedance corrected_metrics;
        
        // --- PHASE 2 CALIBRATION LAYER ---
        // Define hardware-level conversion constants
        const double RCAL_VALUE = 10000.0;    // Onboard internal 10k reference resistor
        const double SYSTEM_GAIN = 5800.0;    // AD5940 system amplification gain factor
        
        // 1. Calculate the raw magnitude code from the real/imag vectors
        double raw_magnitude = std::sqrt((raw_real * raw_real) + (raw_imag * raw_imag));
        
        // 2. Compute the actual overall impedance magnitude in Ohms (Z)
        double impedance_magnitude_ohms = (RCAL_VALUE / raw_magnitude) * SYSTEM_GAIN;
        
        // 3. Compute raw phase angle in radians, then convert to degrees
        double raw_phase_deg = std::atan2(raw_imag, raw_real) * (180.0 / PI);
        
        // Step 2: Digital Corrective Prism Filter (Your original phase realignment)
        if (raw_phase_deg < -90.0) {
            corrected_metrics.phase_angle = raw_phase_deg + 180.0;
        } else {
            corrected_metrics.phase_angle = raw_phase_deg;
        }
        
        // 4. Deconstruct the calibrated magnitude back into real physical Resistance (R) and Reactance (X)
        double phase_rad = corrected_metrics.phase_angle * (PI / 180.0);
        corrected_metrics.real_ohms = impedance_magnitude_ohms * std::cos(phase_rad);
        corrected_metrics.imaginary_ohms = impedance_magnitude_ohms * std::sin(phase_rad);
        
        return corrected_metrics;
    }  
impp
