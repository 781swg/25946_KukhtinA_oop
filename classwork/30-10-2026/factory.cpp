#include "factory.h"

#include <stdexcept>
#include <utility>

// Дружественная функция имеет доступ к приватному полю производителя.
void setManufacturer(Robot& robot, const std::string& manufacturer) {
    if (manufacturer.empty()) {
        throw std::invalid_argument("Manufacturer must not be empty");
    }
    robot.manufacturer = manufacturer;
}

// Дружественным является только этот метод администратора, а не весь класс.
void Administrator::setModel(Robot& robot, const std::string& model) const {
    if (model.empty()) {
        throw std::invalid_argument("Model must not be empty");
    }
    robot.model = model;
}

// Завод меняет все параметры состояния, но сохраняет неизменяемый id робота.
void Factory::configure(Robot& robot, const std::string& name, int charge,
                        const std::string& command, double distanceToday,
                        const std::array<double, 10>& distances,
                        const std::string& manufacturer, const std::string& model) const {
    Robot configured(name, charge, command, distanceToday, distances);
    setManufacturer(configured, manufacturer);
    Administrator admin;
    admin.setModel(configured, model);

    // Сначала проверяем параметры временного объекта, затем меняем исходный.
    robot.name.swap(configured.name);
    std::swap(robot.charge, configured.charge);
    robot.command.swap(configured.command);
    std::swap(robot.distanceToday, configured.distanceToday);
    robot.distances.swap(configured.distances);
    robot.manufacturer.swap(configured.manufacturer);
    robot.model.swap(configured.model);
}
