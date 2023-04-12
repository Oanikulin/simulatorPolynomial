#include "simulation.hpp"

#include <cstdint>
#include <vector>

#include "src/simulation/eventPoint.hpp"
#include "src/graphs/universalGraph.hpp"
#include "gmpxx.h"

int64_t MovementSimulation::getMovingPointsCount() noexcept {
    return pointCount;
}

void MovementSimulation::makeStep() {
    if (pointsByEnd.size() == 0)
    {
        return;
    }
    ++step;
    auto st = pointsByEnd.begin();
    pointCount -= st->second.size();
    for (const auto& v : st->second) {
        addPointsForVertex(v.to, st->first);
    }
    pointsByEnd.erase(pointsByEnd.begin());
}

void MovementSimulation::advanceSteps(int stepCount) {
    for (int i = 0; i < stepCount; ++i)
        makeStep();
}

std::vector<eventPoint> MovementSimulation::getCurrentPoints() {
    std::vector<eventPoint> res;
    for (const auto& st : pointsByEnd) {
        res.insert(res.end(), st.second.begin(), st.second.end());
    }
    return res;
}

MovementSimulation::MovementSimulation(universalGraph graph, int root): g(graph) {
    addPointsForVertex(root, mpq_class(0));
}

void MovementSimulation::addPointsForVertex(int v, mpq_class startTime) {
    std::vector<edge> starting = g.getAdjacent(v);
    for (const auto& cur : starting) {
        pointCount -= pointsByEnd[startTime + cur.value].size();
        pointsByEnd[startTime + cur.value].insert({startTime + cur.value, cur.nodeFrom, cur.nodeTo});
        pointCount += pointsByEnd[startTime + cur.value].size();
    }
}

int64_t MovementSimulation::getStep() noexcept {
    return step;
}
