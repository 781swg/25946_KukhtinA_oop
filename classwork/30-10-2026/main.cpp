#include "factory.h"
#include "squad.h"

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
    std::cout << "--- 9.III: aggregation ---\n";
    {
        std::array<Robot, 5> externalRobots;
        const int count = Robot::getObjectCount();
        {
            const AggregatedSquad squad({externalRobots[0], externalRobots[1],
                                         externalRobots[2], externalRobots[3],
                                         externalRobots[4]});
            squad.printInfo();
            std::cout << "Before squad destruction: " << Robot::getObjectCount() << '\n';
        }
        std::cout << "After squad destruction: " << Robot::getObjectCount()
                  << " (still " << count << ")\n";
        externalRobots[0].printInfo();
    }

    std::cout << "--- 9.III: composition ---\n";
    {
        const ComposedSquad squad;
        squad.printInfo();
        std::cout << "Before squad destruction: " << Robot::getObjectCount() << '\n';
    }
    std::cout << "After squad destruction: " << Robot::getObjectCount() << '\n';
    std::cout << "Objects left: " << Robot::getObjectCount() << '\n';
}
