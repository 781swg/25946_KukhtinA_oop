#pragma once

#include "robot.h"

class CargoRobot : public Robot {
private:
    static constexpr double maxWeight = 50.0;
    double weight;

public:
    CargoRobot();
    CargoRobot(const std::string& name, double weight);
    double getWeight() const;
    void show_weight() const;
};
