//
// Created by nikul on 22.12.2022.
//

#include "universalGraph.hpp"

void universalGraph::add_edge(edge e) {
    add_vertex(e.nodeFrom);
    add_vertex(e.nodeTo);
    g[e.nodeFrom].push_back(e);
    if (e.edgeId % 2 == 0)
        edges.push_back(e);
    if (e.nodeFrom != e.nodeTo && e.edgeId % 2 == 0)
        add_edge(e.getReversedEdge());
}

void universalGraph::add_vertex(int v) {
    if (g.find(v) == g.end()) {
        g[v];
        nodes.push_back(v);
    }
}

void universalGraph::printGraph(ostream& os) const
{
    for (const auto& adjList : this->g) {
        os << "Vertex id: " << adjList.first << "\n";
        for (const auto& edge : adjList.second) {
            os << "Adjacent edge:\n";
            edge.printEdge(os);
            os << "\n";
        }
        os << "\n";
    }
}
