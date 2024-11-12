cmake_minimum_required(VERSION 3.18)
project(knn_gpu LANGUAGES CXX CUDA)

# Optionally, link against CUDA libraries
find_package(CUDAToolkit REQUIRED)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Add the executable
add_executable(knn_gpu_app main.cpp knn_gpu.cuh knn_gpu.cu)

# Specify additional include directories
target_include_directories(knn_gpu_app PRIVATE ${PROJECT_SOURCE_DIR}/include)

include(FindCUDA/select_compute_arch)
CUDA_DETECT_INSTALLED_GPUS(INSTALLED_GPU_CCS_1)
string(STRIP "${INSTALLED_GPU_CCS_1}" INSTALLED_GPU_CCS_2)
string(REPLACE " " ";" INSTALLED_GPU_CCS_3 "${INSTALLED_GPU_CCS_2}")
string(REPLACE "." "" CUDA_ARCH_LIST "${INSTALLED_GPU_CCS_3}")
SET(CMAKE_CUDA_ARCHITECTURES ${CUDA_ARCH_LIST})
message("$(CUDA_ARCH_LIST)")

set_property(TARGET knn_gpu_app PROPERTY "${CUDA_ARCH_LIST}")
# Set CUDA properties
set_target_properties(knn_gpu_app PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
)

target_link_libraries(knn_gpu_app PRIVATE CUDA::cudart)

