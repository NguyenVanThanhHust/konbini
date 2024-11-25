#ifndef KNN_H
#define KNN_H

#include <iostream>
#include <cstring>
#include <chrono>

#include <random>
#include <string>
#include <numeric> // for std::iota
#include <vector> // for vector 
#include <algorithm> // for copy() and assign() 
#include <iterator> // for back_inserter 
#include "utils.h"

// Declare class
namespace konbini {
    template<typename T> 
    struct point 
    {
        std::vector<T> data;
        int label;

        point(const std::vector<T>& d, int l) : data(d), label(l) {}
    };

    template<typename T>
    struct search_result
    {
        std::vector<point<T>> result_data;
        std::vector<T> distances; 
    };

    template<typename T>
    class kNN
    {
        private:
            int k_neighbor_;
            int num_elements_;
            std::string distance_type_;
            std::vector<std::vector<T>> data_;
            std::vector<std::string> allowed_distance_types = {"eucliean", "other"};

        public:
            std::string distance_type;
            kNN();
            kNN(int k_neighbor);
            kNN(int k_neighbor, std::string distance_type);

            void print_info();

            void add_data(std::vector<std::vector<T>> &new_data, std::vector<int> &label);
            void add_data(std::vector<T> &new_dat, int& label);

            search_result<T> search(std::vector<std::vector<T>> &search_data);
            search_result<T> search(std::vector<T> &search_data);
            search_result<T> search_in_data(std::vector<std::vector<point<T>>>& train_data, point<T>& query);
    };
}
#endif