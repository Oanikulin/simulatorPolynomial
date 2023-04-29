//
// Created by nikul on 27.04.2023.
//

#include "fullTreeGenerator.hpp"
#include <random>

int fullTreeGenerator::getNextSize(int curSize, std::mt19937 rand) {
    return 2 * curSize;
}