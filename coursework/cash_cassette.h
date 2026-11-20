#pragma once

#include <stdexcept>

class CashCassette {
private:
    int denomination;
    int count;

public:
    CashCassette(int denomination, int count)
        : denomination(denomination), count(count) {
        if (denomination <= 0 || count < 0) {
            throw std::invalid_argument("Invalid cassette parameters");
        }
    }
    int getDenomination() const { return denomination; }
    int getCount() const { return count; }
};
