#include "robot.h/"
#include <iostream>

int main() {
    std::cout << "--- создание ---\n";
    QuadrupedRobot first;
    QuadrupedRobot second("барс", 80, "идти", 3.5);

    std::cout << "--- копирование ---\n";
    QuadrupedRobot third = second;

    std::cout << "--- присваивание ---\n";
    first = second;

    std::cout << "--- состояние ---\n";
    first.print();
    second.print();
    third.print();
}

