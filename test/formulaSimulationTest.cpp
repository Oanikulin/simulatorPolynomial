#include <gtest/gtest.h>
#include "src/graphs/universalGraph.hpp"
#include "src/graphs/trees/generalTree.hpp"
#include "src/simulation/verification/baseGenerator.hpp"
#include "src/simulation/verification/treeGenerator.hpp"
#include "src/simulation/verification/chainGenerator.hpp"
#include "src/simulation/verification/verificationFormulas.hpp"
#include "src/common/edge.hpp"
#include "src/common/utils/graphUtils.hpp"
#include "src/common/utils/treeUtils.hpp"
#include "gmpxx.h"

TEST(formulaTest, generateRandomChain) {
    for (int i = 0; i < 10; ++i) {
        universalGraph g = chainGenerator().generateGraph(i + 2);
        generalTree tr(g, 0);
        EXPECT_TRUE(tr.isCorrect());
    }
}

TEST(formulaTest, chainFormulaTest) {
    for (int i = 4; i < 10; ++i) {
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
    }
}

TEST(formulaTest, longChainFormulaTest) {
    for (int i = 20; i < 50; ++i) {
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
    }
}
