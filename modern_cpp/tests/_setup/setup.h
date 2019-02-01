//
// Created by Mike Mitterer on 2019-02-01.
//

#ifndef XCTEST_SETUP_H
#define XCTEST_SETUP_H


#include <string>
#include <stdafx.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"

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

class TestSetup {
private:
    Logger logger = DefaultLogger::get(DefaultLogger::TEST_LOGGER);

public:
    explicit TestSetup(const LogLevel logLevel = DefaultLogger::DEFAULT_LOG_LEVEL) {
        logger->set_level(logLevel);
    }

    const Logger getLogger() const {
        return logger;
    }
};

#pragma clang diagnostic pop
#endif //XCTEST_SETUP_H
