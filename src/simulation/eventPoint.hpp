#pragma once

#include "gmpxx.h"

struct eventPoint {
    mpq_class arriveTime;
    int fr;
    int to;

    bool operator < (const eventPoint& other) const {
        return arriveTime < other.arriveTime ||
                (arriveTime == other.arriveTime && fr < other.fr) ||
                (arriveTime == other.arriveTime && fr == other.fr && to < other.to);
    }
};