#pragma once

#include <random>

#include "src/graphs/universalGraph.hpp"
#include "baseGenerator.hpp"

#include "gmpxx.h"

class quadraticGridGenerator : private baseGenerator {
public:
    universalGraph generateGraph(int depth, int precision = -1) override;

    virtual universalGraph generateGraphPrecision(int height, int width, int precision = -1);

    std::pair<std::vector<mpq_class>, std::vector<mpq_class>> getLastEdgeLength();

    std::vector<std::vector<int>> getVertexes();

private:
    std::pair<std::vector<mpq_class>, std::vector<mpq_class>> edges;
    std::vector<std::vector<int>> vertexes;
};