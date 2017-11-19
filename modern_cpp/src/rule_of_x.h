//
// Created by Mike Mitterer on 11.11.17.
//

#ifndef XCTEST_RULE_OF_X_H
#define XCTEST_RULE_OF_X_H

#include "stdafx.h"

class Resource {
private:
    const std::string value { "<undefined>" };

    // Default-Init ist zu bevorzugen
    const std::shared_ptr<spdlog::logger> logger { spdlog::get(mm::TEST_LOGGER) };

public:
    static uint8_t instanceCounter;

public:
    Resource(const std::string& value);
    Resource() = delete;

    virtual ~Resource();

    
};

const std::string MSG_CREATED_IN_DEFAULT_CTOR = " - default-CTOR";
const std::string MSG_CREATED_IN_CTOR = " - CTOR";
const std::string MSG_CREATED_IN_COPY_CTOR = " - copy-CTOR";

const std::string UNDEFINED = "<undefined>";

/**
 * Alle Operatoren können mit = delete gelöscht, oder mit = default in der default-Variante
 * erzeugt werden
 *
 * Rule of 5
 *      https://www.youtube.com/watch?v=JsaTQiYDBb0
 */
class AllDefaultOperators final {
private:
    // Default-Init ist zu bevorzugen
    std::shared_ptr<spdlog::logger> _logger { spdlog::get(mm::TEST_LOGGER) };

    char* name = nullptr;

public:
    /// Default constructor
    ///
    /// A good rule of thumb is: if you cannot define a default constructor
    /// for the class it cannot support move semantics.
    ///
    /// A default constructor is a constructor which can be called with no arguments
    /// (either defined with an empty parameter list,
    /// or with default arguments provided for every parameter)
    ///
    /// ClassName() = delete;
    /// ClassName() = default ;
    AllDefaultOperators();

    /// Explicit constructor
    AllDefaultOperators(const char* arg);

    /// Copy construktor
    AllDefaultOperators(const AllDefaultOperators& _other);

    /// Copy assignment operator
    AllDefaultOperators& operator=(const AllDefaultOperators& _other);

    /// Move constructor
    AllDefaultOperators(AllDefaultOperators&& _other) noexcept;

    /// Move assignment operator
    AllDefaultOperators& operator=(AllDefaultOperators&& _other) noexcept;

    /// Destruktor
    ///
    /// If A is intended to be used as a base class,
    /// and if callers should be able to destroy polymorphically,
    /// then make A::~A public and virtual.
    /// Otherwise make it protected (and not-virtual)
    virtual ~AllDefaultOperators();

    inline const char* getName() const { return name; }

    // Swap for ADL
    friend void swap(AllDefaultOperators& left, AllDefaultOperators& right) {
        using std::swap;
        swap(right.name, left.name);
    }

    const std::string toString() {
        return std::string(name);
    }
    
    //friend std::ostream& operator<<(std::ostream& os, std::string& s);
};

#endif //XCTEST_RULE_OF_X_H
