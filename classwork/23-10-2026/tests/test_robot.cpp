#include "robot.h"

#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <utility>

class RobotTest : public ::testing::Test {
protected:
    const std::array<double, 10> history = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::unique_ptr<Robot> robot;
    int initialCount = 0;

    void SetUp() override {
        initialCount = Robot::getObjectCount();
        robot = std::make_unique<Robot>("Rex", 80, "walk", 2.5, history);
    }

    void TearDown() override {
        robot.reset();
        EXPECT_EQ(Robot::getObjectCount(), initialCount);
    }

    void expectRex(const Robot& value) {
        EXPECT_EQ(value.getName(), "Rex");
        EXPECT_EQ(value.getCharge(), 80);
        EXPECT_EQ(value.getCommand(), "walk");
        EXPECT_DOUBLE_EQ(value.getDistanceToday(), 2.5);
        EXPECT_EQ(value.getDistances(), history);
    }
};

TEST_F(RobotTest, DefaultState) {
    const Robot value;
    EXPECT_FALSE(value.getId().empty());
    EXPECT_EQ(value.getName(), "Robot");
    EXPECT_EQ(value.getCharge(), 100);
    EXPECT_EQ(value.getCommand(), "stand");
    EXPECT_DOUBLE_EQ(value.getDistanceToday(), 0);
    EXPECT_EQ(value.getDistances(), (std::array<double, 10>{}));
}

TEST_F(RobotTest, Initialization) {
    expectRex(*robot);
}

TEST_F(RobotTest, CopyConstructorPreservesSource) {
    const Robot copy(*robot);
    expectRex(copy);
    expectRex(*robot);
    EXPECT_NE(copy.getId(), robot->getId());
    EXPECT_EQ(Robot::getObjectCount(), initialCount + 2);
}

TEST_F(RobotTest, CopyAssignmentPreservesIdentity) {
    Robot target;
    const auto id = target.getId();
    EXPECT_EQ(&(target = *robot), &target);
    expectRex(target);
    expectRex(*robot);
    EXPECT_EQ(target.getId(), id);
    EXPECT_EQ(Robot::getObjectCount(), initialCount + 2);
}

TEST_F(RobotTest, MoveConstructorTransfersState) {
    const auto sourceId = robot->getId();
    const Robot moved(std::move(*robot));
    expectRex(moved);
    EXPECT_NE(moved.getId(), sourceId);
    EXPECT_EQ(robot->getId(), sourceId);
    EXPECT_EQ(robot->getName(), "Robot");
    EXPECT_EQ(robot->getCommand(), "stand");
    EXPECT_EQ(robot->getCharge(), 100);
    EXPECT_DOUBLE_EQ(robot->getDistanceToday(), 0);
    EXPECT_EQ(robot->getDistances(), (std::array<double, 10>{}));
    EXPECT_EQ(Robot::getObjectCount(), initialCount + 2);
}

TEST_F(RobotTest, MoveAssignmentSwapsStateAndPreservesIdentity) {
    Robot target("Spot", 50, "sit", 1, {});
    const auto targetId = target.getId();
    const auto sourceId = robot->getId();
    EXPECT_EQ(&(target = std::move(*robot)), &target);
    expectRex(target);
    EXPECT_EQ(target.getId(), targetId);
    EXPECT_EQ(robot->getId(), sourceId);
    EXPECT_EQ(robot->getName(), "Spot");
    EXPECT_EQ(robot->getCharge(), 50);
    EXPECT_EQ(robot->getCommand(), "sit");
    EXPECT_DOUBLE_EQ(robot->getDistanceToday(), 1);
    EXPECT_EQ(robot->getDistances(), (std::array<double, 10>{}));
    EXPECT_EQ(Robot::getObjectCount(), initialCount + 2);
}

TEST_F(RobotTest, SelfAssignmentPreservesState) {
    Robot& same = *robot;
    *robot = same;
    expectRex(*robot);
    *robot = std::move(same);
    expectRex(*robot);
    EXPECT_EQ(Robot::getObjectCount(), initialCount + 1);
}

TEST_F(RobotTest, MovedFromObjectCanBeAssignedAgain) {
    Robot moved(std::move(*robot));
    *robot = moved;
    expectRex(*robot);
    expectRex(moved);
}

TEST_F(RobotTest, DestructionDecreasesCount) {
    {
        const Robot temporary;
        EXPECT_EQ(Robot::getObjectCount(), initialCount + 2);
    }
    EXPECT_EQ(Robot::getObjectCount(), initialCount + 1);
}

TEST_F(RobotTest, InvalidParametersDoNotIncreaseCount) {
    EXPECT_THROW((Robot("", 80, "walk", 0, history)), std::invalid_argument);
    EXPECT_THROW((Robot("Rex", -1, "walk", 0, history)), std::invalid_argument);
    EXPECT_THROW((Robot("Rex", 101, "walk", 0, history)), std::invalid_argument);
    EXPECT_THROW((Robot("Rex", 80, "walk", -1, history)), std::invalid_argument);
    auto invalid = history;
    invalid[9] = -1;
    EXPECT_THROW((Robot("Rex", 80, "walk", 0, invalid)), std::invalid_argument);
    EXPECT_EQ(Robot::getObjectCount(), initialCount + 1);
}
