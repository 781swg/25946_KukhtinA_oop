#include "robot.h"
#include <iostream>

int main() {
    std::cout << "--- создание ---\n";
    QuadrupedRobot a("барс", 90, "идти", 3.0);
    a.setDayDistance(0, 2.5);
    a.setLegAngle(0, 30);
    a.setLegAngle(1, -25);
    a.print();

    std::cout << "--- глубокое копирование ---\n";
    QuadrupedRobot b = a;
    a.setLegAngle(0, 50);
    std::cout << "оригинал: " << a.getLegAngle(0) << '\n';
    std::cout << "копия: " << b.getLegAngle(0) << '\n';

    std::cout << "--- присваивание ---\n";
    QuadrupedRobot c;
    c = a;
    std::cout << "id до и после присваивания не меняется: " << c.getId() << '\n';
    c.print();

    std::cout << "--- уничтожение объектов ---\n";
}
