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

    // Create the display for showing calculations
    wxTextCtrl* display = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(400, 50), wxTE_RIGHT);
    vbox->Add(display, 0, wxEXPAND | wxALL, 10);

    // Create grid sizer for buttons (5 columns to accommodate numbers and operators)
    wxGridSizer* grid = new wxGridSizer(5, 4, 10, 10);

    // Add number buttons (0-9) to the grid
    for (int i = 1; i <= 9; ++i) {
        wxButton* button = new wxButton(this, wxID_ANY, std::to_string(i));
        grid->Add(button, 0, wxEXPAND);
    }

    // Add the remaining UI elements
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

    // Add grid sizer to the main vertical sizer
    vbox->Add(grid, 1, wxEXPAND | wxALL, 10);

    // Set the main sizer for the frame
    this->SetSizer(vbox);
}
