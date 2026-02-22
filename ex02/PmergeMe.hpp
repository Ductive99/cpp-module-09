#ifndef PMERGEME_HPP_
#define PMERGEME_HPP_

#include <iostream>
#include <vector>
#include <deque>

#include <sstream>
#include <cstdlib>
#include <errno.h>
#include <limits.h>

extern unsigned int nbr_of_comps;

typedef struct s_data {
    int seqSize;
    long straggler;
    bool hasStraggler;
} Data;

typedef struct s_timing {
    double elapsed_ms;
    unsigned int comparisons;
} Timing;

int populateVector(std::vector<unsigned>&, int ac, char **av);
void FordJohnsonSort(std::vector<unsigned>& vec);

Timing ford_johnson_sort(std::vector<unsigned>& data, bool debug = false);
Timing ford_johnson_sort_deque(std::deque<unsigned>& data);

extern unsigned int nbr_of_comps_deque;

template<typename T>
bool _comp(T lv, T rv) {
    nbr_of_comps++;
    return lv <= rv;
}

#endif /* PMERGEME_HPP_ */
