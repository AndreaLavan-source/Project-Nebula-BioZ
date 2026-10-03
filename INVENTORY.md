# 📦 Project Nebula: Phase 2 Hardware Inventory & Bill of Materials

This ledger tracks the active physical components, analog integrated circuits (ICs), and routing hardware allocated for scaling the 128-node multi-channel biosensing matrix.

## 🔬 Core Validation Hardware (On Hand)
* **Base Front-End Platform:** 1x Analog Devices EVAL-AD5940BIOZ Front-End Shield
* **Microcontroller Unit (MCU):** 1x Analog Devices EVAL-ADICUP3029 Cortex-M3 Board
* **Calibration Loop Network:** Multi-pack low-tolerance Metal Film Resistors (330 Ω to 10 kΩ) & Ceramic Capacitors
* **Prototyping Framework:** 1x Standard Solderless Breadboard (830 Tie-Points) with Symmetrical Male-to-Male Jumper Wires

---

## 🛒 Phase 2 Procurement List (Required for Matrix Scaling)

These components expand our validated single-channel front-end into an automated sequential coordinate switching matrix:

| Component Type | Part Number / Specification | Quantity | Purpose in Architecture | Status |
| :--- | :--- | :--- | :--- | :--- |
| **Analog Multiplexer IC** | **CD74HC4067** (16-Channel CMOS) | **8** | Digitally cascades a single AD5940 analog pin to handle 128 discrete spatial coordinates. | *Procurement Pending* |
| **Logic Level Shifter** | **Bi-Directional 4-Channel (3.3V to 5V)** | **2** | Safely translates the 3.3V logic signals from the MCU to 5V rails required by the switching matrix. | *Procurement Pending* |
| **Prototyping Expansion** | **Solderless Breadboard (830 Tie-Points)** | **1** | Expands physical breadboard space to wire the 8 multiplexer arrays inline. | *Procurement Pending* |
| **Dupont Cabling Packs** | **Male-to-Male & Male-to-Female (20cm)** | **1 Pack** | Provides the discrete control channels needed to address the expanded matrix rows. | *Procurement Pending* |

---

## 🗺️ Pin Interconnection Architecture (Target Layout)
* **Digital Address Controls (MCU to Mux):** Microcontroller GPIO lines drive binary routing configurations to sequentially cycle matrix coordinates.
* **Analog Measurement Lines (Mux to AD5940):** Multiplexer common output channels map directly to the validated **CE0, AIN3, AIN2, AIN1** cross-row cross-point layout.
