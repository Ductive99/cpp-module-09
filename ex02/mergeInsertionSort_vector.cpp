#include "PmergeMe.hpp"

unsigned int nbr_of_comps = 0;

static int fj_level = 0;

static void print_indent(int level) {
    for (int i = 0; i < level; ++i) std::cout << "  ";
}

static void print_vec(const std::string& name, const std::vector<unsigned>& v, int level) {
    print_indent(level);
    std::cout << name << ": [";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i + 1 < v.size()) std::cout << ", ";
    }
    std::cout << "]\n";
}

template <typename T>
bool comp(const T& a, const T& b) {
    nbr_of_comps++;
    return a < b;
}

std::vector<unsigned> build_jacobsthal_order(size_t pend_size) {
    std::vector<unsigned> order;
    if (pend_size <= 1) return order;

    std::vector<unsigned> jacob;
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

std::vector<unsigned> fj_recursive(std::vector<unsigned>& arr, bool debug) {
    size_t n = arr.size();

    std::vector<unsigned> perm(n);
    if (debug) {
        ++fj_level;
        print_indent(fj_level - 1);
        std::cout << "fj_recursive level " << fj_level - 1 << " enter, n=" << n << "\n";
        print_vec("input", arr, fj_level - 1);
    }
    for (size_t i = 0; i < n; ++i) perm[i] = i;

    if (n <= 1) return perm;

    std::vector<unsigned> winners, losers;
    std::vector<unsigned> winners_orig_idx, losers_orig_idx;

    for (size_t i = 0; i + 1 < n; i += 2) {
        if (comp(arr[i + 1], arr[i])) {
            winners.push_back(arr[i]);           winners_orig_idx.push_back(i);
            losers.push_back(arr[i + 1]);        losers_orig_idx.push_back(i + 1);
        } else {
            winners.push_back(arr[i + 1]);       winners_orig_idx.push_back(i + 1);
            losers.push_back(arr[i]);            losers_orig_idx.push_back(i);
        }
    }

    if (debug) {
        print_vec("winners (paired) ", winners, fj_level - 1);
        print_vec("losers (paired)  ", losers, fj_level - 1);
    }

    bool has_straggler = (n % 2 != 0);
    unsigned straggler_val = 0, straggler_idx = 0;
    if (has_straggler) {
        straggler_val = arr.back();
        straggler_idx = n - 1;
        if (debug) {
            print_indent(fj_level - 1);
            std::cout << "straggler detected: val=" << straggler_val << " idx=" << straggler_idx << "\n";
        }
    }

    std::vector<unsigned> child_perm = fj_recursive(winners, debug);
    
    if (debug) {
        print_indent(fj_level - 1);
        std::cout << "returned from recursion: child_perm = [";
        for (size_t i = 0; i < child_perm.size(); ++i) {
            std::cout << child_perm[i];
            if (i + 1 < child_perm.size()) std::cout << ", ";
        }
        std::cout << "]\n";
    }

    std::vector<unsigned> sorted_losers(losers.size());
    std::vector<unsigned> sorted_losers_orig(losers.size());
    std::vector<unsigned> sorted_winners_orig(winners.size());

    for (size_t i = 0; i < child_perm.size(); ++i) {
        sorted_losers[i]       = losers[child_perm[i]];
        sorted_losers_orig[i]  = losers_orig_idx[child_perm[i]];
        sorted_winners_orig[i] = winners_orig_idx[child_perm[i]];
    }

    if (has_straggler) {
        sorted_losers.push_back(straggler_val);
        sorted_losers_orig.push_back(straggler_idx);
        if (debug) {
            print_indent(fj_level - 1);
            std::cout << "Appended straggler to sorted_losers: val=" << straggler_val << "\n";
        }
    }

    std::vector<unsigned> main_chain = winners;
    std::vector<unsigned> main_chain_orig = sorted_winners_orig;

    if (!sorted_losers.empty()) {
        main_chain.insert(main_chain.begin(), sorted_losers[0]);
        main_chain_orig.insert(main_chain_orig.begin(), sorted_losers_orig[0]);
        if (debug) {
            print_indent(fj_level - 1);
            std::cout << "Inserted first pend without comparisons: " << sorted_losers[0] << "\n";
        }
    }

    std::vector<unsigned> order = build_jacobsthal_order(sorted_losers.size());
    if (debug) {
        print_indent(fj_level - 1);
        std::cout << "Jacobsthal insertion order: ";
        for (size_t i = 0; i < order.size(); ++i) {
            std::cout << order[i] << (i + 1 < order.size() ? ", " : "\n");
        }
    }
    
    for (size_t i = 0; i < order.size(); ++i) {
        unsigned idx = order[i];
        size_t search_dist;

        if (has_straggler && idx == sorted_losers.size() - 1) {
            search_dist = main_chain.size();
        } else {
            unsigned paired_winner_orig = sorted_winners_orig[idx];
            std::vector<unsigned>::iterator bound_it = std::find(
                main_chain_orig.begin(), main_chain_orig.end(), paired_winner_orig
            );
            search_dist = std::distance(main_chain_orig.begin(), bound_it);
        }

        std::vector<unsigned>::iterator insert_pos = std::lower_bound(
            main_chain.begin(), main_chain.begin() + search_dist, sorted_losers[idx], comp<unsigned>
        );
        
        size_t insert_idx = std::distance(main_chain.begin(), insert_pos);

        if (debug) {
            print_indent(fj_level - 1);
            std::cout << "Inserting pend[" << idx << "]=" << sorted_losers[idx]
                      << " at index=" << insert_idx << "\n";
        }
        main_chain.insert(main_chain.begin() + insert_idx, sorted_losers[idx]);
        main_chain_orig.insert(main_chain_orig.begin() + insert_idx, sorted_losers_orig[idx]);
    }

    arr = main_chain;
    if (debug) {
        print_vec("resulting main_chain", main_chain, fj_level - 1);
        print_indent(fj_level - 1);
        std::cout << "fj_recursive level " << fj_level - 1 << " exit\n";
        --fj_level;
    }

    return main_chain_orig;
}

Timing ford_johnson_sort(std::vector<unsigned>& arr, bool debug) {
    Timing result = {0.0, 0};
    if (arr.size() <= 1) return result;
    
    clock_t start = clock();
    
    fj_recursive(arr, debug);
    
    clock_t end = clock();
    double elapsed_ms = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    
    result.elapsed_ms = elapsed_ms;
    result.comparisons = nbr_of_comps;
    
    return result;
}
