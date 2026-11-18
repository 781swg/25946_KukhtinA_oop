#pragma once

#include "account.h"

class ATM {
private:
    Account account;
    bool authenticated;
    int cash;
    int failedAttempts;
    static const int maxAttempts = 3;

    void requireLogin() const;

public:
    explicit ATM(int cash = 10000);
    bool login(const std::string& pin);
    void logout();
    int getBalance() const;
    int getCash() const;
    int getRemainingAttempts() const;
    bool isBlocked() const;
    void deposit(int amount);
    void withdraw(int amount);
};
