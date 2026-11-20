#pragma once

#include "account.h"
#include "card.h"
#include "cash_cassette.h"
#include "operation.h"

#include <array>
#include <vector>

class ATM {
private:
    Account account;
    bool cardInserted;
    bool authenticated;
    int failedAttempts;
    static const int maxAttempts = 3;
    std::array<CashCassette, 3> cassettes;
    std::vector<Operation> history;

    void requireLogin() const;
    std::array<int, 3> selectNotes(int amount) const;

public:
    explicit ATM(const std::array<int, 3>& counts = {20, 10, 3});
    void insertCard(const Card& card);
    void ejectCard();
    bool hasCard() const;
    bool login(const std::string& pin);
    void logout();
    int getBalance() const;
    int getCash() const;
    int getRemainingAttempts() const;
    bool isBlocked() const;
    const std::array<CashCassette, 3>& getCassettes() const;
    const std::vector<Operation>& getHistory() const;
    void deposit(const std::array<int, 3>& counts, bool confirmed = true);
    std::array<int, 3> withdraw(int amount, bool confirmed = true);
};
