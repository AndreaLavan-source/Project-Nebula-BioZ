# Project-Nebula-BioZ
> ⚠️ **Status:** Open Source (AGPL-3.0) | **Intellectual Property:** U.S. Patent Pending
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

### 1. Isolated Component Bridge Validation (System Baseline)
Prior to biological evaluation, the AFE was cross-verified against a known 4-wire (tetrapolar) calibration bridge built via an isolated parallel RC network at a 10 kHz frequency sweep (100 mV Amplitude) to confirm the baseline integrity of the physical trace tracks and SensorPal configuration registers:
* **Raw Magnitude Vector Output:** 1,136.959 Ω
* **Raw DFT Phase Angle:** -193.685° 
* **Corrected Phase Profile:** **-13.685°** *(180° math library inversion flip corrected)*
* **Status:** **Prinstine Loop Integrity Established.** No open circuits, hardware drift, or unscaled saturation artifacts detected.

### 2. Live Biological Asymmetry Baseline
Operating under an active hardware safety loop strictly clamped to **≤ 10 μA**, I mapped the biological asymmetry between my own hands at a 10 kHz frequency sweep (300 mV Amplitude):

| Metric | Left Hand (Ambidextrous) | Right Hand (Ambidextrous) | Biological Indication |
| :--- | :--- | :--- | :--- |
| **Impedance Magnitude** | 435.46 Ω | 491.28 Ω | Pristine deep-tissue penetration; distinct fluid/moisture variations. |
| **Phase Angle (Corrected)** | -14.32° | -19.32° | Active cellular membrane capacitance tracking without hardware drift. |

*(Note: Raw firmware outputs read at -143.42° and -199.32° on human skin due to a known 180-degree calculation flip in the default AD5940 complex math library combined with hardware isolation delays, mirroring the -193.685° shift observed in the hardware component bridge test).*

## 📜 Complete Thesis & Documentation
The complete 5-chapter academic framework, covering the Micro-Topographical Node Configuration, Safety Architecture, and Technical Pilot Evaluation is available in this repository. 
* [View Full Thesis Text](./thesis.md)
* [view Phase 2 Engineering roadmap](./phase2_roadmap.md)
* 📖 [View the Philosophy & Bio-Sensing Theory Guide](./THEORY.md)
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
* **The Philosophical Mirror:** *The biological sponge of the vital spark.* The cell membrane acts as a protective shield holding internal negative charges seperate from external positive charges. It interacts with the vibrating AC wave by absorbing a microscopic slice of its energy, holding it close, and then releasing it back into the stream.

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

### 8. Enclosed Triangles (The Funnels of Amplification)

*   **The Academic View:** A closed triangular pattern functions as a geometric macro-funnel, bounding a specific micro-topographical region of the palm while narrowing down to a sharp, isolated apex. As the high-frequency AC sweep propagates through the wide base of this triangular envelope toward its restricted tip, the cross-sectional area of the tissue pathways rapidly decreases. This geometric constriction forces a sharp, predictable rise in localized impedance (\(\Omega\)), creating a distinct signal bottleneck that marks the exact spatial coordinate on the data map.
*   **The Philosophical Mirror:** *The biological megaphone.* Just as an acoustic horn concentrates scattered sound waves into a directed, high-energy beam, this architectural triangle captures broad epidermal current paths and compresses them into a singular, highly amplified coordinate point—turning subtle tissue variations into unmistakable data landmarks.

### 9. Sideways Diamonds with Internal "X" Marks

*   **The Academic View:** A diamond-shaped epidermal formation acts as a perimeter isolation shield, cross-secting internal ridge patterns and mechanically insulating the interior core tissue from surrounding directional skin shifts. The outer perimeter lines of this diamond pattern structurally isolate the inner tissue core, blocking lateral current leakage. When paired with an internal intersecting ridge pattern at its center, it forms a multi-stage reactive electrical filter yielding a highly consistent, repeatable capacitive phase delay (\(\theta\)).
*   **The Philosophical Mirror:** *The sovereign sanctuary of the signal.* This layout acts as an electromagnetic fortress, casting a geometric shield around its inner core to repel skin movement artifacts and external noise, ensuring the underlying cryptographic truth remains perfectly preserved and unaltered by physical interaction.

### 10. Macro-M Linear Networks (The Primary Tri-Line Architectural Blueprint)

*   *   **The Academic View:** The dominant macro-configuration on the human hand manifests as a continuous, multi-nodal line network tracking a geometric "M" topology. This framework is formed by the spatial intersection of three primary high-conductivity epidermal traces—the thenar crease, proximal transverse crease, and distal transverse crease—interlinked by a vertical central bridging trace. This structural matrix serves as the global baseline coordinate system.
*   **The Philosophical Mirror:** *The universal chassis of human instrumentation.* While micro-anomalies provide unique cryptographic depth, the Macro-M network represents the shared baseline architecture of human tissue. It is the primary map grid that allows the instrumentation to immediately recognize, orient, and ground itself upon the biological surface.

### 11. Synchronized Dual-Palm Configurations (The Mirror-Symmetric Double M Network)

*   **The Academic View:** A rare structural manifestation where identical Macro-M Linear Networks are perfectly mirrored and synchronized across both the left (non-dominant) and right (dominant) epidermal planes. When queried simultaneously via a dual-differential routing path, this configuration allows for real-time common-mode noise rejection. The system utilizes the non-dominant palm as a stable structural blueprint to dynamically cancel out individual skin-hydration variables, temperature fluctuations, and systemic placement skews on the active hand.
*   **The Philosophical Mirror:** *The biological tuning fork.* When both hands share a perfectly synchronized macro-blueprint, they create an ideal harmonic resonance. By measuring the two palms against one another, the system can instantly filter away the superficial noise of the outside world, isolating the pure, uncorrupted cryptographic key generated by the body's internal symmetry.

---

## System Architecture Specs & Technical Data-Flow

### Multi-Frequency Sensor Specifications

To capture both deep macro-structural paths and high-resolution micro-topographical surface features without signal bleeding, the front-end architecture utilizes a multi-band, frequency-agile AC sweep matrix:

*   **Low-Frequency Band (5 kHz - 20 kHz) — Deep Dermal Sub-Layer Probing:** Optimized for high depth penetration to bypass superficial skin dryness or calluses, establishing the deep anatomical baseline roots of the Macro-M network.
*   **Mid-Frequency Band (20 kHz - 80 kHz) — Network Intersection & Bridge Tracking:** Specially balanced to capture the central bridging traces and multi-nodal junctions where horizontal and vertical lines lock together.
*   **High-Frequency Band (80 MHz - 200 MHz) — Micro-Topographical Surface Scanning:** Deployed during targeted micro-sweeps to map sharp localized impedance bottlenecks (Triangles) and capacitive phase delays (Diamonds) within superficial epidermal ridges.


### Structural ASCII Data-Flow Matrix

```text
=========================================================================================
                           DUAL-PALM SYNCHRONOUS AC SCAN INITIALIZATION
=========================================================================================
                                        |
                                        v
                 [ MULTI-FREQUENCY MULTI-BAND AC SWEEP: 10 kHz - 5 MHz ]
                                        |
                 +----------------------+----------------------+

                 |                                             |
                 v                                             v
    [ LEFT PALM IMPEDANCE PROFILE ]               [ RIGHT PALM IMPEDANCE PROFILE ]
    (Baseline Internal Blueprint)                 (Active Dynamic Surface Plane)

                 |                                             |
                 +----------------------+----------------------+
                                        |
                                        v
                    [ ISOLATE MACRO-M LINEAR NETWORK GEOMETRY ]
          (Extract Foundation Framework: Thenar, Transverse, & Bridge Lines)
                                        |
                                        v
                [ CROSS-HAND MIRROR DIFFERENTIAL VALIDATION FILTER ]
                                        |
               +------------------------+------------------------+

               |                                                 |
      [Mismatched Grid]                                   [Validated Match]

               |                                                 |
               v                                                 v
  [ SYSTEM ERROR / CALIBRATE ]                      [ NORMALIZE COORDINATE MATRIX ]
  (Signal Noise / Misalignment)                     (Lock Anchor Coordinates X,Y,Z)
                                                                 |
                                                                 v
                                                    [ SUB-REGIONAL MICRO-ISOLATION ]
                                                                 |
                                       +-------------------------+-------------------------+

                                       |                                                   |
                                       v                                                   v
                         [ MICRO-TOPOGRAPHY PATHWAY A ]                      [ MICRO-TOPOGRAPHY PATHWAY B ]
                         (Enclosed Triangular Funnels)                       (Sideways Diamonds with Internal 'X')

                                       |                                                   |
                                       v                                                   v
                         [ MEASURE IMPEDANCE BOTTLENECK ]                    [ MEASURE CAPACITIVE PHASE DELAY ]
                         (Geometric Micro-Constriction)                      (Perimeter Shield Core Isolation)
```



## 🎨 System Mapping: High-Resolution Biological Mapping

When **Project Nebula** processes the multi-channel AC data sweeps, it renders a high-resolution localized electrodermal map. The visualization splits the body's physiological output into distinct structural and autonomic zones:

### 🔴 Red / Amber Zones (The Autonomic Response Profile)
* **The Data:** Maps localized pathways of low electrical resistance and high conductance.
* **The Biology:** Identifies high sweat-duct alignment, active sympathetic nervous system (SNS) firing, and real-time electrodermal arousal spikes.
* **The System Philosophy:** *The dynamic signature of somatic activation.* The physical body is not a static electrical load; it is driven by continuous, real-time neural regulation. The Red/Amber zones capture the volatile shifts of this intrinsic systemic activity as it ripples through the physical framework, mapping how the nervous system dynamically adapts to internal state changes and external stimuli.

### 🔵 Blue / Purple Zones (The Cellular Matrix Anchor)
* **The Data:** Maps pathways of high capacitive phase-delay and capacitive reactance.
* **The Biology:** Traces dense cellular tissue clusters, structural layers of muscle, and thick epidermal ridges where healthy, intact cell membranes naturally delay the AC signal.
* **The System Philosophy:** *The stabilizing architecture of localized anatomical form.* Electrodermal energy without structural containment cannot be localized. The Blue/Purple zones map the protective, geometric lipid bilayers that anchor cellular integrity. The cell membrane acts as a vital electrical boundary, stabilizing potentials to provide structural resolution and serving as a highly optimized matrix for tracking localized tissue health
---

## 🏗️ System Architecture Outline

### 🏢 LAYER 1: THE PHYSICIAL RESISTANCE & EXCITATION INTERFACE (Somatic & Hardware Layer)
Layer 1 handles the raw, physical boundary where the instrumentation meets the human body. It is responsible for safe signal injection, isolated routing through the concentric node array, and high-precision analog signal conditioning. 

```text
+-------------------------------------------------------------+

|               BIOLOGICAL TEST LOAD (The Hand)               |
+-------------------------------------------------------------+
                              │
                              ▼ (Current Injection: I+ / I-)
                              ▲ (Voltage Sense: V+ / V-)
+-------------------------------------------------------------+

| 1.1 TETRAPOLAR ELECTRODE MATRIX                             |
|     (128 Concentric Switching Nodes)                        |
+-------------------------------------------------------------+
                              │
                              ▼ Dual Differential Pathways
+-------------------------------------------------------------+

| 1.2 HARDWARE ISOLATION & PASSIVE AMBIENT FILTERS            |
+-------------------------------------------------------------+
                              │
                              ▼ Isolated AC Waveforms
+-------------------------------------------------------------+

| 1.3 ANALOG FRONT END (AFE) ARCHITECTURE (EVAL-AD5940BIOZ)   |
|     - Waveform Generator (50 kHz - 100 kHz Sinusoid)        |
|     - Active Hardware Current-Limiting Circuit (≤ 10 µA)    |
|     - High-Speed Transimpedance Amplifier (TIA)             |
|     - Concurrent DFT Phase Engine                           |
+-------------------------------------------------------------+
                              │
                              ▼ Digitized Complex Impedance Data
                                (Real / Imaginary / Phase)

             [ To Layer 2: Firmware & DSP Pipeline ]
```

#### 1.1 The Tetrapolar Electrode Matrix (The Concentric Arrays)
* **The Academic Blueprint:** Utilizing a customized multi-channel multiplexing network, the system sequentially routes differential current and voltage paths across 128 symmetrical coordinates mapped to localized tissue zones. By isolating the injection pair (I+, I-) from the sensing pair (V+, V-), contact impedance errors from dry or high-resistance epidermal layers are completely eliminated.
* **The System Philosophy:** *The localized sensory gateway.* This layer does not force an electrical response from the body; it non-invasively interrogates the tissue interface. By breaking the hand into 128 micro-coordinates, it bypasses the uniform surface artifact of the outer skin to observe the unique, asymmetrical fluctuations occurring within the deep tissue layers.

#### 1.2 Active Safety Loops & Waveform Generation
* **The Academic Blueprint:** The AD5940 on-chip high-speed digital-to-analog converter (DAC) generates a programmable, low-distortion alternating current (AC) sinusoidal excitation wave calibrated between 50 kHz and 100 kHz. To meet strict medical and human-safety guidelines, an inline active current-limiting protection circuit physically clamps the total maximum current injection to ≤ 10 μA, preventing cellular over-excitation, discomfort, or tissue damage.
* **The System Philosophy:** *The boundary of non-invasive interaction.* The hardware communicates with the cell membranes at specific radio frequencies, utilizing a signal amplitude so minimal that it observes the baseline physiological state of the biological system without modifying, altering, or disrupting the tissue's natural equilibrium.

#### 1.3 Analog Front End (AFE) & Phase Acquisition Engine
* **The Academic Blueprint:** The resulting attenuated voltage wave from the tissue is captured and processed via a high-speed Transimpedance Amplifier (TIA). The system applies a localized Discrete Fourier Transform (DFT) directly on the chip's hardware accelerator. This extracts the Complex Impedance (Z), calculating both the real component (pure resistance, tracking sweat duct activity/epidermal density) and the imaginary component (capacitance, tracking cellular membrane integrity) to deliver a concurrent Phase Angle Tracking resolution down to fractions of a degree.
* **The System Philosophy:** *The acquisition of systemic truth.* This engine separates material tissue density (Ohms) from cellular capacitive resonance (Phase Angle). By tracking how many degrees the cell membrane delays the incoming wave, the AFE converts the raw physical resistance of the outer epidermal shell into a mathematical validation of deep cellular vitality.

---

## 💻 LAYER 2: THE FIRMWARE & DSP PIPELINE (The Logic Processing Layer)

Layer 2 ingests the raw digitized data from the AFE, strips away hardware propagation artifacts, and formats the metrics for true cryptographic compilation.

### 2.1 Quadrant Inversion & DSP Phase Alignment
* **The Academic Blueprint:** Due to propagation delays in hardware isolation stages and a fixed mathematical orientation in standard DFT libraries, raw complex numbers read an inherent 180-degree flip (e.g., -143.42° and -199.32°). The firmware runs a real-time correction loop that applies a sign-inversion filter across incoming vectors to output true biological values (e.g., -14.32° and -19.32°).
* **The System Philosophy:** *Aligning the geometric lens.* Just as a physical optical lens naturally inverts light to project an accurate image, hardware translation layers can introduce systematic coordinate inversions. This firmware layer acts as a digital corrective prism, un-flipping the mathematical coordinate system to align the digital metric with the actual, uncorrupted orientation of the living biological entity.

---

## 🔐 LAYER 3: CRYPTOGRAPHIC PAYLOAD GENERATION (The Sovereign Identity Layer)

Layer 3 compiles the error-corrected biological matrix into an immutable, hardware-level unique identifier.

### 3.1 Asymmetry Mapping & Fuzzy Extractor Matrix
* **The Academic Blueprint:** Tissue properties exhibit biological asymmetry (e.g., Left Hand 435.46 Ω vs. Right Hand 491.28 Ω). Because biological signals naturally fluctuate with ambient temperature and hydration levels, a Fuzzy Extractor block applies helper data algorithms to smooth out systemic noise without altering the core unique baseline.
* **The System Philosophy:** *The immutable biometric seal.* In a digital environment increasingly saturated by synthetic replication and artificial vectors, unique biological asymmetry stands as an un-spoofable anchor of individual presence. This layer honors biological autonomy by transforming natural, localized physical variations into a secure cryptographic key—proving that your biological identity is intrinsically secure, unique to the individual, and structurally resilient against external simulation.


## 👁️ Future Roadmap: Computer Vision Adaptive Grid Scale

To scale the 128-node symmetrical matrix across diverse anatomical structures (such as varied hand sizes, ages, and geometries), the system will integrate a real-time computer vision preprocessing layer. 

* **The Input Mechanism:** Utilizing a standard camera feed or mobile LiDAR spatial scan processed via Python.
* **The Execution Logic:** The software maps localized surface landmarks to dynamically configure, scale, and switch the hardware multiplexer array coordinates.
* **The Architectural Objective:** This ensures precise, normalized anatomical tracking and consistent spatial data density regardless of subject scale or physical variations.

## ⚖️ License & Sovereign Terms 
This project is licensed under the **GNU Affero General Public License v3.0 (AGPL-3.0)**. Please see the [LICENSE](./LICENSE) file for the full legal text.

### 🌟 Project Nebula Preamble 
The AGPL-3.0 is a copyleft license designed specifically to ensure absolute architectural transparency. When any tech entity, developer, or organization builds upon or interacts with Project Nebula over a network, this license guarantees that all modifications, multiplexer array mappings, and digital signal processing pipelines remain completely open to the community.

### 🔑 Key Requirements & Developer Guardrails

* **Complete Copyleft:** If you modify, copy, or adapt this firmware, data schemas, or mathematical mapping code, you **must** release
  your modified source code under the same AGPL-3.0 license.

* **Network Interactivity Requirement:** If you host a modified version of this system on a server to process tomography data remotely, you must make the complete source code available to the users interacting with that service.

*   **Preserve Integrity:** All downstream instances must preserve original author credits, copyright indicators, and hardware mapping protocols intact.

## ⚖️ Intellectual Property Notice
This project incorporates proprietary technology and methods currently protected under a **U.S. Provisional Patent Application (Patent Pending)**. All rights reserved. Unauthorized reproduction, commercial distribution, or reverse engineering of the custom hardware architecture or signal processing methods is strictly prohibited.



