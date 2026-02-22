# Ford-Johnson Algorithm / Merge-Insertion Sort

The goal of the program is to implement the Ford-Johnson Algorithm also known as Merge-Insertion Sort on two containers and compare the time it takes to sort a positive integer sequence.

in C++98.

### Implementation

**1. Isolate the "Straggler" (Odd Elements)**

Check if the size of your input sequence is even or odd. If it is odd, remove the last element and save it in a local variable as a "straggler". This element will be ignored during the pairing and recursive phases and inserted at the very end.

**2. Pair and Sort Locally**
Divide your remaining sequence into arbitrary pairs. Compare the two elements in each pair, and swap them if necessary so that the smaller element (labeled $b$) is on the left, and the larger element (labeled $a$) is on the right.

**3. Recursively Sort the Pairs**
Recursively sort the sequence of pairs based strictly on the values of their larger elements ($a_x$).

* *C++ Implementation Tip:* Because you must not break the original pairings during the recursion, you can handle this by using a `std::vector<std::pair<T, T>>` or by storing the mappings of the $a$ elements to the $b$ elements in a hash map before making the recursive call. Alternatively, swap entire sub-sequences of numbers.

**4. Initialize the "Main" and "Pend" Chains**
After the recursion unwinds, separate your pairs into two new sequences:

* **The Main Chain:** Initialize this with the smallest element of the very first sorted pair ($b_1$), followed by all of the recursively sorted larger elements ($a_1, a_2, \dots, a_n$). At this stage, the main chain is mostly sorted.
* **The Pend Chain:** Collect all the remaining smaller elements ($b_2, b_3, \dots$) and place them into a temporary "pend" array.

**5. Build the Jacobsthal Insertion Sequence**
To achieve optimal binary search efficiency, you must insert the "pend" elements in specific batches. Generate an insertion sequence based on the Jacobsthal numbers, which can be calculated using the formula $J_n = \frac{2^{n+1} + (-1)^n}{3}$. The proper sequence orders elements backwards between the current Jacobsthal number and the previous one (e.g., index 3, then 2; index 5, then 4; index 11, 10, 9, 8, 7, 6). Add your "straggler" element from Step 1 to the very end of this sequence.

**6. Binary Insertion**
Iterate through your "pend" elements using the Jacobsthal-based order you just generated. For each element, use a binary search to find its correct position within the "main" chain, and insert it.

* *C++ Implementation Tip:* Use `std::upper_bound` from the `<algorithm>` library to perform the binary search. You must carefully define your search area (the iterators you pass to `upper_bound`). Because of the algorithm's guarantees, you only need to search up to the corresponding $a$ element's current position in the main chain.

I hope this helps! Do you have any further questions? Ask ChatGPT. ;)
