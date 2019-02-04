#include <utility>

//
// Created by Mike Mitterer on 11.11.17.
//

#include "stdafx.h"
#include "rule_of_x.h"

std::vector<uint8_t> RuleOf5::functionCalls { std::vector<uint8_t>(7,0) }; // NOLINT(cert-err58-cpp)

/// Default constructor
///     auto ado = RuleOf5();
RuleOf5::RuleOf5() {

    functionCalls[static_cast<int>(FunctionType::DefaultCTOR)]++;

    _logger->debug("[{}] Default-Konstruktor ({})",__FILENAME__,getName());
}

/// Explicit constructor
///     auto ado = RuleOf5("Mike");
RuleOf5::RuleOf5(const char* arg) {

    if(arg != nullptr) {
        auto size = strlen(arg);
        name = new char[size+1];
        strcpy(name, arg);
    }

    functionCalls[static_cast<int>(FunctionType::ParamCTOR)]++;

    _logger->debug("[{}] Param-Konstruktor ({})",__FILENAME__, getName());
}

/// Copy construktor
///     auto ado1 = AllDefaultOperators("Mike");
///     auto ado2 = ado1;
///
/// In C++, a Copy Constructor may!!!! be called in following cases:
///     1. When an object is constructed based on another object of the same class.
///     2. When an object of the class is returned by value.
///     3. When an object of the class is passed (to a function) by value as an argument.
///     4. When the compiler generates a temporary object.
///
/// Muss nicht so sein - der compiler kann bestimmte calls optimieren
RuleOf5::RuleOf5(const RuleOf5& _other) {

    if(_other.name != nullptr) {
        auto size = strlen(_other.name);
        name = new char[size+1];
        strcpy(name, _other.name);
    }

    functionCalls[static_cast<int>(FunctionType::CopyCTOR)]++;

    _logger->debug("[{}] Copy-Konstruktor ({})",__FILENAME__, getName());
}

/// Move constructor
///
/// When implementing move special member functions, adhere to the following guideline:
///     - The target object must release its resources (if any) before acquiring new resources.
///     - Acquire the resources.
///     - Set the source's data members to their default values.
///
/// In C++, a Copy Constructor may!!!! be called in following cases:
///     - when an object initializer is std::move(something)
///     - when an object initializer is std::forward<T>(something) and T is not an lvalue reference type (useful in template programming for "perfect forwarding")
///     - when an object initializer is a temporary and the compiler doesn't eliminate the copy/move entirely
///     - when returning a function-local class object by value and the compiler doesn't eliminate the copy/move entirely
///     - when throwing a function-local class object and the compiler doesn't eliminate the copy/move entirely
RuleOf5::RuleOf5(RuleOf5&& _other) noexcept {

    name = _other.name;

    // Reset other
    _other.name = nullptr;

    functionCalls[static_cast<int>(FunctionType::MoveCTOR)]++;

    _logger->debug("[{}] Move-Konstruktor ({})",__FILENAME__, getName());
}


// copy assignment operator
RuleOf5& RuleOf5::operator=(const RuleOf5& _other) noexcept {

    functionCalls[static_cast<int>(FunctionType::AssignmentOperator)]++;

    if(this != &_other) {
        delete[] name;
        name = nullptr;
        if(_other.name != nullptr) {
            auto size = strlen(_other.name);
            name = new char[size+1];
            strcpy(name, _other.name);
        }
    }


    _logger->debug("[{}] copy assignment operator ({})",__FILENAME__, getName());

    return *this;
}

// Move assignment operator
RuleOf5& RuleOf5::operator=(RuleOf5&& _other) noexcept {

    functionCalls[static_cast<int>(FunctionType::MoveAssignmentOperator)]++;

    if(this != &_other) {
        delete[] name;
        name = nullptr;

        name = _other.name;
        _other.name = nullptr;
    }

    _logger->debug("[{}] copy assignment operator ({})",__FILENAME__, getName());

    return *this;
}

/// Destruktor
RuleOf5::~RuleOf5() {

    delete[] name;

    functionCalls[static_cast<int>(FunctionType::Destructor)]++;

    _logger->debug("[{}] Destruktor",__FILENAME__);

}

uint8_t RuleOf5::nrOfCalls() {
    auto result = 0;
    for(const auto calls : functionCalls) {
        result += calls;
    }
    return result;
}

void RuleOf5::showCalls() {
    std::cout << "Default CTOR:      " << functionCalls[static_cast<int>(FunctionType::DefaultCTOR)] << std::endl;
    std::cout << "Param CTOR:        " << functionCalls[static_cast<int>(FunctionType::ParamCTOR)] << std::endl;
    std::cout << "Copy CTOR:         " << functionCalls[static_cast<int>(FunctionType::CopyCTOR)] << std::endl;
    std::cout << "Move CTOR:         " << functionCalls[static_cast<int>(FunctionType::MoveCTOR)] << std::endl;
    std::cout << "Assignment:        " << functionCalls[static_cast<int>(FunctionType::AssignmentOperator)] << std::endl;
    std::cout << "Move-Assignment:   " << functionCalls[static_cast<int>(FunctionType::MoveAssignmentOperator)] << std::endl;
    std::cout << "Destruktor:        " << functionCalls[static_cast<int>(FunctionType::Destructor)] << std::endl;
}

uint8_t RuleOf5::nrOfCalls(const FunctionType forType){
    return functionCalls[static_cast<int>(forType)];
}

RuleOf5::operator std::string() {
    return std::string(getName());
}

std::ostream& operator<<(std::ostream& os, const RuleOf5& rof) {
    os << rof.getName();
    return os;
}
