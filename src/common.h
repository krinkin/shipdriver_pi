#pragma once

namespace MarineNavi {
namespace Utils {

struct Point {
    double& X() {
        return Lon;
    }

    double& Y() {
        return Lat;
    }


    Point operator+(const Point& other) const {
        return Point{Lat + other.Lat, Lon + other.Lon};
    }

    Point operator-(const Point& other) const {
        return Point{Lat - other.Lat, Lon - other.Lon};
    }

    Point operator*(double x) {
        return Point{Lat * x, Lon * x};
    }

    double Lat;
    double Lon;
};

} // namespace Utils
} // namespace MarineNavi