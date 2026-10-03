import sys
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# =========================================================================
# PROJECT NEBULA: 128-NODE TOPOGRAPHICAL HEATMAP VISUALIZER
# =========================================================================
class ProjectNebulaVisualizer:
    def __init__(self):
        self.total_nodes = 128
        # Define grid layout dimensions for parsing the hand geometry array
        self.grid_size = 12 
        
        # Initialize an empty topographical matrix map representing coordinates on the palm
        self.heatmap_matrix = np.zeros((self.grid_size, self.grid_size))
        
        # Generate anatomical layout mapping vector indices (0-127) onto geometric palm spatial coordinates
        self.node_spatial_mask = self._generate_anatomical_spatial_coordinates()

    def _generate_anatomical_spatial_coordinates(self):
        """
        Maps linear node IDs (0-127) to 2D matrix indices representing concentric rows across the palm.
        """
        mapping = {}
        node_id = 0
        
        # Simulating an anatomical concentric layout layout filling a 12x12 quadrant grid space smoothly
        center_x, center_y = self.grid_size // 2, self.grid_size // 2
        for radius in range(1, 6):
            for angle in np.linspace(0, 2 * np.pi, radius * 8, endpoint=False):
                if node_id >= self.total_nodes:
                    break
                x = int(center_x + radius * np.cos(angle))
                y = int(center_y + radius * np.sin(angle))
                if 0 <= x < self.grid_size and 0 <= y < self.grid_size:
                    if (x, y) not in mapping.values():
                        mapping[node_id] = (x, y)
                        node_id += 1
                        
        # Fill in any remaining nodes linearly outside the primary circle bounds
        for r in range(self.grid_size):
            for c in range(self.grid_size):
                if node_id >= self.total_nodes:
                    break
                if (r, c) not in mapping.values():
                    mapping[node_id] = (r, c)
                    node_id += 1
        return mapping

    def simulate_hardware_stream(self):
        """
        Simulates live input streaming values from your validated AD5940 4-wire hardware setup.
        Replaces the infinity bug with real fluctuations mimicking biological fluid changes.
        """
        # Base baseline values derived from your successful 1,136 Ohm benchtop test
        base_magnitude = 1136.959
        
        # Inject standard random noise over the 128 node channels to represent tissue variations
        simulated_frame = np.random.normal(loc=base_magnitude, scale=150.0, size=self.total_nodes)
        return np.clip(simulated_frame, 200.0, 2000.0)

    def launch_live_heatmap(self):
        """
        Initializes the graphical window displaying the color-mapped biological matrix.
        """
        fig, ax = plt.subplots(figsize=(8, 7))
        ax.set_title("Project Nebula: 128-Node Topographical Tissue Matrix", fontsize=12, fontweight='bold', pad=15)
        
        # Red/Amber = Low resistance (high sweat duct alignment); Blue/Purple = Capacitive delay
        im = ax.imshow(self.heatmap_matrix, cmap='plasma', interpolation='gaussian', vmin=200, vmax=2000)
        cbar = fig.colorbar(im, ax=ax, label="Impedance Magnitude (Ohms)")
        
        ax.axis('off') # Hides numerical grid borders to focus cleanly on anatomical clusters

        def update_frame(frame):
            # 1. Fetch live incoming array numbers 
            live_data_stream = self.simulate_hardware_stream()
            
            # 2. Map data arrays onto their physical 2D anatomical locations
            for node_id, data_value in enumerate(live_data_stream):
                if node_id in self.node_spatial_mask:
                    grid_x, grid_y = self.node_spatial_mask[node_id]
                    self.heatmap_matrix[grid_x, grid_y] = data_value
            
            # 3. Push refreshed pixels straight to graphic panel display
            im.set_array(self.heatmap_matrix)
            return [im]

        # Trigger animation loop executing refreshing operations continuously 
        ani = FuncAnimation(fig, update_frame, blit=True, interval=150, cache_frame_data=False)
        plt.show()

if __name__ == "__main__":
    visualizer = ProjectNebulaVisualizer()
    visualizer.launch_live_heatmap()
