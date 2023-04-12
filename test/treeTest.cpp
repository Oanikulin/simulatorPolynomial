//
// Created by nikul on 24.01.2023.
//

#include <gtest/gtest.h>
#include "src/graphs/universalGraph.hpp"
#include "src/graphs/trees/generalTree.hpp"
#include "src/common/edge.hpp"
#include "src/common/utils/graphUtils.hpp"
#include "src/common/utils/treeUtils.hpp"
#include "gmpxx.h"

// Demonstrate some basic assertions.
TEST(treeTest, BasicAssertions) {
    universalGraph testGraph;
    testGraph.add_edge({0, 1, 1});
    testGraph.add_edge({1, 2, 2});
    testGraph.add_edge({1, 3, 3});
}

TEST(treeTest, basicValuesStar) {
    universalGraph testGraph;
    testGraph.add_edge({0, 1, mpq_class(1, 2)});
    testGraph.add_edge({0, 2,  mpq_class(1, 3)});
    testGraph.add_edge({0, 3,  mpq_class(1, 5)});
    testGraph.add_edge({0, 4,  mpq_class(1, 7)});
    generalTree tr(testGraph, 0);
    EXPECT_EQ(polynomialFirstTerm(tr), mpq_class(247, 48));
    EXPECT_EQ(polynomialSecondTerm(tr), mpq_class(105, 4) * mpq_class(101, 210));
}