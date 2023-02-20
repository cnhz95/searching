#ifndef SEARCHING_TIME_MEASUREMENTS_H
#define SEARCHING_TIME_MEASUREMENTS_H

#include "Binary_search.h"
#include "Binary_search_tree.h"
#include "Hash_table.h"
#include "Linear_search.h"
#include "Sieve_of_eratosthenes.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <random>
#include <vector>

enum class Algorithm {
    linear_search, binary_search, binary_search_tree, hash_table
};

struct Result {
    int m_size;
    double m_mean;
    double m_std_dev;
};

class Time_measurements {
public:
    Time_measurements() = delete;
    Time_measurements(int min_size, int max_size, int sample_size, const std::string& filename);
    void measure(const Algorithm& searching);

private:
    double mean();
    double std_dev();
    void export_data(const Algorithm& searching);
    std::vector<int> generate_values();

    int m_min_size;
    int m_max_size;
    int m_sample_size;
    double m_mean{};

    std::ofstream m_file;
    std::vector<int> m_data;
    std::vector<double> m_times;
    std::vector<Result> m_results;
    Binary_search_tree<int> m_bst;
    Hash_table<int> m_hash_table;

    std::chrono::time_point<std::chrono::steady_clock> m_start;
    std::chrono::time_point<std::chrono::steady_clock> m_end;
    std::chrono::duration<double> m_duration{};
};

#endif