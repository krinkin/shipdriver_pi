#pragma once

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
        : wxDialog( parent, id, title, pos, size) {
        
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
        : MarineNaviDlgBase(parent, id, title, pos, size), 
        startLat_(std::make_shared<wxTextCtrl>(this, wxID_ANY, wxEmptyString)),
        startLon_(std::make_shared<wxTextCtrl>(this, wxID_ANY, wxEmptyString)),
        endLat_(std::make_shared<wxTextCtrl>(this, wxID_ANY, wxEmptyString)),
        endLon_(std::make_shared<wxTextCtrl>(this, wxID_ANY, wxEmptyString)) {
    }

private:
    std::shared_ptr<wxTextCtrl> startLat_;
    std::shared_ptr<wxTextCtrl> startLon_;
    std::shared_ptr<wxTextCtrl> endLat_;
    std::shared_ptr<wxTextCtrl> endLon_;  
};

};