#include "PmergeMe.hpp"


int main(int ac, char **av)
{
    std::vector<unsigned int> vec;
    Data data;
    
    nbr_of_comps = 0;
    if (!populateVector(vec, ac - 1, av + 1))
        return 1;
    std::deque<unsigned int> dq(vec.begin(), vec.end());
    data.seqSize = ac - 1;
    data.straggler = -1;

    std::cout << "Before: ";
    for (int i = 0; i < data.seqSize; i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    nbr_of_comps = 0;
    Timing result_vec = ford_johnson_sort(vec, false);

    std::cout << "After: ";
    for (int i = 0; i < data.seqSize; i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    nbr_of_comps_deque = 0;
    Timing result_deque = ford_johnson_sort_deque(dq);

    std::cout << "\n=== Timing Results ===\n";
    std::cout << "Vector: " << result_vec.elapsed_ms << " ms, " << result_vec.comparisons << " comparisons\n";
    std::cout << "Deque:  " << result_deque.elapsed_ms << " ms, " << result_deque.comparisons << " comparisons\n";

    return 0;
}
