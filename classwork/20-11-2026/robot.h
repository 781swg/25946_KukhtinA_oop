#pragma once

#include <string>

class Robot {
private:
    std::string name;

public:
    explicit Robot(const std::string& name);
    virtual ~Robot() = default;
    const std::string& getName() const;
    virtual void move() = 0;
};

class QuadrupedRobot : public Robot {
public:
    explicit QuadrupedRobot(const std::string& name);
    void move() override;
};

class CargoQuadrupedRobot : public QuadrupedRobot {
private:
    double weight;

public:
    CargoQuadrupedRobot(const std::string& name, double weight);
    double getWeight() const;
    void move() override;
};
