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
        fprintf(stderr, "Check is show\n");
        return show_;
    }

    std::optional<wxPoint2DDouble> CrossDetect(const PathData& pathData_) {
        static constexpr int ITER_NUM = 30;

        wxPoint2DDouble start = wxPoint2DDouble(pathData_.StartLat, pathData_.StartLat);
        wxPoint2DDouble end = wxPoint2DDouble(pathData_.EndLat, pathData_.EndLat);
        wxPoint2DDouble vec = end - start;
        
        if (!PlugIn_GSHHS_CrossesLand(start.m_x, start.m_y, end.m_x, end.m_y)) {
            return std::nullopt;
        }

        for(int i = 0; i < ITER_NUM; ++i) {
            vec /= 2;
            auto mid = start + vec;
            if (PlugIn_GSHHS_CrossesLand(start.m_x, start.m_y, mid.m_x, mid.m_y)) {
                end = mid;
            } else {
                start = mid;
            }
        }
        return end;
    }

private:
    std::mutex mutex_;
    PathData pathData_;
    bool show_;
};

} // namespace MarineNavi
