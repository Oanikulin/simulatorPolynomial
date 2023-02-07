#pragma once

#include <iostream>
#include <fstream>

#include "../edge.hpp"
#include "../../graphs/universalGraph.hpp"
#include "gmpxx.h"


std::atomic<int64_t> edge::edgeCounter(0);

inline universalGraph readGraph(std::istream& in) {
    int from, to;
    mpq_class value;
    universalGraph res;
    while (in >> from >> to >> value) {
        res.add_edge({from, to, value});
    }
    return res;
}

inline universalGraph readGraph() {
    return readGraph(std::cin);
}

inline universalGraph readGraphFromFile(std::string filename) {
    std::ifstream file;
    file.open(filename);
    return readGraph(file);
}


