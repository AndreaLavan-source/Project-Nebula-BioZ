# 🗺️ Project Nebula: Phase 2 Engineering Roadmap

This document outlines the software development framework for scaling Project Nebula from a single-channel calibrated hardware bridge to a serialized 128-node multi-channel biosensing matrix.

## 🧵 Phase 2 Architecture: The C++ / Python Integration Bridge

To translate raw impedance signals into a live topographical color-mapped heatmap of the hand, the system uses a dual-layer architectural pipeline split across a physical USB-Serial interface:+------------------------------------+          +-----------------------------------+
|  1. EVAL-ADICUP3029 / C++ FIRMWARE |          |    2. COMPUTER LAYER / PYTHON GUI |
|  - Controls 128-Node Mux Switching |  Serial  |  - Ingests incoming ASCII Packets |
|  - Triggers AD5940 AFE Drivers     | -------->|  - Parses Node IDs & Ohm Metrics  |
|  - PACKS DATA INTO ASCII PACKETS   |   (USB)  |  - RENDERS LIVE GRAPHICAL HEATMAP |
+------------------------------------+          +-----------------------------------+---

## 🛠️ Step-by-Step Implementation Milestone Tasks

### Milestone 1: Standardize the Serial Communication Protocol
The C++ firmware (`matrix_routing.cpp`) must write clean, structured data arrays to the microcontroller's UART TX line so the Python interface can interpret the coordinates without parsing lag.

* **Packet Format Structure:** Every 128-node sweep frame must be delimited by an explicit starting character (`$`), followed by comma-separated node data pairs, and terminated by a newline character (`\n`).
* **Packet String Syntax Example:**
  ```text
  $NODE_ID:MAGNITUDE:PHASE,NODE_ID:MAGNITUDE:PHASE\n
  $0:1136.95:-13.68,1:1120.40:-14.10,2:1085.12:-12.30,...,127:1210.45:-15.20\n
  ```

### Milestone 2: Establish the Python Serial Ingestion Loop
Updated my Python framework to listen to the incoming hardware stream continuously using the `pyserial` processing library. 

Add this dedicated communication thread block to your data collection pipeline to prevent the visualizer GUI from freezing up while waiting for incoming SPI bytes:

```python
import serial
import threading

def initialize_hardware_serial_stream(port_name="COM3", baud_rate=115200, visualizer_instance=None):
    """
    Spawns an isolated background thread to continuously pull live 
    micro-topographical metrics from the physical AD5940 USB bridge.
    """
    def serial_reader_worker():
        try:
            ser = serial.Serial(port_name, baud_rate, timeout=1.0)
            print(f"[SERIAL] Connected to EVAL-ADICUP3029 on {port_name} successfully.")
            
            while True:
                # Read raw serial bytes up to the newline terminator
                raw_line = ser.readline().decode('utf-8').strip()
                
                if raw_line.startswith('$'):
                    # Strip the starting character and split into distinct node entries
                    data_payload = raw_line[1:].split(',')
                    
                    for entry in data_payload:
                        if ':' in entry:
                            node_str, mag_str, phase_str = entry.split(':')
                            node_id = int(node_str)
                            magnitude = float(mag_str)
                            
                            # Safely route the live physical metric to the GUI layout array
                            if visualizer_instance and node_id < visualizer_instance.total_nodes:
                                gx, gy = visualizer_instance.node_spatial_mask[node_id]
                                visualizer_instance.heatmap_matrix[gx, gy] = magnitude
                                
        except Exception as e:
            print(f"[SERIAL ERROR] Disconnected or failed to read USB buffer: {e}")

    # Launch worker loop as an independent background process
    stream_thread = threading.Thread(target=serial_reader_worker, daemon=True)
    stream_thread.start()
```

### Milestone 3: Sequential Node Matrix Switching Logic
The C++ switching algorithm (`matrix_routing.cpp`) must execute a dead-time blanking interval (recommended **50 μs to 100 μs**) every time it updates its external multiplexer address bits to switch from one hand coordinate to another. This delay allows capacitive charge dissipation across the tissue boundary, entirely eliminating signal bleeding or ghost-node artifacts between neighboring anatomical cells.

---

## 🤝 Target Competencies for Software Co-Founder Discovery

To accelerate the delivery of Phase 2 objectives, candidates or software mentors looking at this repository should ideally bring expertise across these technical areas:
* **Embedded System Frameworks:** Experience handling direct hardware abstractions, bare-metal timers, and SPI register writing on Cortex-M microcontrollers.
* **Concurrency in Python:** Proficiency building multi-threaded real-time data visualizers (using `PyQt6`, `Tkinter`, or asynchronous `matplotlib` engines).
* **Signal Processing (DSP):** Competency developing discrete filtering pipelines to handle complex math operations, ratiometric calibration arrays, and artifact suppression.
