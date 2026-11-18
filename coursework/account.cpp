#include "account.h"

#include <stdexcept>
#include <limits>

Account::Account(const std::string& pin, int balance)
    : pin(pin), balance(balance) {
    if (pin.size() != 4) {
        throw std::invalid_argument("PIN must contain four digits");
    }
    for (char digit : pin) {
        if (digit < '0' || digit > '9') {
            throw std::invalid_argument("PIN must contain four digits");
        }
    }
    if (balance < 0) {
        throw std::invalid_argument("Balance must be non-negative");
    }
}

bool Account::checkPin(const std::string& enteredPin) const {
    return pin == enteredPin;
}

int Account::getBalance() const {
    return balance;
}

void Account::deposit(int amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Amount must be positive");
    }
    if (amount > std::numeric_limits<int>::max() - balance) {
        throw std::overflow_error("Balance limit exceeded");
    }
    balance += amount;
}

void Account::withdraw(int amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Amount must be positive");
    }
    if (amount > balance) {
        throw std::invalid_argument("Insufficient account balance");
    }
    balance -= amount;
}
