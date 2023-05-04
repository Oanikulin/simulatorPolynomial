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
#include "src/simulation/verification/chainGenerator.hpp"
#include "gmpxx.h"

#include <random>
#include <optional>

int main() {
    chainGenerator gen;
    int maxn = 30;
    universalGraph g = gen.generateGraph(maxn);
    auto simulation = MovementSimulation(g, 0);
    mpq_class lastTime = 0;
    mpq_class time(0);
    for (int k = 0; k < 30; ++k) {
        time += mpq_class(1, 1);
        int theoreticalCount = getMovingPointCount(gen.getLastVertexByDepthCount(), gen.getLastEdgeLength(), time);
        std::cout << mpf_class(time) << " " << theoreticalCount << std::endl;
    }
    int prev_count = 0;
    while (lastTime < mpq_class(30, 1)) {
        mpf_class currentTime = mpf_class(simulation.getEarliestUnmetTime());
        simulation.advanceSteps(1);
        int calculatedCount = simulation.getMovingPointsCount();
        if (calculatedCount != prev_count && currentTime - lastTime > mpq_class(1, 100000)) {
            std::cout << std::fixed << std::setprecision(20) << " " << currentTime << " ";
            std::cout << std::fixed << std::setprecision(20) << " " << simulation.getMovingPointsCount() << std::endl;
            prev_count = calculatedCount;
            lastTime = currentTime;
        }
    }
    return 0;
}