#pragma once
#include <wx/wx.h>

class ButtonFactory
{
public:
    // Generic button creation method
    static wxButton* CreateButton(wxWindow* parent, wxWindowID id, const wxString& label, wxSize size = wxDefaultSize);

    // Specific button creation methods
    static wxButton* CreateNumberButton(wxWindow* parent, int number);
    static wxButton* CreateAddButton(wxWindow* parent);
    static wxButton* CreateSubtractButton(wxWindow* parent);
    static wxButton* CreateMultiplyButton(wxWindow* parent);
    static wxButton* CreateDivideButton(wxWindow* parent);
    static wxButton* CreateModuloButton(wxWindow* parent);
    static wxButton* CreateEqualsButton(wxWindow* parent);
    static wxButton* CreateClearButton(wxWindow* parent);
    static wxButton* CreateBackspaceButton(wxWindow* parent);
    static wxButton* CreateDecimalButton(wxWindow* parent);
    static wxButton* CreateUnaryOperationButton(wxWindow* parent, const wxString& label);
};

