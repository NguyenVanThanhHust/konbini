import numpy as np
import matplotlib.pyplot as plt

def generate_random_points(center, radius, num_points):
    # Generate random angles
    angles = np.random.uniform(0, 2 * np.pi, num_points)
    # Generate random distances from the center within the given radius
    radii = np.random.uniform(0, radius, num_points)
    
    # Calculate x and y coordinates
    x_points = center[0] + radii * np.cos(angles)
    y_points = center[1] + radii * np.sin(angles)
    
    return x_points, y_points

centers = [(2, 2), (50, 80), (-20, 40)]
all_x = []
all_y = []
with open("2d_dataset.txt", "w") as handle:
    for idx, center in enumerate(centers):
        radius = 20      # Radius of the circle
        num_points = 30 # Number of random points

        xs, ys = generate_random_points(center, radius, num_points)
        all_x.append(xs)
        all_y.append(ys)
        for (x, y) in zip(xs, ys):
            handle.write(str(x))
            handle.write(" ")
            handle.write(str(y))
            handle.write(" ")
            handle.write(str(idx))
            handle.write(" \n")

# Plotting the points
plt.figure(figsize=(6, 6))
plt.scatter(all_x[0], all_y[0], c='blue', alpha=0.5)
plt.scatter(all_x[1], all_y[1], c='green', alpha=0.5)
plt.scatter(all_x[2], all_y[2], c='red', alpha=0.5)
# plt.scatter(center[0], center[1], c='red') # Mark the center
# plt.gca().set_aspect('equal', adjustable='box')
plt.show()