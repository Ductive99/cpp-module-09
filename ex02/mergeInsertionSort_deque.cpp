#include "PmergeMe.hpp"

unsigned int nbr_of_comps_deque = 0;

template <typename T>
bool comp_deque(const T& a, const T& b) {
    nbr_of_comps_deque++;
    return a < b;
}

std::deque<unsigned> build_jacobsthal_order_deque(size_t pend_size) {
    std::deque<unsigned> order;
    if (pend_size <= 1) return order;

    std::deque<unsigned> jacob;
    jacob.push_back(1);
    jacob.push_back(3);
    
    while (jacob.back() < pend_size) {
        jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);
    }

    unsigned last_j = 1;
    for (size_t i = 1; i < jacob.size(); ++i) {
        unsigned current_j = jacob[i];
        unsigned start = (current_j > pend_size) ? pend_size : current_j;
        
        for (unsigned k = start; k > last_j; --k) {
            order.push_back(k - 1);
        }
        last_j = current_j;
        if (last_j >= pend_size) break;
    }
    return order;
}

std::deque<unsigned> fj_recursive_deque(std::deque<unsigned>& arr) {
    size_t n = arr.size();

    std::deque<unsigned> perm(n);
    for (size_t i = 0; i < n; ++i) perm[i] = i;

    if (n <= 1) return perm;

    std::deque<unsigned> winners, losers;
    std::deque<unsigned> winners_orig_idx, losers_orig_idx;

    for (size_t i = 0; i + 1 < n; i += 2) {
        if (comp_deque(arr[i + 1], arr[i])) {
            winners.push_back(arr[i]);           winners_orig_idx.push_back(i);
            losers.push_back(arr[i + 1]);        losers_orig_idx.push_back(i + 1);
        } else {
            winners.push_back(arr[i + 1]);       winners_orig_idx.push_back(i + 1);
            losers.push_back(arr[i]);            losers_orig_idx.push_back(i);
        }
    }

    bool has_straggler = (n % 2 != 0);
    unsigned straggler_val = 0, straggler_idx = 0;
    if (has_straggler) {
        straggler_val = arr.back();
        straggler_idx = n - 1;
    }

    std::deque<unsigned> child_perm = fj_recursive_deque(winners);

    std::deque<unsigned> sorted_losers(losers.size());
    std::deque<unsigned> sorted_losers_orig(losers.size());
    std::deque<unsigned> sorted_winners_orig(winners.size());

    for (size_t i = 0; i < child_perm.size(); ++i) {
        sorted_losers[i]       = losers[child_perm[i]];
        sorted_losers_orig[i]  = losers_orig_idx[child_perm[i]];
        sorted_winners_orig[i] = winners_orig_idx[child_perm[i]];
    }

    if (has_straggler) {
        sorted_losers.push_back(straggler_val);
        sorted_losers_orig.push_back(straggler_idx);
    }

    std::deque<unsigned> main_chain = winners;
    std::deque<unsigned> main_chain_orig = sorted_winners_orig;

    if (!sorted_losers.empty()) {
        main_chain.insert(main_chain.begin(), sorted_losers[0]);
        main_chain_orig.insert(main_chain_orig.begin(), sorted_losers_orig[0]);
    }

    std::deque<unsigned> order = build_jacobsthal_order_deque(sorted_losers.size());

    std::deque<size_t> winner_pos(winners.size());
    for (size_t i = 0; i < winners.size(); ++i) winner_pos[i] = i + 1;
    
    for (size_t i = 0; i < order.size(); ++i) {
        unsigned idx = order[i];
        size_t search_dist;

        if (has_straggler && idx == sorted_losers.size() - 1) {
            search_dist = main_chain.size();
        } else {
            search_dist = winner_pos[idx] + i;
        }

        std::deque<unsigned>::iterator insert_pos = std::lower_bound(
            main_chain.begin(), main_chain.begin() + search_dist, sorted_losers[idx], comp_deque<unsigned>
        );
        
        size_t insert_idx = std::distance(main_chain.begin(), insert_pos);

        main_chain.insert(main_chain.begin() + insert_idx, sorted_losers[idx]);
        main_chain_orig.insert(main_chain_orig.begin() + insert_idx, sorted_losers_orig[idx]);
    }

    arr = main_chain;

    return main_chain_orig;
}

Timing ford_johnson_sort_deque(std::deque<unsigned>& arr) {
    Timing result = {0.0, 0};
    if (arr.size() <= 1) return result;
    
    clock_t start = clock();
    
    fj_recursive_deque(arr);
    
    clock_t end = clock();
    double elapsed_ms = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    
    result.elapsed_ms = elapsed_ms;
    result.comparisons = nbr_of_comps_deque;
    
    return result;
}
