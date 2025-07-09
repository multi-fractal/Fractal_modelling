import matplotlib.pyplot as plt
import pandas as pd
#import numpy as np

points = pd.read_csv("Fractal_modelling/output.csv", header=None)

plt.figure(figsize=(6, 6))
plt.scatter(points[0], points[1], color='blue', s=50)

plt.title("2D Points Visualization")
plt.xlabel("X")
plt.ylabel("Y")
plt.grid(True)
plt.axis("equal") 

plt.show()
