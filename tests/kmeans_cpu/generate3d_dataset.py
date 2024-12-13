import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def generate_random_3d_points(center, radius, num_points):
    # Generate random angles for spherical coordinates
    phi = np.random.uniform(0, 2 * np.pi, num_points)
    theta = np.random.uniform(0, np.pi, num_points)
    r = np.random.uniform(0, radius, num_points)
    
    # Convert spherical coordinates to Cartesian coordinates
    x = center[0] + r * np.sin(theta) * np.cos(phi)
    y = center[1] + r * np.sin(theta) * np.sin(phi)
    z = center[2] + r * np.cos(theta)
    
    return x, y, z

centers = [(2, 2, 2), (50, 80, 40), (-20, 40, -60)]
all_x = []
all_y = []
all_z = []
with open("3d_dataset.txt", "w") as handle:
    for idx, center in enumerate(centers):
        radius = 10      # Radius of the circle
        num_points = 30 # Number of random points

        xs, ys, zs = generate_random_3d_points(center, radius, num_points)
        all_x.append(xs)
        all_y.append(ys)
        all_z.append(zs)
        for (x, y, z) in zip(xs, ys, zs):
            handle.write(str(x))
            handle.write(" ")
            handle.write(str(y))
            handle.write(" ")
            handle.write(str(z))
            handle.write(" ")
            handle.write(str(idx))
            handle.write(" \n")

# Plotting the points
fig = plt.figure(figsize=(8, 8))
ax = fig.add_subplot(111, projection='3d')

ax.scatter(all_x[0], all_y[0], all_z[0], c='blue', alpha=0.5)
ax.scatter(all_x[1], all_y[1], all_z[1], c='green', alpha=0.5)
ax.scatter(all_x[2], all_y[2], all_z[2], c='red', alpha=0.5)
# ax.scatter(center[0], center[1], center[2], c='red') # Mark the center

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
plt.show()
