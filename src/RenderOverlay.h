#pragma once

#include <pidc.h>

#include "Dependencies.h"
#include "CheckPathCase.h"


namespace MarineNavi {

class RenderOverlay {
public:
    RenderOverlay(Dependencies& deps): checkPathCase_(deps.CheckPathCase) {
    }

    bool Render(piDC& dc, PlugIn_ViewPort *vp) { 
        if (checkPathCase_->IsShow()) {
            auto pathData = checkPathCase_->GetPathData();
            RenderCheckPath(dc, vp, pathData);
            return true;
        }
        return false;
    }

private:
    void RenderCheckPath(piDC& dc, PlugIn_ViewPort *vp, const PathData& pathData) {
        dc.SetPen(wxPen(wxColor(0, 0, 0)));
        wxPen pen = dc.GetPen();
        pen.SetWidth(10);

        wxPoint2DDouble ptD;
        GetDoubleCanvasPixLL(vp, &ptD, pathData.StartLat, pathData.StartLon);
        wxPoint pt1, pt2;
        pt1.x = (int)wxRound(ptD.m_x);
        pt1.y = (int)wxRound(ptD.m_y);
        GetDoubleCanvasPixLL(vp, &ptD, pathData.EndLat, pathData.EndLon);
        pt2.x = (int)wxRound(ptD.m_x);
        pt2.y = (int)wxRound(ptD.m_y);
        dc.StrokeLine(pt1.x, pt1.y, pt2.x, pt2.y);

        auto cross = checkPathCase_->CrossDetect(pathData);
        if (cross.has_value()) {
            dc.DrawCircle(cross->m_x, cross->m_y, 10);
        }
    }

private:
std::shared_ptr<CheckPathCase> checkPathCase_;

};

} // namespace MarineNavi