#include "robot.h"

#include <cmath>
#include <stdexcept>

QuadrupedRobot::QuadrupedRobot(const std::string& name) : name(name) {
    if (name.empty()) throw std::invalid_argument("Name must not be empty");
}

const std::string& QuadrupedRobot::getName() const {
    return name;
}

CargoRobot::CargoRobot(const std::string& name, double weight)
    : QuadrupedRobot(name), weight(weight) {
    if (!std::isfinite(weight) || weight < 0 || weight > 50) {
        throw std::invalid_argument("Cargo weight must be between 0 and 50 kg");
    }
}

double CargoRobot::getWeight() const {
    return weight;
}

AutonomousRobot::AutonomousRobot(const std::string& name, double range)
    : QuadrupedRobot(name), range(range) {
    if (!std::isfinite(range) || range < 0) {
        throw std::invalid_argument("Range must be finite and non-negative");
    }
}

double AutonomousRobot::getRange() const {
    return range;
}

// Самый нижний класс инициализирует единственный общий виртуальный базовый объект.
AutonomousCargoRobot::AutonomousCargoRobot(const std::string& name, double weight, double range)
    : QuadrupedRobot(name), CargoRobot(name, weight), AutonomousRobot(name, range) {
}
