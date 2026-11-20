#include "robot.h"
#include "diamond_example.h"

#include <iostream>

int main() {
    std::cout << "--- Diamond problem: two base objects ---\n";
    const diamond::AutonomousCargoRobot bad("Cargo name", "Autonomous name");
    // bad.getName(); // Ошибка: неясно, из какой ветви брать имя.
    std::cout << bad.CargoRobot::getName() << '\n';
    std::cout << bad.AutonomousRobot::getName() << '\n';
    const diamond::QuadrupedRobot* leftBad = static_cast<const diamond::CargoRobot*>(&bad);
    const diamond::QuadrupedRobot* rightBad = static_cast<const diamond::AutonomousRobot*>(&bad);
    std::cout << "Same base object: " << std::boolalpha << (leftBad == rightBad) << '\n';

    std::cout << "--- Individual robots ---\n";
    const QuadrupedRobot robot("Rex");
    const CargoRobot cargo("Carrier", 20);
    const AutonomousRobot autonomous("Scout", 100);
    std::cout << robot.getName() << '\n';
    std::cout << cargo.getName() << ": " << cargo.getWeight() << " kg\n";
    std::cout << autonomous.getName() << ": " << autonomous.getRange() << " km\n";

    std::cout << "--- Solution: virtual inheritance ---\n";
    const AutonomousCargoRobot combined("AutoCarrier", 30, 80);
    std::cout << combined.getName() << ": " << combined.getWeight()
              << " kg, " << combined.getRange() << " km\n";
    const QuadrupedRobot* left = static_cast<const CargoRobot*>(&combined);
    const QuadrupedRobot* right = static_cast<const AutonomousRobot*>(&combined);
    std::cout << "Same base object: " << (left == right) << '\n';
}
