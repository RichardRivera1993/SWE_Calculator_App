#include "C:\Users\dabig\source\repos\SWE_App\SWE_App\ButtonFactory.h"
#include "CppUnitTest.h"
#include "TestApp.h"
#include <wx/button.h>
#include <wx/frame.h>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorAppTests
{
    // This defines a test class for ButtonFactory
    TEST_CLASS(ButtonFactoryTests)
    {
    public:
        // Static parent frame shared across all tests
        static wxFrame* parent;

        // Initialize method runs before each test
        TEST_METHOD_INITIALIZE(Initialize)
        {
            // Initialize wxWidgets only once
            if (!wxTheApp)
            {
                int argc = 0;
                char** argv = nullptr;
                wxEntryStart(argc, argv);
                wxTheApp->CallOnInit();
            }

            // Create a parent frame if not already created
            if (!parent)
            {
                parent = new wxFrame(nullptr, wxID_ANY, "Test Frame");
                parent->Show(false); // Keep the frame hidden
            }
        }

        // Set up a clean up method to run after each test.
        TEST_METHOD_CLEANUP(Cleanup)
        {
   
        }

        // Testing creation of number buttons.
        TEST_METHOD(TestCreateNumberButton)
        {
            int number = 5;
            wxButton* button = ButtonFactory::CreateNumberButton(parent, number);
            Assert::IsNotNull(button, L"Button should not be null.");
            Assert::AreEqual(wxWindowID(1000 + number), button->GetId(), L"Button ID mismatch.");
            Assert::AreEqual(std::to_string(number), std::string(button->GetLabel().mb_str()), L"Button label mismatch.");
            Assert::AreEqual(50, button->GetSize().GetWidth(), L"Button width mismatch.");
            Assert::AreEqual(50, button->GetSize().GetHeight(), L"Button height mismatch.");
            delete button; // Clean up
        }

        // Testing creation of Add button.
        TEST_METHOD(TestCreateAddButton)
        {
            wxButton* button = ButtonFactory::CreateAddButton(parent);
            Assert::IsNotNull(button, L"Add Button should not be null.");
            Assert::AreEqual(wxWindowID(1010), button->GetId(), L"Add Button ID mismatch.");
            Assert::AreEqual(std::string("+"), std::string(button->GetLabel().mb_str()), L"Add Button label mismatch.");
            Assert::AreEqual(50, button->GetSize().GetWidth(), L"Add Button width mismatch.");
            Assert::AreEqual(50, button->GetSize().GetHeight(), L"Add Button height mismatch.");
            delete button;
        }

        // Testing creation of Subtract button.
        TEST_METHOD(TestCreateSubtractButton)
        {
            wxButton* button = ButtonFactory::CreateSubtractButton(parent);
            Assert::IsNotNull(button, L"Subtract Button should not be null.");
            Assert::AreEqual(wxWindowID(1011), button->GetId(), L"Subtract Button ID mismatch.");
            Assert::AreEqual(std::string("-"), std::string(button->GetLabel().mb_str()), L"Subtract Button label mismatch.");
            Assert::AreEqual(50, button->GetSize().GetWidth(), L"Subtract Button width mismatch.");
            Assert::AreEqual(50, button->GetSize().GetHeight(), L"Subtract Button height mismatch.");
            delete button;
        }

        // Testing creation of Multiply button.
        TEST_METHOD(TestCreateMultiplyButton)
        {
            wxButton* button = ButtonFactory::CreateMultiplyButton(parent);
            Assert::IsNotNull(button, L"Multiply Button should not be null.");
            Assert::AreEqual(wxWindowID(1012), button->GetId(), L"Multiply Button ID mismatch.");
            Assert::AreEqual(std::string("*"), std::string(button->GetLabel().mb_str()), L"Multiply Button label mismatch.");
            Assert::AreEqual(50, button->GetSize().GetWidth(), L"Multiply Button width mismatch.");
            Assert::AreEqual(50, button->GetSize().GetHeight(), L"Multiply Button height mismatch.");
            delete button;
        }

        // Testing creation of Divide button.
        TEST_METHOD(TestCreateDivideButton)
        {
            wxButton* button = ButtonFactory::CreateDivideButton(parent);
            Assert::IsNotNull(button, L"Divide Button should not be null.");
            Assert::AreEqual(wxWindowID(1013), button->GetId(), L"Divide Button ID mismatch.");
            Assert::AreEqual(std::string("/"), std::string(button->GetLabel().mb_str()), L"Divide Button label mismatch.");
            Assert::AreEqual(50, button->GetSize().GetWidth(), L"Divide Button width mismatch.");
            Assert::AreEqual(50, button->GetSize().GetHeight(), L"Divide Button height mismatch.");
            delete button;
        }

        // Testing creation of Modulo button.
        TEST_METHOD(TestCreateModuloButton)
        {
            wxButton* button = ButtonFactory::CreateModuloButton(parent);
            Assert::IsNotNull(button, L"Modulo Button should not be null.");
            Assert::AreEqual(wxWindowID(1014), button->GetId(), L"Modulo Button ID mismatch.");
            Assert::AreEqual(std::string("%"), std::string(button->GetLabel().mb_str()), L"Modulo Button label mismatch.");
            Assert::AreEqual(50, button->GetSize().GetWidth(), L"Modulo Button width mismatch.");
            Assert::AreEqual(50, button->GetSize().GetHeight(), L"Modulo Button height mismatch.");
            delete button;
        }

        // Testing creation of Equals button.
        TEST_METHOD(TestCreateEqualsButton)
        {
            wxButton* button = ButtonFactory::CreateEqualsButton(parent);
            Assert::IsNotNull(button, L"Equals Button should not be null.");
            Assert::AreEqual(wxWindowID(1015), button->GetId(), L"Equals Button ID mismatch.");
            Assert::AreEqual(std::string("="), std::string(button->GetLabel().mb_str()), L"Equals Button label mismatch.");
            Assert::AreEqual(50, button->GetSize().GetWidth(), L"Equals Button width mismatch.");
            Assert::AreEqual(50, button->GetSize().GetHeight(), L"Equals Button height mismatch.");
            delete button;
        }

        // Testing creation of Clear button.
        TEST_METHOD(TestCreateClearButton)
        {
            wxButton* button = ButtonFactory::CreateClearButton(parent);
            Assert::IsNotNull(button, L"Clear Button should not be null.");
            Assert::AreEqual(wxWindowID(1016), button->GetId(), L"Clear Button ID mismatch.");
            Assert::AreEqual(std::string("C"), std::string(button->GetLabel().mb_str()), L"Clear Button label mismatch.");
            Assert::AreEqual(50, button->GetSize().GetWidth(), L"Clear Button width mismatch.");
            Assert::AreEqual(50, button->GetSize().GetHeight(), L"Clear Button height mismatch.");
            delete button;
        }

        // Testing creation of Backspace button.
        TEST_METHOD(TestCreateBackspaceButton)
        {
            wxButton* button = ButtonFactory::CreateBackspaceButton(parent);
            Assert::IsNotNull(button, L"Backspace Button should not be null.");
            Assert::AreEqual(wxWindowID(1017), button->GetId(), L"Backspace Button ID mismatch.");
            Assert::AreEqual(std::string("Del"), std::string(button->GetLabel().mb_str()), L"Backspace Button label mismatch.");
            Assert::AreEqual(50, button->GetSize().GetWidth(), L"Backspace Button width mismatch.");
            Assert::AreEqual(50, button->GetSize().GetHeight(), L"Backspace Button height mismatch.");
            delete button;
        }

        // Testing creation of Decimal button.
        TEST_METHOD(TestCreateDecimalButton)
        {
            wxButton* button = ButtonFactory::CreateDecimalButton(parent);
            Assert::IsNotNull(button, L"Decimal Button should not be null.");
            Assert::AreEqual(wxWindowID(1018), button->GetId(), L"Decimal Button ID mismatch.");
            Assert::AreEqual(std::string("."), std::string(button->GetLabel().mb_str()), L"Decimal Button label mismatch.");
            Assert::AreEqual(50, button->GetSize().GetWidth(), L"Decimal Button width mismatch.");
            Assert::AreEqual(50, button->GetSize().GetHeight(), L"Decimal Button height mismatch.");
            delete button;
        }

        // Testing creation of Sin button.
        TEST_METHOD(TestCreateUnaryOperationButton_Sin)
        {
            wxButton* button = ButtonFactory::CreateUnaryOperationButton(parent, "sin");
            Assert::IsNotNull(button, L"Sin Button should not be null.");
            Assert::AreEqual(wxWindowID(1019), button->GetId(), L"Sin Button ID mismatch.");
            Assert::AreEqual(std::string("sin"), std::string(button->GetLabel().mb_str()), L"Sin Button label mismatch.");
            Assert::AreEqual(50, button->GetSize().GetWidth(), L"Sin Button width mismatch.");
            Assert::AreEqual(50, button->GetSize().GetHeight(), L"Sin Button height mismatch.");
            delete button;
        }

        // Testing creation of Cos button.
        TEST_METHOD(TestCreateUnaryOperationButton_Cos)
        {
            wxButton* button = ButtonFactory::CreateUnaryOperationButton(parent, "cos");
            Assert::IsNotNull(button, L"Cos Button should not be null.");
            Assert::AreEqual(wxWindowID(1020), button->GetId(), L"Cos Button ID mismatch.");
            Assert::AreEqual(std::string("cos"), std::string(button->GetLabel().mb_str()), L"Cos Button label mismatch.");
            Assert::AreEqual(50, button->GetSize().GetWidth(), L"Cos Button width mismatch.");
            Assert::AreEqual(50, button->GetSize().GetHeight(), L"Cos Button height mismatch.");
            delete button;
        }

        // Testing creation of Tan button.
        TEST_METHOD(TestCreateUnaryOperationButton_Tan)
        {
            wxButton* button = ButtonFactory::CreateUnaryOperationButton(parent, "tan");
            Assert::IsNotNull(button, L"Tan Button should not be null.");
            Assert::AreEqual(wxWindowID(1021), button->GetId(), L"Tan Button ID mismatch.");
            Assert::AreEqual(std::string("tan"), std::string(button->GetLabel().mb_str()), L"Tan Button label mismatch.");
            Assert::AreEqual(50, button->GetSize().GetWidth(), L"Tan Button width mismatch.");
            Assert::AreEqual(50, button->GetSize().GetHeight(), L"Tan Button height mismatch.");
            delete button;
        }

        // Testing creation of Negative button.
        TEST_METHOD(TestCreateNegativeButton)
        {
            wxButton* button = ButtonFactory::CreateNegativeButton(parent);
            Assert::IsNotNull(button, L"Negative Button should not be null.");
            Assert::AreEqual(wxWindowID(1022), button->GetId(), L"Negative Button ID mismatch.");
            Assert::AreEqual(std::string("+/-"), std::string(button->GetLabel().mb_str()), L"Negative Button label mismatch.");
            Assert::AreEqual(50, button->GetSize().GetWidth(), L"Negative Button width mismatch.");
            Assert::AreEqual(50, button->GetSize().GetHeight(), L"Negative Button height mismatch.");
            delete button;
        }
    };

    // Initialize the static parent pointer
    wxFrame* ButtonFactoryTests::parent = nullptr;
}