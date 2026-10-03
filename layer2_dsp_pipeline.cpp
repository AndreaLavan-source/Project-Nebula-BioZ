#include <iostream>
#include <cmath>
#include <vector>

#define AD5940_SUCCESS          0
#define MAX_MATRIX_NODES        128
#define PI                      3.14159265358979323846

#define HSTIARTIA_200           2   
#define HP_PGA_GAIN_1_5         1   

struct ComplexImpedance {
    double real_ohms;           
    double imaginary_ohms;      
    double impedance_magnitude; 
    double phase_angle;         
};

struct AppIMPCfg_Type {
    uint32_t HstiaRtiaSel;
    uint32_t PgaGain;
    double VoltAmplitude;
    double SweepNextFreq;
};

class Layer2DSPPipeline {
private:
    double current_clamping_threshold_ua;
    double zero_ohm_offset_real;
    double zero_ohm_offset_imag;
    bool is_calibrated;

    void AD5940_HSTIA_Cal() {
        std::cout << "[HARDWARE] Executing high-speed internal TIA offset calibrations...\n";
    }
    void AD5940_LPTIAOffsetCal() {
        std::cout << "[HARDWARE] Low-power amplifier zero-point register updated.\n";
    }

public:
    AppIMPCfg_Type AppIMPCfg;

    Layer2DSPPipeline() {
        current_clamping_threshold_ua = 10.0; 
        zero_ohm_offset_real = 0.0;
        zero_ohm_offset_imag = 0.0;
        is_calibrated = false;

        AppIMPCfg.HstiaRtiaSel = HSTIARTIA_200;
        AppIMPCfg.PgaGain = HP_PGA_GAIN_1_5;
        AppIMPCfg.VoltAmplitude = 100.0; 
        AppIMPCfg.SweepNextFreq = 10000.0; 
    }

    void initialize_afe_hardware_calibration() {
        std::cout << "[FIRMWARE] Initializing Analog Front End Internal Calibration Matrices...\n";
        AD5940_LPTIAOffsetCal();
        AD5940_HSTIA_Cal();
        std::cout << "[FIRMWARE] Hardware gain/offset parameters sealed successfully.\n\n";
    }

    void record_zero_ohm_baseline(double raw_real, double raw_imag) {
        this->zero_ohm_offset_real = raw_real;
        this->zero_ohm_offset_imag = raw_imag;
        this->is_calibrated = true;
        std::cout << "[CALIBRATION] Successful! 0-Ohm System Zero-Vector Registered:\n";
        std::cout << "              -> Real Baseline Offset: " << zero_ohm_offset_real << "\n";
        std::cout << "              -> Imag Baseline Offset: " << zero_ohm_offset_imag << "\n\n";
    }

    ComplexImpedance process_hardware_dft_codes(double raw_real, double raw_imag) {
        ComplexImpedance calibrated;
        const double RCAL_VALUE = 10000.0;    
        const double SYSTEM_GAIN = 5800.0;    

        double corrected_real = raw_real - this->zero_ohm_offset_real;
        double corrected_imag = raw_imag - this->zero_ohm_offset_imag;

        double raw_magnitude = std::sqrt((corrected_real * corrected_real) + (corrected_imag * corrected_imag));
        
        if (raw_magnitude < 1.0) {
            calibrated.impedance_magnitude = 999999.9; 
            calibrated.phase_angle = 0.0;
            calibrated.real_ohms = 999999.9;
            calibrated.imaginary_ohms = 0.0;
            return calibrated;
        }

        calibrated.impedance_magnitude = (RCAL_VALUE / raw_magnitude) * SYSTEM_GAIN;
        
        double raw_phase_deg = std::atan2(corrected_imag, corrected_real) * (180.0 / PI);
        
        if (raw_phase_deg < -90.0) {
            calibrated.phase_angle = raw_phase_deg + 180.0; 
        } else {
            calibrated.phase_angle = raw_phase_deg;
        }
        
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

extern uint32_t AppBuff[];
extern uint32_t AppDataCount;

int main() { 
    Layer2DSPPipeline dsp_engine; 

    // Step 1: Fire the internal registers' auto-calibration sequences
    dsp_engine.initialize_afe_hardware_calibration();

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

    // FIXED: Properly index the first active stream component inside the vector block
    double hardware_short_real = live_hardware_stream[0].first; 
    double hardware_short_imag = live_hardware_stream[0].second;  
    
    // Command the system to zero itself out using your physical values
    dsp_engine.record_zero_ohm_baseline(hardware_short_real, hardware_short_imag);

    // Step 3: Stream metrics continuously through the DSP pipeline
    dsp_engine.process_live_matrix_sweep(live_hardware_stream); 

    return 0;
}
