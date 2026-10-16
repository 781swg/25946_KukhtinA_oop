#pragma once

#include <array>
#include <string>

class Robot {
private:
    static int objectCount;
    static int nextId;
    static const std::string className;

    const std::string id;
    std::string name;
    int charge;
    std::string command;
    double distanceToday;
    std::array<double, 10> distances;

    static std::string createId();
    void validate() const;
    void log(const std::string& action) const;

public:
    Robot();
    Robot(const std::string& name, int charge, const std::string& command,
          double distanceToday, const std::array<double, 10>& distances);
    Robot(const Robot& other);
    Robot& operator=(const Robot& other);
    ~Robot();

    const std::string& getId() const;
    const std::string& getName() const;
    int getCharge() const;
    const std::string& getCommand() const;
    double getDistanceToday() const;
    const std::array<double, 10>& getDistances() const;

    static int getObjectCount();
    static const std::string& getClassName();

    void printInfo() const;
};
