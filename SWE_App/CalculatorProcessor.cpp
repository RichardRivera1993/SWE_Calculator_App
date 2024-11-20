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

void CalculatorProcessor::ResetInstance()
{
    if (instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}

double CalculatorProcessor::Calculate(const std::string& expression)
{
    std::queue<std::string> rpnQueue = ShuntingYard(expression);
    return EvaluateRPN(rpnQueue);
}

std::queue<std::string> CalculatorProcessor::ShuntingYard(const std::string& expression)
{
    std::queue<std::string> outputQueue;
    std::stack<std::string> operatorStack;
    size_t i = 0;
    while (i < expression.length())
    {
        if (isspace(expression[i]))
        {
            i++;
            continue;
        }

        // Number parsing (including decimal numbers)
        if (isdigit(expression[i]) || expression[i] == '.')
        {
            std::string number;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.'))
            {
                number += expression[i];
                i++;
            }
            outputQueue.push(number);
        }
        // Function parsing (e.g., sin, cos, tan)
        else if (isalpha(expression[i]))
        {
            std::string func;
            while (i < expression.length() && isalpha(expression[i]))
            {
                func += expression[i];
                i++;
            }
            operatorStack.push(func);
        }
        // Operator parsing
        else if (IsOperator(std::string(1, expression[i])))
        {
            std::string op(1, expression[i]);
            while (!operatorStack.empty() && IsOperator(operatorStack.top()) &&
                ((GetPrecedence(operatorStack.top()) > GetPrecedence(op)) ||
                    (GetPrecedence(operatorStack.top()) == GetPrecedence(op))))
            {
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.push(op);
            i++;
        }
        // Left parenthesis
        else if (expression[i] == '(')
        {
            operatorStack.push("(");
            i++;
        }
        // Right parenthesis
        else if (expression[i] == ')')
        {
            while (!operatorStack.empty() && operatorStack.top() != "(")
            {
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }
            if (operatorStack.empty())
                throw std::runtime_error("Mismatched parentheses.");
            operatorStack.pop(); // Remove "("

            // If top of stack is a function, pop it to output queue
            if (!operatorStack.empty() && IsUnaryFunction(operatorStack.top()))
            {
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }
            i++;
        }
        else
        {
            throw std::runtime_error(std::string("Invalid character in expression: ") + expression[i]);
        }
    }

    // After processing all tokens, pop any remaining operators to output queue
    while (!operatorStack.empty())
    {
        if (operatorStack.top() == "(" || operatorStack.top() == ")")
            throw std::runtime_error("Mismatched parentheses.");
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
    }

    return outputQueue;
}

double CalculatorProcessor::EvaluateRPN(std::queue<std::string>& rpnQueue)
{
    std::stack<double> evalStack;
    while (!rpnQueue.empty())
    {
        std::string token = rpnQueue.front();
        rpnQueue.pop();

        if (IsNumber(token))
        {
            evalStack.push(std::stod(token));
        }
        else if (IsUnaryFunction(token))
        {
            if (evalStack.empty())
                throw std::runtime_error("Insufficient operands for function: " + token);
            double operand = evalStack.top();
            evalStack.pop();
            if (token == "sin")
                evalStack.push(std::sin(operand));
            else if (token == "cos")
                evalStack.push(std::cos(operand));
            else if (token == "tan")
                evalStack.push(std::tan(operand));
            else
                throw std::runtime_error("Unknown function: " + token);
        }
        else if (IsOperator(token))
        {
            if (evalStack.size() < 2)
                throw std::runtime_error("Insufficient operands for operator: " + token);
            double right = evalStack.top(); evalStack.pop();
            double left = evalStack.top(); evalStack.pop();
            if (token == "+")
                evalStack.push(left + right);
            else if (token == "-")
                evalStack.push(left - right);
            else if (token == "*")
                evalStack.push(left * right);
            else if (token == "/")
            {
                if (right == 0)
                    throw std::runtime_error("Error: Division by zero.");
                evalStack.push(left / right);
            }
            else if (token == "%")
            {
                if (right == 0)
                    throw std::runtime_error("Error: Modulo by zero.");
                evalStack.push(std::fmod(left, right));
            }
            else
                throw std::runtime_error("Unknown operator: " + token);
        }
        else
        {
            throw std::runtime_error("Invalid token in RPN: " + token);
        }
    }

    if (evalStack.size() != 1)
        throw std::runtime_error("Invalid expression.");

    return evalStack.top();
}

int CalculatorProcessor::GetPrecedence(const std::string& op)
{
    if (op == "+" || op == "-")
        return 1;
    if (op == "*" || op == "/" || op == "%")
        return 2;
    if (IsUnaryFunction(op))
        return 3;
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
    if (token.empty())
        return false;
    std::istringstream iss(token);
    double d;
    char c;
    if (!(iss >> d))
        return false;
    return !(iss >> c);
}