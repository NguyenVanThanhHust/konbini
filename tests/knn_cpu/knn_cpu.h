#include <iostream>
#include <cstring>
#include <chrono>

#include <random>
#include <numeric> // for std::iota
#include <vector> // for vector 
#include <algorithm> // for copy() and assign() 
#include <iterator> // for back_inserter 

namespace konbini {
    template<typename T>
    struct search_result
    {
        std::vector<std::vector<T>> result_data;
        std::vector<T> distances; 
    };
    
    class kNN
    {
        int k_neighbor;

    };
}