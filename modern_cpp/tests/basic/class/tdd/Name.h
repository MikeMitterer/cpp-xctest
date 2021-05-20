#pragma once

//
// Created by Mike Mitterer on 20.05.21.
//

class Name {
private:
    uint8_t age { 99 };

public:
    static std::string lastname;

    std::string firstname { "Mike" };

    Name(std::string firstname) : firstname(std::move(firstname)) {}

    // By reference ist notwendig da sonst an dieser Stelle wieder der Copy-CTOR aufgerufen
    // würde
    Name(const Name& name)
            : age{ name.age }, firstname{ name.firstname } {
    }

    uint8_t getAge() const {
        return age;
    }

    std::string getNameWithBrackets() {
        return "[ " + firstname + " ]";
    }

    static std::string getLastName() {
        return lastname;
    };
};



