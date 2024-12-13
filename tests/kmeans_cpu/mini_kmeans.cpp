#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define NUM_K_CENTERS 3

struct Points
{
    std::vector<float> data;
    int label;
};

float calculate_distance(const Points& p1, const Points& p2)
{
    float dist = 0.0;
    int dim = p1.data.size();
    for (int i = 0; i < dim; i++)
    {
        dist += (p1.data[i] - p2.data[i])**2;
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
    std::vector<Points> train_data;
    std::vector<Points> test_data;
    int data_idx=0;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        float f1, f2;
        int i;
        // Parse each line
        if (iss >> f1 >> f2 >> i) {
            Points p;
            p.data = {f1, f2};
            p.label = i;
            std::cout << "Read floats: " << f1 << ", " << f2 << " and int: " << i << std::endl;
            if (data_idx%3 == 0) {
                test_data.push_back(p);
            } else {
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
    std::vector<std::vector<Points>> all_centers_in_each_step;
    std::vector<Points> centers;
    // Initialize center of each cluster

    for (int i = 0; i < NUM_K_CENTERS; i++)
    {
        centers.push_back(train_data[i]);
    }
    all_centers_in_each_step.push_back(centers);
    centers.clear();
    
    while (true)
    {
        int current_step = all_centers_in_each_step.size();
        int train_set_size = train_data.size();
        for (int i = 0; i < train_set_size; i++)
        {
            for (int j = 0; j < all_centers_in_each_step[current_step].size(); j++)
            {
                float dist = calculate_distance(all_centers_in_each_step[current_step][j], train_data[i]);
            }
        }
    }
    

    return 0;
}
