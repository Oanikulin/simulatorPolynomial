#pragma once

#include <random>

#include "src/graphs/universalGraph.hpp"
#include "baseGenerator.hpp"

#include "gmpxx.h"

class treeGenerator : private baseGenerator {
public:
    universalGraph generateGraph(int depth, int precision = -1) override;

    std::vector<mpq_class> getLastEdgeLength();

    std::vector<int> getLastVertexByDepthCount();

protected:
    virtual int getNextSize(int curSize, std::mt19937 rand);

private:
    std::vector<mpq_class> edges;
    std::vector<int> vertexCount;
};