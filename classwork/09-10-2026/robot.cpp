#include "robot.h"

#include <iostream>
#include <stdexcept>

std::string Robot::createId() {
    static int nextId = 0;
    return "robot-" + std::to_string(++nextId);
}

void Robot::validate() const {
    if (name.empty()) {
        throw std::invalid_argument("Name must not be empty");
    }
    if (charge < 0 || charge > 100) {
        throw std::invalid_argument("Charge must be between 0 and 100");
    }
    if (!(distanceToday >= 0)) {
        throw std::invalid_argument("Distance must be non-negative");
    }
    for (double distance : distances) {
        if (!(distance >= 0)) {
            throw std::invalid_argument("Distance must be non-negative");
        }
    }
}

Robot::Robot()
    : id(createId()), name("Robot"), charge(100), command("stand"),
      distanceToday(0), distances{} {
    std::cout << "Default constructor | " << id << '\n';
}

Robot::Robot(const std::string& name, int charge, const std::string& command,
             double distanceToday, const std::array<double, 10>& distances)
    : id(createId()), name(name), charge(charge), command(command),
      distanceToday(distanceToday), distances(distances) {
    validate();
    std::cout << "Initialization constructor | " << id << '\n';
}

Robot::Robot(const Robot& other)
    : id(createId()), name(other.name), charge(other.charge),
      command(other.command), distanceToday(other.distanceToday),
      distances(other.distances) {
    std::cout << "Copy constructor | " << id << " from " << other.id << '\n';
}

Robot& Robot::operator=(const Robot& other) {
    if (this != &other) {
        // Присваиваем состояние, но сохраняем собственный id объекта.
        name = other.name;
        charge = other.charge;
        command = other.command;
        distanceToday = other.distanceToday;
        distances = other.distances;
    }
    std::cout << "Copy assignment | " << id << " from " << other.id << '\n';
    return *this;
}

Robot::~Robot() {
    std::cout << "Destructor | " << id << '\n';
}

void Robot::printInfo() const {
    std::cout << id << " | " << name << " | charge: " << charge
              << "% | command: " << command
              << " | today: " << distanceToday << '\n';
    std::cout << "Last 10 days:";
    for (double distance : distances) {
        std::cout << ' ' << distance;
    }
    std::cout << '\n';
}
