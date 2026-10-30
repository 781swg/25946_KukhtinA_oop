#include "robot.h"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(RobotTests, DefaultConstructor) {
    QuadrupedRobot robot;
    EXPECT_FALSE(robot.getId().empty());
    EXPECT_EQ(robot.getName(), "робот");
    EXPECT_EQ(robot.getBattery(), 100);
    EXPECT_EQ(robot.getCommand(), "ожидание");
    EXPECT_DOUBLE_EQ(robot.getTodayDistance(), 0);
    for (int day = 0; day < 10; ++day) {
        EXPECT_DOUBLE_EQ(robot.getDayDistance(day), 0);
    }
}

TEST(RobotTests, InitializationAndNormalization) {
    QuadrupedRobot robot("", 200, "", -5);
    EXPECT_EQ(robot.getName(), "робот");
    EXPECT_EQ(robot.getBattery(), 100);
    EXPECT_EQ(robot.getCommand(), "ожидание");
    EXPECT_DOUBLE_EQ(robot.getTodayDistance(), 0);
}

TEST(RobotTests, GettersAndSetters) {
    QuadrupedRobot robot;
    robot.setName("барс");
    robot.setBattery(-10);
    robot.setCommand("бежать");
    robot.setTodayDistance(6.5);
    robot.setDayDistance(0, 2.0);
    robot.setDayDistance(9, -1.0);
    EXPECT_EQ(robot.getName(), "барс");
    EXPECT_EQ(robot.getBattery(), 0);
    EXPECT_EQ(robot.getCommand(), "бежать");
    EXPECT_DOUBLE_EQ(robot.getTodayDistance(), 6.5);
    EXPECT_DOUBLE_EQ(robot.getDayDistance(0), 2.0);
    EXPECT_DOUBLE_EQ(robot.getDayDistance(9), 0.0);
    EXPECT_THROW(robot.getDayDistance(10), std::out_of_range);
    EXPECT_THROW(robot.setDayDistance(-1, 1), std::out_of_range);
}

TEST(RobotTests, CopyConstructor) {
    QuadrupedRobot a("барс", 60, "идти", 4);
    a.setDayDistance(2, 12.5);
    QuadrupedRobot b = a;
    EXPECT_NE(a.getId(), b.getId());
    EXPECT_EQ(b.getName(), "барс");
    EXPECT_EQ(b.getBattery(), 60);
    EXPECT_EQ(b.getCommand(), "идти");
    EXPECT_DOUBLE_EQ(b.getTodayDistance(), 4);
    EXPECT_DOUBLE_EQ(b.getDayDistance(2), 12.5);
}

TEST(RobotTests, AssignmentAndSelfAssignment) {
    QuadrupedRobot a("барс", 60, "идти", 4);
    QuadrupedRobot b;
    std::string originalId = b.getId();
    b = a;
    EXPECT_EQ(b.getId(), originalId);
    EXPECT_NE(b.getId(), a.getId());
    EXPECT_EQ(b.getName(), a.getName());
    b = b;
    EXPECT_EQ(b.getId(), originalId);
    EXPECT_EQ(b.getName(), "барс");
}


TEST(RobotTests, DynamicArrayAndBounds) {
    QuadrupedRobot robot;
    for (int i = 0; i < 4; ++i) EXPECT_DOUBLE_EQ(robot.getLegAngle(i), 0);
    robot.setLegAngle(0, 25);
    robot.setLegAngle(1, 100);
    robot.setLegAngle(2, -100);
    EXPECT_DOUBLE_EQ(robot.getLegAngle(0), 25);
    EXPECT_DOUBLE_EQ(robot.getLegAngle(1), 90);
    EXPECT_DOUBLE_EQ(robot.getLegAngle(2), -90);
    EXPECT_THROW(robot.getLegAngle(4), std::out_of_range);
    EXPECT_THROW(robot.setLegAngle(-1, 0), std::out_of_range);
}

TEST(RobotTests, DeepCopy) {
    QuadrupedRobot first;
    first.setLegAngle(0, 12);
    QuadrupedRobot second = first;
    first.setLegAngle(0, 36);
    EXPECT_DOUBLE_EQ(second.getLegAngle(0), 12);
    EXPECT_DOUBLE_EQ(first.getLegAngle(0), 36);
    EXPECT_NE(first.getId(), second.getId());
}

TEST(RobotTests, DeepAssignment) {
    QuadrupedRobot first;
    first.setLegAngle(2, 15);
    QuadrupedRobot second;
    second.setLegAngle(2, 40);
    const std::string previousId = second.getId();
    second = first;
    first.setLegAngle(2, 80);
    EXPECT_DOUBLE_EQ(second.getLegAngle(2), 15);
    EXPECT_EQ(second.getId(), previousId);
    second = second;
    EXPECT_DOUBLE_EQ(second.getLegAngle(2), 15);
}

TEST(RobotTests, DestructorMessage) {
    // проверяем, что вызывается деструктор
    testing::internal::CaptureStdout();
    {
        QuadrupedRobot robot;
    }
    const std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("деструктор"), std::string::npos);
}
