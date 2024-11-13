#include "CalculatorProcessor.h"
#include <sstream>
#include <stdexcept>
#include <cctype> 

// Initialize static instance
CalculatorProcessor* CalculatorProcessor::instance = nullptr;

CalculatorProcessor* CalculatorProcessor::GetInstance()
{
    if (instance == nullptr)
        instance = new CalculatorProcessor();
    return instance;
}

double CalculatorProcessor::Calculate(const std::string& expression)
{
    auto rpnQueue = ShuntingYard(expression);
    return EvaluateRPN(rpnQueue);
}

// Shunting Yard Algorithm
std::queue<std::string> CalculatorProcessor::ShuntingYard(const std::string& expression)
{
    std::stack<std::string> operatorStack;
    std::queue<std::string> outputQueue;
    std::istringstream input(expression);
    std::string token;

    while (input >> token) {
        if (IsNumber(token)) {
            outputQueue.push(token);
        }
        else if (IsUnaryFunction(token)) {
            operatorStack.push(token);
        }
        else if (IsOperator(token)) {
            while (!operatorStack.empty() && IsOperator(operatorStack.top()) &&
                GetPrecedence(operatorStack.top()) >= GetPrecedence(token)) {
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.push(token);
        }
    }

    while (!operatorStack.empty()) {
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
    }

    return outputQueue;
}

// Evaluate Reverse Polish Notation
double CalculatorProcessor::EvaluateRPN(std::queue<std::string>& rpnQueue)
{
    std::stack<double> resultStack;

    while (!rpnQueue.empty()) {
        std::string token = rpnQueue.front();
        rpnQueue.pop();

        if (IsNumber(token)) {
            resultStack.push(std::stod(token));
        }
        else if (IsUnaryFunction(token)) {
            if (resultStack.empty()) throw std::runtime_error("Error: Missing operand for function.");
            double value = resultStack.top();
            resultStack.pop();
            if (token == "sin") value = std::sin(value);
            else if (token == "cos") value = std::cos(value);
            else if (token == "tan") value = std::tan(value);
            resultStack.push(value);
        }
        else if (IsOperator(token)) {
            if (resultStack.size() < 2) throw std::runtime_error("Error: Missing operand(s).");
            double b = resultStack.top();
            resultStack.pop();
            double a = resultStack.top();
            resultStack.pop();

            if (token == "+") resultStack.push(a + b);
            else if (token == "-") resultStack.push(a - b);
            else if (token == "*") resultStack.push(a * b);
            else if (token == "/") {
                if (b == 0) throw std::runtime_error("Error: Division by zero.");
                resultStack.push(a / b);
            }
            else if (token == "%") {
                if (b == 0) throw std::runtime_error("Error: Modulo by zero.");
                resultStack.push(static_cast<int>(a) % static_cast<int>(b));
            }
        }
    }

    if (resultStack.size() != 1) throw std::runtime_error("Error: Invalid expression.");
    return resultStack.top();
}

int CalculatorProcessor::GetPrecedence(const std::string& op)
{
    if (op == "sin" || op == "cos" || op == "tan") return 3;
    if (op == "*" || op == "/" || op == "%") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

bool CalculatorProcessor::IsOperator(const std::string& token)
{
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "%";
}

bool CalculatorProcessor::IsUnaryFunction(const std::string& token)
{
    return token == "sin" || token == "cos" || token == "tan";
}

bool CalculatorProcessor::IsNumber(const std::string& token)
{
    // Check if each character in token is a digit or a decimal point
    return !token.empty() && (std::isdigit(token[0]) || token[0] == '-' || token[0] == '_');
}
