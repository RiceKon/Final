#include "Rpn.h"


RPN::RPN() {}

double RPN::evaluate(const Queue<Token> &tokens, double X, double Y)
{
    Stack<double> values;
    Queue<Token> tokenQueue = tokens;

    while (!tokenQueue.empty())
    {
        Token token = tokenQueue.pop();
        if (token.isNumber())
        {
            values.push(stod(token.getValue()));
        }else if (token.isVariable())
        {
            double value = (token.getValue() == "x") ? X : Y;
            values.push(value);
        }
        else if (token.isOperator())
        {
            if (values.size() < 2)
            {
                throw runtime_error("Invalid expression");
            }
            double b = values.pop();
            double a = values.pop();
            double result = applyOperator(token.getValue(), a, b);
            values.push(result);
        }
        else if (token.isFunction())
        {
            if (token.getValue() == "pi" || token.getValue() == "e" || token.getValue() == "phi")
            {
                values.push(applyFunction(token.getValue(), 0));
            }
            else
            {
                double a = values.pop();
                double result = applyFunction(token.getValue(), a);
                values.push(result);
            }
        }
    }

    if (values.size() != 1)
    {
        throw runtime_error("Invalid expression");
    }

    return values.top();
}

double RPN::applyOperator(const string &op, double a = 0, double b = 0)
{

    if (op == "+")
        return a + b;
    if (op == "-")
        return a - b;
    if (op == "*")
        return a * b;
    if (op == "/")
    {
        if (b == 0)
            return a;
        return a / b;
    }
    if (op == "^")
        return pow(a, b);
    throw runtime_error("Unknown operator: " + op);
}

double RPN::applyFunction(const string &func, double a = 0)
{
    if (func == "pi")
        return M_PI;
    if (func == "e")
        return exp(1);
    if (func == "phi")
        return (1 + sqrt(5)) / 2;
    if (func == "sin")
        return sin(a);
    if (func == "cos")
        return cos(a);
    if (func == "tan")
        return tan(a);
    if (func == "csc")
    {
        if (a == 0)
            throw runtime_error("csc undefined for 0");
        return 1.0 / sin(a);
    }
    if (func == "sec")
    {
        if (a == M_PI / 2 || a == 3 * M_PI / 2)
            throw runtime_error("sec undefined for pi/2 + k*pi");
        return 1.0 / cos(a);
    }
    if (func == "cot")
    {
        if (a == 0)
            throw runtime_error("cot undefined for 0");
        return 1.0 / tan(a);
    }
    if (func == "sinh")
        return sinh(a);
    if (func == "cosh")
        return cosh(a);
    if (func == "tanh")
        return tanh(a);
    if (func == "log")
    {
        if (a <= 0)
            throw runtime_error("log undefined for non-positive values");
        return log10(a);
    }
    if (func == "ln")
    {
        if (a <= 0)
            throw runtime_error("ln undefined for non-positive values");
        return log(a);
    }
    if (func == "sqrt")
    {
        if (a < 0)
            throw runtime_error("sqrt undefined for negative values");
        return sqrt(a);
    }
    if (func == "abs")
        return fabs(a);
    if (func == "exp")
        return exp(a);
    if (func == "arcsin")
    {
        if (a < -1 || a > 1)
            throw runtime_error("arcsin undefined for values outside [-1, 1]");
        return asin(a);
    }
    if (func == "arccos")
    {
        if (a < -1 || a > 1)
            throw runtime_error("arccos undefined for values outside [-1, 1]");
        return acos(a);
    }
    if (func == "arctan")
        return atan(a);
    if (func == "arcsinh")
        return asinh(a);
    if (func == "arccosh")
    {
        if (a < 1)
            throw runtime_error("arccosh undefined for values less than 1");
        return acosh(a);
    }
    if (func == "arctanh")
    {
        if (a <= -1 || a >= 1)
            throw runtime_error("arctanh undefined for values outside (-1, 1)");
        return atanh(a);
    }
    throw runtime_error("Unknown function: " + func);
}