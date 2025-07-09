import pandas as pd
import matplotlib.pyplot as plt
#from mpl_toolkits.mplot3d import Axes3D

# Download CSV
df = pd.read_csv("Fractal_modelling/output.csv", header=None)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.scatter(df[0], df[1], df[2], c='b', marker='o')

ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")
ax.set_title("3D Point Cloud")

plt.tight_layout()
plt.show()
