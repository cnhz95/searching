cmake_minimum_required(VERSION 3.24)
project(searching)

set(CMAKE_CXX_STANDARD 17)

add_executable(searching main.cpp Time_measurements.cpp Time_measurements.h Sieve_of_eratosthenes.h Linear_search.h Binary_search_tree.h Binary_search.h Hash_table.h)
