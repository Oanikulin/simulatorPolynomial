//
// Created by nikul on 22.12.2022.
//

#pragma once

#include <iostream>
#include <type_traits>
#include <cstdint>
#include <atomic>

#include "gmpxx.h"

using std::ostream;

//template<typename T>
struct edge
{
    static std::atomic<int64_t> edgeCounter;
    int nodeFrom;
    int nodeTo;
    mpq_class  value;
    int64_t edgeId;

    edge(int from, int to, mpq_class length) noexcept : nodeFrom(from), nodeTo(to), value(length)
    {
        value.canonicalize();
        edgeId = edgeCounter.fetch_add(2);
    }

    [[nodiscard]] edge getReversedEdge() const noexcept
    {
        return edge(nodeTo, nodeFrom, value, edgeId ^ 1);
    }

    void printEdge(ostream& os) const
    {
        os << " To: " << this->nodeTo << "\n";
        os << " Id: " << this->edgeId << "\n";
        os << " Value: " << this->value << "\n";
    }

protected:
    edge(int from, int to, mpq_class length, int64_t id) noexcept
        : nodeFrom(from), nodeTo(to), value(length), edgeId(id)
    {
        value.canonicalize();
    }
};

