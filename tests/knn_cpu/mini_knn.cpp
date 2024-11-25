#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>

struct Point
{
    std::vector<double> features;
    int label;

    Point(std::vector<double> f, int l) : features(f), label(l) {} 
};

struct result
{
    std::vector<Point> points;
    std::vector<double> distances;
};

double calEuclideanDistance(std::vector<double>& a, std::vector<double>& b)
{
    double sum=0.0;
    int num_elements = a.size();
    assert(num_elements==b.size());
    for (int i = 0; i < num_elements; i++)
    {
        sum += std::pow(a[i]-b[i], 2);
    }
    return std::sqrt(sum);
}

std::vector<int> argsort(const std::vector<double>& values)
{
    // Create a vector of indices
    std::vector<int> indices(values.size());
    for (int i = 0; i < indices.size(); i++)
    {
        indices[i] = i;
    }
    // Sort the indices based on the values they point to 
    std::sort(indices.begin(), indices.end(), [&values](int a, int b) { return values[a] < values[b];});
    return indices;  
}

class mini_knn
{
private:
    /* data */
public:
    int num_neighbor;
    std::vector<Point> train_dataset;
    int data_size;
    mini_knn(int n_neighbor=3): num_neighbor(n_neighbor) {}
    ~mini_knn();
    void fit(const std::vector<Point>& train_data);
    std::vector<int> predict(std::vector<double>& features);
};

mini_knn::~mini_knn()
{
}

void mini_knn::fit(const std::vector<Point>& train_data)
{
    train_dataset = train_data;
    data_size = train_dataset.size();
}

std::vector<int> mini_knn::predict(std::vector<double>& features)
{
    std::vector<double> distances;
    
    for (int i = 0; i < data_size; i++)
    {
        double distance = calEuclideanDistance(train_dataset[i].features, features);  
        distances.push_back(distance);
    }
    std::vector<int> sorted_indexes = argsort(distances);
    std::vector<int> res;
    for (int i = 0; i < num_neighbor; i++)
    {
        res.push_back(train_dataset[sorted_indexes[i]].label);
    }
    return res;
}


int main()
{
    std::vector<Point> dataset = { Point({1.0, 2.0}, 0), Point({1.5, 1.8}, 0), Point({5.0, 8.0}, 1), Point({6.0, 8.0}, 1), Point({1.0, 0.6}, 0), Point({9.0, 11.0}, 1), Point({8.0, 2.0}, 1), Point({10.0, 2.0}, 1), Point({9.0, 3.0}, 1)};
    mini_knn new_mini_knn = mini_knn(2);
    new_mini_knn.fit(dataset);
    std::vector<double> new_sample{6.0, 2.5};
    std::vector<int> res = new_mini_knn.predict(new_sample);
    for (int i = 0; i < res.size(); i++)
    {
        std::cout<<res[i]<<" ";
    }
    
    return 0;
}