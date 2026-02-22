#include "PmergeMe.hpp"


int main(int ac, char **av)
{
    std::vector<unsigned int> vec;
    
    nbr_of_comps = 0;
    if (!populateVector(vec, ac - 1, av + 1))
        return 1;
    std::deque<unsigned int> dq(vec.begin(), vec.end());

    std::cout << "Before: ";
    for (int i = 0; i < ac - 1; i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    nbr_of_comps = 0;
    Timing result_vec = ford_johnson_sort(vec, DEBUG);

    std::cout << "After:  ";
    for (int i = 0; i < ac - 1; i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    nbr_of_comps_deque = 0;
    Timing result_deque = ford_johnson_sort_deque(dq);

    std::cout << "Time taken using std::vector: " << result_vec.elapsed_ms << " ms, " << result_vec.comparisons << " comparisons\n";
    std::cout << "Time take using std::deque:   " << result_deque.elapsed_ms << " ms, " << result_deque.comparisons << " comparisons\n";

    return 0;
}
