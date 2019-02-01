#include <utility>

//
// Created by Mike Mitterer on 11.11.17.
//

#include "stdafx.h"
#include "rule_of_x.h"

uint8_t Resource::instanceCounter{0};

Resource::Resource(std::string _value)
        : value{ std::move(_value) } {
    
    instanceCounter++;
    logger->debug("[] Resource - Konstruktor");
}

Resource::~Resource() {
    //logger->debug("[{}] Resource - Destruktor",__FILENAME__);
    
    spdlog::drop(_class());
}

const std::string AllDefaultOperators::_LOGGER_NAME = "AllDefaultOperators";

/// Default constructor
///     auto ado = AllDefaultOperators();
AllDefaultOperators::AllDefaultOperators()
        : name(new char[UNDEFINED.length() + 1 + MSG_CREATED_IN_DEFAULT_CTOR.length()]) {
    
    std::strcpy(name,UNDEFINED.c_str());
    std::strcat(name, MSG_CREATED_IN_DEFAULT_CTOR.c_str());

    // _logger->debug("[{}] Default-Konstruktor ({})",__FILENAME__,name);
}

/// Explicit constructor
///     auto ado = AllDefaultOperators("Mike");
AllDefaultOperators::AllDefaultOperators(const char* arg)
: name(new char[std::strlen(arg) + 1 + MSG_CREATED_IN_CTOR.length()]) {

    std::strcpy(name,arg);
    std::strcat(name, MSG_CREATED_IN_CTOR.c_str());

    // _logger->debug("[{}] Konstruktor ({})",__FILENAME__,name);
}

/// Copy construktor
///     auto ado1 = AllDefaultOperators("Mike");
///     auto ado2 = ado1;
AllDefaultOperators::AllDefaultOperators(const AllDefaultOperators& _other)
: name(new char[std::strlen(_other.getName()) + 1 + MSG_CREATED_IN_COPY_CTOR.length()]) {

    std::strcpy(name,_other.getName());
    std::strcat(name, MSG_CREATED_IN_COPY_CTOR.c_str());

    // _logger->debug("[{}] Copy-Konstruktor ({})",__FILENAME__,name);
}

/// Move constructor
///
/// When implementing move special member functions, adhere to the following guideline:
///     - The target object must release its resources (if any) before acquiring new resources.
///     - Acquire the resources.
///     - Set the source's data members to their default values.
AllDefaultOperators::AllDefaultOperators(AllDefaultOperators&& _other) noexcept
/* :  name{std::move(_other.name)} */ {

    name = _other.name;

    // Reset other
    _other.name = nullptr;

    // _logger->debug("[{}] Move-Konstruktor ({})",__FILENAME__,name);
}


/// Diese Variante kombiniert den
/// (Copy + Swap pattern: https://cpppatterns.com/patterns/copy-and-swap.html)
///
///     // copy assignment operator
///     AllDefaultOperators& AllDefaultOperators::operator=(const AllDefaultOperators& _other)
///
/// und den
///
///     // Move assignment operator
///     AllDefaultOperators& AllDefaultOperators::operator=(AllDefaultOperators&& _other) noexcept
///
/// This assignment operator takes its argument by value,
/// making use of the existing copy and move constructor implementations.
AllDefaultOperators& AllDefaultOperators::operator=(AllDefaultOperators _other) noexcept {
      swap(*this, _other);
      return *this;
}

// Swap for ADL
void swap(AllDefaultOperators& left, AllDefaultOperators& right) {
    std::swap(right.name, left.name);
}


/// Destruktor
AllDefaultOperators::~AllDefaultOperators() {

    // _logger->debug("[{}] Destruktor",__FILENAME__);

    delete[] name;
    
    // spdlog::drop(_LOGGER_NAME);
}


//
//void AllDefaultOperators::swap(AllDefaultOperators& left, AllDefaultOperators& right) {
//    using std::swap;
//    swap(left.name, right.name);
//}

//std::ostream& AllDefaultOperators::operator<<(std::ostream& os, std::string& s) {
//
//    std::cout << "std::ostream operator called" << std::endl;
//    os << s.begin() ;
//
//    return os;
//}
