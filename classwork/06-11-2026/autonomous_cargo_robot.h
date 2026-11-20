#pragma once

#include "cargo_robot.h"

class AutonomousCargoRobot final : private CargoRobot {
public:
    AutonomousCargoRobot();
    AutonomousCargoRobot(const std::string& name, double weight);
    using CargoRobot::show_weight;
    void showMode() const;
};
