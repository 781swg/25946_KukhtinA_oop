#include "atm.h"

#include <iostream>
#include <string>

int main() {
    ATM atm;
    std::cout << "ATM simulator: initial prototype\n"
              << "Demo PIN: 1234\n";

    std::string pin;
    std::cout << "Enter PIN: ";
    if (!(std::cin >> pin)) {
        return 0;
    }
    if (!atm.login(pin)) {
        std::cout << "Wrong PIN. Session ended.\n";
        return 0;
    }

    std::string choice;
    while (true) {
        std::cout << "\n1. Show balance\n0. End session\n> ";
        if (!(std::cin >> choice) || choice == "0") {
            break;
        }
        if (choice == "1") {
            std::cout << "Balance: " << atm.getBalance() << " RUB\n";
        } else {
            std::cout << "Unknown command\n";
        }
    }

    atm.logout();
    std::cout << "Session ended.\n";
}
