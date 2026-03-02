#ifndef PMERGEME_HPP_
#define PMERGEME_HPP_

#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <errno.h>
#include <limits.h>

extern unsigned int nbr_of_comps;
extern unsigned int nbr_of_comps_deque;

typedef struct s_timing {
    double elapsed_ms;
    unsigned int comparisons;
} Timing;

int populateVector(std::vector<unsigned>&, int ac, char **av);
void FordJohnsonSort(std::vector<unsigned>& vec);

Timing ford_johnson_sort(std::vector<unsigned>& data);
Timing ford_johnson_sort_deque(std::deque<unsigned>& data);

template <typename T>
bool checkSorted(T& v, size_t size) {
    if (v.size() != size) return false;
    if (v.size() < 2) return true;
    for (size_t i = 0; i < v.size() - 1; ++i) {
        if (v[i] > v[i + 1]) {
            return false;
        }
    }
    return true;
}

template <typename T>
void printNumbers(const char *str, T& v) {
    size_t i = 0;

    std::cout << str;
    for (; i < v.size() - 1; i++)
        std::cout << v[i] << " ";
    std::cout << v[i] << std::endl;
}

#endif /* PMERGEME_HPP_ */
