#include <iostream>

#include "verificationFormulas.hpp"
#include "src/graphs/universalGraph.hpp"
#include "src/simulation/simulation.hpp"
#include "src/common/edge.hpp"
#include "src/common/utils/graphUtils.hpp"
#include "src/common/utils/treeUtils.hpp"
#include "src/simulation/verification/baseGenerator.hpp"
#include "src/simulation/verification/treeGenerator.hpp"
#include "gmpxx.h"

#include <random>
#include <optional>

using namespace std;

void printState(MovementSimulation sim) {
    std::cout << "Step is " << sim.getStep() << std::endl;
    std::cout << "Point count is " << sim.getMovingPointsCount() << std::endl;
    std::cout << "Point list [from, to, arrive_time]:" << std::endl;
    for (auto pt : sim.getCurrentPoints()) {
        std::cout << " " << pt.fr << " " << pt.to << " " << pt.arriveTime << std::endl;
    }
    std::cout << endl;
}

bool checkRandomTree(std::mt19937& rnd) {
    int depth = rnd() % 50 + 2;
    treeGenerator gen;
    universalGraph g = gen.generateGraph(depth);
    auto simulation = MovementSimulation(g, 0);
    mpq_class lastTime = simulation.getEarliestUnmetTime();
    for (int i = 0; i < std::min(50, depth - 2); ++i) {
        //std::cerr << "new step " << std::endl;
        int theoreticalCount = getMovingPointCount(gen.getLastVertexByDepthCount(), gen.getLastEdgeLength(), lastTime);
        simulation.advanceSteps(1);
        int calculatedCount = simulation.getMovingPointsCount();
        if (calculatedCount != theoreticalCount) {
            std::cout << "Error. Theoretical point count: " << theoreticalCount << "\n";
            std::cout << "Simulation point count: " << calculatedCount << "\n";
            //g.printGraph(std::cout);
            std::cout << "Depth = " << gen.getLastVertexByDepthCount().size() << "\n";
            std::cout << "Vertex on depth count: ";
            for (auto cnt : gen.getLastVertexByDepthCount()) {
                std::cout << cnt << " ";
            }
            std::cout << "\n";
            printState(simulation);
            return false;
        }
        if (calculatedCount >= 1e6) {
            std::cout << "Generated tree with too many points. Worked correctly till step " << simulation.getStep() << std::endl;
            return true;
        }
        lastTime = simulation.getEarliestUnmetTime();
    }
    return true;
}

int main(int argc, char** argv) {
    std::mt19937 rand(time(0));
    int iteration_count = 10;
    if (argc != 1) {
        iteration_count = std::stoi(argv[1]);
    }
    for (int i = 0; i < iteration_count; ++i) {
        if (!checkRandomTree(rand)) {
            return 1;
        }
        std::cout << "done iteration" << std::endl;
    }
    return 0;
}
