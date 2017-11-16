//
// Created by Mike Mitterer on 02.11.15.
//

#include "gtest/gtest.h"
#include "rule_of_x.h"

TEST(basic_check_ma, test_instance_counter) {

    // Führt zu einer Fehlermeldung da dieser Konstruktor gelöscht wurde
    // const auto r1 = Resource{};

    const auto r1 = Resource{"Mike1"};
    EXPECT_EQ(r1.instanceCounter, 1);

    const auto r2 = Resource{"Mike2"};
    EXPECT_EQ(r1.instanceCounter, 2);
    EXPECT_EQ(r2.instanceCounter, 2);
}

TEST(basic_check_ma, test_neq) {
    EXPECT_NE(1, 0);
}

