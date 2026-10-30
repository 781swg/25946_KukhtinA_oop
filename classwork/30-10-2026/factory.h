#pragma once

#include "robot.h"

class Factory {
public:
    void configure(Robot& robot, const std::string& name, int charge,
                   const std::string& command, double distanceToday,
                   const std::array<double, 10>& distances,
                   const std::string& manufacturer, const std::string& model) const;
};
