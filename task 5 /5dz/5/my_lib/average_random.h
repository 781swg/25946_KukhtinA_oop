#pragma once
#include "average.h"
#include <random>

namespace modified {
    template <typename T>
    T average_random(const T& a, const T& b) {
        T result = orig::average(a, b);

        static std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<int> chance(0, 1);
        std::uniform_int_distribution<int> bonus(1, 10);

        if (chance(generator) == 1) {
            result += static_cast<T>(bonus(generator));
        }
        return result;
    }
}
