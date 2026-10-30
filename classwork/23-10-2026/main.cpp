#include "robot.h"

#include <iostream>
#include <utility>

int main() {
    const std::array<double, 10> history = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    {
        Robot original("Rex", 80, "walk", 2.5, history);

        std::cout << "--- Copy constructor: source stays the same ---\n";
        Robot copy(original);
        original.printInfo();
        copy.printInfo();

        std::cout << "--- Move constructor: source gets default state ---\n";
        Robot moved(std::move(original));
        original.printInfo();
        moved.printInfo();

        std::cout << "--- Copy assignment: source stays the same ---\n";
        Robot assigned;
        assigned = copy;
        copy.printInfo();
        assigned.printInfo();

        std::cout << "--- Move assignment: states are swapped ---\n";
        Robot target;
        target = std::move(moved);
        moved.printInfo();
        target.printInfo();

        std::cout << "--- Destructors ---\n";
    }
    std::cout << "Objects left: " << Robot::getObjectCount() << '\n';
}
