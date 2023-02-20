#ifndef SEARCHING_BINARY_SEARCH_H
#define SEARCHING_BINARY_SEARCH_H

#include <iterator>

template<typename RandomIt>
bool binary_search(RandomIt first, RandomIt last, int value) {
    RandomIt low = first;
    RandomIt high = std::prev(last);
    while (low <= high) {
        RandomIt middle = low + (std::distance(low, high) >> 1);
        if (*middle > value) {
            high = std::prev(middle);
        }
        else if (*middle < value) {
            low = std::next(middle);
        }
        else {
            return true;
        }
    }
    return false;
}

#endif