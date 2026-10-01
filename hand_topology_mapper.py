import numpy as np
import math

class AdaptiveGridMapper:
    def __init__(self, target_nodes=128):
        self.target_nodes = target_nodes
        print(f"[INFO] Initializing Adaptive Bio-Impedance Grid Mapper for {self.target_nodes} nodes.")

    def normalize_hand_topology(self, raw_camera_landmarks):
        """
        Accepts raw 2D/3D camera coordinate arrays and normalizes them 
        against biological scale variances using a bounding box vector.
        """
        landmarks = np.array(raw_camera_landmarks)
        
        # Calculate extreme anatomical boundaries (bounding box)
        min_coords = np.min(landmarks, axis=0)
        max_coords = np.max(landmarks, axis=0)
        hand_scale = max_coords - min_coords
        
   # Prevent division by zero errors by replacing 0 scales with 1.0
hand_scale = np.where(hand_scale == 0, 1.0, hand_scale)

# Perform min-max normalization to map hand into a standard 0.0 to 1.0 geometric space
normalized_grid = (landmarks - min_coords) / hand_scale

return normalized_grid

    def generate_multiplexer_map(self, normalized_grid):
        """
        Maps normalized spatial data directly into a programmatic sequence 
        for the 128-node hardware switching matrix.
        """
        hardware_routing_table = []
        for i, coordinate in enumerate(normalized_grid):
            if i >= self.target_nodes:
                break
            # Translate normalized coordinates directly into a target hardware channel address
            channel_assignment = min(int(np.mean(coordinate) * 128), 127) 
            hardware_routing_table.append({
                "node_index": i,
                "spatial_vector": coordinate.tolist(),
                "mux_channel_address": channel_assignment
            })
        return hardware_routing_table

# Benchtop Validation Example
if __name__ == "__main__":
    # Simulated raw pixel coordinates from a camera stream tracking 5 anatomical points
    simulated_hand_data = [[100,100], # Wrist base,  # Left palm periphery,  # Right palm periphery,  # Index base coordinate
        [190, 115]   # Pinky base coordinate
    ]
    
    mapper = AdaptiveGridMapper(target_nodes=128)
    normalized_space = mapper.normalize_hand_topology(simulated_hand_data)
    routing_instructions = mapper.generate_multiplexer_map(normalized_space)
    
    print(f"[SUCCESS] Successfully mapped {len(routing_instructions)} target tissue zones to hardware multiplexer channels.")
    print(f"[SAMPLE NODE 0]: {routing_instructions[0]}")
