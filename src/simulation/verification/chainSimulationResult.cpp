

int main() {
    chainGenerator gen;
    universalGraph g = gen.generateGraph(i);
    int depth = i;
    auto simulation = MovementSimulation(g, 0);
    mpq_class lastTime = simulation.getEarliestUnmetTime();
    for (int k = 0; k < std::min(50, depth - 2); ++k) {
        int theoreticalCount = getMovingPointCount(gen.getLastVertexByDepthCount(), gen.getLastEdgeLength(), lastTime);
        simulation.advanceSteps(1);
        int calculatedCount = simulation.getMovingPointsCount();
        ASSERT_EQ(calculatedCount, theoreticalCount);
        lastTime = simulation.getEarliestUnmetTime();
    }
    retunr 0;
}