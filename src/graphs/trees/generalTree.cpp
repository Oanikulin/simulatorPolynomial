//
// Created by nikul on 22.01.2023.
//

#include "generalTree.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <optional>
#include <numeric>

#include "../../common/edge.hpp"
#include "../../graphs/universalGraph.hpp"
#include "../../graphs/trees/generalTree.hpp"
#include "../../common/utils/mathUtils.hpp"
#include "gmpxx.h"

using std::map;

bool generalTree::precalcDfs(int v, int p, map<int, bool> &used)
{
    vector<edge> adjacent = getAdjacent(v);
    used[v] = true;
    for (const edge& nxt : adjacent) {
        int u = nxt.nodeTo;
        if (u == v)
            return true;
        if (used[u] && u != p)
            return true;
        parent.insert({v, nxt});
        if (u != p) {
            degree[v]++;
            degree[u]++;
            depth[u] = depth[v] + 1;
        }
        if (!used[u] && precalcDfs(u, v, used))
            return true;
    }
    return false;
}

bool generalTree::isCorrect() {
    map<int, bool> used;
    vector<int> graphNodes(std::move(getNodes()));
    if (graphNodes.empty())
        return true;
    if (precalcDfs(root, root, used))
        return false;
    return used.size() == graphNodes.size();
}

std::vector<edge> generalTree::getParentEdges(edge ed) {
    int v = ed.nodeTo;
    if (depth[ed.nodeFrom] > depth[ed.nodeTo])
        v = ed.nodeFrom;
    std::vector<edge> res;
    while (depth[v] != 0) {
        auto it = parent.find(v);
        if (it == parent.begin())
            break;
        edge prev = it->second;
        res.push_back(prev);
        v = prev.nodeTo;
        if (depth[prev.nodeFrom] < depth[prev.nodeTo])
            v = prev.nodeFrom;
    }
    return res;
}

std::vector<edge> generalTree::getEndEdges() {
    std::vector<edge> res;
    for (const edge& current : getEdges()) {
        if (degree[current.nodeTo] == 1 || degree[current.nodeFrom] == 1) {
            if (current.edgeId % 2)
                res.push_back(current.getReversedEdge());
            else
                res.push_back(current);
        }
    }
    return res;
}
