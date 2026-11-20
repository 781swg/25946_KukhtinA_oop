#pragma once

#include <string>

class QuadrupedRobot {
private:
    std::string name;

public:
    explicit QuadrupedRobot(const std::string& name);
    const std::string& getName() const;
};

class CargoRobot : virtual public QuadrupedRobot {
private:
    double weight;

public:
    CargoRobot(const std::string& name, double weight);
    double getWeight() const;
};

class AutonomousRobot : virtual public QuadrupedRobot {
private:
    double range;

public:
    AutonomousRobot(const std::string& name, double range);
    double getRange() const;
};

class AutonomousCargoRobot : public CargoRobot, public AutonomousRobot {
public:
    AutonomousCargoRobot(const std::string& name, double weight, double range);
};
