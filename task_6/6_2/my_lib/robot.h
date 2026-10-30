#pragma once
#include <string>

class QuadrupedRobot {
private:
    static unsigned int nextId_;
    static std::string makeId();
    static std::string normalizeText(const std::string& text, const std::string& fallback);
    static int normalizeBattery(int value);
    static double normalizeDistance(double value);

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

    const std::string& getId() const;
    const std::string& getName() const;
    int getBattery() const;
    const std::string& getCommand() const;
    double getTodayDistance() const;
    double getDayDistance(int day) const;

    void setName(const std::string& name);
    void setBattery(int battery);
    void setCommand(const std::string& command);
    void setTodayDistance(double distance);
    void setDayDistance(int day, double distance);
    void print() const;
};
