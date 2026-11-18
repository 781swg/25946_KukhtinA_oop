#include "atm.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

int main() {
    ATM atm;
    std::cout << "ATM simulator\nDemo PIN: 1234\n";

    std::string pin;
    while (true) {
        std::cout << "Enter PIN: ";
        if (!std::getline(std::cin, pin)) {
            return 0;
        }
        if (atm.login(pin)) {
            break;
        }
        if (atm.isBlocked()) {
            std::cout << "Access blocked. Restart the simulator.\n";
            return 0;
        }
        std::cout << "Wrong PIN. Attempts left: " << atm.getRemainingAttempts() << '\n';
    }

    std::string choice;
    while (true) {
        std::cout << "\n1. Show balance\n2. Deposit\n3. Withdraw\n0. End session\n> ";
        if (!std::getline(std::cin, choice) || choice == "0") {
            break;
        }
        try {
            if (choice == "1") {
                std::cout << "Balance: " << atm.getBalance() << " RUB\n";
            } else if (choice == "2" || choice == "3") {
                std::cout << "Amount in whole RUB: ";
                std::string input;
                if (!std::getline(std::cin, input)) break;
                std::istringstream stream(input);
                int amount;
                std::string extra;
                if (!(stream >> amount) || (stream >> extra) || amount <= 0) {
                    throw std::invalid_argument("Enter a positive whole amount");
                }
                std::cout << "Confirm " << amount << " RUB (y to confirm): ";
                std::string confirmation;
                if (!std::getline(std::cin, confirmation)) break;
                if (confirmation != "y") {
                    std::cout << "Operation cancelled\n";
                    continue;
                }
                if (choice == "2") {
                    atm.deposit(amount);
                } else {
                    atm.withdraw(amount);
                }
                std::cout << "Success. Balance: " << atm.getBalance() << " RUB\n";
            } else {
                std::cout << "Unknown command\n";
            }
        } catch (const std::exception& error) {
            std::cout << "Operation rejected: " << error.what() << '\n';
        }
    }

    atm.logout();
    std::cout << "Session ended.\n";
}
