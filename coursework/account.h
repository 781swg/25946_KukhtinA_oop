#pragma once

#include <string>

class Account {
private:
    std::string pin;
    int balance;

public:
    Account(const std::string& pin, int balance);
    bool checkPin(const std::string& enteredPin) const;
    int getBalance() const;
    void deposit(int amount);
    void withdraw(int amount);
};
