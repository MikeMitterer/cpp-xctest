//
// Created by Mike Mitterer on 02.04.21.
//

#include "utils.h"

namespace mm::utils {
    bool isSpace(unsigned char c) {
        return (c == ' ' || c == '\n' || c == '\r' ||
                c == '\t' || c == '\v' || c == '\f');
    }

    std::string toLower(const std::string& value) {
        auto temp = value;

        std::transform(
                temp.begin(), temp.end(), temp.begin(),
                [](unsigned char c) {
                    return std::tolower(c);
                }
        );
        return temp;
    }

    std::string removeSpace(const std::string& value) {
        auto temp = value;

        temp.erase(std::remove_if(temp.begin(), temp.end(), isSpace), temp.end());
        return temp;
    }

}


