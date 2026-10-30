#pragma once

#include <array>
#include <string>

class Robot;

class Administrator {
public:
    void setModel(Robot& robot, const std::string& model) const;
};

void setManufacturer(Robot& robot, const std::string& manufacturer);

class Robot {
private:
    static int objectCount;
    static int nextId;
    static const std::string className;

    const std::string id;
    std::string name;
    std::string manufacturer;
    std::string model;
    int charge;
    std::string command;
    double distanceToday;
    std::array<double, 10> distances;

    static std::string createId();
    void validate() const;
    void log(const std::string& action) const;

    friend void setManufacturer(Robot& robot, const std::string& manufacturer);
    friend class Factory;
    friend void Administrator::setModel(Robot& robot, const std::string& model) const;

public:
    Robot();
    Robot(const std::string& name, int charge, const std::string& command,
          double distanceToday, const std::array<double, 10>& distances);
    Robot(const Robot& other);
    Robot(Robot&& other);
    Robot& operator=(const Robot& other);
    Robot& operator=(Robot&& other);
    ~Robot();

    const std::string& getId() const;
    const std::string& getName() const;
    const std::string& getManufacturer() const;
    const std::string& getModel() const;
    int getCharge() const;
    const std::string& getCommand() const;
    double getDistanceToday() const;
    const std::array<double, 10>& getDistances() const;

    static int getObjectCount();
    static const std::string& getClassName();

    void printInfo() const;
};
