//
// Created by Mike Mitterer on 11.11.17.
//

#include "stdafx.h"
#include "rule_of_x.h"

uint8_t Resource::instanceCounter{0};

Resource::Resource(const std::string& _value)
        : value{_value} {
    
    instanceCounter++;
    logger->debug("")
}

Resource::~Resource() {

}


/// Default Konstruktor
AllDefaultOperators::AllDefaultOperators(const char* arg)
: name(new char[std::strlen(arg) + 1]) {
    std::strcpy(name,arg);
}

/// Copy Construktor
AllDefaultOperators::AllDefaultOperators(const AllDefaultOperators& _other)
: name(new char[std::strlen(_other.name) + 1]) {
    std::strcpy(name,_other.name);
}

/// Zuweisungsoperator
AllDefaultOperators& AllDefaultOperators::operator=(const AllDefaultOperators& _other) {
    //std::swap(name,_other.name);
    return *this;
}

/// Move Konstruktor
AllDefaultOperators::AllDefaultOperators(AllDefaultOperators&& _other)
: name(_other.name) {
    _other.name = nullptr;
}

/// Move-Zuweisungsoperator
AllDefaultOperators& AllDefaultOperators::operator=(AllDefaultOperators&& _other) {
    //std::swap(name,_other.name);
    return *this;
}

/// Destruktor
AllDefaultOperators::~AllDefaultOperators() {
    delete[] name;
}

