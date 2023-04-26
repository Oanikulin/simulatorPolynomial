#include "quadraticGridGenerator.hpp"

#include <random>
#include <ctime>
#include <vector>
#include <iostream>

#include "src/graphs/universalGraph.hpp"
#include "src/graphs/trees/generalTree.hpp"
#include "src/common/edge.hpp"
#include "baseGenerator.hpp"

#include "gmpxx.h"

universalGraph quadraticGridGenerator::generateGraph(int depth) {
    return generateGraph(depth, depth);
}

universalGraph quadraticGridGenerator::generateGraph(int height, int width, int precision) {
    std::mt19937 rand(time(0));
    universalGraph g;
    int totalSize = height + width;
    if (precision == -1) {
        precision = 1LL * 2 * totalSize;
    }
    std::vector<std::vector<int>> vertex(totalSize);
    std::vector<mpq_class> totalEdges = generateSemiIndependentQuotes(totalSize, 10000, precision);
    std::vector<mpq_class> heightEdges, widthEdges;
    for (int i = 0; i < totalSize; ++i) {
        if (i < height)
            heightEdges.push_back(totalEdges[i]);
        else
            widthEdges.push_back(totalEdges[i]);
    }
    edges = {heightEdges, widthEdges};
    vertexes.resize(height, std::vector(width, 0));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            vertexes[i][j] = i * width + j;
            if (i + 1 < height) {
                g.add_edge(edge(i * width + j, (i + 1) * width + j, heightEdges[i + 1]));
            }
            if (j  + 1 < width) {
                g.add_edge(edge(i * width + j, i * width + j + 1, widthEdges[j + 1]));
            }
        }
    }
    return g;
}

std::pair<std::vector<mpq_class>, std::vector<mpq_class>> quadraticGridGenerator::getLastEdgeLength() {
    return edges;
}

std::vector<std::vector<int>> quadraticGridGenerator::getVertexes() {
    return vertexes;
}
