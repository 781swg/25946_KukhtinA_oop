#include "robot.h"

#include <iostream>
#include <stdexcept>

int Robot::objectCount = 0;
int Robot::nextId = 0;
const std::string Robot::className = "Robot";

std::string Robot::createId() {
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

void Robot::log(const std::string& action) const {
    std::cout << action << " | " << className << " | " << id
              << " | objects: " << objectCount << '\n';
}

Robot::Robot()
    : id(createId()), name("Robot"), charge(100), command("stand"),
      distanceToday(0), distances{} {
    ++objectCount;
    log("Default constructor");
}

Robot::Robot(const std::string& name, int charge, const std::string& command,
             double distanceToday, const std::array<double, 10>& distances)
    : id(createId()), name(name), charge(charge), command(command),
      distanceToday(distanceToday), distances(distances) {
    validate();
    ++objectCount;
    log("Initialization constructor");
}

Robot::Robot(const Robot& other)
    : id(createId()), name(other.name), charge(other.charge),
      command(other.command), distanceToday(other.distanceToday),
      distances(other.distances) {
    ++objectCount;
    log("Copy constructor");
}

Robot& Robot::operator=(const Robot& other) {
    if (this != &other) {
        // id и количество объектов при присваивании не меняются.
        name = other.name;
        charge = other.charge;
        command = other.command;
        distanceToday = other.distanceToday;
        distances = other.distances;
    }
    log("Copy assignment");
    return *this;
}

Robot::~Robot() {
    --objectCount;
    log("Destructor");
}

const std::string& Robot::getId() const {
    return id;
}

const std::string& Robot::getName() const {
    return name;
}

int Robot::getCharge() const {
    return charge;
}

const std::string& Robot::getCommand() const {
    return command;
}

double Robot::getDistanceToday() const {
    return distanceToday;
}

const std::array<double, 10>& Robot::getDistances() const {
    return distances;
}

int Robot::getObjectCount() {
    return objectCount;
}

const std::string& Robot::getClassName() {
    return className;
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
