#pragma once

#include <ctime>
#include <string>
#include <time.h>

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

time_t ParseDate(const std::string& repr, const std::string& format = "%Y-%m-%d %H:%M:%S") {
    struct tm tm;
    strptime(repr.data(), format.data(), &tm);
    return mktime(&tm);
}

} // namespace Utils
} // namespace MarineNavi