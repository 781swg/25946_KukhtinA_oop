#include "cargo_robot.h"

#include <iostream>
#include <stdexcept>

int main() {
    {
        std::cout << "--- Empty cargo robot ---\n";
        const CargoRobot empty;
        empty.printInfo();
        empty.show_weight();

        std::cout << "--- Cargo robot with 20 kg ---\n";
        const CargoRobot loaded("Carrier", 20);
        loaded.printInfo();
        loaded.show_weight();

        std::cout << "--- Maximum weight ---\n";
        const CargoRobot full("Heavy", 50);
        full.show_weight();

        std::cout << "--- Overload ---\n";
        try {
            const CargoRobot overloaded("Overloaded", 60);
            overloaded.show_weight();
        } catch (const std::invalid_argument& error) {
            std::cout << error.what() << '\n';
        }
    }
    std::cout << "Objects left: " << Robot::getObjectCount() << '\n';
}
