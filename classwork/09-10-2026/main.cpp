#include "robot.h"

#include <array>
#include <iostream>

int main() {
    const std::array<double, 10> history = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "--- Constructors ---\n";
    Robot first;
    Robot second("Rex", 80, "walk", 2.5, history);
    Robot third(second);

    std::cout << "--- Assignment ---\n";
    first = second;

    std::cout << "--- Robots ---\n";
    first.printInfo();
    second.printInfo();
    third.printInfo();

    std::cout << "--- Destructors ---\n";
    return 0;
}
