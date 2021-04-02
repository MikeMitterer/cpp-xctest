#pragma once

//
// Created by Mike Mitterer on 02.04.21.
//

#import "ToJson.h"
#include <sstream>

class NameEvent : public ToJson {
private:
    const std::string name;

    // uint8_t - macht Probleme bei der Konvertierung von int zu uint8_t...
    uint16_t age = 0;

public:
    NameEvent(std::string _name, uint16_t _age) : name{std::move(_name)}, age{_age} { }

    std::string toJson() const override {
        std::stringstream out;

        out << "{ " <<
            "\"name\": " << "\"" << name << "\", " <<
            "\"age\": " << static_cast<uint16_t>(this->age) <<
            " }";

        return out.str();
    }
};
