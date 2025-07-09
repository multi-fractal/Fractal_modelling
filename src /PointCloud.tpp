// PointCloud.tpp

#include <fstream>
#include <stdexcept>
#include <sstream>

template<int D>
PointCloud<D>::PointCloud(const std::array<double, D>& sizes) : domain_sizes(sizes) {}

template<int D>
void PointCloud<D>::addPoint(const Point& pt) {
    points.push_back(pt);
}

template<int D>
void PointCloud<D>::saveToCSV(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file.");
    }

    for (const auto& pt : points) {
        for (int i = 0; i < D; ++i) {
            file << pt[i];
            if (i < D - 1) file << ",";
        }
        file << "\n";
    }
}

template<int D>
std::array<double, D> PointCloud<D>::getSizes() const {
    return domain_sizes;
}

template<int D>
const std::vector<typename PointCloud<D>::Point>& PointCloud<D>::getPoints() const {
    return points;
}
