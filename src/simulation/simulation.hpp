#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include <set>

#include "src/simulation/eventPoint.hpp"
#include "src/graphs/universalGraph.hpp"
#include "gmpxx.h"

class MovementSimulation {
public:

    MovementSimulation(universalGraph graph, int root);

    int64_t getMovingPointsCount() noexcept;

    void makeStep();

    void advanceSteps(int stepCount);

    int64_t getStep() noexcept;

    mpq_class getEarliestUnmetTime();

    std::vector<eventPoint> getCurrentPoints();

protected:
    void addPointsForVertex(int v, mpq_class startTime);

    std::map<mpq_class, std::set<eventPoint>> pointsByEnd;
    universalGraph g;
    int64_t pointCount = 0;
    int64_t step = 0;
};