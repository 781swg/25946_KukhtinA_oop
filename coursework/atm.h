#pragma once

#include "account.h"

class ATM {
private:
    Account account;
    bool authenticated;

public:
    ATM();
    bool login(const std::string& pin);
    void logout();
    int getBalance() const;
};
