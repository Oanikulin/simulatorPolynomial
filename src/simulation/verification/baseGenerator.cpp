#include "baseGenerator.hpp"

#include <algorithm>
#include <vector>
#include <stdexcept>

#include "gmpxx.h"

std::vector<mpq_class> baseGenerator::generateSemiIndependentQuotes(int n, int startingStep, int precision) {
    std::vector<mpq_class> res;
    std::vector<int> primeNumbers = getPrimes(startingStep, n);
    for (int i = 0; i < n; ++i) {
        res.push_back(mpq_class(1, primeNumbers[i]));
    }
    std::random_shuffle(res.begin(), res.end());
    return res;
}

std::vector<int> baseGenerator::getPrimes(int startingStep, int n) {
    std::vector<int> lp(N);
    std::vector<int> pr;
    std::vector<int> prres;

    for (int i = 2; i <= N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
            if (i >= startingStep) {
                prres.push_back(i);
                if (prres.size() == n)
                    return prres;
            }
        }
        for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=N; ++j)
            lp[i * pr[j]] = pr[j];
    }
    throw std::invalid_argument("Requested prime is too big " + std::to_string(n) + " from " + std::to_string(startingStep));
}
