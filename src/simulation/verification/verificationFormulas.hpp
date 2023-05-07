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

long long getMovingPointCount(const std::vector<int>& vertexCount, const std::vector<mpq_class>& edges, mpq_class time) {
    int md = vertexCount.size();
    long long  ans = vertexCount[1];
    for (int i = 2; i < md; ++i) {
        for (int k = 1; k <= i; ++k) {
            ans += 1LL * vertexCount[k] * f(edges, time, i, k);
        }
    }
    return ans;
}

int getSamePointSolutionCount(const std::vector<mpq_class>& edge_i, const std::vector<mpq_class>& edge_j, int i, int j, mpq_class time) {
    std::vector<mpq_class> coef;
    //std::cout << time << std::endl;
    for (int k = 0; k < i; ++k) {
        time -= edge_i[k];
        coef.push_back(2 * edge_i[k]);
    }
    for (int k = 0; k < j; ++k) {
        time -= edge_j[k];
        coef.push_back(2 * edge_j[k]);
    }
    if (time < 0) {
        return 0;
    }
    //std::cout << "same " << i << " " << j << " " << time << std::endl;
    return 2 * countSolutionNumber(coef, time, coef.size(), coef.size() + 5, 0);
}

int getDifferentPointsSolutionCount(const std::vector<mpq_class>& edge_i, const std::vector<mpq_class>& edge_j, int i, int j, int il, int jl, mpq_class time) {
    std::vector<mpq_class> coef;
    mpq_class t = time;
    int ans = 0;
    if (i != 0) {
        for (int k = 0; k < j; ++k) {
            time -= edge_j[k];
            coef.push_back(2 * edge_j[k]);
        }
        for (int k = j; k < jl; ++k) {
            time -= 2 * edge_j[k];
            coef.push_back(2 * edge_j[k]);
        }
        for (int k = 0; k < i - 1; ++k) {
            time -= edge_i[k];
            coef.push_back(2 * edge_i[k]);
        }
        time -= edge_i[i - 1];
        for (int k = i; k < il; ++k) {
            time -= 2 * edge_i[k];
            coef.push_back(2 * edge_i[k]);
        }
        if (time >= 0) {
            ans += countSolutionNumber(coef, time, coef.size(), coef.size() + 5, 0);
        }
    }

    if (j != 0) {
        time = t;
        coef.resize(0);
        for (int k = 0; k < i; ++k) {
            time -= edge_i[k];
            coef.push_back(2 * edge_i[k]);
        }
        for (int k = i; k < il; ++k) {
            time -= 2 * edge_i[k];
            coef.push_back(2 * edge_i[k]);
        }
        for (int k = 0; k < j - 1; ++k) {
            time -= edge_j[k];
            coef.push_back(2 * edge_j[k]);
        }
        time -= edge_j[j - 1];
        for (int k = j; k < jl; ++k) {
            time -= 2 * edge_j[k];
            coef.push_back(2 * edge_j[k]);
        }
        if (time >= 0) {
            ans += countSolutionNumber(coef, time, coef.size(), coef.size() + 5, 0);
        }
    }
    return ans;
}

int getOneDifferentPointSolutionCount (const std::vector<mpq_class>& edge_i, const std::vector<mpq_class>& edge_j, int i, int j, int il, int jl, mpq_class time) {
    std::vector<mpq_class> coef;
    mpq_class t = time;
    int ans = 0;
    for (int k = 0; k < j; ++k) {
        time -= edge_j[k];
        coef.push_back(2 * edge_j[k]);
    }
    for (int k = 0; k < i - 1; ++k) {
        time -= edge_i[k];
        coef.push_back(2 * edge_i[k]);
    }
    if (i != 0)
        time -= edge_i[i - 1];
    for (int k = i; k < il; ++k) {
        time -= 2 * edge_i[k];
        coef.push_back(2 * edge_i[k]);
    }
    if (i != 0 && time >= 0) {
        ans += countSolutionNumber(coef, time, coef.size(), coef.size() + 5, 0);
    }
    coef.push_back(2 * edge_i[i]);
    if (time >= 0) {
        ans += countSolutionNumber(coef, time, coef.size(), coef.size() + 5, 0);
    }
    return ans;
}

int getQuadraticGridPointCount(const std::pair<std::vector<mpq_class>, std::vector<mpq_class>>& edges, mpq_class time) {
    int height = edges.first.size();
    int w = edges.second.size();
    int ans = 2;
    for (int il = 0; il < height; ++il) {
        for (int jl = 0; jl < w; ++jl) {
            for (int i = 0; i <= il; ++i) {
                for (int j = 0; j <= jl; ++j) {
                    if (mpq_class(il) > time || mpq_class(jl) > time)
                        continue;
                    if (i == 0 && j == 0 && il == 0 && jl == 0)
                        continue;
                    //std::cout << "syart " << i << " " << j << " " << il << " " << jl << std::endl;
                    int prevans = ans;
                    if (i == il && j == jl) {
                        //std::cout << "Same point" << std::endl;
                        ans += getSamePointSolutionCount(edges.first, edges.second, i, j, time);
                        /*if (prevans != ans) {
                            std::cout << "same point  " << i << " " << j << " " << il << " " << jl << " " << prevans << " " << ans << std::endl;
                        }*/
                    }
                    else if (i != il && j != jl) {
                        prevans = ans;
                        ans += getDifferentPointsSolutionCount(edges.first, edges.second, i, j, il, jl, time);
                        /*if (prevans != ans) {
                            std::cout << "all different " << i << " " << j << " " << il << " " << jl << " " << prevans << " " << ans << std::endl;
                        }*/
                    }
                    else if (i != il) {
                        prevans = ans;
                        ans += getOneDifferentPointSolutionCount(edges.first, edges.second, i, j, il, jl, time);
                        /*if (prevans != ans) {
                            std::cout << "i different " << i << " " << j << " " << il << " " << jl << " " << prevans << " " << ans << std::endl;
                        }*/
                    }
                    //j != jl
                    else {
                        prevans = ans;
                        ans += getOneDifferentPointSolutionCount(edges.second, edges.first, j, i, jl, il, time);
                        /*if (prevans != ans) {
                            std::cout << "j different " << i << " " << j << " " << il << " " << jl << " " << prevans << " " << ans << std::endl;
                        }*/
                    }
                }
            }
        }
    }
    return ans;
}