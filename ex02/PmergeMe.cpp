#include "PmergeMe.hpp"

unsigned int nbr_of_comps = 0;
unsigned int nbr_of_comps_deque = 0;

template <typename T>
class CountingLess {
public:
    explicit CountingLess(unsigned int& count) : counter_(&count) {}

    bool operator()(const T& a, const T& b) const {
        ++(*counter_);
        return a < b;
    }

private:
    unsigned int* counter_;
};

template <typename Seq>
Seq build_jacobsthal_order(size_t pend_size) {
    Seq order;
    if (pend_size <= 1) return order;

    Seq jacob;
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

template <typename Seq>
Seq fj_recursive(Seq& arr, unsigned int& comparisons) {
    size_t n = arr.size();
    if (n <= 1) {
        Seq perm(n);
        for (size_t i = 0; i < n; ++i) perm[i] = i;
        return perm;
    }

    Seq winners;
    Seq losers;
    Seq winners_orig_idx;
    Seq losers_orig_idx;

    for (size_t i = 0; i + 1 < n; i += 2) {
        if (CountingLess<unsigned>(comparisons)(arr[i + 1], arr[i])) {
            winners.push_back(arr[i]);
            winners_orig_idx.push_back(i);
            losers.push_back(arr[i + 1]);
            losers_orig_idx.push_back(i + 1);
        } else {
            winners.push_back(arr[i + 1]);
            winners_orig_idx.push_back(i + 1);
            losers.push_back(arr[i]);
            losers_orig_idx.push_back(i);
        }
    }

    bool has_straggler = (n % 2 != 0);
    unsigned straggler_val = 0;
    unsigned straggler_idx = 0;
    if (has_straggler) {
        straggler_val = arr.back();
        straggler_idx = n - 1;
    }

    Seq child_perm = fj_recursive(winners, comparisons);

    Seq sorted_losers(losers.size());
    Seq sorted_losers_orig(losers.size());
    Seq sorted_winners_orig(winners.size());

    for (size_t i = 0; i < child_perm.size(); ++i) {
        sorted_losers[i] = losers[child_perm[i]];
        sorted_losers_orig[i] = losers_orig_idx[child_perm[i]];
        sorted_winners_orig[i] = winners_orig_idx[child_perm[i]];
    }

    if (has_straggler) {
        sorted_losers.push_back(straggler_val);
        sorted_losers_orig.push_back(straggler_idx);
    }

    Seq main_chain = winners;
    Seq main_chain_orig = sorted_winners_orig;

    if (!sorted_losers.empty()) {
        main_chain.insert(main_chain.begin(), sorted_losers[0]);
        main_chain_orig.insert(main_chain_orig.begin(), sorted_losers_orig[0]);
    }

    Seq order = build_jacobsthal_order<Seq>(sorted_losers.size());

    for (size_t i = 0; i < order.size(); ++i) {
        unsigned idx = order[i];
        size_t search_dist = idx + i + 1;

        typename Seq::iterator insert_pos = std::lower_bound(
            main_chain.begin(),
            main_chain.begin() + search_dist,
            sorted_losers[idx],
            CountingLess<unsigned>(comparisons)
        );

        size_t insert_idx = std::distance(main_chain.begin(), insert_pos);

        main_chain.insert(main_chain.begin() + insert_idx, sorted_losers[idx]);
        main_chain_orig.insert(main_chain_orig.begin() + insert_idx, sorted_losers_orig[idx]);
    }

    arr = main_chain;
    return main_chain_orig;
}

template <typename Seq>
Timing ford_johnson_sort_impl(Seq& arr, unsigned int& comparisons) {
    Timing result = {0.0, 0};
    if (arr.size() <= 1) return result;

    clock_t start = clock();
    fj_recursive(arr, comparisons);
    clock_t end = clock();

    result.elapsed_ms = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    result.comparisons = comparisons;
    return result;
}

Timing ford_johnson_sort(std::vector<unsigned>& data) {
    return ford_johnson_sort_impl(data, nbr_of_comps);
}

Timing ford_johnson_sort_deque(std::deque<unsigned>& data) {
    return ford_johnson_sort_impl(data, nbr_of_comps_deque);
}
