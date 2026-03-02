#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    std::vector<unsigned int> vec;
    nbr_of_comps = 0, nbr_of_comps_deque = 0;

    if (!populateVector(vec, ac - 1, av + 1)) return 1;
    std::deque<unsigned int> dq(vec.begin(), vec.end());

    printNumbers("Before: ", vec);

    Timing result_vec = ford_johnson_sort(vec);

    printNumbers("After: ", dq);

    Timing result_deque = ford_johnson_sort_deque(dq);

    std::cout << "Time taken using std::vector: " << result_vec.elapsed_ms << " ms, "
              << result_vec.comparisons << " comparisons\n";
    std::cout << "Time take using std::deque:   " << result_deque.elapsed_ms << " ms, "
              << result_deque.comparisons << " comparisons\n";

    bool sorted = checkSorted(vec, ac - 1) && checkSorted(dq, ac - 1);
    if (sorted) std::cout << ">>> SUCCESS <<<" << std::endl;
    else std::cout << ">>> FAILURE <<<" << std::endl;

    return 0;
}
