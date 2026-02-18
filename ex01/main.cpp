#include "RPN.hpp"

int main(int ac, char **av)
{
    std::stack<int> stack;
    if (ac != 2) {
        std::cout << "Usage: " << av[0] << " \"{RPN notation}\"" << std::endl;
        return 1;
    }
    
    try {
        computeRPN(stack, av[1]);
        std::cout << stack.top() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 2;
    }

    return 0;
}
