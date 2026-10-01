import csv
import time
from datetime import datetime

class ProjectNebulaLogger:
    def __init__(self, filename="bench_test_log.csv"):
        self.filename = filename
        self.headers = [
            "Timestamp", "Node_Index", "Frequency_Hz", 
            "Resistance_Ohms", "Phase_Angle_Deg", "State_Label"
        ]
        self.initialize_csv()

    def initialize_csv(self):
        """Creates the CSV file and writes academic headers if it doesn't exist."""
        try:
            with open(self.filename, mode='w', newline='') as file:
                writer = csv.writer(file)
                writer.writerow(self.headers)
            print(f"[SUCCESS] Data log initialized: '{self.filename}' is ready.")
        except Exception as e:
            print(f"[ERROR] Failed to initialize file: {e}")

    def log_node_data(self, node_index, frequency_hz, resistance_ohms, phase_angle, state_label):
        """Appends a single node measurement packet directly to the permanent file.
        
        state_label: Use 'Baseline_Dry' or 'Induced_Moisture' to tag your data.
        """
        current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]
        try:
            with open(self.filename, mode='a', newline='') as file:
                writer = csv.writer(file)
                writer.writerow([
                    current_time, node_index, frequency_hz, 
                    resistance_ohms, phase_angle, state_label
                ])
            print(f"[LOGGED] Node {node_index} | {frequency_hz} Hz | {resistance_ohms} Ω | {phase_angle}° | {state_label}")
        except Exception as e:
            print(f"[ERROR] Failed to write packet to disk: {e}")


# Benchtop Simulation Routine
if __name__ == "__main__":
    # 1. Initialize your log file
    logger = ProjectNebulaLogger("project_nebula_data.csv")
    print("\n--- Simulating Test Session ---")

    # 2. Simulate capturing your Baseline Dry metrics at 50 kHz
    print("\n[STEP 1] Running Baseline Dry Tests...")
    time.sleep(0.5)
    logger.log_node_data(node_index=0, frequency_hz=50000, resistance_ohms=343.89, phase_angle=181.39, state_label="Baseline_Dry")
    logger.log_node_data(node_index=1, frequency_hz=50000, resistance_ohms=342.12, phase_angle=181.45, state_label="Baseline_Dry")

    # 3. Simulate capturing your Induced Moisture metrics after thermal friction
    print("\n[STEP 2] Inducing Dynamic Somatic Shift...")
    time.sleep(0.5)
    logger.log_node_data(node_index=0, frequency_hz=50000, resistance_ohms=272.85, phase_angle=183.04, state_label="Induced_Moisture")

    # 4. Simulate capturing deep cellular penetration at 100 kHz
    print("\n[STEP 3] Escalating to High-Frequency Cellular Interrogation...")
    time.sleep(0.5)
    logger.log_node_data(node_index=0, frequency_hz=100000, resistance_ohms=338.99, phase_angle=-14.32, state_label="Deep_Membrane_Scan")

    print("\n[SUCCESS] Session complete. Check 'project_nebula_data.csv' to see your structured dataset.")
