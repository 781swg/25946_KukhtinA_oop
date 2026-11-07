#include "squad.h"

#include <iostream>

// Отделение хранит ссылки: сами роботы должны существовать дольше отделения.
AggregatedSquad::AggregatedSquad(
    const std::array<std::reference_wrapper<Robot>, 5>& robots)
    : robots(robots) {
}

Robot& AggregatedSquad::getRobot(std::size_t index) {
    return robots.at(index).get();
}

const Robot& AggregatedSquad::getRobot(std::size_t index) const {
    return robots.at(index).get();
}

void AggregatedSquad::printInfo() const {
    std::cout << "Aggregated squad: 5 external robots\n";
    for (const auto& robot : robots) {
        robot.get().printInfo();
    }
}

Robot& ComposedSquad::getRobot(std::size_t index) {
    return robots.at(index);
}

const Robot& ComposedSquad::getRobot(std::size_t index) const {
    return robots.at(index);
}

// Роботы являются полями отделения и создаются и уничтожаются вместе с ним.
void ComposedSquad::printInfo() const {
    std::cout << "Composed squad: 5 owned robots\n";
    for (const Robot& robot : robots) {
        robot.printInfo();
    }
}
