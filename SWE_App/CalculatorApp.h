#pragma once
#include <wx/wx.h>

class CalculatorApp : public wxApp
{
public:
    virtual bool OnInit();
};

class CalculatorFrame : public wxFrame
{
public:
    CalculatorFrame(const wxString& title);
private:
    void CreateCalculatorUI();
    void OnButtonClick(wxCommandEvent& event);
    void OnClear(wxCommandEvent& event);
    void OnBackspace(wxCommandEvent& event);
    void OnEquals(wxCommandEvent& event);
    void EvaluateExpression();

    wxTextCtrl* display;
    wxDECLARE_EVENT_TABLE();
};
