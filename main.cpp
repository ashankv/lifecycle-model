#include "common.h"
#include <chrono>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <omp.h>

// ==============
// Main Function
// ==============

int main(int argc, char** argv) {

    // Algorithm
    auto start_time = std::chrono::steady_clock::now();

#ifdef _OPENMP
#pragma omp parallel default(shared)
#endif
    {
        lifecycle();
    }

    auto end_time = std::chrono::steady_clock::now();

    std::chrono::duration<double> diff = end_time - start_time;
    double seconds = diff.count();

    // Finalize
    std::cout << "Simulation Time = " << seconds << " seconds for " << num_parts << " particles.\n";
}
