#ifndef SEARCHING_SIEVE_OF_ERATOSTHENES_H
#define SEARCHING_SIEVE_OF_ERATOSTHENES_H

#include <vector>

template<typename T>
std::vector<int> sieve_of_eratosthenes(T N) {
    std::vector<bool> is_prime(N + 1, true);
    is_prime[0] = is_prime[1] = 0;
    for (int i = 4; i <= N; i += 2) { // Multiples of 2
        is_prime[i] = false;
    }
    for (int i = 3; i * i <= N; i += 2) { // Odd numbers up to sqrt(N)
        if (is_prime[i]) {
            for (int j = i * i; j <= N; j += i * 2) { // All non-even multiples of i
                is_prime[j] = false;
            }
        }
    }
    std::vector<int> primes;
    for (int i = 2; i <= N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

#endif