#include <iostream>
#include "average.h"
#include "average_random.h"

int main() {
    int a = 10;
    int b = 20;

    std::cout << "Ordinary average: " << orig::average(a, b) << '\n';
    std::cout << "Random average: " << modified::average_random(a, b) << '\n';

    return 0;
}
