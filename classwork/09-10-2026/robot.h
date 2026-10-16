#pragma once

#include <array>
#include <string>

class Robot {
private:
    const std::string id;
    std::string name;
    int charge;
    std::string command;
    double distanceToday;
    std::array<double, 10> distances;

    static std::string createId();
    void validate() const;

public:
    Robot();
    Robot(const std::string& name, int charge, const std::string& command,
          double distanceToday, const std::array<double, 10>& distances);
    Robot(const Robot& other);
    Robot& operator=(const Robot& other);
    ~Robot();

    void printInfo() const;
};
