#include "atm.h"

#include <stdexcept>

ATM::ATM() : account("1234", 1000), authenticated(false) {
}

bool ATM::login(const std::string& pin) {
    authenticated = account.checkPin(pin);
    return authenticated;
}

void ATM::logout() {
    authenticated = false;
}

// Проверка доступа находится в модели, чтобы будущий GUI не обходил её.
int ATM::getBalance() const {
    if (!authenticated) {
        throw std::logic_error("Enter PIN first");
    }
    return account.getBalance();
}
