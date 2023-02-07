//
// Created by nikul on 21.01.2023.
//

#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <numeric>

#include "../edge.hpp"
#include "../../graphs/universalGraph.hpp"
#include "../../graphs/trees/generalTree.hpp"
#include "mathUtils.hpp"
#include "gmpxx.h"

using std::map;

inline mpq_class polynomialFirstTerm(generalTree g)
{
    if (!g.isCorrect())
        throw std::invalid_argument("Graph is not tree");
    vector<edge> edges(g.getEdges());
    int edge_count = static_cast<int>(edges.size());
    mpq_class answer = mpq_class(1) / (factorial(edge_count - 1) * mpqPow(2, edge_count - 1));
    mpq_class sm = 0;
    mpq_class prod = 1;
    for (int i = 0; i < edges.size(); ++i) {
        sm += edges[i].value;
        prod *= edges[i].value;
    }
    answer = answer * sm / prod;
    return answer;
}

inline mpq_class polynomialSecondTerm(generalTree g)
{
    if (!g.isCorrect())
        throw std::invalid_argument("Graph is not tree");
    vector<edge> edges(g.getEdges());
    int edge_count = static_cast<int>(edges.size());
    if (edge_count < 2)
        return 0;
    mpq_class answer = mpq_class(1) / (factorial(edge_count - 2) * mpqPow(2, edge_count - 2));
    mpq_class prod = 1;
    for (int i = 0; i < edges.size(); ++i) {
        prod *= edges[i].value;
    }
    answer /= prod;
    vector<edge> endEdges = g.getEndEdges();
    mpq_class upperSum = 0;
    mpq_class endSum = 0;
    mpq_class mixSum = 0;
    for (const edge& cur : edges) {
        for (const edge& oth : edges) {
            upperSum += oth.value * cur.value;
        }
        endSum += cur.value * cur.value;
        vector<edge> upper = g.getParentEdges(cur);
        for (const edge& oth : upper) {
            upperSum -= oth.value * cur.value;
        }
    }
    for (const edge& cur : endEdges) {
        for (const edge& oth : edges) {
            mixSum += (oth.edgeId != cur.edgeId) * (oth.value * cur.value);
        }
        endSum -= cur.value * cur.value;
    }
    mpq_class p2 = -mpq_class(1, 2) * upperSum - mpq_class(1, 2) * endSum + mixSum;
    return answer * p2;
}


