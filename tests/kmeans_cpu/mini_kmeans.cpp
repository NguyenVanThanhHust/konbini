#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <typeinfo>

#define NUM_K_CENTERS 3

using std::cout;
using std::endl;

struct Point
{
    std::vector<float> data;
    int label;

    Point operator+(const Point& other)
    {
        if (data.size() != other.data.size())
        {
            std::ostringstream oss;
            oss << "Vectors must be of the same size: "
                << "this data size = " << data.size() 
                << ", other data size = " << other.data.size();
            throw std::invalid_argument(oss.str());        
        }
        int dim = data.size();
        Point result;
        result.data.resize(dim);
        for (int i = 0; i < dim; i++)
        {
            result.data[i] = data[i] + other.data[i];
        }
        result.label = label;
        return result;
    }

    void average(int num_sample) 
    {
        int dim = data.size();
        for (int i = 0; i < dim; i++)
        {
            data[i] = data[i] / num_sample;
        }
        

    }
    // Overload the << operator as a friend function
    friend std::ostream& operator<<(std::ostream& os, const Point& point) 
    {
        os << "Point[label=" << point.label << ", data={";
        for (size_t i = 0; i < point.data.size(); ++i) {
            os << point.data[i];
            if (i < point.data.size() - 1) {
                os << ", "; // Add a comma between elements
            }
        }
        os << "}]";
        return os; // Return the output stream
    }

};

float calculate_distance(const Point& p1, const Point& p2)
{
    float dist = 0.0;
    int dim = p1.data.size();
    for (int i = 0; i < dim; i++)
    {
        float tmp = p1.data[i] - p2.data[i];
        dist += tmp*tmp;
    }
    return dist / dim;
}


int main() {
    // Open the input file
    std::ifstream infile("../2d_dataset.txt");
    if (!infile) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    std::string line;
    // Read file line by line
    std::vector<Point> train_data;
    std::vector<Point> test_data;
    int data_idx=0;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        float f1, f2;
        int i;
        // Parse each line
        if (iss >> f1 >> f2 >> i) {
            Point p;
            p.data = {f1, f2};
            p.label = i;
            // std::cout << "Read floats: " << f1 << ", " << f2 << " and int: " << i << std::endl;
            if (data_idx%3 == 0) {
                test_data.push_back(p);
            } else {
                // remove label of train set here
                p.label = -1;
                train_data.push_back(p);
            }
            data_idx++;
        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

    // Close the file
    infile.close();

    // Start K means algorithm in here
    std::vector<std::vector<Point>> all_centers_in_each_step;
    std::vector<Point> init_centers;
    // Initialize center of each cluster

    for (int i = 0; i < NUM_K_CENTERS; i++)
    {
        init_centers.push_back({train_data[i].data, i});
    }
    all_centers_in_each_step.push_back(init_centers);
    init_centers.clear();

    // Train process start here
    int iteration = 0;
    while (true)
    {
        cout<<"iteration: "<<iteration<<endl;
        iteration++;
        // Assignment step 
        int current_step = all_centers_in_each_step.size() - 1;
        std::vector<Point> current_centers = all_centers_in_each_step[current_step];
        int train_set_size = train_data.size();

        for (int i = 0; i < train_set_size; i++)
        {
            std::vector<float> dists;
            for (int j = 0; j < NUM_K_CENTERS; j++)
            {
                float dist = calculate_distance(current_centers[j], train_data[i]);
                dists.push_back(dist);
            }

            std::vector<float>::iterator min_pos = std::min_element(dists.begin(), dists.end());
            int position_of_min = min_pos - dists.begin();
            train_data[i].label = position_of_min;
        }

        // Update step is here
        std::vector<Point> new_centers;
        std::vector<int> num_sample_in_each_cluster;
        for (int i = 0; i < NUM_K_CENTERS; i++)
        {
            new_centers.push_back(Point{{0, 0}, i});
            num_sample_in_each_cluster.push_back(0);
        }
        
        for (int i = 0; i < train_set_size; i++)
        {
            new_centers[train_data[i].label] = new_centers[train_data[i].label] + train_data[i];
            num_sample_in_each_cluster[train_data[i].label]++;
        }
        for (int i = 0; i < NUM_K_CENTERS; i++)
        {
            new_centers[i].average(num_sample_in_each_cluster[i]);
        }
        
        // check condition to break
        float total_move_distance = 0;
        for (int i = 0; i < NUM_K_CENTERS; i++)
        {
            float distance = calculate_distance(new_centers[i], current_centers[i]);
            total_move_distance += abs(distance);
        }
        all_centers_in_each_step.push_back(new_centers);
        
        if (total_move_distance < 5)
        {
            break;
        }
    }
    
    // Test process start here
    int test_size = test_data.size();
    std::vector<Point> centers = all_centers_in_each_step[all_centers_in_each_step.size()-1];
    for (int i = 0; i < test_size; i++)
    {
        std::vector<float> dists;
        for (int j = 0; j < NUM_K_CENTERS; j++)
        {
            float dist = calculate_distance(centers[j], test_data[i]);
            dists.push_back(dist);
        }

        std::vector<float>::iterator min_pos = std::min_element(dists.begin(), dists.end());
        int position_of_min = min_pos - dists.begin();
        cout<<test_data[i].label <<" "<<position_of_min<<endl;
    }
    

    return 0;
}
