#include <iostream>
#include <iomanip>
#include <chrono>

#include "src/simulation/verification/verificationFormulas.hpp"
#include "src/graphs/universalGraph.hpp"
#include "src/simulation/simulation.hpp"
#include "src/common/edge.hpp"
#include "src/common/utils/graphUtils.hpp"
#include "src/common/utils/treeUtils.hpp"
#include "src/simulation/verification/baseGenerator.hpp"
#include "src/simulation/verification/quadraticGridGenerator.hpp"
#include "gmpxx.h"

#include <random>
#include <optional>

using namespace std;

void measureRunTime(int n, int iterationCount) {
    quadraticGridGenerator gen;
    std::chrono::high_resolution_clock::time_point total;
    for (int i = 3; i <= 2 * n; ++i) {
        std::chrono::high_resolution_clock::time_point current;
        long double pointCount = 0;
        if (i <= n) {
            for (int j = 0; j < iterationCount; ++j) {
                const auto& start = std::chrono::high_resolution_clock::now();
                universalGraph g = gen.generateGraphPrecision(i, i);
                int theoreticalCount = getQuadraticGridPointCount(gen.getLastEdgeLength(), i);
                const auto& stop = std::chrono::high_resolution_clock::now();
                current += (stop - start);
                pointCount += theoreticalCount;
            }
        }
        std::chrono::duration<double, std::micro> dur = std::chrono::duration<double>(current.time_since_epoch());
        double micros = dur.count();
        micros /= iterationCount;
        pointCount /= iterationCount;
        std::cout << std::fixed << std::setprecision(20) << i << " " << i << " " << micros << " " << pointCount << std::endl;

        pointCount = 0;
        std::chrono::high_resolution_clock::time_point currentHalf;
        int tmpIterationCount = (i > n ? iterationCount / 2 : iterationCount);
        for (int j = 0; j < tmpIterationCount; ++j) {
            const auto& start = std::chrono::high_resolution_clock::now();
            universalGraph g = gen.generateGraphPrecision(i, i);
            int theoreticalCount = getQuadraticGridPointCount(gen.getLastEdgeLength(), i / 2);
            const auto& stop = std::chrono::high_resolution_clock::now();
            currentHalf += (stop - start);
            pointCount += theoreticalCount;
        }

        dur = std::chrono::duration<double>(currentHalf.time_since_epoch());;
        micros = dur.count();
        micros /= tmpIterationCount;
        pointCount /= tmpIterationCount;
        std::cout << std::fixed << std::setprecision(20) << i << " " << i / 2 << " " << micros << " " << pointCount << std::endl;
    }
}

int main(int argc, char** argv) {
    std::mt19937 rand(time(0));
    int maxn = 25;
    if (argc != 1) {
        maxn = std::stoi(argv[1]);
    }
    measureRunTime(maxn, 20);
    return 0;
}
