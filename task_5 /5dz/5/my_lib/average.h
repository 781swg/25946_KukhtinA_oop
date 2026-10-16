#pragma once

namespace orig {
    template <typename T>
    T average(const T& a, const T& b) {
        return (a + b) / static_cast<T>(2);
    }
}
