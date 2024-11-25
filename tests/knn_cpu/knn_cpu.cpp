#include "knn_cpu.h"

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
    search_result<T> kNN<T>::search(std::vector<std::vector<T>> &search_data)
    {

    }

    template<typename T>
    search_result<T> kNN<T>::search(std::vector<T> &search_data) 
    {

    }

    template<typename T>
    search_result<T> kNN<T>::search_in_data(std::vector<std::vector<point<T>>>& train_data, point<T>& query) 
    {

    }
}