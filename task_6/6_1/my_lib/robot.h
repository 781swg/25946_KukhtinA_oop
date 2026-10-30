#pragma once
#include <string>

class QuadrupedRobot {
private:
    static unsigned int nextId_;
    static std::string makeId();

    const std::string id_;
    std::string name_;
    int battery_;
    std::string command_;
    double todayDistance_;
    double last10Days_[10];

public:
    QuadrupedRobot();
    QuadrupedRobot(std::string name, int battery, std::string command, double distance);
    QuadrupedRobot(const QuadrupedRobot& other);
    QuadrupedRobot& operator=(const QuadrupedRobot& other);
    void print() const;
};
