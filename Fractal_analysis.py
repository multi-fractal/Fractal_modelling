import numpy as np
import pandas as pd
from scipy.spatial import KDTree
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

def load_points_from_csv(file_path):
    df = pd.read_csv(file_path)
    return df.values  # numpy array, shape (N, D)

def correlation_sum_kdtree(tree, N, radius):
    count = tree.query_pairs(r=radius)
    return 2 * len(count) / (N * (N - 1))

def estimate_correlation_dimension(points, radii, plot=True, save_path=None):
    tree = KDTree(points)
    N = len(points)
    log_r = []
    log_c = []

    for r in radii:
        c = correlation_sum_kdtree(tree, N, r)
        if c > 0:
            log_r.append(np.log(r))
            log_c.append(np.log(c))

    # Линейная регрессия
    X = np.array(log_r).reshape(-1, 1)
    y = np.array(log_c)
    model = LinearRegression().fit(X, y)
    print(model.coef_)
    D2 = model.coef_[0]

    if plot:
        plt.figure(figsize=(6, 4))
        plt.scatter(log_r, log_c, label='log(C(r))')
        plt.plot(X, model.predict(X), color='red', label=f'fit (D₂ ≈ {D2:.2f})')
        plt.xlabel('log(r)')
        plt.ylabel('log(C(r))')
        plt.title('Correlation Dimension Estimate')
        plt.grid(True)
        plt.legend()
        plt.tight_layout()
        if save_path:
            plt.savefig(save_path)
            print(f"График сохранён в файл: {save_path}")
        else:
            plt.show()

    return D2


if __name__ == "__main__":
    
    np.random.seed(42)  
    
    file_path = "Fractal_modelling/output.csv" 
    save_plot_to = "correlation_dimension.png" 
     
    points = load_points_from_csv(file_path)
    radii = np.logspace(-2.0, 0.25, num=10)
    print(radii)

    d2 = estimate_correlation_dimension(points, radii, plot=True, save_path=save_plot_to)
    print(f"Estimation of correlation dimension D₂ ≈ {d2:.4f}")    
    

