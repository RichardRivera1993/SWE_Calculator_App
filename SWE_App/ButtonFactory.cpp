#include "ButtonFactory.h"

// Generic button creation method
wxButton* ButtonFactory::CreateButton(wxWindow* parent, wxWindowID id, const wxString& label, wxSize size)
{
    return new wxButton(parent, id, label, wxDefaultPosition, size, 0);
}

// Specific button creation methods
wxButton* ButtonFactory::CreateNumberButton(wxWindow* parent, int number)
{
    return CreateButton(parent, wxWindowID(1000 + number), std::to_string(number), wxSize(50, 50));
}

wxButton* ButtonFactory::CreateAddButton(wxWindow* parent)
{
    return CreateButton(parent, wxWindowID(1010), "+", wxSize(50, 50));
}

wxButton* ButtonFactory::CreateSubtractButton(wxWindow* parent)
{
    return CreateButton(parent, wxWindowID(1011), "-", wxSize(50, 50));
}

wxButton* ButtonFactory::CreateMultiplyButton(wxWindow* parent)
{
    return CreateButton(parent, wxWindowID(1012), "*", wxSize(50, 50));
}

wxButton* ButtonFactory::CreateDivideButton(wxWindow* parent)
{
    return CreateButton(parent, wxWindowID(1013), "/", wxSize(50, 50));
}

wxButton* ButtonFactory::CreateModuloButton(wxWindow* parent)
{
    return CreateButton(parent, wxWindowID(1014), "%", wxSize(50, 50));
}

wxButton* ButtonFactory::CreateEqualsButton(wxWindow* parent)
{
    return CreateButton(parent, wxWindowID(1015), "=", wxSize(50, 50));
}

wxButton* ButtonFactory::CreateClearButton(wxWindow* parent)
{
    return CreateButton(parent, wxWindowID(1016), "C", wxSize(50, 50));
}

wxButton* ButtonFactory::CreateBackspaceButton(wxWindow* parent)
{
    return CreateButton(parent, wxWindowID(1017), "Del", wxSize(50, 50));
}

wxButton* ButtonFactory::CreateDecimalButton(wxWindow* parent)
{
    return CreateButton(parent, wxWindowID(1018), ".", wxSize(50, 50));
}

wxButton* ButtonFactory::CreateUnaryOperationButton(wxWindow* parent, const wxString& label)
{
    int id = (label == "sin") ? 1019 : (label == "cos") ? 1020 : 1021;
    return CreateButton(parent, wxWindowID(id), label, wxSize(50, 50));
}

wxButton* ButtonFactory::CreateNegativeButton(wxWindow* parent)
{
    return CreateButton(parent, wxWindowID(1022), "+/-", wxSize(50,50));
}

wxButton* ButtonFactory::CreateLeftParenthesisButton(wxWindow* parent)
{
    return CreateButton(parent, wxWindowID(1023), "(", wxSize(50, 50));
}

wxButton* ButtonFactory::CreateRightParenthesisButton(wxWindow* parent)
{
    return CreateButton(parent, wxWindowID(1024), ")", wxSize(50, 50));
}
