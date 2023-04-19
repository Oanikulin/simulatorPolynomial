#pragma once

#include <iostream>

#include "src/graphs/universalGraph.hpp"
#include "src/simulation/simulation.hpp"
#include "src/common/edge.hpp"
#include "src/common/utils/graphUtils.hpp"
#include "src/common/utils/treeUtils.hpp"
#include "src/simulation/verification/baseGenerator.hpp"
#include "src/simulation/verification/treeGenerator.hpp"
#include "gmpxx.h"

#include <random>
#include <optional>

int countSolutionNumber(const std::vector<mpq_class>& edges, mpq_class time, int L, int K, int ind) {
    int cnt = 0;
    if (time < 0)
        return 0;
    if (ind >= L)
        return 1;
    if (K - 1 == ind)
        return countSolutionNumber(edges, time, L, K, ind + 1);
    while (time >= 0) {
        cnt += countSolutionNumber(edges, time, L, K, ind + 1);
        time -= edges[ind];
    }
    return cnt;
}

int f(const std::vector<mpq_class>& edges, mpq_class time, int L, int K) {
    mpq_class tau = time;
    if (K < L) {
        for (int i = 0; i < K; ++i) {
            tau -= edges[i];
        }
        for (int i = K; i < L; ++i)
            tau -= 2 * edges[i];
    }
    else {
        for (int i = 0; i < K - 1; ++i) {
            tau -= edges[i];
        }
    }
    if (tau < 0) {
        return 0;
    }
    tau /= 2;
    int cnt  = countSolutionNumber(edges, tau, L, K, 0);
    return cnt;
}

int getMovingPointCount(const std::vector<int>& vertexCount, const std::vector<mpq_class>& edges, mpq_class time) {
    int md = vertexCount.size();
    int ans = vertexCount[1];
    for (int i = 2; i < md; ++i) {
        for (int k = 1; k <= i; ++k) {
            ans += vertexCount[k] * f(edges, time, i, k);
        }
    }
    return ans;
}
