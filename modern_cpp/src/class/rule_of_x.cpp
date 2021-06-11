//
// Created by Mike Mitterer on 11.11.17.
//

#include "stdafx.h"
#include "rule_of_x.h"

std::vector<uint8_t> RuleOf5::functionCalls { std::vector<uint8_t>(20,0) }; // NOLINT(cert-err58-cpp)
uint8_t RuleOf5::idCounter = 0;

/// Default constructor
///     auto ado = RuleOf5();
RuleOf5::RuleOf5() {
    functionCalls[static_cast<int>(FunctionType::DefaultCTOR)]++;
    ctorID = ++idCounter;

    _logger->debug("[{}] Default-Konstruktor ({}), ID: {}",__FILENAME__,getName(), ctorID);
}

/// Explicit constructor oder User-Defined-CTOR
///     auto ado = RuleOf5("Mike");
RuleOf5::RuleOf5(const char* firstname) {
    saveCopyFirstName(firstname);

    functionCalls[static_cast<int>(FunctionType::ParamCTOR)]++;
    ctorID = ++idCounter;

    _logger->debug("[{}] 1-Param-Konstruktor ( ({}), ID: {}",__FILENAME__, getName(), ctorID);
}

/// User-Defined-Constructor
///
/// Dieser CTOR wird auch als Delegation-CTOR (wird von einem anderen CTOR aufgerufen)
/// verwendet.
///
/// Der letzte Parameter (delegate) gibt an ob der CTOR als Delegate-CTOR aufgerufen wurde
RuleOf5::RuleOf5(const char* firstname, std::string _lastname, int8_t _age, std::vector<std::string> _hobbies, const Delegate& delegate)
: hobbies{ std::move(_hobbies) }, lastname { std::move(_lastname) }, age{ _age } {

    saveCopyFirstName(firstname);

    if(delegate == Delegate::No) {
        functionCalls[static_cast<int>(FunctionType::ParamCTOR)]++;
        ctorID = ++idCounter;

        _logger->debug("[{}] 4-Param-Konstruktor ({},{},{},{{ {} }}), ID: {}",
                       __FILENAME__,
                       getName(),
                       this->lastname,
                       this->age,
                       getHobbies(),
                       ctorID
        );
    }
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
///
/// Um Code-Duplication zu vermeiden wird hier der User-Defined-CTOR aufgerufen
RuleOf5::RuleOf5(const RuleOf5& _other)
: RuleOf5(_other.firstname, _other.lastname, _other.age, _other.hobbies, Delegate::Yes) {

    ctorID = ++idCounter;

    functionCalls[static_cast<int>(FunctionType::CopyCTOR)]++;
    _logger->debug("[{}] Copy-Konstruktor ({},{},{},{{ {} }}), ID: {}",
                   __FILENAME__,
                   getName(),
                   this->lastname,
                   this->age,
                   getHobbies(),
                   ctorID
    );

    functionCalls[static_cast<int>(FunctionType::DelegateCTOR)]++;
    _logger->debug("[{}]     Delegation-Konstruktor ({},{},{},{{ {} }}), ID: {}",
                   __FILENAME__,
                   getName(),
                   this->lastname,
                   this->age,
                   getHobbies(),
                   ctorID
    );

}

// copy assignment operator
RuleOf5& RuleOf5::operator=(RuleOf5 _other) noexcept {
    functionCalls[static_cast<int>(FunctionType::AssignmentOperator)]++;

    //    if(this != &_other) {
    //        delete[] firstname;
    //        firstname = nullptr;
    //        if(_other.firstname != nullptr) {
    //            auto size = strlen(_other.firstname);
    //            firstname = new char[size + 1];
    //            strcpy(firstname, _other.firstname);
    //        }
    //    }

    _logger->debug("[{}] copy assignment operator",__FILENAME__);
    _logger->debug("[{}]     Vor swap: ({}), ID: {}",__FILENAME__, getName(), ctorID);

    // Use copy and swap idiom to implement assignment.
    // _other wurde bereits kopiert!!! (Übergabeparameter = by value)
    swap(*this, _other);

    _logger->debug("[{}]     Nach swap: ({}), ID: {}",__FILENAME__, getName(), ctorID);

    return *this;
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
    //    firstname = _other.firstname;
    //
    //    // Reset other
    //    _other.firstname = nullptr;

    functionCalls[static_cast<int>(FunctionType::MoveCTOR)]++;
    ctorID = ++idCounter;

    _logger->debug("[{}] Move-Konstruktor",__FILENAME__);
    _logger->debug("[{}]    Vor swap: ({}), ID: {}",__FILENAME__,getName(), ctorID);

    // Swap ersetzt auch hier den oben auskommentierten Code-Block
    swap(*this, _other);
    
    _logger->debug("[{}]    Nach swap: ({}), ID: {}",__FILENAME__,getName(), ctorID);
}

// Move assignment operator
RuleOf5& RuleOf5::operator=(RuleOf5&& _other) noexcept {

    functionCalls[static_cast<int>(FunctionType::MoveAssignmentOperator)]++;

    //    if(this != &_other) {
    //        delete[] firstname;
    //        firstname = nullptr;
    //
    //        firstname = _other.firstname;
    //        _other.firstname = nullptr;
    //    }

    _logger->debug("[{}] move assignment operator",__FILENAME__);
    _logger->debug("    Vor swap: ({}), ID: {}",getName(), ctorID);

    // Auskommentierter Code-Block wird durch Swap ersetzt
    swap(*this, _other);

    _logger->debug("    Nach swap: ({}), ID: {}",getName(), ctorID);

    return *this;
}

/// Destruktor
RuleOf5::~RuleOf5() {

   functionCalls[static_cast<int>(FunctionType::Destructor)]++;


    if(firstname != nullptr) {
        _logger->debug("[{}] Destruktor for {}, ID: {}",__FILENAME__, firstname, ctorID);
    } else {
        _logger->debug("[{}] Destruktor ID: {}",__FILENAME__, ctorID);
        _logger->debug("[{}]    firstname is a nullptr (is OK for default CTOR)", __FILENAME__);
    }

    // firstname könnte auch ein nullptr sein - stellt aber kein Problem dar
    delete[] firstname;
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

RuleOf5::operator std::string() const {
    return std::string(getName());
}

std::ostream& operator<<(std::ostream& os, const RuleOf5& rof) {
    os << rof.getName();
    return os;
}

void swap(RuleOf5& lhs, RuleOf5& rhs) {
    using std::swap;

    // Logger!!!!????
    // std::swap(lhs._logger, rhs._logger);

    std::swap(lhs.hobbies, rhs.hobbies);
    std::swap(lhs.firstname, rhs.firstname);
    std::swap(lhs.lastname, rhs.lastname);
    std::swap(lhs.age, rhs.age);

    // std::swap(lhs.ctorID, rhs.ctorID);
}

