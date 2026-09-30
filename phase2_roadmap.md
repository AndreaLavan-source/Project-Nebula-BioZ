# Project Nebula: Phase 2 Engineering Roadmap

## Iterative Scaling, Crosstalk Mitigation, and Tetrapolar Parameterization

**Status:** Planning & Active Architecture Redesign  
**Derived From:** Open-Source Peer Review ([r/BiomedicalEngineering](https://reddit.com) Validation)

---

## 🎯 Strategic Pivot: Scaling to a 16/32-Channel Proof-of-Concept

To ensure maximum data integrity and prevent encoding errors into complex firmware switching logic, Project Nebula is pivoting from its initial 128-node conceptual deployment down to an **iterative 16 or 32-channel Proof-of-Concept (PoC)**. This allows for modular testing, stage-by-stage bug verification, and rigorous crosstalk characterization before scaling to full palmar topography.

---

## Core Engineering Redesigns

### 1. Tetrapolar (4-Pin) Measurement Configuration
* **The Problem:** The initial bipolar/3-wire setup was heavily confounded by skin-surface contact impedance and interference at the electrode-tissue interface.
* **The Solution:** Phase 2 implements a formal **tetrapolar array configuration**. For every channel measurement, two dedicated pins will drive the AC excitation current, while two entirely separate pins will sense the resulting voltage drop. This ensures contact impedance drops completely out of the sensed voltage, unlocking pristine data from deep sub-surface tissue layers.

### 2. Micro-Topographical Hardware Upgrades
* **Sensor Form Factor:** Phasing out sharp, high-pressure sub-millimeter pogo pin tips to prevent uneven localized pressure gradients (1 to 2.5 MPa). The stabilizer interface will transition to **flat metal pads on a flexible PCB (Flex-PCB)** to match natural anatomical curves gently.
* **Sweat Film & Lateral Crosstalk Mitigation:** To eliminate lateral electrical conduction through the stratum corneum and sweat films, a thin **silicone isolation barrier** will be layered over the Flex-PCB, with micro-apertures punched directly over the active flat sensor pads.

### 3. Safety & Calibration Protocols
* **DC Blocking Enforcements:** Incorporating physical, hardware-level inline DC-blocking capacitors on all driving leads to ensure absolute human safety during benchtop live evaluations.
* **Resistor-Capacitor Phantom Testing:** Halting all direct human-subject evaluation until the hardware is validated against a static, known network model. Calibration benchmarks require achieving **< 1% Magnitude Error** and **< 0.5° Phase Angle Error** per channel across a full multi-frequency sweep.

---

## Software & Firmware Directives

### Priority 1: The Stage-1 Data Logger
Before writing the final C++ sequential matrix switching code, the immediate software objective is developing a basic, robust **Data Logger**. This tool will focus solely on capturing and printing stable, raw serial output (Magnitude and Corrected Phase) from a known system, ensuring software verification happens in clean, predictable stages.

---

## 🚀 How to Join the Phase 2 Sprint

We are actively seeking collaborators with experience in:

* **Printed Circuit Board Design (Altium/KiCad):** Specifically dealing with guard traces, analog multiplexers, and Flex-PCBs.
* **Embedded Software:** Setting up raw data logging and handling multi-channel serial streams.

If you are interested in reviewing our schematics or helping build the Phase 2 test fixture, please **open an Issue** or comment on our main thread!
