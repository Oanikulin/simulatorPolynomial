#include <iostream>

#include "src/graphs/universalGraph.hpp"
#include "src/common/edge.hpp"
#include "src/common/utils/graphUtils.hpp"
#include "src/common/utils/treeUtils.hpp"
#include "gmpxx.h"

#include <optional>

using namespace std;

int main() {
    auto tr = generalTree(readGraph(), 0);
    cout << polynomialFirstTerm(tr) << " " << polynomialSecondTerm(tr) << endl;
    return 0;
}
