#include "factory.h"

#include <iostream>

int main() {
    {
        Robot robot;
        std::cout << "--- Initial state ---\n";
        robot.printInfo();

        std::cout << "--- 9.I: friend function ---\n";
        setManufacturer(robot, "NSU Robotics");
        robot.printInfo();

        std::cout << "--- 9.I: friend class Factory ---\n";
        const Factory factory;
        const std::array<double, 10> history = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        factory.configure(robot, "Rex", 90, "walk", 3.5, history,
                          "NSU Robotics", "Q-1");
        robot.printInfo();

        std::cout << "--- 9.II: friend method of Administrator ---\n";
        const Administrator admin;
        admin.setModel(robot, "Q-2");
        robot.printInfo();

        std::cout << "--- Destructors ---\n";
    }
    std::cout << "Objects left: " << Robot::getObjectCount() << '\n';
}
