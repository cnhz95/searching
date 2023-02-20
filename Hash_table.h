#ifndef SEARCHING_HASH_TABLE_H
#define SEARCHING_HASH_TABLE_H

#include "Sieve_of_eratosthenes.h"
#include <algorithm>
#include <forward_list>
#include <iterator>
#include <vector>

template<typename T>
class Hash_table {
public:
    Hash_table() = default;

    template<typename RandomIt>
    Hash_table(RandomIt first, RandomIt last) : m_capacity(prime_size(std::distance(first, last))),
        m_hash_table(m_capacity), m_depth(m_capacity), m_threshold(m_capacity * M_LOAD_FACTOR) {
        for (RandomIt it = first; it != last; it++) {
            insert(*it);
        }
    }

    Hash_table<T>& operator=(const Hash_table<T>& rhs) {
        swap(rhs);
        return *this;
    }

    Hash_table<T>& operator=(Hash_table<T>&& rhs) noexcept {
        swap(rhs);
        return *this;
    }

    bool find(T data) const {
        int hash = hash_function(data);
        for (const auto& entry : m_hash_table[hash]) {
            if (entry == data) {
                return true;
            }
        }
        return false;
    }

    size_t size() const {
        return m_element_count;
    }

private:
    const double M_LOAD_FACTOR = 0.5;
    const size_t M_MAX_DEPTH = 4;
    size_t m_element_count{};
    size_t m_capacity; // Number of buckets
    size_t m_threshold;
    std::vector<std::forward_list<T>> m_hash_table;
    std::vector<size_t> m_depth;

    void insert(T data) {
        int hash = hash_function(data);
        if (m_element_count >= m_threshold || m_depth[hash] >= M_MAX_DEPTH) {
            rehash();
        }
        ++m_depth[hash];
        ++m_element_count;
        m_hash_table[hash].push_front(data);
    }

    void rehash() {
        resize();
        std::vector<std::forward_list<T>> temp = std::move(m_hash_table);
        m_hash_table.resize(m_capacity);
        for (const auto& list : temp) {
            if (!list.empty()) {
                for (const auto& entry : list) {
                    insert(entry);
                }
            }
        }
    }

    void resize() {
        m_capacity = prime_size(m_hash_table.size());
        m_threshold = m_capacity * M_LOAD_FACTOR;
        m_depth.assign(m_capacity, 0);
        m_element_count = 0;
    }

    void swap(Hash_table<T>& rhs) {
        std::swap(m_hash_table, rhs.m_hash_table);
        std::swap(m_depth, rhs.m_depth);
        std::swap(m_element_count, rhs.m_element_count);
        std::swap(m_capacity, rhs.m_capacity);
        std::swap(m_threshold, rhs.m_threshold);
    }

    int prime_size(int size) const {
        std::vector<int> primes = sieve_of_eratosthenes(size << 2);
        return *std::upper_bound(primes.begin(), primes.end(), size << 1);
    }

    int hash_function(T data) const {
        return data % m_capacity;
    }
};

#endif