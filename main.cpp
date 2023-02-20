#include "Time_measurements.h"

int main() {
    constexpr int SAMPLES = 50;
    constexpr int MIN_SIZE = 10000;
    constexpr int MAX_SIZE = MIN_SIZE * 20;
    const std::string FILENAME = "results.txt";
    Time_measurements test(MIN_SIZE, MAX_SIZE, SAMPLES, FILENAME);

    test.measure(Algorithm::linear_search);
    test.measure(Algorithm::binary_search);
    test.measure(Algorithm::binary_search_tree);
    test.measure(Algorithm::hash_table);


    /*
    std::vector<int> v = sieve_of_eratosthenes(50);
    Binary_search_tree<int> bst(v.begin(), v.end());
    for (size_t i = 2; i <= v.size(); i++) {
        std::cout << (bst.find(i) ? i : 0) << " ";
    }
    */

    return 0;
}