import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

def visualize_1d(points):

    y = np.zeros_like(points)
    plt.figure(figsize=(10, 1))
    plt.scatter(points, y, color='blue', marker='o')
    plt.yticks([])  # убрать ось Y
    plt.xlabel("X")
    plt.title("1D Points Visualization")
    plt.grid(True, axis='x')
    plt.tight_layout()
    plt.show()

points = pd.read_csv("Fractal_modelling/output.csv", header=None)
visualize_1d(points)