#include "CalculatorProcessor.h"
#include <sstream>
#include <stdexcept>
#include <cctype> 
#include <iostream>

CalculatorProcessor* CalculatorProcessor::instance = nullptr;

CalculatorProcessor* CalculatorProcessor::GetInstance()
{
    if (instance == nullptr)
        instance = new CalculatorProcessor();
    return instance;
}

double CalculatorProcessor::Calculate(const std::string& expression)
{
    std::cout << "Expression received for calculation: " << expression << std::endl;

    // Convert to Reverse Polish Notation (RPN) using Shunting Yard algorithm
    auto rpnQueue = ShuntingYard(expression);

    std::cout << "RPN Queue: ";
    std::queue<std::string> debugQueue = rpnQueue;
    while (!debugQueue.empty()) {
        std::cout << debugQueue.front() << " ";
        debugQueue.pop();
    }
    std::cout << std::endl;

    // Evaluate the RPN expression and return the result
    return EvaluateRPN(rpnQueue);
}


std::queue<std::string> CalculatorProcessor::ShuntingYard(const std::string& expression)
{
    std::stack<std::string> operatorStack;
    std::queue<std::string> outputQueue;
    std::istringstream input(expression);
    std::string token;
    std::string prevToken; // To keep track of the previous token for unary minus detection

    std::cout << "Shunting Yard input tokens: ";
    while (input >> token) {
        std::cout << token << " ";

        if (IsNumber(token)) {
            // Push the number directly to the output queue
            outputQueue.push(token);
        }
        else if (IsUnaryFunction(token)) {
            // Push functions onto the operator stack
            operatorStack.push(token);
        }
        else if (token == "(") {
            // Push left parentheses onto the operator stack
            operatorStack.push(token);
        }
        else if (token == ")") {
            // Pop operators from the operator stack to the output queue until a left parenthesis is encountered
            while (!operatorStack.empty() && operatorStack.top() != "(") {
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }
            // Pop the left parenthesis from the operator stack
            if (!operatorStack.empty() && operatorStack.top() == "(") {
                operatorStack.pop();
            }
            else {
                throw std::runtime_error("Error: Mismatched parentheses.");
            }
        }
        else if (IsOperator(token)) {
            // Handle unary minus
            if (token == "-" && (prevToken.empty() || IsOperator(prevToken) || prevToken == "(")) {
                // Unary minus detected, treat it as a unary operator "u-"
                operatorStack.push("u-");
            }
            else {
                // Binary operator
                while (!operatorStack.empty() && (
                    (IsOperator(operatorStack.top()) && GetPrecedence(operatorStack.top()) >= GetPrecedence(token)) ||
                    (IsUnaryFunction(operatorStack.top()) && GetPrecedence(operatorStack.top()) > GetPrecedence(token))
                    )) {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.push(token);
            }
        }
        else {
            throw std::runtime_error("Error: Invalid token encountered.");
        }

        prevToken = token;
    }
    std::cout << std::endl;

    // Pop remaining operators from the operator stack to the output queue
    while (!operatorStack.empty()) {
        if (operatorStack.top() == "(" || operatorStack.top() == ")") {
            throw std::runtime_error("Error: Mismatched parentheses.");
        }
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
    }

    return outputQueue;
}




double CalculatorProcessor::EvaluateRPN(std::queue<std::string>& rpnQueue)
{
    std::stack<double> resultStack;

    std::cout << "Evaluating RPN Queue..." << std::endl;
    while (!rpnQueue.empty()) {
        std::string token = rpnQueue.front();
        rpnQueue.pop();
        std::cout << "Processing token: " << token << std::endl;

        if (IsNumber(token)) {
            std::string numberToken = token;
            if (numberToken[0] == '_') {
                numberToken[0] = '-';
            }
            resultStack.push(std::stod(numberToken));
        }
        else if (token == "_") {  // Handle `_` as unary negative
            if (resultStack.empty()) throw std::runtime_error("Error: Missing operand for unary negative.");
            double value = resultStack.top();
            resultStack.pop();
            resultStack.push(-value);  // Apply unary negation
        }
        else if (IsUnaryFunction(token)) {
            if (resultStack.empty()) throw std::runtime_error("Error: Missing operand for function.");
            double value = resultStack.top();
            resultStack.pop();
            if (token == "sin") value = std::sin(value);
            else if (token == "cos") value = std::cos(value);
            else if (token == "tan") value = std::tan(value);
            else if (token == "u-") value = -value;
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
    std::cout << "Final result: " << resultStack.top() << std::endl;
    return resultStack.top();
}



int CalculatorProcessor::GetPrecedence(const std::string& op)
{
    if (op == "sin" || op == "cos" || op == "tan") return 4;
    if (op == "u-") return 3;
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
    return token == "sin" || token == "cos" || token == "tan" || token == "u-";
}

bool CalculatorProcessor::IsNumber(const std::string& token)
{
    if (token.empty()) return false;

    // Support for underscore (_) as negative sign
    size_t start = (token[0] == '_') ? 1 : 0;
    for (size_t i = start; i < token.size(); ++i) {
        if (!std::isdigit(token[i]) && token[i] != '.') {
            return false;
        }
    }
    return true;
}
