#pragma once

//
// Created by Mike Mitterer on 02.04.21.
//

#include "utils.h"
#include "ToJson.h"

#include <sstream>
#include <utility>

/**
 * Das zweite typename schränkt den Typ ein auf alle Klassen die von ToJson
 * abgeleitet wurden
 */
template<typename T, typename std::enable_if<std::is_base_of<ToJson, T>::value>::type* = nullptr>
class JsonEvent : ToJson {
public:
    std::string event;
    T data;

public:
    JsonEvent(const std::string& _event, T _data)
        : event{mm::utils::toLower((_event))}, data{_data} {}

    [[nodiscard]] std::string toJson() const override {
        std::stringstream out;

        out << "{" << "\n "
            "\"event\": " << "\"" << event << "\"" << "," << "\n "
            "\"data\": " << data.toJson() << "\n "
            "}" << "\n ";

        return out.str();
    }
};

template<typename T>
class StaticTemplateSample {
public:
    std::string name;
    T value;

    // Initialisierung erfolgt in template_test.cpp - ganz oben
    static uint8_t instanceCounter;

    StaticTemplateSample(std::string name, T value) : name(std::move(name)), value(value) {
        instanceCounter++;
    }

    virtual ~StaticTemplateSample() {
        instanceCounter--;
    }
};

/**
 * Kein Template!!!!!
 */
class StaticSample {
public:
    std::string name;
    int value;

    // Initialisierung erfolgt in template_test.cpp - ganz oben
    static uint8_t instanceCounter;

    StaticSample(std::string name, int value) : name(std::move(name)), value(value) {
        instanceCounter++;
    }

    virtual ~StaticSample() {
        instanceCounter--;
    }
};

class SimpleClass {
public:
    template<typename T>
    std::string convToString(T value) { return std::to_string(value); }

    std::string sayMyName() { return "Sarah"; }
};
