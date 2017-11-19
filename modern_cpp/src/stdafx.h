//
// Created by Mike Mitterer on 19.05.17.
//

#ifndef XCTEST_STDAFX_H
#define XCTEST_STDAFX_H

#include <iostream>
#include <string>
#import <memory>

#include "spdlog/spdlog.h"
#include "config.h"

// https://stackoverflow.com/questions/8487986/file-macro-shows-full-path
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

namespace mm {
    const std::string APP_LOGGER = "moderncpp";
    const std::string TEST_LOGGER = "test_moderncpp";

    //const spdlog::level::level_enum DEFAULT_LOG_LEVEL = spdlog::level::info;
    const spdlog::level::level_enum DEFAULT_LOG_LEVEL = spdlog::level::debug;
}

#endif //XCTEST_STDAFX_H
