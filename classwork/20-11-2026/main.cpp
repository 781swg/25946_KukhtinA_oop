#include "robot.h"

#include <iostream>

int main() {
    std::cout << "--- Quadruped robot ---\n";
    QuadrupedRobot robot("Rex");
    robot.move();

    std::cout << "--- Cargo quadruped robot ---\n";
    CargoQuadrupedRobot cargo("Carrier", 20);
    cargo.move();
    std::cout << "Cargo weight: " << cargo.getWeight() << " kg\n";
}
