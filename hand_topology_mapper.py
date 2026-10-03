import serial
import time
import numpy as np

class HandTopologyMapper:
    def __init__(self, port='COM3', baudrate=9600):
        """
        Initializes the 128-Node Bioimpedance Matrix Parser.
        Adjust 'port' to match your microcontroller's USB connection (e.g., 'COM3' or '/dev/ttyACM0').
        """
        self.total_nodes = 128
        self.matrix_data = np.zeros((self.total_nodes, 2))  # Column 0: Magnitude (Ω), Column 1: Phase (°)
        
        print(f"Connecting to Project-Nebula-BioZ Hardware on {port}...")
        try:
            self.serial_connection = serial.Serial(port, baudrate, timeout=1)
            time.sleep(2)  # Allow hardware time to reset after plug-in
            print("Hardware link established successfully.")
        except Exception as e:
            print(f"Error connecting to hardware: {e}")
            self.serial_connection = None

    def process_raw_stream(self):
        """
        Listens to the incoming serial stream from the hardware,
        parses out the global node indices, and maps them to their anatomical profiles.
        """
        if not self.serial_connection:
            print("Cannot stream: Hardware connection is offline.")
            return

        print("[STREAM] Listening for live 128-node matrix packets...")
        try:
            while True:
                if self.serial_connection.in_waiting > 0:
                    # Read incoming serial byte strings up to the newline terminator
                    raw_line = self.serial_connection.readline().decode('utf-8').strip()
                    
                    # Ensure packet matches our Phase 2 ASCII standard protocol
                    if raw_line.startswith('$'):
                        # Strip '$' and split into individual node blocks
                        node_payloads = raw_line[1:].split(',')
                        
                        for payload in node_payloads:
                            if ':' in payload:
                                # Unpack structured string format "NODE_ID:MAGNITUDE:PHASE"
                                node_str, mag_str, phase_str = payload.split(':')
                                node_id = int(node_str)
                                magnitude = float(mag_str)
                                phase = float(phase_str)
                                
                                # Clamp parameters safely inside the NumPy data matrix arrays
                                if 0 <= node_id < self.total_nodes:
                                    self.matrix_data[node_id, 0] = magnitude
                                    self.matrix_data[node_id, 1] = phase
                                    
                        print(f" -> Live Stream Sample Frame Sync: Node [0] Magnitude = {self.matrix_data[0, 0]} Ω")
                        
        except KeyboardInterrupt:
            print("\n[STREAM] Data collection paused by operator.")
        except Exception as e:
            print(f"[STREAM ERROR] Disconnected during runtime monitoring: {e}")
        finally:
            self.serial_connection.close()
            print("[SERIAL] Port safely closed.")

if __name__ == "__main__":
    # Execution entry runway for live hardware ingestion testing
    mapper = HandTopologyMapper(port='COM3', baudrate=9600)
    mapper.process_raw_stream()
