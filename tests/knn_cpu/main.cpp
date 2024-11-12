#include "knn_cpu.h"

int main()
{
    konbini::kNN<float> knn(2);
    knn.print_info();
    konbini::kNN<float> knn_v2(2, "eucliean");

    return 0;
}