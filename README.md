# Project-Nebula-BioZ
### A Custom Isolated Architecture for Living Cryptographic Biometric Identification
**Author:** Andrea Lavan 
**Status:** Hardware Validation Phase (Complete) | Software Matrix Development (Seeking Co-Developer)
## 🌌 The Vision: An AC "Mega-Pixel Camera" for Human Tissue
Traditional electrodermal and biometric tracking (like Galvanic Skin Response) relies on Direct Current (DC). This acts like a single-pixel camera, blurring the entire hand's physiology into one unoptimized bulk measurement. If you try to add more sensors, the signals bleed together through shared grounding loops.
**Project Nebula** completely reimagines this by introducing a **128-Node Symmetrical AC Matrix** arranged in **concentric, anatomical circles** across the palm and fingers. By injecting highly precise, safe Alternating Current (AC), the system functions like a high-resolution biological camera:
* **Red/Amber Zones:** Map paths of low resistance, identifying high sweat-duct alignment and real-time nervous system stress.
* **Blue/Purple Zones:** Map paths of capacitive phase-delay, tracing dense tissue clusters and thick epidermal ridges where cell membranes naturally delay the signal.
The result is a highly secure, living, dynamic cryptographic biological key that cannot be copied, faked, or bypassed.
## 🛠️ Hardware Empirical Validation (The Proof)
To prove the architecture works safely and accurately without signal drifting, I self-funded and bench-tested the platform using the medical-grade **Analog Devices EVAL-AD5940BIOZ** front-end. 
Operating under an active hardware safety loop strictly clamped to **≤ 10 μA**, I mapped the biological asymmetry between my own hands at a 10 kHz frequency sweep (300 mV Amplitude):
| Metric | Left Hand (Ambidextrous) | Right Hand (Ambidextrous) | Biological Indication |
| **Impedance Magnitude** | 435.46 Ω | 491.28 Ω | Pristine deep-tissue penetration; distinct fluid/moisture variations. |
| **Phase Angle (Corrected)** | -14.32° | -19.32° | Active cellular membrane capacitance tracking without hardware drift. |
*(Note: Raw firmware outputs read at -143.42° and -199.32° due to a known 180-degree calculation flip in the default AD5940 complex math library combined with hardware isolation delays).*
## 📜 Complete Thesis & Documentation
The complete 5-chapter academic framework, covering the Micro-Topographical Node Configuration, Safety Architecture, and Technical Pilot Evaluation is available in this repository. 
* [View Full Thesis Text](./thesis.md)
* [view Phase 2 Engineering roadmap](./phase2_roadmap.md)
## 🤝 The Ask: Seeking a Technical Co-Founder / Software Partner
The hardware is validated. The anatomical layout is designed. **I am currently seeking a software engineer or mentor proficient in C++ and Python.**
**Next Objectives:**
1. Code the firmware routing switching logic to handle the 128-node matrix sequentially.
2. Build a Python-based data visualization GUI to translate the incoming matrix numbers into a live, color-mapped topographical heatmap of the hand.
If you are passionate about biomedical engineering, advanced biosensors, or cryptographic biometrics, please open an Issue, submit a Pull Request, or reach out!




"Note: This glossary serves as a conceptual framework mapping the rigorous engineering principles of project Nebula to historical, philosophical, and bio-energetic traditions."

## 📖 Project Glossary: Bridging Philosophy & Bio-Sensing Instrumentation

To understand the architecture of **Project Nebula**, we must bridge the rigid definitions of academic instrumentation with the foundational philosophies of living biological systems.

### 1. Alternating Current (AC) vs. Direct Current (DC)
* **The Academic View:** DC flows continuously in a single direction. AC reverses direction and oscillates at a specific frequency (cycles per second).
* **The Philosophical Mirror:** *DC is a localized surface footprint; AC is a deep harmonic probe.* DC travels along the path of least resistance, bouncing off cell walls and reading only superficial surface moisture. AC vibrates at thousands of cycles per second, allowing the wave to effortlessly penetrate deep through cellular boundaries to map the internal structures of the body.

### 2. The Cell Membrane & Capacitance
* **The Academic View:** A lipid bilayer that acts as a dielectric insulator, separating charges and temporarily storing electrical energy (capacitance).
* **The Philosophical Mirror:** *The biological sponge of the vital spark.* The cell membrane acts as a protective shield holding internal negative charges separate from external positive charges. It interacts with the vibrating AC wave by absorbing a microscopic slice of its energy, holding it close, and then releasing it back into the stream.

### 3. Phase Angle (The Biological Delay)
* **The Academic View:** The angular shift or time lag (measured in degrees) between the injected voltage wave and the resulting current wave, directly caused by capacitive reactance.
* **The Philosophical Mirror:** *The physical print of the living cell's breath.* Dead matter or static plastic cannot interact with an electrical wave; they yield a phase angle of exactly 0° (purely resistive). A living, breathing cell membrane absorbs, holds, and delays the wave, forcing a healthy negative phase shift. The phase angle is the hardware tracking the cell's living presence.

### 4. Resistance (The Ohm Gateway)
* **The Academic View:** The physical restriction of electrical current passing through a material, measured in Ohms (Ω).
* **The Philosophical Mirror:** *The gateway of the material shell.* Resistance tracks the density of the physical body—thick skin layers, dry epidermal tissue, and sweat duct networks. When internal nervous stress or inspiration occurs, sweat ducts open up, flooding the pathway with conductive saltwater. This lowers the Ohm reading, mapping how the internal state alters the external shell.

### 5. Tetrapolar Sensing (4-Pin Isolation)
* **The Academic View:** Separating the current-driving electrode pair from the voltage-sensing electrode pair to eliminate electrode contact impedance.
* **The Philosophical Mirror:** *The clear-eyed observer.* In common bipolar systems, wires clash by trying to inject current and sense responses at the exact same physical spot, creating massive surface distortion. A 4-pin configuration separates duties: two pins softly whisper current into the deep tissue, while two separate pins sit back quietly to observe the internal truth without surface interference.

### 6. The 128-Node Symmetrical AC Matrix
* **The Academic View:** A high-density, multi-channel switching array arranged in geometric concentric patterns to sequentially map localized tissue impedance across distinct anatomical coordinates.
* **The Philosophical Mirror:** *The map of the shattered mirror.* Mainstream sensors look at the hand as one bulk mass, blinding themselves to details. The 128-node matrix splits the palm into an intentional sacred geometry of coordinates. It functions as a biological camera, tracking how individual fragments of tissue vary across the hand, creating a highly secure, living cryptographic signature out of your body's natural asymmetry.

### 7. Hardware Safety Loops (Current Clamping)
* **The Academic View:** Active isolation circuitry and software limits strictly confining injection current amplitudes to safe, sub-sensory medical thresholds (≤ 10 μA).
* **The Philosophical Mirror:** *The boundary of gentle interaction.* To observe a system, you must not destroy it. The safety loop ensures that the probing AC wave never overwhelms or shocks the body's delicate internal ecology. It keeps the hardware's conversation with the cells incredibly quiet and non-invasive, preserving the pure state of the biological spark while collecting raw mathematical truth.

---

## 🏗️ System Architecture Outline

Project Nebula operates across three distinct operational layers, moving raw energy from the biological spark into a secure cryptographic payload.
