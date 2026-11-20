#pragma once

#include <string>

class Operation {
private:
    std::string type;
    long long amount;
    std::string result;
    std::string message;

public:
    Operation(const std::string& type, long long amount,
              const std::string& result, const std::string& message)
        : type(type), amount(amount), result(result), message(message) {}
    const std::string& getType() const { return type; }
    long long getAmount() const { return amount; }
    const std::string& getResult() const { return result; }
    const std::string& getMessage() const { return message; }
};
