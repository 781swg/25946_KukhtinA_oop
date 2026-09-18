#include <random>

namespace modified {
    template <typename Result, typename First, typename Second>
    Result average(const First& a, const Second& b) {
        static std::random_device seed;
        static std::mt19937 gen(seed());
        static std::uniform_int_distribution<int> chance(0, 1);
        static std::uniform_int_distribution<int> number(1, 10);

        Result result = static_cast<Result>((a + b) / 2.0);
        if (chance(gen) == 1) {
            result += static_cast<Result>(number(gen));
        }
        return result;
    }
}
