#include "atm.h"

#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>

class ATMTest : public ::testing::Test {
protected:
    ATM atm;
    Card card{"0001"};
    void SetUp() override {
        atm.insertCard(card);
        ASSERT_TRUE(atm.login("1234"));
    }
};

TEST_F(ATMTest, DepositUpdatesNotesAndBalance) {
    atm.deposit({1, 2, 1});
    EXPECT_EQ(atm.getBalance(), 3100);
    EXPECT_EQ(atm.getCash(), 12100);
    EXPECT_EQ(atm.getCassettes()[0].getCount(), 21);
    EXPECT_EQ(atm.getCassettes()[1].getCount(), 12);
    EXPECT_EQ(atm.getCassettes()[2].getCount(), 4);
    ASSERT_EQ(atm.getHistory().size(), 1u);
    EXPECT_EQ(atm.getHistory().back().getResult(), "Success");
    EXPECT_EQ(atm.getHistory().back().getAmount(), 2100);
}

TEST_F(ATMTest, WithdrawUpdatesBothBalances) {
    const auto notes = atm.withdraw(600);
    EXPECT_EQ(notes, (std::array<int, 3>{1, 1, 0}));
    EXPECT_EQ(atm.getBalance(), 400);
    EXPECT_EQ(atm.getCash(), 9400);
    EXPECT_EQ(atm.getCassettes()[0].getCount(), 19);
    EXPECT_EQ(atm.getCassettes()[1].getCount(), 9);
}

TEST_F(ATMTest, CancelledOperationsKeepMoneyUnchanged) {
    atm.deposit({1, 0, 0}, false);
    EXPECT_EQ(atm.withdraw(500, false), (std::array<int, 3>{}));
    EXPECT_EQ(atm.getBalance(), 1000);
    EXPECT_EQ(atm.getCash(), 10000);
    ASSERT_EQ(atm.getHistory().size(), 2u);
    EXPECT_EQ(atm.getHistory()[0].getResult(), "Cancelled");
    EXPECT_EQ(atm.getHistory()[1].getResult(), "Cancelled");
}

TEST_F(ATMTest, InvalidOperationsAreRecordedWithoutChangingMoney) {
    EXPECT_THROW(atm.deposit({-1, 0, 0}), std::invalid_argument);
    EXPECT_THROW(atm.deposit({0, 0, 0}), std::invalid_argument);
    EXPECT_THROW(atm.withdraw(0), std::invalid_argument);
    EXPECT_THROW(atm.withdraw(-100), std::invalid_argument);
    EXPECT_THROW(atm.withdraw(1100), std::invalid_argument);
    EXPECT_THROW(atm.withdraw(150), std::invalid_argument);
    EXPECT_EQ(atm.getBalance(), 1000);
    EXPECT_EQ(atm.getCash(), 10000);
    ASSERT_EQ(atm.getHistory().size(), 6u);
    for (const auto& operation : atm.getHistory()) {
        EXPECT_EQ(operation.getResult(), "Rejected");
        EXPECT_FALSE(operation.getMessage().empty());
    }
}

TEST_F(ATMTest, OverflowDoesNotChangeMoney) {
    EXPECT_THROW(atm.deposit({std::numeric_limits<int>::max(), 0, 0}), std::overflow_error);
    EXPECT_EQ(atm.getBalance(), 1000);
    EXPECT_EQ(atm.getCash(), 10000);
    EXPECT_EQ(atm.getHistory().back().getResult(), "Rejected");
}

TEST_F(ATMTest, CardReturnEndsSessionButKeepsHistory) {
    atm.deposit({1, 0, 0});
    atm.ejectCard();
    EXPECT_FALSE(atm.hasCard());
    EXPECT_THROW(atm.getBalance(), std::logic_error);
    EXPECT_THROW(atm.getHistory(), std::logic_error);
    EXPECT_THROW(atm.deposit({1, 0, 0}), std::logic_error);
    EXPECT_THROW(atm.withdraw(100), std::logic_error);
    EXPECT_THROW(atm.login("1234"), std::logic_error);
    atm.insertCard(card);
    ASSERT_TRUE(atm.login("1234"));
    EXPECT_EQ(atm.getBalance(), 1100);
    EXPECT_EQ(atm.getHistory().size(), 1u);
}

TEST_F(ATMTest, WrongAndDuplicateCardsAreRejected) {
    EXPECT_THROW(atm.insertCard(card), std::logic_error);
    atm.ejectCard();
    EXPECT_THROW(atm.insertCard(Card("other")), std::invalid_argument);
    EXPECT_FALSE(atm.hasCard());
}

TEST_F(ATMTest, ReturningCardDoesNotResetPINBlock) {
    for (int i = 0; i < 3; ++i) {
        atm.ejectCard();
        atm.insertCard(card);
        EXPECT_FALSE(atm.login("0000"));
    }
    EXPECT_TRUE(atm.isBlocked());
    atm.ejectCard();
    atm.insertCard(card);
    EXPECT_FALSE(atm.login("1234"));
    EXPECT_EQ(atm.getRemainingAttempts(), 0);
    EXPECT_THROW(atm.withdraw(100), std::logic_error);
}

TEST_F(ATMTest, SuccessfulPINResetsErrorCount) {
    EXPECT_FALSE(atm.login("0000"));
    EXPECT_EQ(atm.getRemainingAttempts(), 2);
    EXPECT_TRUE(atm.login("1234"));
    EXPECT_EQ(atm.getRemainingAttempts(), 3);
}

TEST_F(ATMTest, InsufficientCashAndImpossibleNotesAreDifferentFailures) {
    ATM scarce({0, 0, 1});
    scarce.insertCard(card);
    ASSERT_TRUE(scarce.login("1234"));
    EXPECT_THROW(scarce.withdraw(500), std::invalid_argument);
    EXPECT_EQ(scarce.getHistory().back().getMessage(), "Cannot assemble the amount with available notes");
    EXPECT_EQ(scarce.getBalance(), 1000);
    EXPECT_EQ(scarce.getCash(), 1000);
    ATM empty({0, 0, 0});
    empty.insertCard(card);
    ASSERT_TRUE(empty.login("1234"));
    EXPECT_THROW(empty.withdraw(100), std::invalid_argument);
    EXPECT_EQ(empty.getHistory().back().getMessage(), "Insufficient ATM cash");
}

TEST_F(ATMTest, CanUseSmallerNotesInsteadOfThousands) {
    ATM smaller({5, 1, 0});
    smaller.insertCard(card);
    ASSERT_TRUE(smaller.login("1234"));
    EXPECT_EQ(smaller.withdraw(1000), (std::array<int, 3>{5, 1, 0}));
    EXPECT_EQ(smaller.getBalance(), 0);
    EXPECT_EQ(smaller.getCash(), 0);
}

TEST_F(ATMTest, EveryRepresentableSmallAmountCanBeDispensed) {
    for (int hundreds = 0; hundreds <= 3; ++hundreds) {
        for (int fives = 0; fives <= 2; ++fives) {
            for (int thousands = 0; thousands <= 2; ++thousands) {
                for (int amount = 100; amount <= 1000; amount += 100) {
                    bool possible = false;
                    for (int a = 0; a <= hundreds; ++a)
                        for (int b = 0; b <= fives; ++b)
                            for (int c = 0; c <= thousands; ++c)
                                if (a * 100 + b * 500 + c * 1000 == amount) possible = true;
                    ATM sample({hundreds, fives, thousands});
                    sample.insertCard(card);
                    ASSERT_TRUE(sample.login("1234"));
                    if (possible) {
                        auto notes = sample.withdraw(amount);
                        EXPECT_EQ(notes[0] * 100 + notes[1] * 500 + notes[2] * 1000, amount);
                    } else {
                        EXPECT_THROW(sample.withdraw(amount), std::invalid_argument);
                        EXPECT_EQ(sample.getBalance(), 1000);
                    }
                }
            }
        }
    }
}
