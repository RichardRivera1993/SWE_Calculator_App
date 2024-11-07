#include "CalculatorApp.h"

wxIMPLEMENT_APP(CalculatorApp);

bool CalculatorApp::OnInit()
{
    CalculatorFrame* frame = new CalculatorFrame("Calculator");
    frame->Show(true);
    return true;
}

CalculatorFrame::CalculatorFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 500))
{
    CreateCalculatorUI();
}
void CalculatorFrame::CreateCalculatorUI()
{
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // This creates the display for showing calculations
    wxTextCtrl* display = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(400, 50), wxTE_RIGHT);
    vbox->Add(display, 0, wxEXPAND | wxALL, 10);

    // This creates grid sizer for buttons (setting rows to 0 so that wxwidgets will calculate the required rows based on the number of columns, just in case I want to add or remove buttons later.)
    wxGridSizer* grid = new wxGridSizer(0, 4, 10, 10);

    // This adds number buttons (0-9) to the grid
    for (int i = 1; i <= 9; ++i) {
        wxButton* button = new wxButton(this, wxID_ANY, std::to_string(i));
        grid->Add(button, 0, wxEXPAND);
    }

    // This adds the remaining UI elements
    grid->Add(new wxButton(this, wxID_ANY, "0"), 0, wxEXPAND);
    grid->Add(new wxButton(this, wxID_ANY, "."), 0, wxEXPAND);
    grid->Add(new wxButton(this, wxID_ANY, "+"), 0, wxEXPAND);
    grid->Add(new wxButton(this, wxID_ANY, "-"), 0, wxEXPAND);
    grid->Add(new wxButton(this, wxID_ANY, "*"), 0, wxEXPAND);
    grid->Add(new wxButton(this, wxID_ANY, "/"), 0, wxEXPAND);
    grid->Add(new wxButton(this, wxID_ANY, "%"), 0, wxEXPAND);
    grid->Add(new wxButton(this, wxID_ANY, "sin"), 0, wxEXPAND);
    grid->Add(new wxButton(this, wxID_ANY, "cos"), 0, wxEXPAND);
    grid->Add(new wxButton(this, wxID_ANY, "tan"), 0, wxEXPAND);
    grid->Add(new wxButton(this, wxID_ANY, "="), 0, wxEXPAND);
    grid->Add(new wxButton(this, wxID_ANY, "C"), 0, wxEXPAND); // Clear
    grid->Add(new wxButton(this, wxID_ANY, "Del"), 0, wxEXPAND); // Backspace/Delete
    grid->Add(new wxButton(this, wxID_ANY, "+/-"), 0, wxEXPAND); // Negative symbol

    // This adds grid sizer to the main vertical sizer
    vbox->Add(grid, 1, wxEXPAND | wxALL, 10);

    // This sets the main sizer for the frame
    this->SetSizer(vbox);
}
