#include "C:\Users\dabig\source\repos\SWE_App\SWE_App\CalculatorProcessor.h"
#include "CppUnitTest.h"
#include <stdexcept>
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorAppTests
{
    TEST_CLASS(CalculatorProcessorTests)
    {
    public:

        TEST_METHOD(TestAddition)
        {
            CalculatorProcessor* processor = CalculatorProcessor::GetInstance();
            double result = processor->Calculate("2 + 3");
            Assert::AreEqual(5.0, result, L"2 + 3 should equal 5");
        }

        TEST_METHOD(TestSubtraction)
        {
            CalculatorProcessor* processor = CalculatorProcessor::GetInstance();
            double result = processor->Calculate("5 - 2");
            Assert::AreEqual(3.0, result, L"5 - 2 should equal 3");
        }

        TEST_METHOD(TestMultiplication)
        {
            CalculatorProcessor* processor = CalculatorProcessor::GetInstance();
            double result = processor->Calculate("4 * 3");
            Assert::AreEqual(12.0, result, L"4 * 3 should equal 12");
        }

        TEST_METHOD(TestDivision)
        {
            CalculatorProcessor* processor = CalculatorProcessor::GetInstance();
            double result = processor->Calculate("10 / 2");
            Assert::AreEqual(5.0, result, L"10 / 2 should equal 5");
        }

        TEST_METHOD(TestModulo)
        {
            CalculatorProcessor* processor = CalculatorProcessor::GetInstance();
            double result = processor->Calculate("10 % 3");
            Assert::AreEqual(1.0, result, L"10 % 3 should equal 1");
        }

        TEST_METHOD(TestOrderOfOperations)
        {
            CalculatorProcessor* processor = CalculatorProcessor::GetInstance();
            double result = processor->Calculate("2 + 3 * 4");
            Assert::AreEqual(14.0, result, L"2 + 3 * 4 should equal 14");
        }

        TEST_METHOD(TestParentheses)
        {
            CalculatorProcessor* processor = CalculatorProcessor::GetInstance();
            double result = processor->Calculate("(2 + 3) * 4");
            Assert::AreEqual(20.0, result, L"(2 + 3) * 4 should equal 20");
        }

        TEST_METHOD(TestSinFunction)
        {
            CalculatorProcessor* processor = CalculatorProcessor::GetInstance();
            double result = processor->Calculate("sin 0");
            Assert::AreEqual(0.0, result, 1e-5, L"sin 0 should equal 0");
        }

        TEST_METHOD(TestCosFunction)
        {
            CalculatorProcessor* processor = CalculatorProcessor::GetInstance();
            double result = processor->Calculate("cos 0");
            Assert::AreEqual(1.0, result, 1e-5, L"cos 0 should equal 1");
        }

        TEST_METHOD(TestDivisionByZero)
        {
            CalculatorProcessor* processor = CalculatorProcessor::GetInstance();
            try {
                double result = processor->Calculate("10 / 0");
                Assert::Fail(L"Division by zero should throw an exception.");
            }
            catch (const std::runtime_error& e) {
                std::string expected = "Error: Division by zero.";
                std::string actual = e.what();
                Assert::AreEqual(expected, actual, L"Expected division by zero error.");
            }
            catch (...) {
                Assert::Fail(L"Unexpected exception type thrown.");
            }
        }
    };
}