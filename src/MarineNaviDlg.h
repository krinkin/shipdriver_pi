#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/gauge.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/tglbtn.h>
#include <wx/stattext.h>
#include <wx/statbox.h>
#include <wx/timer.h>
#include <wx/dialog.h>
#include <wx/checkbox.h>

#include "wx/sizer.h"
#include "wx/stattext.h"
#include "wx/wx.h"

#include <memory>
#include <unordered_map>
#include <vector>

namespace MarineNavi {

class MarineNaviDlgBase : public wxDialog {
public:
    enum class EventType {
        kClose,
    };

public:
    MarineNaviDlgBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxDialog( parent, id, title, pos, size, wxRESIZE_BORDER) {
        
        this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MarineNaviDlgBase::OnClose));
    }

    void Register(std::function<void(void)> func, EventType event) {
        callbacks_[event].push_back(func);
    }

protected:
    virtual void OnClose(wxCloseEvent& event) {
        for(auto& callback : callbacks_[EventType::kClose]) {
            callback();
        }
    }

private:
    std::unordered_map<EventType, std::vector<std::function<void(void)>>> callbacks_;

};

class MarineNaviMainDlg : public MarineNaviDlgBase {
public:
    MarineNaviMainDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size)
        : MarineNaviDlgBase(parent, id, title, pos, size) {

        auto fgSizer = new wxFlexGridSizer(0, 2, 0, 0);
        fgSizer->AddGrowableCol(1);
        fgSizer->SetFlexibleDirection(wxBOTH);
        fgSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
        
        fgSizer->Add(new wxStaticText(this, wxID_ANY, _("Start point lat")));
        fgSizer->Add(new wxTextCtrl(this, wxID_ANY));
        fgSizer->Add(new wxStaticText(this, wxID_ANY, _("Start point lon")));
        fgSizer->Add(new wxTextCtrl(this, wxID_ANY));
        fgSizer->Add(new wxStaticText(this, wxID_ANY, _("End point lat")));
        fgSizer->Add(new wxTextCtrl(this, wxID_ANY));
        fgSizer->Add(new wxStaticText(this, wxID_ANY, _("End point lon")));
        fgSizer->Add(new wxTextCtrl(this, wxID_ANY));

        SetSizerAndFit(fgSizer);
        this->Centre( wxBOTH );
    }

private:
    // wxStaticBoxSizer* startLoc_;
    // wxStaticBoxSizer* endLoc_;
    // wxTextCtrl* startLat_;
    // wxTextCtrl* startLon_;
    // wxTextCtrl* endLat_;
    // wxTextCtrl* endLon_;  
};

};
