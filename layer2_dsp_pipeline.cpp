int main() { 
    Layer2DSPPipeline dsp_engine; 

    // Step 1: Fire the internal registers' auto-calibration sequences
    dsp_engine.initialize_afe_hardware_calibration();

    // --- HARDWARE BUFFER REFRESH LOOP ---
    // Explicitly command the physical hardware sequencer to flush stale registers
    extern void AD5940_FIFOCmd(uint32_t FifoSel, BoolFlag bEnable);
    extern void AD5940_INTCCmd(uint32_t IntSel, BoolFlag bEnable);
    
    // Clear and reset the physical FIFO buffer to handle the live sweep
    AD5940_FIFOCmd(0, bFALSE); // Turn off FIFO temporarily to clear registers
    AD5940_FIFOCmd(0, bTRUE);  // Turn back on to capture clean physical signals

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

    // Capture the true live stream parameters from your breadboard jumper link
    double hardware_short_real = live_hardware_stream.first; 
double hardware_short_imag = live_hardware_stream.second; 
    
    // Command the system to zero itself out using your physical values
    dsp_engine.record_zero_ohm_baseline(hardware_short_real, hardware_short_imag);

    // Step 3: Stream metrics continuously through the DSP pipeline
    dsp_engine.process_live_matrix_sweep(live_hardware_stream); 

    return 0;
}
