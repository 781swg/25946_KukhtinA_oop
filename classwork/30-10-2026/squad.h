#pragma once

#include "robot.h"

#include <array>
#include <cstddef>
#include <functional>

class AggregatedSquad {
private:
    std::array<std::reference_wrapper<Robot>, 5> robots;

public:
    explicit AggregatedSquad(const std::array<std::reference_wrapper<Robot>, 5>& robots);
    Robot& getRobot(std::size_t index);
    const Robot& getRobot(std::size_t index) const;
    void printInfo() const;
};

class ComposedSquad {
private:
    std::array<Robot, 5> robots;

public:
    Robot& getRobot(std::size_t index);
    const Robot& getRobot(std::size_t index) const;
    void printInfo() const;
};
