#pragma once

#include <string>

// Намеренно без virtual: у итогового робота два экземпляра общего предка.
namespace diamond {
class QuadrupedRobot {
private:
    std::string name;

public:
    explicit QuadrupedRobot(const std::string& name) : name(name) {}
    const std::string& getName() const { return name; }
};

class CargoRobot : public QuadrupedRobot {
public:
    explicit CargoRobot(const std::string& name) : QuadrupedRobot(name) {}
};

class AutonomousRobot : public QuadrupedRobot {
public:
    explicit AutonomousRobot(const std::string& name) : QuadrupedRobot(name) {}
};

class AutonomousCargoRobot : public CargoRobot, public AutonomousRobot {
public:
    AutonomousCargoRobot(const std::string& cargoName, const std::string& autonomousName)
        : CargoRobot(cargoName), AutonomousRobot(autonomousName) {}
};
}
