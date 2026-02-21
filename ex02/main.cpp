#include "PmergeMe.hpp"


int main(int ac, char **av)
{
    std::vector<unsigned> vec;
    
    if (ac == 1) {
        std::cout << "Usage: " << av[0] << " <positive_number_sequence>" << std::endl;
        return (0);
    }
    
    if (!populateVector(vec, ac - 1, av + 1))
        return 1;
    std::deque<unsigned> dq(vec.begin(), vec.end());

    for (int i = 0; i < ac - 1; i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
    for (int i = 0; i < ac - 1; i++)
        std::cout << dq[i] << " ";
}
