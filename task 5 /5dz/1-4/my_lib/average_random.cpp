#include "average_random.h"
#include "average.h"
#include <random>

namespace modified {
    int average_random(const int& a, const int& b) {
        int result = orig::average(a, b);

        // Reuse one random-number generator across function calls.
        static std::mt19937 generator(std::random_device{}());

        // 0 or 1 with equal probability.
        std::uniform_int_distribution<int> chance(0, 1);
        // An integer from 1 to 10, inclusive.
        std::uniform_int_distribution<int> bonus(1, 10);

        if (chance(generator) == 1) {
            result += bonus(generator);
        }
        return result;
    }
}
