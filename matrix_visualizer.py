import serial
import time
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# --- SYSTEM CONFIGURATION ---
SERIAL_PORT = 'COM3'  # Change to your actual microcontroller port (e.g., 'COM4' or '/dev/ttyACM0')
BAUD_RATE = 9600
ROWS, COLS = 8, 16    # 8 Multiplexers x 16 Channels = 128 Nodes

# Try setting up the serial data pipeline
try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=0.1)
    print(f"Successfully bound visualization engine to {SERIAL_PORT}")
    time.sleep(2)  # Allow hardware board to cleanly settle after reboot
except Exception as e:
    print(f"Hardware connection skipped ({e}). Visualizer running in emulation mode.")
    ser = None

# --- GRAPHICAL INTERFACE SETUP ---
# Create a dual-plot layout (1 Row, 2 Columns)
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))
fig.canvas.manager.set_window_title('Project-Nebula-BioZ: Live Dual-Matrix View')

# Initialize two separate 2D grids in memory to track Magnitude and Phase
mag_grid = np.zeros((ROWS, COLS))
phase_grid = np.zeros((ROWS, COLS))

# Left Screen: Impedance Magnitude (Ohms) using the plasma map
im1 = ax1.imshow(mag_grid, cmap='plasma', interpolation='nearest', origin='upper', vmin=200, vmax=2000)
ax1.set_title("Resistance Gateway (Ω)\n[Low Ohms = Stress Tracker]", fontsize=11, fontweight='bold')
ax1.set_xticks(np.arange(COLS))
ax1.set_yticks(np.arange(ROWS))
cbar1 = fig.colorbar(im1, ax=ax1, orientation='vertical', pad=0.05)
cbar1.set_label("Impedance Magnitude (Ohms)", fontsize=9)

# Right Screen: Corrected Phase Delay (Degrees) using the purples map
im2 = ax2.imshow(phase_grid, cmap='Purples', interpolation='nearest', origin='upper', vmin=-25, vmax=-5)
ax2.set_title("Corrected Phase Profile (°)\n[High Delay = Living Cell Tracker]", fontsize=11, fontweight='bold')
ax2.set_xticks(np.arange(COLS))
ax2.set_yticks(np.arange(ROWS))
cbar2 = fig.colorbar(im2, ax=ax2, orientation='vertical', pad=0.05)
cbar2.set_label("Phase Profile (Degrees °)", fontsize=9)

fig.suptitle("Project Nebula: 128-Node Real-Time Micro-Topographical Dual Heatmap", fontsize=13, fontweight='bold', y=0.98)

def parse_incoming_serial_data():
    """
    Pulls data lines from the serial port buffer and populates both 2D grid matrices.
    If hardware is missing, it injects clean mathematical emulation noise to simulate tissue.
    """
    global mag_grid, phase_grid
    
    if ser and ser.in_waiting > 0:
        try:
            raw_line = ser.readline().decode('utf-8').strip()
            
            # Parse standard Project Nebula protocol string: $NODE_ID:MAGNITUDE:PHASE,...
            if raw_line.startswith('$'):
                node_payloads = raw_line[1:].split(',')
                for payload in node_payloads:
                    if ':' in payload:
                        # Extract all three values cleanly from the serial text packet
                        node_str, mag_str, phase_str = payload.split(':')
                        node_id = int(node_str)
                        magnitude = float(mag_str)
                        
                        # Read raw phase and apply your 180° hardware correction flip
                        raw_phase = float(phase_str)
                        corrected_phase = raw_phase + 180.0
                        if corrected_phase > 180:
                            corrected_phase -= 360
                        
                        # Map the 1D node ID (0-127) directly to 2D row/column grid indices
                        if 0 <= node_id < (ROWS * COLS):
                            r = node_id // COLS
                            c = node_id % COLS
                            mag_grid[r, c] = magnitude
                            phase_grid[r, c] = corrected_phase
        except Exception as e:
            # Prevent occasional garbled serial bits from breaking the rendering loop
            pass
    elif ser is None:
        # EMULATION MODE: Inject realistic biological variables for both domains based on benchmarks
        base_val = 1136.959
        mag_grid = np.random.normal(loc=base_val, scale=100.0, size=(ROWS, COLS))
        mag_grid = np.clip(mag_grid, 200, 2000)
        
        # Emulate your validated live hand phase benchmark (-14.32° to -19.32°)
        phase_grid = np.random.uniform(-22.0, -10.0, size=(ROWS, COLS))

def update_visualization_frame(frame):
    """
    Core execution frame loop triggered continuously by the Matplotlib animator.
    """
    parse_incoming_serial_data()
    im1.set_array(mag_grid)   # Refresh the material Ohm matrix colors
    im2.set_array(phase_grid) # Refresh the living phase delay matrix colors
    return [im1, im2]

# Trigger the live high-performance animation framework loop
ani = animation.FuncAnimation(fig, update_visualization_frame, blit=True, interval=100, cache_frame_data=False)

plt.tight_layout()
plt.show()
