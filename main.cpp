#include <iostream>

#include "src/graphs/universalGraph.hpp"
#include "src/simulation/simulation.hpp"
#include "src/common/edge.hpp"
#include "src/common/utils/graphUtils.hpp"
#include "src/common/utils/treeUtils.hpp"
#include "gmpxx.h"

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
int main(int argc, char** argv) {
    universalGraph gr;
    if (argc != 1) {
        gr = readGraphFromFile(argv[1]);
    } else {
        gr = readGraph();
    }
    auto simulation = MovementSimulation(gr, 0);
    int cnt = 0;
    printState(simulation);
    while (cin >> cnt) {
        simulation.advanceSteps(cnt);
        printState(simulation);
    }
    return 0;
}
