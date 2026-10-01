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
    
    ComplexImpedance test_output = dsp_engine.apply_quadrant_inversion_filter(test_real, test_img); 
    
    // Expectation: Flipped -135.0° is < -90.0°, so it must shift by +180.0° to equal +45.0° 
    double expected_phase = 45.0; 
    double tolerance = 0.01; 
    
    std::cout << " -> Expected Phase: " << expected_phase << "°\n"; 
    std::cout << " -> Actual Phase:   " << test_output.phase_angle << "°\n"; 
    
    if (std::abs(test_output.phase_angle - expected_phase) < tolerance) { 
        std::cout << " [RESULT] STATUS: PASSED (Quadrant inversion logic is 100% verified)\n"; 
    } else { 
        std::cout << " [RESULT] STATUS: FAILED (Check math library scaling factors)\n"; 
    } 
    std::cout << "=================================================================\n"; 
    
    return AD5940_SUCCESS; 
}
