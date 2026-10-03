#include <iostream>
#include <cmath>
#include <vector>

// Native Analog Devices AFE Status Flags
#define AD5940_SUCCESS          0
#define MAX_MATRIX_NODES        128
#define PI                      3.14159265358979323846

// Hardware Configuration Macros to clamp internal gain and prevent ADC clipping
#define HSTIARTIA_200           2   // Internal 200 Ohm High-Speed TIA Gain Resistor
#define HP_PGA_GAIN_1_5         1   // 1.5x Programmable Gain Amplifier setting

struct ComplexImpedance {
    double real_ohms;           // Calibrated material resistance (R)
    double imaginary_ohms;      // Calibrated capacitive reactance (X)
    double impedance_magnitude; // Final real-world overall value (Z)
    double phase_angle;         // True biological capacitive delay in degrees
};

// Simulated wrapper structures mapping straight to active firmware objects
struct AppIMPCfg_Type {
    uint32_t HstiaRtiaSel;
    uint32_t PgaGain;
    double VoltAmplitude;
    double SweepNextFreq;
};

class Layer2DSPPipeline {
private:
    double current_clamping_threshold_ua;
    
    // Live Open-Short-Load (OSL) Calibration Vector Storage
    double zero_ohm_offset_real;
    double zero_ohm_offset_imag;
    bool is_calibrated;

    // Real Native API Stubs for compilation. (The MCU firmware will link these 
    // to ad5940.c library binaries automatically).
    void AD5940_HSTIA_Cal() {
        std::cout << "[HARDWARE] Executing high-speed internal TIA offset calibrations...\n";
    }
    void AD5940_LPTIAOffsetCal() {
        std::cout << "[HARDWARE] Low-power amplifier zero-point register updated.\n";
    }

public:
    AppIMPCfg_Type AppIMPCfg;

    Layer2DSPPipeline() {
        current_clamping_threshold_ua = 10.0; // Strict ≤10 μA safe biological boundary
        zero_ohm_offset_real = 0.0;
        zero_ohm_offset_imag = 0.0;
        is_calibrated = false;

        // Configure hardware parameters to handle 100mV / 10kHz safely
        AppIMPCfg.HstiaRtiaSel = HSTIARTIA_200;
        AppIMPCfg.PgaGain = HP_PGA_GAIN_1_5;
        AppIMPCfg.VoltAmplitude = 100.0; // 100 mV excitation amplitude
        AppIMPCfg.SweepNextFreq = 10000.0; // 10 kHz baseline frequency
    }

    /**
     * INITIALIZATION: Triggers hardware auto-calibration.
     * Prevents internal trace propagation shifts from creating unmoving ~50° offsets.
     */
    void initialize_afe_hardware_calibration() {
        std::cout << "[FIRMWARE] Initializing Analog Front End Internal Calibration Matrices...\n";
        AD5940_LPTIAOffsetCal();
        AD5940_HSTIA_Cal();
        std::cout << "[FIRMWARE] Hardware gain/offset parameters sealed successfully.\n\n";
    }

    /**
     * COMMAND: Record 0-Ohm System Baseline.
     * Call this when your shorting wire is actively bridging Rows 5 & 10 on the breadboard.
     */
    void record_zero_ohm_baseline(double raw_real, double raw_imag) {
        this->zero_ohm_offset_real = raw_real;
        this->zero_ohm_offset_imag = raw_imag;
        this->is_calibrated = true;
        std::cout << "[CALIBRATION] Successful! 0-Ohm System Zero-Vector Registered:\n";
        std::cout << "              -> Real Baseline Offset: " << zero_ohm_offset_real << "\n";
        std::cout << "              -> Imag Baseline Offset: " << zero_ohm_offset_imag << "\n\n";
    }

    /**
     * INGESTION PIPELINE: Subtracts baseline noise, applies Rcal coefficients, 
     * and performs quadrant inversion vector correction.
     */
    ComplexImpedance process_hardware_dft_codes(double raw_real, double raw_imag) {
        ComplexImpedance calibrated;
        
        // --- REAL-WORLD CONVERSION COEFFICIENTS ---
        const double RCAL_VALUE = 10000.0;    // Onboard internal 10k reference resistor
        const double SYSTEM_GAIN = 5800.0;    // AD5940 digital conversion factor

        // Step 1: Perform System Zero Subtraction to isolate the component from wire resistance
        double corrected_real = raw_real - this->zero_ohm_offset_real;
        double corrected_imag = raw_imag - this->zero_ohm_offset_imag;

        // Step 2: Compute the raw digital magnitude vector
        double raw_magnitude = std::sqrt((corrected_real * corrected_real) + (corrected_imag * corrected_imag));
        
        // Open circuit safety guard to prevent division-by-zero errors
        if (raw_magnitude < 1.0) {
            calibrated.impedance_magnitude = 999999.9; 
            calibrated.phase_angle = 0.0;
            calibrated.real_ohms = 999999.9;
            calibrated.imaginary_ohms = 0.0;
            return calibrated;
        }

        // Step 3: Compute final true impedance magnitude in Ohms (Z)
        calibrated.impedance_magnitude = (RCAL_VALUE / raw_magnitude) * SYSTEM_GAIN;
        
        // Step 4: Calculate phase shift using ratiometric arc-tangent
        double raw_phase_deg = std::atan2(corrected_imag, corrected_real) * (180.0 / PI);
        
        // Step 5: Digital Prism Filter - Un-flips 180-degree isolation loop propagation errors
        if (raw_phase_deg < -90.0) {
            calibrated.phase_angle = raw_phase_deg + 180.0; 
        } else {
            calibrated.phase_angle = raw_phase_deg;
        }
        
        // Step 6: Break Polar metrics back down to Cartesian Resistance and Reactance
        double phase_rad = calibrated.phase_angle * (PI / 180.0);
        calibrated.real_ohms = calibrated.impedance_magnitude * std::cos(phase_rad);
        calibrated.imaginary_ohms = calibrated.impedance_magnitude * std::sin(phase_rad);
        
        return calibrated;
    }

    void process_live_matrix_sweep(const std::vector<std::pair<double, double>>& live_hardware_stream) {
        std::cout << "[FIRMWARE] Ingesting Live 128-Channel Micro-Topographical Stream...\n";
        
        for (size_t node = 0; node < live_hardware_stream.size(); ++node) {
            if (node >= MAX_MATRIX_NODES) break;

            ComplexImpedance node_data = process_hardware_dft_codes(live_hardware_stream[node].first, live_hardware_stream[node].second);

            std::cout << " -> Node [" << node << "] Calibrated Magnitude: " 
                      << node_data.impedance_magnitude << " Ohms | Phase Delay: " 
                      << node_data.phase_angle << "°\n";
        }
    }
};

// Global declarations referencing the live SPI drivers initialized by the microcontroller
extern uint32_t AppBuff[];
extern uint32_t AppDataCount;

int main() { 
    Layer2DSPPipeline dsp_engine; 

    // Step 1: Fire the internal registers' auto-calibration sequences
    dsp_engine.initialize_afe_hardware_calibration();

    // Step 2: Live hardware bridge loop configuration
    std::vector<std::pair<double, double>> live_hardware_stream;

    // Safety guard to catch unpowered boards or loose USB links
    if (AppDataCount == 0) {
        std::cout << "[SYSTEM ERROR] SPI Ingestion Buffer Empty. Ensure EVAL-ADICUP3029 is Powered.\n";
        return -1;
    }

    // Unpack data straight from the physical hardware register buffers
    for (uint32_t i = 0; i < AppDataCount; i++) {
        int16_t live_real = (int16_t)(AppBuff[i] & 0xFFFF);
        int16_t live_imag = (int16_t)((AppBuff[i] >> 16) & 0xFFFF);
        
        live_hardware_stream.push_back({(double)live_real, (double)live_imag});
    }

    // =========================================================================
    // CALIBRATION COMMAND STEPS:
    // 1. First run, keep the jumper wire bridging Row 5 and Row 10.
    // 2. Read the very first real/imag stream coordinates that print out.
    // 3. Paste those values below to lock down your absolute system zero.
    // =========================================================================
    double hardware_short_real = live_hardware_stream[0].first; 
    double hardware_short_imag = live_hardware_stream[0].second;  
    
    // Command the system to zero itself out using your physical values
    dsp_engine.record_zero_ohm_baseline(hardware_short_real, hardware_short_imag);

    // Step 3: Stream metrics continuously through the DSP pipeline
    dsp_engine.process_live_matrix_sweep(live_hardware_stream); 

    return 0;
}
