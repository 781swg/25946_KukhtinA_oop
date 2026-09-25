#pragma once
#include <random>

namespace mod {

    template <typename T1, typename T2>
    T2 average(const T1& a, const T1& b) {
        static std::random_device seed;
        static std::mt19937 gen(seed());
        static std::uniform_int_distribution<int> chance(0, 1);
        static std::uniform_int_distribution<int> number(1, 10);

        T2 result = static_cast<T2>((a + b) / 2.0);

        if (chance(gen) == 1) {
            result += static_cast<T2>(number(gen));
        }

        return result;
    }

}