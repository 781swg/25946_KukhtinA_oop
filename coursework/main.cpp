#include "atm.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

bool readNumber(const std::string& prompt, int& value) {
    std::cout << prompt;
    std::string input, extra;
    if (!std::getline(std::cin, input)) return false;
    std::istringstream stream(input);
    if (!(stream >> value) || (stream >> extra)) {
        throw std::invalid_argument("Enter a whole number");
    }
    return true;
}

bool confirm(long long amount) {
    std::cout << "Confirm " << amount << " RUB (y to confirm, anything else to cancel): ";
    std::string answer;
    return std::getline(std::cin, answer) && answer == "y";
}

int main() {
    ATM atm;
    const Card card("0001");
    std::cout << "ATM simulator\nDemo card: 0001. PIN: 1234\n";
    std::string choice;
    while (true) {
        std::cout << "\n1. Insert demo card\n0. Exit simulator\n> ";
        if (!std::getline(std::cin, choice) || choice == "0") break;
        if (choice != "1") {
            std::cout << "Unknown command\n";
            continue;
        }
        atm.insertCard(card);
        bool loggedIn = false;
        while (!atm.isBlocked()) {
            std::cout << "Enter PIN (c to return card): ";
            std::string pin;
            if (!std::getline(std::cin, pin) || pin == "c") break;
            if (atm.login(pin)) {
                loggedIn = true;
                break;
            }
            std::cout << "Wrong PIN. Attempts left: " << atm.getRemainingAttempts() << '\n';
        }
        if (atm.isBlocked()) std::cout << "Access blocked. Restart the simulator.\n";
        while (loggedIn) {
            std::cout << "\n1. Show balance\n2. Deposit notes\n3. Withdraw\n"
                         "4. Operation history\n5. Cash cassettes\n0. Return card\n> ";
            if (!std::getline(std::cin, choice) || choice == "0") break;
            try {
                if (choice == "1") {
                    std::cout << "Balance: " << atm.getBalance() << " RUB\n";
                } else if (choice == "2") {
                    std::array<int, 3> counts{};
                    bool complete = true;
                    const int denominations[] = {100, 500, 1000};
                    long long amount = 0;
                    for (int i = 0; i < 3; ++i) {
                        if (!readNumber("Number of " + std::to_string(denominations[i]) + " RUB notes: ", counts[i])) {
                            complete = false;
                            break;
                        }
                        amount += 1LL * counts[i] * denominations[i];
                    }
                    if (!complete) break;
                    bool accepted = confirm(amount);
                    atm.deposit(counts, accepted);
                    std::cout << (accepted ? "Deposit completed" : "Cancelled. Notes returned") << '\n';
                } else if (choice == "3") {
                    int amount;
                    if (!readNumber("Amount in RUB: ", amount)) break;
                    bool accepted = confirm(amount);
                    const auto notes = atm.withdraw(amount, accepted);
                    if (accepted) {
                        std::cout << "Issued: 100 RUB x " << notes[0] << ", 500 RUB x "
                                  << notes[1] << ", 1000 RUB x " << notes[2] << '\n';
                    } else {
                        std::cout << "Operation cancelled\n";
                    }
                } else if (choice == "4") {
                    const auto& history = atm.getHistory();
                    if (history.empty()) std::cout << "No operations yet\n";
                    for (const auto& operation : history) {
                        std::cout << operation.getType() << " | " << operation.getAmount()
                                  << " RUB | " << operation.getResult() << " | "
                                  << operation.getMessage() << '\n';
                    }
                } else if (choice == "5") {
                    for (const auto& cassette : atm.getCassettes()) {
                        std::cout << cassette.getDenomination() << " RUB x " << cassette.getCount() << '\n';
                    }
                    std::cout << "Total cash: " << atm.getCash() << " RUB\n";
                } else {
                    std::cout << "Unknown command\n";
                }
            } catch (const std::exception& error) {
                std::cout << "Operation rejected: " << error.what() << '\n';
            }
        }
        atm.ejectCard();
        std::cout << "Card returned. Session ended.\n";
    }
}
