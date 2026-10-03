# 📊 Project Nebula: Hardware Verification & Calibration Logs

This document tracks empirical hardware validation milestones for the 128-Node Symmetrical AC Matrix using the Analog Devices EVAL-AD5940BIOZ.

## 🛠️ Run 001: Baseline Component Bridge Test (PASSED)
* **Date:** October 2, 2026
* **Operator:** Andrea Lavan
* **Test Environment:** Benchtop verification via SensorPal GUI
* **Hardware State:** 4-Wire Cross-Row Dual-Inline Header (CE0, AIN3, AIN2, AIN1)
* **Target Load:** Isolated Parallel Resistor-Capacitor (RC) Network (Breadboard Rows 5 & 10)
* **Excitation Parameters:** 10 kHz Frequency Sweep | 100 mV Amplitude | 1 Sample Step

### Empirical Metrics
* **Raw Reported Magnitude:** 1,136.959 Ω
* **Raw DFT Phase Angle:** -193.685°
* **Corrected Phase Angle:** **-13.685°** *(180° math library inversion flip corrected)*
* **System State:** Stable closed loop. No clipping, ADC saturation, or open-circuit floating faults detected.

---

## 📋 Future Calibration Run Ledger (128-Node Scaling)

Use this template to record systematic multi-channel data points as the sequence switching engine rolls out:

| Run ID | Active Node Group | Target Tissue / Load | Peak Magnitude (Ω) | Corrected Phase Angle (°) | Pass/Fail |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **002** | Concentric Circle 1 (Nodes 0-15) | Hand Matrix (Dry) | *Pending Phase 2* | *Pending Phase 2* | *TBD* |
| **003** | Concentric Circle 2 (Nodes 16-31) | Hand Matrix (Dry) | *Pending Phase 2* | *Pending Phase 2* | *TBD* |
