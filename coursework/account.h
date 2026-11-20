#pragma once

#include <string>

class Account {
private:
    const std::string number = "0001";
    std::string pin;
    int balance;

public:
    Account(const std::string& pin, int balance);
    const std::string& getNumber() const { return number; }
    bool checkPin(const std::string& enteredPin) const;
    int getBalance() const;
    void deposit(int amount);
    void withdraw(int amount);
};
