#pragma once

#include <random>

#include "treeGenerator.hpp"

class fullTreeGenerator : public treeGenerator {
protected:
    int getNextSize(int curSize, std::mt19937 rand) override;
};
