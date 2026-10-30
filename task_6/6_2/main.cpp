#include "robot.h"
#include <iostream>

int main() {
    std::cout << "--- создание ---\n";
    QuadrupedRobot first;
    QuadrupedRobot second("барс", 150, "идти", -2);

    std::cout << "--- нормализация ---\n";
    second.setDayDistance(0, 3.5);
    second.setDayDistance(1, -4);
    second.print();

    std::cout << "--- копирование ---\n";
    QuadrupedRobot third = second;
    third.print();

    std::cout << "--- присваивание ---\n";
    first = second;
    first.print();

    std::cout << "--- id после присваивания ---\n";
    std::cout << first.getId() << " != " << second.getId() << '\n';
}
