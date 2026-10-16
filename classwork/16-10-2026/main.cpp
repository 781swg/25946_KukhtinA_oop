#include "robot.h"

#include <array>
#include <iostream>

int main() {
    const std::array<double, 10> history = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "Class: " << Robot::getClassName() << '\n';
    std::cout << "Before creation: " << Robot::getObjectCount() << '\n';

    {
        std::cout << "--- Constructors ---\n";
        Robot first;
        const Robot second("Rex", 80, "walk", 2.5, history);
        Robot third(second);

        std::cout << "--- Assignment ---\n";
        first = second;

        std::cout << "--- Const getters ---\n";
        std::cout << "Id: " << second.getId() << '\n';
        std::cout << "Name: " << second.getName() << '\n';
        std::cout << "Charge: " << second.getCharge() << '\n';
        std::cout << "Command: " << second.getCommand() << '\n';
        std::cout << "Today: " << second.getDistanceToday() << '\n';
        std::cout << "Last 10 days:";
        for (double distance : second.getDistances()) {
            std::cout << ' ' << distance;
        }
        std::cout << '\n';

        std::cout << "--- Robots ---\n";
        first.printInfo();
        second.printInfo();
        third.printInfo();

        std::cout << "--- Destructors ---\n";
    }

    std::cout << "After destruction: " << Robot::getObjectCount() << '\n';
    return 0;
}
