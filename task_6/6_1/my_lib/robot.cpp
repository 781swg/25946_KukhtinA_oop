#include "robot.h"
#include <iostream>
#include <utility>

unsigned int QuadrupedRobot::nextId_ = 0;

std::string QuadrupedRobot::makeId() {
    return "R" + std::to_string(++nextId_);
}

// конструктор по умолчанию
QuadrupedRobot::QuadrupedRobot()
    : id_(makeId()), name_("робот"), battery_(100),
      command_("ожидание"), todayDistance_(0), last10Days_{} {
    std::cout << "конструктор по умолчанию | " << id_ << '\n';
}

// инициализирующий конструктор
QuadrupedRobot::QuadrupedRobot(std::string name, int battery,
                               std::string command, double distance)
    : id_(makeId()), name_(name.empty() ? "робот" : std::move(name)),
      battery_(battery < 0 ? 0 : (battery > 100 ? 100 : battery)),
      command_(command.empty() ? "ожидание" : std::move(command)),
      todayDistance_(distance < 0 ? 0 : distance), last10Days_{} {
    std::cout << "инициализирующий конструктор | " << id_ << '\n';
}

// конструктор копирования
QuadrupedRobot::QuadrupedRobot(const QuadrupedRobot& other)
    : id_(makeId()), name_(other.name_), battery_(other.battery_),
      command_(other.command_), todayDistance_(other.todayDistance_) {
    for (int i = 0; i < 10; ++i) {
        last10Days_[i] = other.last10Days_[i];
    }
    std::cout << "конструктор копирования | " << id_ << '\n';
}

// присваивание 
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

void QuadrupedRobot::print() const {
    std::cout << "id: " << id_ << " | имя: " << name_
              << " | заряд: " << battery_ << "% | команда: " << command_
              << " | сегодня: " << todayDistance_ << " км\n";
    std::cout << "последние 10 дней:";
    for (double distance : last10Days_) {
        std::cout << ' ' << distance;
    }
    std::cout << "\n";
}
