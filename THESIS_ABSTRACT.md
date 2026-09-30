# 📄 Thesis Abstract

**Title:** Design and Benchtop Validation of a High-Resolution Multi-Frequency AC Bio-Impedance Measurement Matrix for Localized Electrodermal Topographical Mapping

---

### 📋 Abstract

Conventional commercial direct-current (DC) Galvanic Skin Response (GSR) instrumentation is fundamentally limited in high-resolution topographical tissue mapping due to shared grounding loops, severe signal cross-talk, and an absence of concurrent phase-angle tracking. To address these technical constraints, this thesis presents the design, architectural implementation, and benchtop validation of a custom alternating current (AC) bio-impedance measurement matrix leveraging the research-grade **Analog Devices EVAL-AD5940BIOZ** hardware architecture.

Configured as a high-density, **128-node symmetrical switching array** utilizing a tetrapolar sensing configuration, the developed system successfully decouples current-driving and voltage-sensing electrode pairs to eliminate contact impedance artifacts across localized human tissue boundaries. The instrumentation operates under an active hardware current-limiting protection circuit strictly clamped to **≤ 10 μA** to ensure absolute human safety across multi-frequency testing profiles.

System performance was evaluated via a **Single-Subject Technical Pilot Evaluation** under the influence of live, real-time biological noise and transient signal drifting. Initial baseline metrics under high-impedance dry skin states at 50 kHz excitation (300 mV amplitude) demonstrated highly stable circuit behavior, yielding a stable tissue impedance magnitude of **343.89 Ω** and a concurrent phase tracking angle of **181.39°**. To evaluate system responsiveness to dynamic somatic shifts, localized thermal friction and surface moisture variations were induced. The system successfully captured real-time responsive shifts, tracking an impedance magnitude reduction to **272.85 Ω** and a corresponding phase angle shift to **183.04°**.

Advanced multi-frequency parameterization at 100 kHz (600 mV amplitude) successfully triggered deep cellular membrane penetration, recording a tissue magnitude drop to **338.99 Ω** and forcing the phase angle into a stable capacitive negative envelope at **-151.461°**. Furthermore, firmware-level DSP correction loops successfully resolved systemic 180-degree phase inversions caused by hardware isolation propagation delays. These results validate the structural stability, electronic isolation, and active tracking capabilities of the developed AC bio-impedance architecture, establishing a viable, high-resolution technical proof-of-concept for localized electrodermal tracking and unique cryptographic biometric generation.

---

**Keywords:** *AC Bio-Impedance, Phase-Angle Tracking, EVAL-AD5940BIOZ, Electrodermal Mapping, Hardware Validation, Biometric Identification.*
