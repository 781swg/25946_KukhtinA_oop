#include "factory.h"
#include "squad.h"

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

TEST_F(RobotTest, FriendFunctionSetsManufacturer) {
    setManufacturer(*robot, "NSU Robotics");
    EXPECT_EQ(robot->getManufacturer(), "NSU Robotics");
    EXPECT_THROW(setManufacturer(*robot, ""), std::invalid_argument);
    EXPECT_EQ(robot->getManufacturer(), "NSU Robotics");
}

TEST_F(RobotTest, FriendMethodSetsModel) {
    const Administrator admin;
    admin.setModel(*robot, "Q-2");
    EXPECT_EQ(robot->getModel(), "Q-2");
    EXPECT_THROW(admin.setModel(*robot, ""), std::invalid_argument);
    EXPECT_EQ(robot->getModel(), "Q-2");
}

TEST_F(RobotTest, FactorySetsAllStateAndPreservesId) {
    const Factory factory;
    const auto id = robot->getId();
    factory.configure(*robot, "Spot", 50, "sit", 1, {}, "Factory A", "Q-3");
    EXPECT_EQ(robot->getId(), id);
    EXPECT_EQ(robot->getName(), "Spot");
    EXPECT_EQ(robot->getCharge(), 50);
    EXPECT_EQ(robot->getCommand(), "sit");
    EXPECT_DOUBLE_EQ(robot->getDistanceToday(), 1);
    EXPECT_EQ(robot->getDistances(), (std::array<double, 10>{}));
    EXPECT_EQ(robot->getManufacturer(), "Factory A");
    EXPECT_EQ(robot->getModel(), "Q-3");
    EXPECT_EQ(Robot::getObjectCount(), initialCount + 1);
}

TEST_F(RobotTest, InvalidFactoryParametersLeaveRobotUnchanged) {
    const Factory factory;
    EXPECT_THROW(factory.configure(*robot, "Spot", -1, "sit", 0, {}, "A", "Q"),
                 std::invalid_argument);
    EXPECT_THROW(factory.configure(*robot, "Spot", 50, "sit", 0, {}, "", "Q"),
                 std::invalid_argument);
    EXPECT_THROW(factory.configure(*robot, "Spot", 50, "sit", 0, {}, "A", ""),
                 std::invalid_argument);
    expectRex(*robot);
    EXPECT_EQ(robot->getManufacturer(), "Unknown");
    EXPECT_EQ(robot->getModel(), "Standard");
    EXPECT_EQ(Robot::getObjectCount(), initialCount + 1);
}

TEST_F(RobotTest, ManufacturerAndModelFollowCopyAndMove) {
    setManufacturer(*robot, "Factory A");
    Administrator admin;
    admin.setModel(*robot, "Q-2");
    Robot copy(*robot);
    EXPECT_EQ(copy.getManufacturer(), "Factory A");
    EXPECT_EQ(copy.getModel(), "Q-2");
    Robot moved(std::move(copy));
    EXPECT_EQ(moved.getManufacturer(), "Factory A");
    EXPECT_EQ(moved.getModel(), "Q-2");
    EXPECT_EQ(copy.getManufacturer(), "Unknown");
    EXPECT_EQ(copy.getModel(), "Standard");
    Robot target;
    target = moved;
    EXPECT_EQ(target.getManufacturer(), "Factory A");
    EXPECT_EQ(target.getModel(), "Q-2");
    target = std::move(*robot);
    EXPECT_EQ(target.getManufacturer(), "Factory A");
    EXPECT_EQ(target.getModel(), "Q-2");
}

TEST_F(RobotTest, AggregationDoesNotCreateOrDestroyRobots) {
    std::array<Robot, 5> externalRobots;
    const int count = Robot::getObjectCount();
    {
        AggregatedSquad squad({externalRobots[0], externalRobots[1],
                               externalRobots[2], externalRobots[3], externalRobots[4]});
        EXPECT_EQ(Robot::getObjectCount(), count);
        EXPECT_EQ(&squad.getRobot(0), &externalRobots[0]);
        const Administrator admin;
        admin.setModel(squad.getRobot(0), "Squad-Q");
        EXPECT_EQ(externalRobots[0].getModel(), "Squad-Q");
        EXPECT_THROW(squad.getRobot(5), std::out_of_range);
        const AggregatedSquad& view = squad;
        EXPECT_EQ(&view.getRobot(4), &externalRobots[4]);
    }
    EXPECT_EQ(Robot::getObjectCount(), count);
    EXPECT_EQ(externalRobots[0].getModel(), "Squad-Q");
}

TEST_F(RobotTest, CompositionOwnsFiveDistinctRobots) {
    const int count = Robot::getObjectCount();
    {
        ComposedSquad squad;
        EXPECT_EQ(Robot::getObjectCount(), count + 5);
        const Administrator admin;
        admin.setModel(squad.getRobot(0), "Owned-Q");
        const ComposedSquad& view = squad;
        EXPECT_EQ(view.getRobot(0).getModel(), "Owned-Q");
        for (std::size_t i = 0; i < 5; ++i) {
            for (std::size_t j = i + 1; j < 5; ++j) {
                EXPECT_NE(view.getRobot(i).getId(), view.getRobot(j).getId());
            }
        }
        EXPECT_THROW(squad.getRobot(5), std::out_of_range);
    }
    EXPECT_EQ(Robot::getObjectCount(), count);
}
