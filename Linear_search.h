#ifndef SEARCHING_LINEAR_SEARCH_H
#define SEARCHING_LINEAR_SEARCH_H

template<typename FwdIt>
bool linear_search(FwdIt first, FwdIt last, int value) {
    for (FwdIt it = first; it != last; it++) {
        if (*it == value) {
            return true;
        }
    }
    return false;
}

#endif