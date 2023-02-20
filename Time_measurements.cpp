#include "Time_measurements.h"

Time_measurements::Time_measurements(int min_size, int max_size, int sample_size, const std::string& filename)
    : m_min_size(min_size), m_max_size(max_size), m_sample_size(sample_size), m_file(filename) {}

void Time_measurements::measure(const Algorithm& searching) {
    for (int size = m_min_size; size <= m_max_size; size += m_min_size) {
        switch (searching) {
            case Algorithm::linear_search:
                m_data = sieve_of_eratosthenes(size);
                break;
            case Algorithm::binary_search:
                m_data = sieve_of_eratosthenes(size);
                break;
            case Algorithm::binary_search_tree: {
                m_data = sieve_of_eratosthenes(size);
                Binary_search_tree<int> bst(m_data.begin(), m_data.end());
                m_bst = std::move(bst);
                break;
            }
            case Algorithm::hash_table: {
                m_data = sieve_of_eratosthenes(size);
                Hash_table<int> hash_table(m_data.begin(), m_data.end());
                m_hash_table = std::move(hash_table);
                break;
            }
        }
        int hit_count = 0;
        int miss_count = 0;
        for (int sample = 0; sample < m_sample_size; sample++) {
            std::vector<int> values = generate_values();
            switch (searching) {
                case Algorithm::linear_search:
                    m_start = std::chrono::steady_clock::now();
                    for (int inner_sample = 0; inner_sample < m_sample_size; inner_sample++) {
                        linear_search(m_data.begin(), m_data.end(), values[inner_sample]) ? ++hit_count : ++miss_count;
                    }
                    m_end = std::chrono::steady_clock::now();
                    break;
                case Algorithm::binary_search:
                    m_start = std::chrono::steady_clock::now();
                    for (int inner_sample = 0; inner_sample < m_sample_size; inner_sample++) {
                        binary_search(m_data.begin(), m_data.end(), values[inner_sample]) ? ++hit_count : ++miss_count;
                    }
                    m_end = std::chrono::steady_clock::now();
                    break;
                case Algorithm::binary_search_tree:
                    m_start = std::chrono::steady_clock::now();
                    for (int inner_sample = 0; inner_sample < m_sample_size; inner_sample++) {
                        m_bst.find(values[inner_sample]) ? ++hit_count : ++miss_count;
                    }
                    m_end = std::chrono::steady_clock::now();
                    break;
                case Algorithm::hash_table:
                    m_start = std::chrono::steady_clock::now();
                    for (int inner_sample = 0; inner_sample < m_sample_size; inner_sample++) {
                        m_hash_table.find(values[inner_sample]) ? ++hit_count : ++miss_count;
                    }
                    m_end = std::chrono::steady_clock::now();
                    break;
            }
            m_duration = m_end - m_start;
            m_times.push_back(m_duration.count() / m_sample_size);
        }
        m_results.push_back({size, mean(), stdev() });
        m_times.clear();
        std::cout << hit_count << '\n' << miss_count << '\n';
    }
    export_data(searching);
    m_results.clear();
}

std::vector<int> Time_measurements::generate_values() {
    std::mt19937 rng((uint32_t)std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> uid(0, m_data[m_data.size() - 1]);
    std::vector<int> values(m_sample_size);
    for (int& value : values) {
        value = uid(rng);
    }
    return values;
}

double Time_measurements::mean() {
    return m_mean = std::accumulate(m_times.begin(), m_times.end(), 0.0) / m_sample_size;
}

double Time_measurements::stdev() {
    double square_sum = std::accumulate(m_times.begin(), m_times.end(), 0.0, [=](double sum, const double x) -> double {
        return sum += std::pow(x - m_mean, 2);
    });
    return std::sqrt(1.0 / (m_sample_size - 1) * square_sum);
}

void Time_measurements::export_data(const Algorithm& searching) {
    if (!m_file) {
        std::cerr << "The output file couldn't be opened!\n";
        return;
    }
    switch (searching) {
        case Algorithm::linear_search:
            m_file << "Linear search\n";
            break;
        case Algorithm::binary_search:
            m_file << "Binary search\n";
            break;
        case Algorithm::binary_search_tree:
            m_file << "Binary search tree\n";
            break;
        case Algorithm::hash_table:
            m_file << "Hash table\n";
            break;
    }
    m_file << "N\t\t\tT[s]\t\t\tStdev[s]\t\tSamples\n";
    std::for_each(m_results.begin(), m_results.end(), [&](const Result& elem) -> void {
        m_file << std::setprecision(10) << std::fixed << elem.m_size << "\t\t\t"
               << elem.m_mean << "\t\t\t" << elem.m_std_dev << "\t\t\t" << m_sample_size << '\n';
    });
    m_file << '\n';
}