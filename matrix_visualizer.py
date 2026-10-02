import serial
import struct
import numpy as np
import math

class ProjectNebulaVisualizer:
    def __init__(self, port='/dev/ttyACM0', baudrate=115200):
        """Initializes the connection to the microcontroller serial interface."""
        self.total_nodes = 128
        # Define a symmetrical 11x11 spatial grid matrix layout to map the palm anatomy
        self.grid_size = 11  
        self.serial_port = port
        self.baudrate = baudrate
        
    def parse_raw_serial_packet(self):
        """
        Ingests digitized complex byte streams streaming from the microcontroller.
        Parses 16-bit real and imaginary vectors payload per node.
        """
        print(f"[SERIAL] Listening for continuous matrix sweep on {self.serial_port}...")
        simulated_sweep_data = []
        
        # Simulated stream matrix matching Chapter 4 hardware validation bounds
        # Real/Imaginary coordinates derived from baseline ~340 Ohm magnitudes
        for node_id in range(self.total_nodes):
            if node_id % 3 == 0:
                # Active sudomotor alignment profile (Low resistance / Red Zone)
                simulated_sweep_data.append((-275.5, -203.2))
            else:
                # Stable cellular membrane baseline (High capacitance / Blue Zone)
                simulated_sweep_data.append((-343.89, -151.46))
                
        return simulated_sweep_data

    def reconstruct_topographical_matrix(self, raw_vectors):
        """
        Processes Layer 2 DSP: Applies rectangular-to-polar calculations,
        corrects quadrant phase inversions, and shapes data into an anatomical grid.
        """
        magnitude_array = np.zeros(self.total_nodes)
        phase_array = np.zeros(self.total_nodes)
        
        for node_id, (real, imag) in enumerate(raw_vectors):
            # Calculate absolute impedance magnitude
            magnitude_array[node_id] = math.sqrt(real**2 + imag**2)
            
            # Apply Quadrant Inversion Correction Filter
            raw_phase_deg = math.degrees(math.atan2(imag, real))
            if raw_phase_deg < -90.0:
                phase_array[node_id] = raw_phase_deg + 180.0
            else:
                phase_array[node_id] = raw_phase_deg

        # Map the 128 linear vector channels into a unified 2D concentric matrix array
        # Note: Truncating/padding elements to fit the 11x11 (121 elements) spatial map coordinate bounds
        padded_magnitude_grid = np.pad(magnitude_array, (0, (self.grid_size * self.grid_size) - self.total_nodes), 'constant')
        topographical_grid = padded_magnitude_grid.reshape((self.grid_size, self.grid_size))
        
        return topographical_grid, phase_array

    def render_live_dashboard(self):
        """Runs the processing pipeline and outputs matrix metrics to terminal interface."""
        raw_stream = self.parse_raw_serial_packet()
        grid, phases = self.reconstruct_topographical_matrix(raw_stream)
        
        print("\n[DSP] Reconstructed 11x11 Palmar Topographical Coordinate Matrix:")
        print("-----------------------------------------------------------------")
        # Display localized topographical slice grid matrix numbers to console terminal
        for row in grid[:5]: # Displaying first 5 rows for validation overview
            print(" ".join(f"{val:6.1f}" for val in row))
        print("-----------------------------------------------------------------")
        print(f" -> Matrix Status: Reconstructed (Mean Base Phase Angle: {np.mean(phases):.2f}°)")
        print("[GUI] Ready to bind to Matplotlib/PyQt interface for color heatmap rendering.")

if __name__ == "__main__":
    # Mock runtime hook simulation
    visualizer = ProjectNebulaVisualizer(port='SIMULATED_PORT')
    visualizer.render_live_dashboard()
