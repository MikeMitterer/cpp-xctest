#include "stdafx.h"
#include "setup.h"

#include "NameEvent.h"
#include "class_template.h"
#include "function_template.h"

#include <utility>
#include <gtest/gtest.h>


using namespace std;

template<typename T>
uint8_t StaticTemplateSample<T>::instanceCounter = 0;

uint8_t StaticSample::instanceCounter = 0;

class TemplateTestCast : public ::testing::Test {
protected:
    TestSetup* testSetup = nullptr;

    void SetUp() override {
        delete testSetup;
        testSetup = new TestSetup();
    }

    void TearDown() override {
        delete testSetup;
        testSetup = nullptr;
    }
};

TEST_F(TemplateTestCast, functionTemplate) {

    EXPECT_EQ(toString("Mike"), "Mike");

    EXPECT_EQ(toString(10), "10");

    // Math-Constants:
    //      https://www.quantstart.com/articles/Mathematical-Constants-in-C/
    EXPECT_EQ(toString(M_PI + 10.0), "13.14");
    EXPECT_EQ(toString(M_PI + 100.0), "103.14");

    EXPECT_EQ(toString(3.14f), "3.14f");
}



TEST_F(TemplateTestCast, toJson) {
    const NameEvent name{"Mike", 55};

    const auto json = name.toJson();
    std::cout << json;

    EXPECT_EQ(json, "{ \"name\": \"Mike\", \"age\": 55 }");
}

TEST_F(TemplateTestCast, classTemplate) {
    // Compiliert - ist aber falsch!!!!! (Definiert eine Funktion)
    // const JsonEvent<NameEvent> event1()

    // const auto name = Name{ "Mike", 99u };
    
    const JsonEvent<NameEvent> event {
        "mm.event.SendName", NameEvent{ "Mike", 88u }
    };

    const auto json = event.toJson();
    std::cout << json;

    EXPECT_EQ(mm::utils::removeSpace(json), "{\"event\":\"mm.event.sendname\",\"data\":{\"name\":\"Mike\",\"age\":88}}");
}

TEST_F(TemplateTestCast, typeConstraint) {

    // In template:
    //      failed requirement
    //      'std::is_base_of<ToJson, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>>::value'; 'enable_if' cannot be used to disable this declaration

    // Compiliert nicht - mit oben genannter Fehlermeldung!
    // const JsonEvent<std::string> event("mm.event.SendName", Name("Mike", 99));

    EXPECT_EQ(true, true);
}

TEST_F(TemplateTestCast, nonStaticClassWithFunctionTemplate) {
    SimpleClass testClass;

    EXPECT_EQ(testClass.convToString(10), "10");
    EXPECT_EQ(testClass.sayMyName(), "Sarah");
}

// -------------------------------------------------------------------------------------------------
// Quiz
// -------------------------------------------------------------------------------------------------

// [] Implementiere die Funktion "myswap"
TEST_F(TemplateTestCast, staticMember) {
    StaticTemplateSample<int> s1{"Mike", 1};
    StaticTemplateSample<int> s2{"Mike", 1};
    StaticTemplateSample<float> s3{"Mike", 1};

    StaticSample s4{"Mike", 1};
    StaticSample s5{"Mike", 1};
    StaticSample s6{"Mike", 1};

    EXPECT_EQ(s2.instanceCounter, 2);
    EXPECT_EQ(s3.instanceCounter, 1);
    EXPECT_EQ(s6.instanceCounter, 3);

    {
        StaticTemplateSample<int> s1{"Mike", 1};
        EXPECT_EQ(s1.instanceCounter, 3);

        StaticSample s7("Mike", 1);

        EXPECT_EQ(s6.instanceCounter, 4);
        EXPECT_EQ(s7.instanceCounter, 4);
    }

    // [] Welchen Wert hat s1.instanceCounter
    EXPECT_EQ(s1.instanceCounter, 2);

    // [] Welchen Wert hat s6.instanceCounter
    EXPECT_EQ(s6.instanceCounter, 3);
}


// [] Implementiere die Funktion "myswap"
TEST_F(TemplateTestCast, swapValue) {

    auto v1 = 10;
    auto v2 = 20;
    myswap(v1, v2);

    EXPECT_EQ(v2, 10);

    auto v3 = "Mike";
    auto v4 = "Sarah";
    myswap(v3, v4);

    EXPECT_EQ(v3, "Sarah");
}



