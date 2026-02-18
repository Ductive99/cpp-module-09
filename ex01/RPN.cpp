#include "RPN.hpp"

void computeRPN(std::stack<int> &stack, const char *str)
{
    std::string token;
    std::stringstream ss(str);

    while (ss >> token)
    {
        if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (stack.size() < 2)
                throw InsufficientOperandsException();
            int right = stack.top(); stack.pop();
            int left = stack.top(); stack.pop();

            if (token == "+") stack.push(left + right);
            if (token == "-") stack.push(left - right);
            if (token == "*") stack.push(left * right);
            if (token == "/") stack.push(left / right);
        }
        else
        {
            std::stringstream convert(token);
            int operand;
            if (!(convert >> operand) || operand >= 10 || operand < 0)
                throw InvalidOperandException();
            stack.push(operand);
        }
    }
    if (stack.empty())
        throw EmptyOperationException();
    if (stack.size() != 1)
        throw TooManyOperandsException();
}
