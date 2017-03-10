//
// Created by Mike Mitterer on 10.03.17.
//
// cmake-Template für config.h
//

#ifndef XCTEST_CONFIG_H_IN_H
#define XCTEST_CONFIG_H_IN_H

#include <string>

// the configured options and settings for HelloWorld
const std::string HelloWorld_VERSION_MAJOR = "1";
const std::string HelloWorld_VERSION_MINOR = "4";

// Password compiled into source
// Set in .config/passwords.cmake (or via ENV-VAR)
const std::string HelloWorld_PASSWORD = "<not set2>";

#endif //XCTEST_CONFIG_H_IN_H
