#pragma once
#include <wx/wx.h>


class TestApp: public wxApp
{
public:
	virtual bool OnInit() override { return true; }
};
wxDECLARE_APP(TestApp);

