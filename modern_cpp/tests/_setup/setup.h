//
// Created by Mike Mitterer on 2019-02-01.
//

#ifndef XCTEST_SETUP_H
#define XCTEST_SETUP_H


#include <string>
#include <stdafx.h>

#include "logger.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"

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
