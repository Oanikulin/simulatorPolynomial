#pragma once

#include <vector>
#include "src/graphs/universalGraph.hpp"

#include "gmpxx.h"

class baseGenerator {
public:
    virtual universalGraph generateGraph(int depth, int precision = -1) = 0;


    virtual  ~baseGenerator() = default;

protected:
    //The functions generates quotes, as 1/p_i, where p_i is prime and >= startingStep
    //For very big n creates bad distribution with small abs value of some numbers
    virtual std::vector<mpq_class> generateSemiIndependentQuotes(int n, int startingStep, int precision);
private:
    std::vector<int> getPrimes(int startingStep, int n);

    static const int N = 10000000;
};
