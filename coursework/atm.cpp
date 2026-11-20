#include "atm.h"

#include <algorithm>
#include <limits>
#include <stdexcept>

ATM::ATM(const std::array<int, 3>& counts)
    : account("1234", 1000), cardInserted(false), authenticated(false),
      failedAttempts(0), cassettes{CashCassette(100, counts[0]),
                                 CashCassette(500, counts[1]),
                                 CashCassette(1000, counts[2])} {
    long long total = 0;
    for (const auto& cassette : cassettes) {
        total += 1LL * cassette.getDenomination() * cassette.getCount();
    }
    if (total > std::numeric_limits<int>::max()) {
        throw std::overflow_error("ATM cash limit exceeded");
    }
}

void ATM::insertCard(const Card& card) {
    if (cardInserted) throw std::logic_error("A card is already inserted");
    if (card.getAccountNumber() != account.getNumber()) {
        throw std::invalid_argument("Unknown card");
    }
    cardInserted = true;
    authenticated = false;
}

void ATM::ejectCard() {
    authenticated = false;
    cardInserted = false;
}

bool ATM::hasCard() const { return cardInserted; }

bool ATM::login(const std::string& pin) {
    authenticated = false;
    if (!cardInserted) throw std::logic_error("Insert a card first");
    if (isBlocked()) return false;
    if (!account.checkPin(pin)) {
        ++failedAttempts;
        return false;
    }
    failedAttempts = 0;
    authenticated = true;
    return true;
}

void ATM::logout() { ejectCard(); }
int ATM::getRemainingAttempts() const { return maxAttempts - failedAttempts; }
bool ATM::isBlocked() const { return failedAttempts >= maxAttempts; }

void ATM::requireLogin() const {
    if (!cardInserted || !authenticated || isBlocked()) {
        throw std::logic_error("Insert a card and enter PIN first");
    }
}

int ATM::getBalance() const {
    requireLogin();
    return account.getBalance();
}

int ATM::getCash() const {
    requireLogin();
    int total = 0;
    for (const auto& cassette : cassettes) {
        total += cassette.getDenomination() * cassette.getCount();
    }
    return total;
}

const std::array<CashCassette, 3>& ATM::getCassettes() const {
    requireLogin();
    return cassettes;
}

const std::vector<Operation>& ATM::getHistory() const {
    requireLogin();
    return history;
}

// Сначала рассчитываем набор купюр, не меняя кассеты и баланс.
std::array<int, 3> ATM::selectNotes(int amount) const {
    if (amount % 100 != 0) throw std::invalid_argument("Amount must be a multiple of 100");
    const int maxThousands = std::min(amount / 1000, cassettes[2].getCount());
    for (int thousands = maxThousands; thousands >= 0; --thousands) {
        int rest = amount - thousands * 1000;
        int fiveHundreds = std::min(rest / 500, cassettes[1].getCount());
        int hundreds = (rest - fiveHundreds * 500) / 100;
        if (hundreds <= cassettes[0].getCount()) {
            return {hundreds, fiveHundreds, thousands};
        }
    }
    throw std::invalid_argument("Cannot assemble the amount with available notes");
}

void ATM::deposit(const std::array<int, 3>& counts, bool confirmed) {
    requireLogin();
    long long amount = 0;
    for (int i = 0; i < 3; ++i) {
        amount += 1LL * counts[i] * cassettes[i].getDenomination();
    }
    try {
        for (int count : counts) {
            if (count < 0) throw std::invalid_argument("Note count must be non-negative");
        }
        if (amount <= 0) throw std::invalid_argument("Deposit at least one note");
        if (amount > std::numeric_limits<int>::max() - getCash() ||
            amount > std::numeric_limits<int>::max() - account.getBalance()) {
            throw std::overflow_error("Cash or balance limit exceeded");
        }
        if (!confirmed) {
            history.emplace_back("Deposit", amount, "Cancelled", "Notes returned");
            return;
        }
        auto updated = cassettes;
        for (int i = 0; i < 3; ++i) {
            updated[i] = CashCassette(cassettes[i].getDenomination(),
                                     cassettes[i].getCount() + counts[i]);
        }
        history.emplace_back("Deposit", amount, "Success", "Notes accepted");
        account.deposit(static_cast<int>(amount));
        cassettes = updated;
    } catch (const std::exception& error) {
        history.emplace_back("Deposit", amount, "Rejected", error.what());
        throw;
    }
}

std::array<int, 3> ATM::withdraw(int amount, bool confirmed) {
    requireLogin();
    try {
        if (amount <= 0) throw std::invalid_argument("Amount must be positive");
        if (amount > account.getBalance()) throw std::invalid_argument("Insufficient account balance");
        if (amount > getCash()) throw std::invalid_argument("Insufficient ATM cash");
        if (!confirmed) {
            history.emplace_back("Withdraw", amount, "Cancelled", "No money issued");
            return {};
        }
        const auto notes = selectNotes(amount);
        auto updated = cassettes;
        for (int i = 0; i < 3; ++i) {
            updated[i] = CashCassette(cassettes[i].getDenomination(),
                                     cassettes[i].getCount() - notes[i]);
        }
        history.emplace_back("Withdraw", amount, "Success", "Notes issued");
        account.withdraw(amount);
        cassettes = updated;
        return notes;
    } catch (const std::exception& error) {
        history.emplace_back("Withdraw", amount, "Rejected", error.what());
        throw;
    }
}
