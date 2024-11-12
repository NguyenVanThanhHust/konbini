cmake_minimum_required(VERSION 3.15)
project(knn VERSION 1.0 LANGUAGES CXX)

# Define a library
add_library(knn STATIC knn_cpu.h)
# Set the linker language for the target 
set_target_properties(knn PROPERTIES LINKER_LANGUAGE CXX)

# Define an executable
add_executable(sample_knn main.cpp)

# Link the executable with the library
target_link_libraries(sample_knn PRIVATE knn)
