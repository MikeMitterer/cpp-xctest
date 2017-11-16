//
// Created by Mike Mitterer on 11.11.17.
//

#ifndef XCTEST_RULE_OF_X_H
#define XCTEST_RULE_OF_X_H

#include "stdafx.h"

////using
class Resource {
private:
    const std::string value { "<undefined>" };

    // Default-Init ist zu bevorzugen
    const std::shared_ptr<spdlog::logger> logger { spdlog::get(APP_LOGGER) };

public:
    static uint8_t instanceCounter;

public:
    Resource(const std::string& value);
    Resource() = delete;

    virtual ~Resource();

    
};

/**
 * Alle Operatoren können mit = delete gelöscht, oder mit = default in der default-Variante
 * erzeugt werden
 */
class AllDefaultOperators {
private:

    char *name;

public:
    /// Default Konstruktor
    AllDefaultOperators(const char* arg);

    /// Copy Construktor
    AllDefaultOperators(const AllDefaultOperators& _other);

    /// Zuweisungsoperator
    AllDefaultOperators& operator=(const AllDefaultOperators& _other);

    /// Move Konstruktor
    AllDefaultOperators(AllDefaultOperators&& _other);

    /// Move-Zuweisungsoperator
    AllDefaultOperators& operator=(AllDefaultOperators&& _other);

    /// Destruktor
    virtual ~AllDefaultOperators();

};

#endif //XCTEST_RULE_OF_X_H
