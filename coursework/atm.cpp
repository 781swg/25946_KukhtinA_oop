#include "atm.h"

#include <limits>
#include <stdexcept>

ATM::ATM(int cash)
    : account("1234", 1000), authenticated(false), cash(cash), failedAttempts(0) {
    if (cash < 0) {
        throw std::invalid_argument("ATM cash must be non-negative");
    }
}

bool ATM::login(const std::string& pin) {
    authenticated = false;
    if (isBlocked()) {
        return false;
    }
    if (!account.checkPin(pin)) {
        ++failedAttempts;
        return false;
    }
    failedAttempts = 0;
    authenticated = true;
    return true;
}

void ATM::logout() {
    authenticated = false;
}

int ATM::getRemainingAttempts() const {
    return maxAttempts - failedAttempts;
}

bool ATM::isBlocked() const {
    return failedAttempts >= maxAttempts;
}

// Проверки остаются в модели, независимо от интерфейса.
void ATM::requireLogin() const {
    if (!authenticated || isBlocked()) {
        throw std::logic_error("Enter PIN first");
    }
}

int ATM::getBalance() const {
    requireLogin();
    return account.getBalance();
}

int ATM::getCash() const {
    requireLogin();
    return cash;
}

void ATM::deposit(int amount) {
    requireLogin();
    if (amount <= 0) {
        throw std::invalid_argument("Amount must be positive");
    }
    if (amount > std::numeric_limits<int>::max() - cash) {
        throw std::overflow_error("ATM cash limit exceeded");
    }
    account.deposit(amount);
    cash += amount;
}

void ATM::withdraw(int amount) {
    requireLogin();
    if (amount <= 0) {
        throw std::invalid_argument("Amount must be positive");
    }
    if (amount > cash) {
        throw std::invalid_argument("Insufficient ATM cash");
    }
    account.withdraw(amount);
    cash -= amount;
}
