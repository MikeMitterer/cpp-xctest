#pragma once

//
// Created by Mike Mitterer on 01.04.21.
//

#include <sstream>
#include <iomanip>

/**
 * Normales Function-Template
 */
template<typename T>
std::string toString(const T& value) {
    std::stringstream ss;

    ss << value;
    return ss.str();
}

/**
 * Specialization - hier auf double
 */
template<>
std::string toString(const double& value) {
    std::stringstream ss;

    ss << std::fixed << std::setprecision(2) << value;
    return ss.str();
}

/**
 * Specialization - und auf float
 */
template<>
std::string toString(const float & value) {
    std::stringstream ss;

    ss << std::fixed << std::setprecision(2) << value << "f";
    return ss.str();
}
