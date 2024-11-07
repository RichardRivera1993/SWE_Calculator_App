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
};
