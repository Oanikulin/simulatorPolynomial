//
// Created by nikul on 22.12.2022.
//

#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

#include "src/common/edge.hpp"

using std::ostream;
using std::vector;

class universalGraph {
protected:
    std::unordered_map<int, vector<edge>> g;
    vector<edge> edges;
    vector<int> nodes;

public:
    universalGraph() = default;

    explicit universalGraph(std::unordered_map<int, vector<edge>> graph) : g(std::move(graph))
    {
    }

    virtual void add_edge(edge e);

    virtual void add_vertex(int v);

    vector<edge> getAdjacent(int v)
    {
        return g[v];
    }

    vector<edge> getAdjacent(int v) const
    {
        if (g.find(v) == g.end())
            return {};
        return g.at(v);
    }

    vector<edge> getEdges() const
    {
        return edges;
    }

    vector<int> getNodes() const
    {
        return nodes;
    }

    virtual bool isCorrect()
    {
        return true;
    }

    void printGraph(ostream& os) const;

    virtual ~universalGraph() = default;
};


