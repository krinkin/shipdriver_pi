#pragma once

#include <mutex>

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
        show_ = show;
    }

    bool IsShow() {
        std::lock_guard lock(mutex_);
        return show_;
    }

private:
    std::mutex mutex_;
    PathData pathData_;
    bool show_;
};

} // namespace MarineNavi
