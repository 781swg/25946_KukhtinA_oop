#include <iostream>
#include "average.h"
#include "average_random.h"

int main() {
    std::cout << "int average: " << orig::average(10, 20) << '\n';
    std::cout << "double average: " << orig::average(10.0, 21.0) << '\n';
    std::cout << "int random average: " << modified::average_random(10, 20) << '\n';
    std::cout << "double random average: " << modified::average_random(10.0, 21.0) << '\n';
    return 0;
}
