#include "robot.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

Robot::Robot(const std::string& name) : name(name) {
    if (name.empty()) {
        throw std::invalid_argument("Robot name must not be empty");
    }
}

const std::string& Robot::getName() const {
    return name;
}

QuadrupedRobot::QuadrupedRobot(const std::string& name) : Robot(name) {
}

// Реализация чистого виртуального метода для обычного квадропедального робота.
void QuadrupedRobot::move() {
    std::cout << getName() << ": walking on four legs\n";
}

CargoQuadrupedRobot::CargoQuadrupedRobot(const std::string& name, double weight)
    : QuadrupedRobot(name), weight(weight) {
    if (!std::isfinite(weight) || weight < 0 || weight > 50) {
        throw std::invalid_argument("Cargo weight must be between 0 and 50 kg");
    }
}

double CargoQuadrupedRobot::getWeight() const {
    return weight;
}

// У грузового наследника свой вариант движения.
void CargoQuadrupedRobot::move() {
    std::cout << getName() << ": walking carefully with " << weight << " kg of cargo\n";
}
