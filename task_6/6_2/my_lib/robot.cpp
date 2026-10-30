#include "robot.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

unsigned int QuadrupedRobot::nextId_ = 0;

std::string QuadrupedRobot::makeId() {
    return "R" + std::to_string(++nextId_);
}

std::string QuadrupedRobot::normalizeText(const std::string& text,
                                         const std::string& fallback) {
    return text.empty() ? fallback : text;
}

int QuadrupedRobot::normalizeBattery(int value) {
    if (value < 0) return 0;
    if (value > 100) return 100;
    return value;
}

double QuadrupedRobot::normalizeDistance(double value) {
    return std::isfinite(value) && value >= 0 ? value : 0;
}

// конструкторы поддерживают инвариант
QuadrupedRobot::QuadrupedRobot()
    : id_(makeId()), name_("робот"), battery_(100),
      command_("ожидание"), todayDistance_(0), last10Days_{} {
    std::cout << "конструктор по умолчанию | " << id_ << '\n';
}

QuadrupedRobot::QuadrupedRobot(std::string name, int battery,
                               std::string command, double distance)
    : id_(makeId()), name_(normalizeText(name, "робот")),
      battery_(normalizeBattery(battery)),
      command_(normalizeText(command, "ожидание")),
      todayDistance_(normalizeDistance(distance)), last10Days_{} {
    std::cout << "инициализирующий конструктор | " << id_ << '\n';
}

QuadrupedRobot::QuadrupedRobot(const QuadrupedRobot& other)
    : id_(makeId()), name_(other.name_), battery_(other.battery_),
      command_(other.command_), todayDistance_(other.todayDistance_) {
    for (int i = 0; i < 10; ++i) {
        last10Days_[i] = other.last10Days_[i];
    }
    std::cout << "конструктор копирования | " << id_ << '\n';
}

QuadrupedRobot& QuadrupedRobot::operator=(const QuadrupedRobot& other) {
    if (this != &other) {
        name_ = other.name_;
        battery_ = other.battery_;
        command_ = other.command_;
        todayDistance_ = other.todayDistance_;
        for (int i = 0; i < 10; ++i) {
            last10Days_[i] = other.last10Days_[i];
        }
    }
    std::cout << "оператор присваивания | " << id_ << '\n';
    return *this;
}

const std::string& QuadrupedRobot::getId() const { return id_; }
const std::string& QuadrupedRobot::getName() const { return name_; }
int QuadrupedRobot::getBattery() const { return battery_; }
const std::string& QuadrupedRobot::getCommand() const { return command_; }
double QuadrupedRobot::getTodayDistance() const { return todayDistance_; }

double QuadrupedRobot::getDayDistance(int day) const {
    if (day < 0 || day >= 10) throw std::out_of_range("номер дня: от 0 до 9");
    return last10Days_[day];
}

void QuadrupedRobot::setName(const std::string& name) {
    name_ = normalizeText(name, "робот");
}
void QuadrupedRobot::setBattery(int battery) {
    battery_ = normalizeBattery(battery);
}
void QuadrupedRobot::setCommand(const std::string& command) {
    command_ = normalizeText(command, "ожидание");
}
void QuadrupedRobot::setTodayDistance(double distance) {
    todayDistance_ = normalizeDistance(distance);
}
void QuadrupedRobot::setDayDistance(int day, double distance) {
    if (day < 0 || day >= 10) throw std::out_of_range("номер дня: от 0 до 9");
    last10Days_[day] = normalizeDistance(distance);
}

void QuadrupedRobot::print() const {
    std::cout << "id: " << id_ << " | имя: " << name_
              << " | заряд: " << battery_ << "% | команда: " << command_
              << " | сегодня: " << todayDistance_ << " км\n";
    std::cout << "последние 10 дней:";
    for (double distance : last10Days_) std::cout << ' ' << distance;
    std::cout << "\n";
}
