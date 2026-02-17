#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cout << "Usage: " << av[0] << " \"{RPN notation}\"" << std::endl;
        return 1;
    }
    
    computeRPN(av[1]);

    return 0;
}
