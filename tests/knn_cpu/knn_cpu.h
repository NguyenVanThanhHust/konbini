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
    struct search_result
    {
        std::vector<std::vector<T>> result_data;
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

            search_result<T> search_knn(std::vector<std::vector<T>> &search_data);
            search_result<T> search_knn(std::vector<T> &search_data);
    };
}

// Define class
namespace konbini {
    using std::cout;
    using std::endl;

    template<typename T>
    kNN<T>::kNN() 
    {
        k_neighbor_ = 3;
        num_elements_ = 0;
        distance_type_ = "eucliean";
    }

    template<typename T>
    kNN<T>::kNN(int k_neighbor) 
    {
        k_neighbor_ = k_neighbor;
        CUSTOM_ASSERT(k_neighbor > 0, "number of neighbor must > 0");
        num_elements_ = 0;
        distance_type_ = "eucliean";
    }

    template<typename T>
    kNN<T>::kNN(int k_neighbor, std::string distance_type) 
    {
        k_neighbor_ = k_neighbor;
        CUSTOM_ASSERT(k_neighbor > 0, "number of neighbor must > 0");
        CUSTOM_ASSERT(element_in_vector(distance_type, allowed_distance_types), "this type of distance isn't define: " + distance_type);
        num_elements_ = 0;
        distance_type_ = distance_type_;
    }

    template<typename T>
    void kNN<T>::print_info()
    {
        cout<<"This knn is set with: "<<k_neighbor_<<" neighbor."<<endl;
        cout<<"Current instance have: "<<num_elements_<<" elements."<<endl;
    }

    template<typename T>
    void kNN<T>::add_data(std::vector<std::vector<T>> &new_data, std::vector<int> &labels)
    {
        data_.insert(data_.end(), new_data.begin(), new_data.end());
    }

    template<typename T>
    void kNN<T>::add_data(std::vector<T> &new_dat, int& label)
    {

    }

    template<typename T>
    search_result<T> kNN<T>::search_knn(std::vector<std::vector<T>> &search_data)
    {

    }

    template<typename T>
    search_result<T> kNN<T>::search_knn(std::vector<T> &search_data) 
    {

    }
}
#endif