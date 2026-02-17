#include "RPN.hpp"

void computeRPN(const char *str)
{
    std::stack<int> stack;
    std::string token;
    std::stringstream ss(str);

    while (ss >> token)
    {
        if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (stack.size() < 2)
            {
                std::cout << "Error" << std::endl;
                return ;
            }
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
            if (!(convert >> operand) || (operand >= 10 && operand < 0))
            {
                std::cout << "Error" << std::endl;
                return ;
            }
            stack.push(operand);
        }
    }
    if (stack.size() != 1)
    {
        std::cout << "Error" << std::endl;
        return ;
    }
    std::cout << stack.top() << std::endl;
}
