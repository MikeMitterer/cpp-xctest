//
// Created by Mike Mitterer on 11.11.17.
//

#ifndef XCTEST_RULE_OF_X_H
#define XCTEST_RULE_OF_X_H

#include "stdafx.h"

#include <vector>

#include "logger.h"

enum class FunctionType {
    DefaultCTOR, ParamCTOR, CopyCTOR, MoveCTOR,
    AssignmentOperator, MoveAssignmentOperator, Destructor
};

/**
 * Alle Operatoren können mit = delete gelöscht, oder mit = default in der default-Variante
 * erzeugt werden
 *
 * Rule of 5
 *      https://www.youtube.com/watch?v=JsaTQiYDBb0
 */
class RuleOf5 final {
    static const std::string _class() { return "RuleOf5"; }

private:

    // Default-Init ist zu bevorzugen
    std::shared_ptr<spdlog::logger> _logger { DefaultLogger::get(_class()) };

    char* name = nullptr;

public:
    static std::vector<uint8_t> functionCalls;

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
    RuleOf5();

    /// Explicit constructor (Single argument CTOR)
    explicit RuleOf5(const char* arg);

    /// Copy construktor
    RuleOf5(const RuleOf5& _other);

    /// Move constructor
    RuleOf5(RuleOf5&& _other) noexcept;

    /// Copy assignment operator
    RuleOf5& operator=(const RuleOf5& _other) noexcept;

    /// Move assignment operator
    RuleOf5& operator=(RuleOf5&& _other) noexcept;

    /// Destruktor
    ///
    /// If A is intended to be used as a base class,
    /// and if callers should be able to destroy polymorphically,
    /// then make A::~A public and virtual.
    /// Otherwise make it protected (and not-virtual)
    virtual ~RuleOf5();

    /// Das RuleOf5 object wird in einen String konvertiert
    /// Hier könnte auch "explicit" verwendet werden
    operator std::string();

    /// Ist als globale funktion zu implementieren
    /// 
    ///     std::stringstream buffer;
    ///     auto ruf = RuleOf5{"Mike"};
    ///
    ///     buffer << ruf;
    ///
    ///     auto result = buffer.str();
    ///
    friend std::ostream& operator<<(std::ostream& os, const RuleOf5& rof);

    inline const char* getName() const { return (name != nullptr ? name : "<null>"); }

    const std::string toString() const {
        return std::string(name);
    }

    static uint8_t nrOfCalls();
    static uint8_t nrOfCalls(FunctionType forType);

    static void showCalls();
};

#endif //XCTEST_RULE_OF_X_H
