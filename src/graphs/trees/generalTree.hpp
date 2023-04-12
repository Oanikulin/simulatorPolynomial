#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <map>

#include "src/common/edge.hpp"
#include "src/graphs/universalGraph.hpp"

using std::ostream;
using std::vector;

class generalTree : public universalGraph {
protected:
    int root;
    std::map<int, edge> parent;
    std::map<int, int> depth;
    std::map<int, int> degree;
public:

    generalTree(const universalGraph& g, int root): universalGraph(g), root(root)
    {

    }

    virtual bool precalcDfs(int v, int p, std::map<int, bool>& used);

    bool isCorrect() override;

    //includes input edge
    std::vector<edge> getParentEdges(edge ed);

    std::vector<edge> getEndEdges();
};