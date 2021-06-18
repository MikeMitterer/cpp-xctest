//
// Created by Mike Mitterer on 11.11.17.
//

#ifndef XCTEST_RULE_OF_X_H
#define XCTEST_RULE_OF_X_H

#include "stdafx.h"

#include "logger.h"
#include "string_utils.h"

#include <utility>
#include <vector>


enum class FunctionType {
    DefaultCTOR, ParamCTOR, CopyCTOR,
    DelegateCTOR,
    MoveCTOR,
    AssignmentOperator, MoveAssignmentOperator,
    Destructor
};

enum class Delegate {
    Yes, No
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

    // Default-Init ist zu bevorzugen - auch in Hinblick auf das
    // Swap-Ideom, Move-Constructor + Move-Assignment-Operator
    std::shared_ptr<spdlog::logger> _logger { DefaultLogger::get(_class()) };

    std::vector<std::string> hobbies;

    char* firstname = nullptr;
    std::string lastname { "" };

    int8_t age{ -1 };
    
public:
    /** Merkt sich die jeweilige CTOR-ID (idCounter) */
    uint8_t ctorID;

    // Wird beim Aufruf eines CTORs um eins erhöht!
    // Friend-Function ist hier zu kompliziert...
    static uint8_t idCounter;
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
    explicit RuleOf5(const char* firstname);

    /// Mit explicit wird die implizite Typumwandlung des Compilers unterbunden
    explicit RuleOf5(const char* firstname, std::string lastname, int8_t age, std::vector<std::string> hobbies = {}, const Delegate& delegate = Delegate::No);

    /// Copy construktor
    RuleOf5(const RuleOf5& _other);

    /// Copy assignment operator
    RuleOf5& operator=(RuleOf5 _other) noexcept;

    /// Move constructor
    RuleOf5(RuleOf5&& _other) noexcept;

    /// Move assignment operator
    RuleOf5& operator=(RuleOf5&& _other) noexcept;

    friend void swap(RuleOf5& lhs, RuleOf5& rhs);

    /// Destruktor
    ///
    /// If A is intended to be used as a base class,
    /// and if callers should be able to destroy polymorphically,
    /// then make A::~A public and virtual.
    /// Otherwise make it protected (and not-virtual)
    virtual ~RuleOf5();

    /// Das RuleOf5 object wird in einen String konvertiert
    /// Hier könnte auch "explicit" verwendet werden
    /// Usage:
    ///       auto ruf = RuleOf5{"Mike"};
    ///       std::string name = ruf;
    ///
    operator std::string() const;

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

    inline const char* getName() const { return (firstname != nullptr ? firstname : "<null>"); }

    std::string getHobbies(const char *const delimiter = ", ") {
        return mm::string::Join(hobbies, delimiter);
    }

    int8_t getAge() { return age; }

    std::string getFullName() {
        return std::string(getName()) + " " + lastname;
    }

    [[nodiscard]]
    const std::string toString() const {
        return std::string(firstname);
    }

    static uint8_t nrOfCalls();
    static uint8_t nrOfCalls(FunctionType forType);

    static void showCalls();

private:
    void saveCopyFirstName(const char* firstname) {
        if(firstname != nullptr) {
            auto size = strlen(firstname);

            // Size ist die länge + 1 für die \0-Terminierung des Strings
            this->firstname = new char[size + 1];
            strcpy(this->firstname, firstname);
        }
    }
};

#endif //XCTEST_RULE_OF_X_H
