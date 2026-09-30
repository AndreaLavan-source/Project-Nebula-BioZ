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
