//
// Created by Mike Mitterer on 23.04.21.
//

#include <stdafx.h>

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

#include "setup.h"
#include "tdd/base.h"

class BaseTestCase : public ::testing::Test {
protected:
    TestSetup* testSetup = nullptr;

    void SetUp() override { testSetup = new TestSetup(); }
    void TearDown() override { delete testSetup; testSetup = nullptr; }
};

TEST_F(BaseTestCase, structTest) {
    const Point point{ 10, 5};

    EXPECT_EQ(point.x, 10);
    EXPECT_EQ(point.y, 5);
}

TEST_F(BaseTestCase, classExtendsStructTest) {
    const Point3D point{ {10, 5}, 8};

    EXPECT_EQ(point.x, 10);
    EXPECT_EQ(point.y, 5);
    EXPECT_EQ(point.z, 8);
}

TEST_F(BaseTestCase, stackTest) {
    const Point point1{ 10, 5};
    const Point point2{ 5, 5};

    EXPECT_EQ(point1.x, 10);
    EXPECT_EQ(point2.x, 5);
}

TEST_F(BaseTestCase, heapTest) {
    const Point* point1 = new Point{ 10, 5};
    auto point2 = new Point{ 88, 99};

    EXPECT_EQ(point1->x, 10);
    EXPECT_EQ(point2->x, 88);

    delete point1;
    delete point2;
}

TEST_F(BaseTestCase, heapTestSmartPointer) {
    const std::shared_ptr<PrecisePoint> point1 = std::make_shared<PrecisePoint>(5.5, 99);
    const auto point2 = std::make_shared<PrecisePoint>(8, 9.9);

    EXPECT_EQ(point1->x, 5.5);
    EXPECT_EQ(point2->y, 9.9);
}





