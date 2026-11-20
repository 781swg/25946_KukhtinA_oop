#pragma once

#include <string>

class Card {
private:
    std::string accountNumber;

public:
    explicit Card(const std::string& accountNumber) : accountNumber(accountNumber) {}
    const std::string& getAccountNumber() const { return accountNumber; }
};
