import serial
import time
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# --- SYSTEM CONFIGURATION ---
SERIAL_PORT = 'COM3'  # Change to your actual microcontroller port (e.g., 'COM4' or '/dev/ttyACM0')
BAUD_RATE = 9600
ROWS, COLS = 8, 16    # 8 Multiplexers x 16 Channels = 128 Nodes

# Initialize global data grid for the visualization
# This grid stores the live values coming from the hardware matrix
data_grid = np.zeros((ROWS, COLS))

# Try setting up the serial data pipeline
try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=0.1)
    print(f"Successfully bound visualization engine to {SERIAL_PORT}")
    time.sleep(2)  # Allow hardware board to cleanly settle after reboot
except Exception as e:
    print(f"Hardware connection skipped ({e}). Visualizer running in emulation mode.")
    ser = None

# --- GRAPHICAL INTERFACE SETUP ---
fig, ax = plt.subplots(figsize=(10, 6))
fig.canvas.manager.set_window_title('Project-Nebula-BioZ: Live 128-Node Matrix View')

# Create the initial visual layout grid map using the 'plasma' colormap
# Red/Amber = High sweat-duct alignment / stress; Blue/Purple = Capacitive delay
im = ax.imshow(data_grid, cmap='plasma', interpolation='nearest', origin='upper', vmin=200, vmax=2000)

# Add UI design labels and structural annotations
ax.set_title("Project Nebula: 128-Node Real-Time Micro-Topographical Heatmap", fontsize=12, fontweight='bold', pad=15)
ax.set_xlabel("Multiplexer Sourcing Channels (0 - 15)", fontsize=10, labelpad=10)
ax.set_ylabel("Cascaded Multiplexer IC Banks (0 - 7)", fontsize=10, labelpad=10)

# Add ticks matching the exact rows and columns of your multiplexer setup
ax.set_xticks(np.arange(COLS))
ax.set_yticks(np.arange(ROWS))

# Add a visual color bar legend scaled to your validated Ohm thresholds
cbar = fig.colorbar(im, ax=ax, orientation='vertical', pad=0.05)
cbar.set_label("Impedance Magnitude (Ohms)", fontsize=10, labelpad=10)

def parse_incoming_serial_data():
    """
    Pulls data lines from the serial port buffer and populates the 2D grid matrix.
    If hardware is missing, it injects clean mathematical emulation noise to simulate tissue.
    """
    global data_grid
    
    if ser and ser.in_waiting > 0:
        try:
            raw_line = ser.readline().decode('utf-8').strip()
            
            # Parse standard Project Nebula protocol string: $NODE_ID:MAGNITUDE:PHASE,...
            if raw_line.startswith('$'):
                node_payloads = raw_line[1:].split(',')
                for payload in node_payloads:
                    if ':' in payload:
                        node_str, mag_str, _ = payload.split(':')
                        node_id = int(node_str)
                        magnitude = float(mag_str)
                        
                        # Map the 1D node ID (0-127) directly to 2D row/column grid indices
                        if 0 <= node_id < (ROWS * COLS):
                            r = node_id // COLS
                            c = node_id % COLS
                            data_grid[r, c] = magnitude
        except Exception as e:
            # Prevent occasional garbled serial bits from breaking the rendering loop
            pass
    elif ser is None:
        # EMULATION MODE: Inject localized random fluctuations centered around your validated 1136 Ohm benchmark
        base_val = 1136.959
        data_grid = np.random.normal(loc=base_val, scale=100.0, size=(ROWS, COLS))
        data_grid = np.clip(data_grid, 200, 2000)

def update_visualization_frame(frame):
    """
    Core execution frame loop triggered continuously by the Matplotlib animator.
    """
    parse_incoming_serial_data()
    im.set_array(data_grid)  # Refresh colors based on new data grid parameters
    return [im]

# Trigger the live high-performance animation framework loop
ani = animation.FuncAnimation(fig, update_visualization_frame, blit=True, interval=100, cache_frame_data=False)

plt.tight_layout()
plt.show()
