// Fractal_modelling.cpp
#include "PointCloud.hpp"
#include "simulate.hpp"

int main() { 
    float Length = 10.0;          // Cube length

//  1D case
//    constexpr int dim = 1;
//    std::array<double, dim> sizes = {Length};
 
//  2D case 
//    constexpr int dim = 2;
//    std::array<double, dim> sizes = { Length, Length};

//  3D case
    constexpr int dim = 3;        // Problem dimensiot
    std::array<double, dim> sizes = { Length, Length, Length};

    int K = 7;                    // Recursion depth
    int n_points = 1000;          // Number of points
    float D2 = 2.5;              // Correlation fractal dimension

    PointCloud<dim> cloud(sizes);

    simulate(cloud, D2, K, n_points);
    cloud.saveToCSV("output.csv");

    return 0;
}
