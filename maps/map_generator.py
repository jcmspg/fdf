import numpy as np

# Parameters
map_size = 76
mean = 16  # Mean height
std_dev = 2  # Standard deviation to control spread of heights
min_height = -10
max_height = 90

# Function to generate a random HEX color in the format 0xXXXXXX
def random_hex_color():
    return "0x{:06X}".format(np.random.randint(0, 0xFFFFFF + 1))

# Generate Gaussian distributed heights
heights = np.random.normal(loc=mean, scale=std_dev, size=(map_size, map_size))

# Clip heights to be within the range [-60, 60]
heights = np.clip(heights, min_height, max_height)

# Convert heights to integers
heights = np.round(heights).astype(int)

# Generate random HEX colors
colors = np.array([[random_hex_color() for _ in range(map_size)] for _ in range(map_size)])

# Save height and color data to a file
with open('height_map.fdf', 'w') as f:
    for i in range(map_size):
        line = " ".join(f"{heights[i][j]},{colors[i][j]}" for j in range(map_size))
        f.write(line + "\n")

print("random height map with colors has been saved to 'height_map.fdf'.")

