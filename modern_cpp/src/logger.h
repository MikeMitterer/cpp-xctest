//
// Created by Mike Mitterer on 2019-02-08.
//

#ifndef XCTEST_LOGGER_H
#define XCTEST_LOGGER_H

#include "stdafx.h"

using Logger = std::shared_ptr<spdlog::logger>;
using LogLevel = spdlog::level::level_enum;

class DefaultLogger final {
public:
    static const LogLevel DEFAULT_LOG_LEVEL = spdlog::level::debug;
    static const std::string TEST_LOGGER;

public:
    static Logger get(const std::string& name) {
        if (spdlog::get(name) != nullptr) {
            return spdlog::get(name);
        }
        auto logger = spdlog::stdout_color_mt(name);
        logger->set_level(DEFAULT_LOG_LEVEL);

        return logger;
    }
};

#endif //XCTEST_LOGGER_H
