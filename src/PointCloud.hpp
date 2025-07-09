// PointCloud.hpp

#include <array>
#include <vector>
#include <string>
#pragma once

// Template Class for Point Clouds
template<int D>
class PointCloud {
public:
    using Point = std::array<double, D>;

    PointCloud(const std::array<double, D>& sizes);

    void addPoint(const Point& pt);
    void saveToCSV(const std::string& filename) const;

    std::array<double, D> getSizes() const;
    const std::vector<Point>& getPoints() const;

private:
    std::array<double, D> domain_sizes;
    std::vector<Point> points;
};

#include "PointCloud.tpp"
