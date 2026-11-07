#include "cargo_robot.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

CargoRobot::CargoRobot() : Robot(), weight(0) {
}

// Проверяем массу при создании: груз от 0 до 50 кг включительно.
CargoRobot::CargoRobot(const std::string& name, double weight)
    : Robot(name, 100, "stand", 0, {}), weight(weight) {
    if (!std::isfinite(weight) || weight < 0 || weight > maxWeight) {
        throw std::invalid_argument("Cargo weight must be between 0 and 50 kg");
    }
}

void CargoRobot::show_weight() const {
    std::cout << "Cargo weight: " << weight << " / " << maxWeight << " kg\n";
}

double CargoRobot::getWeight() const {
    return weight;
}
