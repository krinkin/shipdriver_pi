#pragma once

#include <ocpn_plugin.h>

#include <wx/wx.h>

#include <mutex>
#include <optional>

namespace MarineNavi {

struct PathData {
    double StartLat;
    double StartLon;

    double EndLat;
    double EndLon;
};

class CheckPathCase {
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

    std::optional<wxPoint2DDouble> CrossDetect(const PathData& pathData_) const {
        static constexpr int ITER_NUM = 30;

        double origX = pathData_.StartLat, origY = pathData_.StartLon;
        double startX = pathData_.StartLat, startY = pathData_.StartLon;
        double endX = pathData_.EndLat, endY = pathData_.EndLon;
        double vecX = endX - startX, vecY = endY - startY;

        // wxPoint2DDouble start = wxPoint2DDouble(pathData_.StartLat, pathData_.StartLon);
        // wxPoint2DDouble end = wxPoint2DDouble(pathData_.EndLat, pathData_.EndLat);
        // wxPoint2DDouble vec = end - start;
        
        if (!PlugIn_GSHHS_CrossesLand(startX, startY, endX, endY)) {
            return std::nullopt;
        }

        fprintf(stderr, "Collision detected %f %f %f %f\n", startX, startY, endX, endY);

        for(int i = 0; i < ITER_NUM; ++i) {
            vecX /= 2;
            vecY /= 2;
            double midX = startX + vecX;
            double midY = startY + vecY;

            if (PlugIn_GSHHS_CrossesLand(origX, origY, midX, midY)) {
                endX = midX;
                endY = midY;
            } else {
                startX = midX;
                startY = midY;
            }
        }
        return wxPoint2DDouble(endX, endY);
    }

private:
    std::mutex mutex_;
    PathData pathData_;
    bool show_;
};

} // namespace MarineNavi
