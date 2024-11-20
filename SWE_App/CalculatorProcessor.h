#pragma once
#include <string>
#include <queue>
#include <stack>
#include <cmath>
#include <stdexcept>

class CalculatorProcessor
{
public:
    // Singleton accessor
    static CalculatorProcessor* GetInstance();

    // For testing: Reset the singleton instance
    static void ResetInstance();

    // Calculate method that takes a string expression and returns the result
    double Calculate(const std::string& expression);

private:
    // Private constructor for Singleton
    CalculatorProcessor() {}

    // Helper methods for Shunting Yard and evaluation
    std::queue<std::string> ShuntingYard(const std::string& expression);
    double EvaluateRPN(std::queue<std::string>& rpnQueue);

    // Utility functions
    int GetPrecedence(const std::string& op);
    bool IsOperator(const std::string& token);
    bool IsUnaryFunction(const std::string& token);
    bool IsNumber(const std::string& token);

    // Singleton instance
    static CalculatorProcessor* instance;
};

