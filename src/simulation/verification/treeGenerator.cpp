//
// Created by nikul on 17.04.2023.
//

#include "treeGenerator.hpp"

#include <random>
#include <ctime>
#include <vector>
#include <iostream>

#include "src/graphs/universalGraph.hpp"
#include "src/graphs/trees/generalTree.hpp"
#include "src/common/edge.hpp"
#include "baseGenerator.hpp"

#include "gmpxx.h"

universalGraph treeGenerator::generateGraph(int depth, int precision) {
    std::mt19937 rand(time(0));
    universalGraph g;
    if (precision == -1) {
        precision =  1LL * 2 * depth;
    }
    std::vector<std::vector<int>> vertex(depth);
    edges = generateSemiIndependentQuotes(depth, 10000, precision);
    vertex[0].push_back(0);
    vertexCount.resize(1, 1);
    int cnt = 1;
    for (int i = 1; i < depth; ++i) {
        int val = getNextSize(vertex[i - 1].size(), rand);
        vertexCount.push_back(val);
        for (int j = 0; j < val; ++j) {
            vertex[i].push_back(cnt);
            ++cnt;
        }
        for (int j = 0; j < vertex[i - 1].size(); ++j) {
            g.add_edge(edge(vertex[i - 1][j], vertex[i][j], edges[i - 1]));
        }
        for (int j = vertex[i - 1].size(); j < val; ++j) {
            int par = rand() % vertex[i - 1].size();
            g.add_edge(edge(vertex[i - 1][par], vertex[i][j], edges[i - 1]));
        }
    }
    return g;
}

std::vector<mpq_class> treeGenerator::getLastEdgeLength() {
    return edges;
}

std::vector<int> treeGenerator::getLastVertexByDepthCount() {
    return vertexCount;
}

int treeGenerator::getNextSize(int curSize, std::mt19937 rand) {
    return curSize + rand() % (curSize + 1);;
}
