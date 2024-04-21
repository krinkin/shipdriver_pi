#pragma once

#include "DepthGrid.h"
#include "common.h"

#include <ocpn_plugin.h>

#include <wx/wx.h>

#include <mutex>
#include <optional>

namespace MarineNavi {

struct PathData {
    Utils::Point Start;
    Utils::Point End;

    std::optional<double> ShipDraft;
    std::optional<std::string> PathToDepthFile;
};

class CheckPathCase {
    using Point = Utils::Point;
public:
    CheckPathCase() : mutex_(), pathData_(), show_(false) {}

    void SetPathData(const PathData& pathData) {
        std::lock_guard lock(mutex_);
        pathData_ = pathData;
    }

    PathData GetPathData() {
        std::lock_guard lock(mutex_);
        return pathData_;
    }

    void SetShow(bool show) {
        std::lock_guard lock(mutex_);
        fprintf(stderr, "Trying set show\n");
        show_ = show;
    }

    bool IsShow() {
        std::lock_guard lock(mutex_);
        return show_;
    }

    bool CheckLandIntersection(const Point& p1, const Point& p2) const {
        static constexpr double EPS = 1e-5;

        Point minCorner{std::min(p1.Lat, p2.Lat), std::min(p1.Lon, p2.Lon)};
        Point maxCorner{std::max(p1.Lat, p2.Lat), std::max(p1.Lon, p2.Lon)};
        minCorner.Lat -= EPS;
        minCorner.Lon -= EPS;
        maxCorner.Lat += EPS;
        maxCorner.Lon += EPS;

        return PlugIn_GSHHS_CrossesLand(minCorner.Lat, minCorner.Lon, maxCorner.Lat, maxCorner.Lon);
    }

    bool CheckDepth(const DepthGrid& grid, const Point& p, double draft) const {
        auto depth = grid.GetDetph(p);

        if (depth.has_value()) {
            return depth >= draft; // TODO perhaps it needs to be taken into account with some margin
        }

        return true;
    }

    std::optional<wxPoint2DDouble> CrossDetect(const PathData& pathData_) const {
        static constexpr int ITER_NUM = 50;
        const Point start = pathData_.Start;
        const Point end = pathData_.End; 
        std::optional<DepthGrid> grid;
        if (pathData_.PathToDepthFile.has_value() && pathData_.ShipDraft.has_value()) {
            grid = DepthGrid(pathData_.PathToDepthFile.value());
        }

        if (!CheckLandIntersection(start, end)) {
            return std::nullopt;
        }

        Utils::Point vec = pathData_.End - pathData_.Start;

        for(int i = 0; i <= ITER_NUM; ++i) {
            double k = static_cast<double>(i) / ITER_NUM;
            Point p = start + vec * k;

            if (grid.has_value() && !CheckDepth(grid.value(), p, pathData_.ShipDraft.value())) {
                return wxPoint2DDouble(p.X(), p.Y());
            }

            if (CheckLandIntersection(pathData_.Start, p)) {
                return wxPoint2DDouble(p.X(), p.Y());
            }
        }
        return std::nullopt;
    }

private:
    std::mutex mutex_;
    PathData pathData_;
    bool show_;
};

} // namespace MarineNavi
