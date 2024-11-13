#include "CalculatorApp.h"
#include "ButtonFactory.h"
#include "CalculatorProcessor.h"
#include <wx/tokenzr.h>
#include <cmath>

wxIMPLEMENT_APP(CalculatorApp);



enum
{
    ID_BUTTON_0 = 1000,
    ID_BUTTON_1,
    ID_BUTTON_2,
    ID_BUTTON_3,
    ID_BUTTON_4,
    ID_BUTTON_5,
    ID_BUTTON_6,
    ID_BUTTON_7,
    ID_BUTTON_8,
    ID_BUTTON_9,
    ID_BUTTON_ADD,
    ID_BUTTON_MINUS,
    ID_BUTTON_MULTIPLY,
    ID_BUTTON_DIVIDE,
    ID_BUTTON_MODULO,
    ID_BUTTON_EQUALS,
    ID_BUTTON_CLEAR,
    ID_BUTTON_BACKSPACE,
    ID_BUTTON_DECIMAL,
    ID_BUTTON_SIN,
    ID_BUTTON_COS,
    ID_BUTTON_TAN,
    ID_BUTTON_NEGATIVE
};

wxBEGIN_EVENT_TABLE(CalculatorFrame, wxFrame)
// Number Buttons
EVT_BUTTON(1000, CalculatorFrame::OnButtonClick) // Button 0
EVT_BUTTON(1001, CalculatorFrame::OnButtonClick) // Button 1
EVT_BUTTON(1002, CalculatorFrame::OnButtonClick) // Button 2
EVT_BUTTON(1003, CalculatorFrame::OnButtonClick) // Button 3
EVT_BUTTON(1004, CalculatorFrame::OnButtonClick) // Button 4
EVT_BUTTON(1005, CalculatorFrame::OnButtonClick) // Button 5
EVT_BUTTON(1006, CalculatorFrame::OnButtonClick) // Button 6
EVT_BUTTON(1007, CalculatorFrame::OnButtonClick) // Button 7
EVT_BUTTON(1008, CalculatorFrame::OnButtonClick) // Button 8
EVT_BUTTON(1009, CalculatorFrame::OnButtonClick) // Button 9

// Operation Buttons
EVT_BUTTON(1010, CalculatorFrame::OnButtonClick) // Addition
EVT_BUTTON(1011, CalculatorFrame::OnButtonClick) // Subtraction
EVT_BUTTON(1012, CalculatorFrame::OnButtonClick) // Multiplication
EVT_BUTTON(1013, CalculatorFrame::OnButtonClick) // Division
EVT_BUTTON(1014, CalculatorFrame::OnButtonClick) // Modulo

// Function Buttons
EVT_BUTTON(1015, CalculatorFrame::OnEquals)       // Equals
EVT_BUTTON(1016, CalculatorFrame::OnClear)        // Clear
EVT_BUTTON(1017, CalculatorFrame::OnBackspace)    // Backspace
EVT_BUTTON(1018, CalculatorFrame::OnButtonClick)  // Decimal Point
EVT_BUTTON(1019, CalculatorFrame::OnButtonClick)  // Sin
EVT_BUTTON(1020, CalculatorFrame::OnButtonClick)  // Cos
EVT_BUTTON(1021, CalculatorFrame::OnButtonClick)  // Tan
EVT_BUTTON(1022, CalculatorFrame::OnButtonClick)  // Negative
wxEND_EVENT_TABLE()



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
    display = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(400, 50), wxTE_RIGHT);
    vbox->Add(display, 0, wxEXPAND | wxALL, 10);

    wxGridSizer* grid = new wxGridSizer(0, 4, 10, 10);

    // Add number buttons (0-9)
    grid->Add(ButtonFactory::CreateNumberButton(this, 0), 0, wxEXPAND);
    for (int i = 1; i <= 9; ++i) {
        grid->Add(ButtonFactory::CreateNumberButton(this, i), 0, wxEXPAND);
    }

    // Add operation and function buttons
    grid->Add(ButtonFactory::CreateDecimalButton(this), 0, wxEXPAND);
    grid->Add(ButtonFactory::CreateAddButton(this), 0, wxEXPAND);
    grid->Add(ButtonFactory::CreateSubtractButton(this), 0, wxEXPAND);
    grid->Add(ButtonFactory::CreateMultiplyButton(this), 0, wxEXPAND);
    grid->Add(ButtonFactory::CreateDivideButton(this), 0, wxEXPAND);
    grid->Add(ButtonFactory::CreateModuloButton(this), 0, wxEXPAND);
    grid->Add(ButtonFactory::CreateUnaryOperationButton(this, "sin"), 0, wxEXPAND);
    grid->Add(ButtonFactory::CreateUnaryOperationButton(this, "cos"), 0, wxEXPAND);
    grid->Add(ButtonFactory::CreateUnaryOperationButton(this, "tan"), 0, wxEXPAND);
    grid->Add(ButtonFactory::CreateEqualsButton(this), 0, wxEXPAND);
    grid->Add(ButtonFactory::CreateClearButton(this), 0, wxEXPAND);
    grid->Add(ButtonFactory::CreateBackspaceButton(this), 0, wxEXPAND);
    grid->Add(ButtonFactory::CreateNegativeButton(this), 0, wxEXPAND);

    vbox->Add(grid, 1, wxEXPAND | wxALL, 10);
    this->SetSizer(vbox);
}


void CalculatorFrame::OnButtonClick(wxCommandEvent& event)
{
    int id = event.GetId();
    wxString label;

    switch (id)
    {
    case ID_BUTTON_0: label = "0"; break;
    case ID_BUTTON_1: label = "1"; break;
    case ID_BUTTON_2: label = "2"; break;
    case ID_BUTTON_3: label = "3"; break;
    case ID_BUTTON_4: label = "4"; break;
    case ID_BUTTON_5: label = "5"; break;
    case ID_BUTTON_6: label = "6"; break;
    case ID_BUTTON_7: label = "7"; break;
    case ID_BUTTON_8: label = "8"; break;
    case ID_BUTTON_9: label = "9"; break;
    case ID_BUTTON_DECIMAL: label = "."; break; // Decimal
    case ID_BUTTON_ADD: label = "+"; break;     // Addition
    case ID_BUTTON_MINUS: label = "-"; break;   // Subtraction
    case ID_BUTTON_MULTIPLY: label = "*"; break;// Multiplication
    case ID_BUTTON_DIVIDE: label = "/"; break;  // Division
    case ID_BUTTON_MODULO: label = "%"; break;  // Modulo
    case ID_BUTTON_SIN: label = "sin "; break;  // Sin function
    case ID_BUTTON_COS: label = "cos "; break;  // Cos function
    case ID_BUTTON_TAN: label = "tan "; break;  // Tan function
    case ID_BUTTON_NEGATIVE:                   // Negative symbol handling
    {
        wxString currentText = display->GetValue();

        // Find the position of the last operator in the expression
        int lastOperatorPos = -1;
        for (int i = currentText.length() - 1; i >= 0; --i) {
            if (currentText[i] == '+' || currentText[i] == '-' ||
                currentText[i] == '*' || currentText[i] == '/' ||
                currentText[i] == '%') {
                lastOperatorPos = i;
                break;
            }
        }

        // Determine the starting position of the last operand
        int operandStart = (lastOperatorPos == -1) ? 0 : lastOperatorPos + 1;

        // Check if the operandStart is within the range of the current text
        if (operandStart < currentText.length()) {
            // Check if the last operand already has a negative symbol
            if (currentText[operandStart] == '_') {
                // Remove the negative symbol for the last operand
                currentText.Remove(operandStart, 1);
            }
            else {
                // Add the negative symbol at the beginning of the last operand
                currentText.insert(operandStart, "_");
            }
        }

        display->SetValue(currentText);
        return;
    }
    case ID_BUTTON_EQUALS:
        OnEquals(event);
        return;
    case ID_BUTTON_BACKSPACE:
        OnBackspace(event);
        return;
    case ID_BUTTON_CLEAR:
        OnClear(event);
        return;
    }

    display->AppendText(label); // Adds the label to the display
}


void CalculatorFrame::OnClear(wxCommandEvent& event)
{
    if (display) {
        display->Clear();
    }
}

void CalculatorFrame::OnBackspace(wxCommandEvent& event)
{
    // Get the current text in the display
    wxString currentText = display->GetValue();

    // Check if the text box is empty
    if (currentText.IsEmpty()) {
        // Display a message to the user
        wxMessageBox("The text box is already empty.", "Backspace Error", wxICON_WARNING);
        return; // Exit the function early
    }

    // Remove the last character from the text box
    currentText.RemoveLast();
    display->SetValue(currentText);
}


void CalculatorFrame::OnEquals(wxCommandEvent& event)
{
    wxString expression = display->GetValue().Trim(true).Trim(false);
    expression.Replace("-", " - ");
    expression.Replace("+", " + ");
    expression.Replace("*", " * ");
    expression.Replace("/", " / ");
    expression.Replace("%", " % ");

    std::string expr = expression.ToStdString();

    try {
        double result = CalculatorProcessor::GetInstance()->Calculate(expr);

        if (result == static_cast<int>(result)) {
            display->SetValue(wxString::Format("%d", static_cast<int>(result)));
        }
        else {
            display->SetValue(wxString::Format("%.10f", result));
        }
    }
    catch (const std::runtime_error& e) {
        wxMessageBox(e.what(), "Calculation Error", wxICON_ERROR);
        display->Clear();
    }
    catch (...) {
        wxMessageBox("An unknown error occurred.", "Error", wxICON_ERROR);
        display->Clear();
    }
}


void CalculatorFrame::EvaluateExpression()
{
    try
    {
        wxString expression = display->GetValue().Trim(true).Trim(false);
        std::string expr = expression.ToStdString();

        double result = CalculatorProcessor::GetInstance()->Calculate(expr);

        if (result == static_cast<int>(result)) {
            display->SetValue(wxString::Format("%d", static_cast<int>(result)));
        }
        else {
            display->SetValue(wxString::Format("%.10f", result));
        }
    }
    catch (const std::runtime_error& e)
    {
        wxMessageBox(e.what(), "Calculation Error", wxICON_ERROR);
        display->Clear();
    }
    catch (...)
    {
        wxMessageBox("An unknown error occurred.", "Error", wxICON_ERROR);
        display->Clear();
    }
}





















