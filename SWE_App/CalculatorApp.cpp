#include "CalculatorApp.h"
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
    ID_BUTTON_DECIMAL,
    ID_BUTTON_ADD,
    ID_BUTTON_MINUS,
    ID_BUTTON_MULTIPLY,
    ID_BUTTON_DIVIDE,
    ID_BUTTON_MODULO,
    ID_BUTTON_SIN,
    ID_BUTTON_COS,
    ID_BUTTON_TAN,
    ID_BUTTON_EQUALS,
    ID_BUTTON_CLEAR,
    ID_BUTTON_BACKSPACE,
    ID_BUTTON_NEGATIVE
};

wxBEGIN_EVENT_TABLE(CalculatorFrame, wxFrame)
EVT_BUTTON(ID_BUTTON_0, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_1, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_2, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_3, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_4, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_5, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_6, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_7, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_8, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_9, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_DECIMAL, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_ADD, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_MINUS, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_MULTIPLY, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_DIVIDE, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_MODULO, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_SIN, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_COS, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_TAN, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_NEGATIVE, CalculatorFrame::OnButtonClick)
EVT_BUTTON(ID_BUTTON_CLEAR, CalculatorFrame::OnClear)
EVT_BUTTON(ID_BUTTON_BACKSPACE, CalculatorFrame::OnBackspace)
EVT_BUTTON(ID_BUTTON_EQUALS, CalculatorFrame::OnEquals)

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

    // This creates grid sizer for buttons (setting rows to 0 so that wxwidgets will calculate the required rows based on the number of columns, just in case I want to add or remove buttons later.)
    wxGridSizer* grid = new wxGridSizer(0, 4, 10, 10);

    // This adds number buttons (0-9) to the grid
    grid->Add(new wxButton(this, ID_BUTTON_0, "0"), 0, wxEXPAND);
    for (int i = 1; i <= 9; ++i) {
        wxButton* button = new wxButton(this, ID_BUTTON_1 + i - 1, std::to_string(i));
        grid->Add(button, 0, wxEXPAND);
    }


    // This adds the remaining UI elements
    grid->Add(new wxButton(this, ID_BUTTON_DECIMAL, "."), 0, wxEXPAND);
    grid->Add(new wxButton(this, ID_BUTTON_ADD, "+"), 0, wxEXPAND);
    grid->Add(new wxButton(this, ID_BUTTON_MINUS, "-"), 0, wxEXPAND);
    grid->Add(new wxButton(this, ID_BUTTON_MULTIPLY, "*"), 0, wxEXPAND);
    grid->Add(new wxButton(this, ID_BUTTON_DIVIDE, "/"), 0, wxEXPAND);
    grid->Add(new wxButton(this, ID_BUTTON_MODULO, "%"), 0, wxEXPAND);
    grid->Add(new wxButton(this, ID_BUTTON_SIN, "sin"), 0, wxEXPAND);
    grid->Add(new wxButton(this, ID_BUTTON_COS, "cos"), 0, wxEXPAND);
    grid->Add(new wxButton(this, ID_BUTTON_TAN, "tan"), 0, wxEXPAND);
    grid->Add(new wxButton(this, ID_BUTTON_EQUALS, "="), 0, wxEXPAND);
    grid->Add(new wxButton(this, ID_BUTTON_CLEAR, "C"), 0, wxEXPAND); // Clear
    grid->Add(new wxButton(this, ID_BUTTON_BACKSPACE, "Del"), 0, wxEXPAND); // Backspace
    grid->Add(new wxButton(this, ID_BUTTON_NEGATIVE, "+/-"), 0, wxEXPAND); // Negative symbol

    // This adds grid sizer to the main vertical sizer
    vbox->Add(grid, 1, wxEXPAND | wxALL, 10);

    // This sets the main sizer for the frame
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
    case ID_BUTTON_ADD: label = "+"; break;
    case ID_BUTTON_MINUS: label = "-"; break;
    case ID_BUTTON_MULTIPLY: label = "*"; break;
    case ID_BUTTON_DIVIDE: label = "/"; break;
    case ID_BUTTON_MODULO: label = "%"; break;
    case ID_BUTTON_SIN: label = "sin "; break;
    case ID_BUTTON_COS: label = "cos "; break;
    case ID_BUTTON_TAN: label = "tan "; break;
    case ID_BUTTON_DECIMAL: label = "."; break;
    case ID_BUTTON_NEGATIVE: label = "-"; break;
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
    EvaluateExpression();
}


#include <cmath> // Include for mathematical functions like sin, cos, tan

void CalculatorFrame::EvaluateExpression()
{
    try
    {
        wxString expression = display->GetValue().Trim(true).Trim(false); // Trim whitespace
        if (expression.IsEmpty()) throw std::runtime_error("Error: Empty expression.");

        double result = 0;

        // Check if the expression starts with a unary function
        if (expression.StartsWith("sin")) {
            wxString argument = expression.Mid(3).Trim();
            double value = wxAtof(argument);
            result = std::sin(value); // Assumes input is in radians
        }
        else if (expression.StartsWith("cos")) {
            wxString argument = expression.Mid(3).Trim();
            double value = wxAtof(argument);
            result = std::cos(value); // Assumes input is in radians
        }
        else if (expression.StartsWith("tan")) {
            wxString argument = expression.Mid(3).Trim();
            double value = wxAtof(argument);
            result = std::tan(value); // Assumes input is in radians
        }
        else {
            int operatorPos = -1;
            wxString operation;
            bool isUnaryNegation = (expression[0] == '-'); // Start by checking for initial unary negation
            int startIdx = isUnaryNegation ? 1 : 0;

            bool operatorFound = false;

            // Scan for the main operator in the expression
            for (int i = startIdx; i < expression.length(); ++i) {
                // Check if current character is an operator (excluding unary negation at the start)
                if (expression[i] == '+' || expression[i] == '*' || expression[i] == '/' || expression[i] == '%') {
                    if (operatorFound) {
                        throw std::runtime_error("Error: Multiple consecutive operators are not allowed.");
                    }
                    operatorPos = i;
                    operation = expression[i];
                    operatorFound = true;
                }
                else if (expression[i] == '-') {
                    // Allow "-" as subtraction if an operator has already been found
                    if (operatorFound) {
                        operatorPos = i;
                        operation = '-';
                        break;
                    }
                    else if (i > 0 && wxIsdigit(expression[i - 1])) {
                        // If "-" follows a number, treat it as a subtraction operator
                        operatorPos = i;
                        operation = '-';
                        break;
                    }
                    else {
                        // Otherwise, treat it as part of a negative number
                        operatorFound = true;
                    }
                }
                else if (wxIsdigit(expression[i]) || expression[i] == '.') {
                    operatorFound = false;
                }
            }

            // Check if an operator was found
            if (operatorPos == -1) {
                throw std::runtime_error("Error: Missing operator.");
            }

            // Extract the first number, allowing for initial unary negation
            wxString num1Str = expression.Mid(0, operatorPos).Trim();
            double num1 = wxAtof(num1Str);

            // Extract the second number, allowing for unary negation
            wxString num2Str = expression.Mid(operatorPos + 1).Trim();
            if (num2Str.StartsWith("-")) {
                // Handle cases like "1 - -3" by keeping the negative sign in num2
                num2Str = "-" + num2Str.Mid(1).Trim();
            }
            double num2 = wxAtof(num2Str);

            // Validate that both operands are provided
            if (num1Str.IsEmpty() || num2Str.IsEmpty()) {
                throw std::runtime_error("Error: Missing operand(s).");
            }

            // Perform calculation based on the operator
            if (operation == "+") result = num1 + num2;
            else if (operation == "-") result = num1 - num2;
            else if (operation == "*") result = num1 * num2;
            else if (operation == "/") {
                if (num2 == 0) throw std::runtime_error("Error: Division by zero.");
                result = num1 / num2;
            }
            else if (operation == "%") {
                if (num2 == 0) throw std::runtime_error("Error: Modulo by zero.");
                result = static_cast<int>(num1) % static_cast<int>(num2);
            }
            else {
                throw std::runtime_error("Error: Invalid operation.");
            }
        }

        // Display the result with appropriate formatting
        if (result == static_cast<int>(result)) {
            // If result is a whole number, show without decimal places
            display->SetValue(wxString::Format("%d", static_cast<int>(result)));
        }
        else {
            // If result has a decimal part, show with limited precision
            display->SetValue(wxString::Format("%.6f", result));
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
















