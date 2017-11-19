//
// Created by Mike Mitterer on 02.11.15.
//

#include "gtest/gtest.h"
#include "rule_of_x.h"

Resource createObjectTest(bool condition);

AllDefaultOperators getTempValueViaCopyElision();
AllDefaultOperators getTempValueViaMoveCTOR();

void moveCTOR(AllDefaultOperators operators);

TEST(rule_of_x, test_instance_counter) {
    auto logger = spdlog::stdout_color_mt(mm::TEST_LOGGER);
    //logger->set_level(mm::DEFAULT_LOG_LEVEL);

    // Führt zu einer Fehlermeldung da dieser Konstruktor gelöscht wurde
    // const auto r1 = Resource{};

    const auto r1 = Resource{"Mike1"};
    EXPECT_EQ(r1.instanceCounter, 1);

    const auto r2 = Resource{"Mike2"};
    EXPECT_EQ(r1.instanceCounter, 2);
    EXPECT_EQ(r2.instanceCounter, 2);

    const auto r3 = createObjectTest(true);
    EXPECT_EQ(r1.instanceCounter, 4);
    EXPECT_EQ(r2.instanceCounter, 4);
    EXPECT_EQ(r3.instanceCounter, 4);
}

TEST(rule_of_x, test_default_ctor) {
    auto logger = spdlog::stdout_color_mt(mm::TEST_LOGGER);
    //logger->set_level(spdlog::level::info);

    auto ado = AllDefaultOperators();
    auto expectedResult = (UNDEFINED + MSG_CREATED_IN_DEFAULT_CTOR);

    ASSERT_STREQ(ado.getName(), expectedResult.c_str());
}

TEST(rule_of_x, test_ctor) {
    auto logger = spdlog::stdout_color_mt(mm::TEST_LOGGER);
    //logger->set_level(spdlog::level::info);

    auto ado = AllDefaultOperators{"Mike"};
    auto expectedResult = (std::string("Mike") + MSG_CREATED_IN_CTOR);

    ASSERT_STREQ(ado.getName(), expectedResult.c_str());
}

TEST(rule_of_x, test_copy_ctor) {
    auto logger = spdlog::stdout_color_mt(mm::TEST_LOGGER);
    //logger->set_level(spdlog::level::info);

    auto ado1 = AllDefaultOperators{"Mike"};
    auto ado2 = ado1;

    auto expectedName1 = (std::string{"Mike"} + MSG_CREATED_IN_CTOR);
    auto expectedName2 = (expectedName1 + MSG_CREATED_IN_COPY_CTOR);

    ASSERT_STREQ(ado2.getName(), expectedName2.c_str());
}

TEST(rule_of_x, test_assignement_operator) {
    auto logger = spdlog::stdout_color_mt(mm::TEST_LOGGER);
    logger->set_level(spdlog::level::debug);
    
    auto ado1 = AllDefaultOperators{"Mike"};
    auto ado2 = AllDefaultOperators{"Gerda"};

    // copy assignment operator
    ado1 = ado2;

    auto expectedName1 = (std::string{"Gerda"} + MSG_CREATED_IN_CTOR);
    auto expectedName2 = (std::string{"Gerda"} + MSG_CREATED_IN_CTOR);

    ASSERT_STREQ(ado1.getName(), expectedName1.c_str());
    ASSERT_STREQ(ado2.getName(), expectedName2.c_str());
}


TEST(rule_of_x, test_move_ctor) {
    auto logger = spdlog::stdout_color_mt(mm::TEST_LOGGER);
    logger->set_level(spdlog::level::debug);

    auto ado1 = AllDefaultOperators{"Sarah"};

    // Param von moveCTOR wird per Value übergeben
    moveCTOR(std::move(ado1));

    ASSERT_TRUE(ado1.getName() == nullptr);
}

TEST(rule_of_x, test_move_ctor2) {
    auto logger = spdlog::stdout_color_mt(mm::TEST_LOGGER);
    logger->set_level(spdlog::level::debug);

    auto ado1 = getTempValueViaCopyElision();

    auto expectedName1 = (std::string{"Pepples"} + MSG_CREATED_IN_CTOR);
    ASSERT_STREQ(ado1.getName(),expectedName1.c_str());
}

TEST(rule_of_x, test_move_ctor3) {
    auto logger = spdlog::stdout_color_mt(mm::TEST_LOGGER);
    logger->set_level(spdlog::level::debug);

    auto ado1 = getTempValueViaMoveCTOR();

    auto expectedName1 = (std::string{"Pepples2"} + MSG_CREATED_IN_CTOR);
    ASSERT_STREQ(ado1.getName(),expectedName1.c_str());
}

TEST(rule_of_x, test_move_assignement) {
    auto logger = spdlog::stdout_color_mt(mm::TEST_LOGGER);
    logger->set_level(spdlog::level::debug);

    auto ado1 = AllDefaultOperators{};
    auto ado2 = AllDefaultOperators{"Mike"};

    // copy assignment operator
    ado1 = ado2;

    auto expectedName1 = (std::string{"Mike"} + MSG_CREATED_IN_CTOR);
    auto expectedName2 = (std::string{"Mike"} + MSG_CREATED_IN_CTOR);

    ASSERT_STREQ(ado1.getName(), expectedName1.c_str());
    ASSERT_STREQ(ado2.getName(), expectedName2.c_str());

    // Move assignment wird aufgerufen
    ado1 = std::move(AllDefaultOperators{"Sarah"});
    expectedName1 = (std::string{"Sarah"} + MSG_CREATED_IN_CTOR);
    ASSERT_STREQ(ado1.getName(), expectedName1.c_str());
}

/// Return value optimization (RVO)
///
/// Bei der Rückgabe wird keine Kopie angelegt
/// https://en.wikipedia.org/wiki/Copy_elision#Return_value_optimization
Resource createObjectTest(bool condition) {
    const auto r1 = Resource("Gerda");
    const auto r2 = Resource("Sarah");

    return condition ? r1 : r2;
}

AllDefaultOperators getTempValueViaCopyElision() {
    auto ado1 = AllDefaultOperators{"Pepples"};

    // Move bringt hier nichts - copy elision!!!
    // Return value optimization!!!
    return ado1;
}

/// Die Funktion hat mehr als einen möglichen Rückgabewert!!!!
/// Move-CTRO wird aufgerufen
AllDefaultOperators getTempValueViaMoveCTOR() {
    auto ado1 = AllDefaultOperators{"Pepples2"};

    if(std::strcmp(ado1.getName(),"abc") == 0) {
        return nullptr;
    }
    return ado1;
}

/// Nur wenn der Param keine Adresse oder Referenze ist wird
/// der move constructor aufgerufen
void moveCTOR(AllDefaultOperators operators) {
    auto logger = spdlog::get(mm::TEST_LOGGER);
    logger->set_level(spdlog::level::debug);

    logger->debug("Inside function: {}",operators.getName());
}


