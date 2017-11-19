//
// Created by Mike Mitterer on 11.11.17.
//

#include "stdafx.h"
#include "rule_of_x.h"

uint8_t Resource::instanceCounter{0};

Resource::Resource(const std::string& _value)
        : value{_value} {
    
    instanceCounter++;
    logger->debug("[{}] Resource - Konstruktor",__FILENAME__);
}

Resource::~Resource() {
    logger->debug("[{}] Resource - Destruktor",__FILENAME__);
}

/// Default constructor
///     auto ado = AllDefaultOperators();
AllDefaultOperators::AllDefaultOperators()
        : name(new char[UNDEFINED.length() + 1 + MSG_CREATED_IN_DEFAULT_CTOR.length()]) {
    
    std::strcpy(name,UNDEFINED.c_str());
    std::strcat(name, MSG_CREATED_IN_DEFAULT_CTOR.c_str());

    _logger->debug("[{}] Default-Konstruktor ({})",__FILENAME__,name);
}

/// Explicit constructor
///     auto ado = AllDefaultOperators("Mike");
AllDefaultOperators::AllDefaultOperators(const char* arg)
: name(new char[std::strlen(arg) + 1 + MSG_CREATED_IN_CTOR.length()]) {

    std::strcpy(name,arg);
    std::strcat(name, MSG_CREATED_IN_CTOR.c_str());

    _logger->debug("[{}] Konstruktor ({})",__FILENAME__,name);
}

/// Copy construktor
///     auto ado1 = AllDefaultOperators("Mike");
///     auto ado2 = ado1;
AllDefaultOperators::AllDefaultOperators(const AllDefaultOperators& _other)
: name(new char[std::strlen(_other.getName()) + 1 + MSG_CREATED_IN_COPY_CTOR.length()]) {

    std::strcpy(name,_other.getName());
    std::strcat(name, MSG_CREATED_IN_COPY_CTOR.c_str());

    _logger->debug("[{}] Copy-Konstruktor ({})",__FILENAME__,name);
}

/// copy assignment operator
/// 
///     auto ado1 = AllDefaultOperators{"Mike"};
///     auto ado2 = AllDefaultOperators{"Gerda"};
///     
///     ado1 = ado2;
AllDefaultOperators& AllDefaultOperators::operator=(const AllDefaultOperators& _other) {
    //using std::swap;
    //swap(*this, _other);

    if(this == &_other) {
        return *this;
    }

    delete[] name;
    name = new char[std::strlen(_other.name) + 1];
    std::strcpy(name, _other.name);

    this->_logger = _other._logger;

//    // GOOD: no need to check for self-assignment (other than performance)
//    auto tmp = _other;
//    std::swap(*this, tmp);
//    return *this;

    _logger->debug("[{}] Zuweisungsoperator",__FILENAME__);
    return *this;
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

    _logger->debug("[{}] Move-Konstruktor ({})",__FILENAME__,name);
}

/// Move assignment operator
AllDefaultOperators& AllDefaultOperators::operator=(AllDefaultOperators&& _other) noexcept {

    if(this == &_other) {
        return *this;
    }

    delete[] name;
    name = _other.name;

    // Reset other
    _other.name = nullptr;

    _logger->debug("[{}] Move-Assignment",__FILENAME__);
    return *this;
}

/// Destruktor
AllDefaultOperators::~AllDefaultOperators() {

    delete[] name;
    _logger->debug("[{}] Destruktor",__FILENAME__);
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
