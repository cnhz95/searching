#ifndef SEARCHING_BINARY_SEARCH_TREE_H
#define SEARCHING_BINARY_SEARCH_TREE_H

#include <iterator>
#include <memory>
#include <vector>

template<typename T>
class Binary_search_tree {
public:
    Binary_search_tree() = default;

    template<typename RandomIt>
    Binary_search_tree(RandomIt first, RandomIt last) : m_root(insert(first, last)) {}

    bool find(T elem) const {
        return find(m_root, elem);
    }

private:
    struct Node {
        explicit Node(T data) : m_data(data), m_left(nullptr), m_right(nullptr) {}
        T m_data;
        std::unique_ptr<Node> m_left;
        std::unique_ptr<Node> m_right;
    };

    std::unique_ptr<Node> m_root;

    template<typename RandomIt>
    std::unique_ptr<Node> insert(RandomIt first, RandomIt last) const {
        if (first >= last) {
            return nullptr;
        }
        RandomIt middle = first + (std::distance(first, last) >> 1);
        std::unique_ptr<Node> root = std::make_unique<Node>(*middle);
        root->m_left = insert(first, middle);
        root->m_right = insert(std::next(middle), last);
        return root;
    }

    bool find(const std::unique_ptr<Node>& root, T elem) const {
        if (!root) {
            return false;
        }
        if (elem > root->m_data) {
            return find(root->m_right, elem);
        }
        else if (elem < root->m_data) {
            return find(root->m_left, elem);
        }
        else {
            return true;
        }
    }
};

#endif