#include "autonomous_cargo_robot.h"

#include <iostream>
#include <random>

AutonomousCargoRobot::AutonomousCargoRobot() : CargoRobot() {
}

AutonomousCargoRobot::AutonomousCargoRobot(const std::string& name, double weight)
    : CargoRobot(name, weight) {
}

// Вероятность каждого сообщения — 1/2, а не обязательное чередование режимов.
void AutonomousCargoRobot::showMode() const {
    static std::mt19937 generator(std::random_device{}());
    std::bernoulli_distribution autonomous(0.5);
    std::cout << (autonomous(generator) ? "Autonomous mode" : "Controlled mode") << '\n';
}
