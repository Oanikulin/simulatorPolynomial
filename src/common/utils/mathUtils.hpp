//
// Created by nikul on 21.01.2023.
//

#pragma once

#include "gmpxx.h"

inline mpq_class factorial(int value) {
    if (value <= 1)
        return mpq_class(1);
    return mpq_class(value) * factorial(value - 1);
}

inline mpq_class mpqPow(int base, int pw) {
    mpq_class res(1);
    for (int i = 1; i <= pw; ++i) {
        res *= 2;
    }
    return res;
}