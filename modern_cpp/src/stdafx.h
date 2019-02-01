//
// Created by Mike Mitterer on 19.05.17.
//

#ifndef XCTEST_STDAFX_H
#define XCTEST_STDAFX_H

#include <iostream>
#include <string>
#include <memory>

#include "spdlog/spdlog.h"
#include <spdlog/common.h>
#include <spdlog/logger.h>

#include "config.h"

// https://stackoverflow.com/questions/8487986/file-macro-shows-full-path
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

//namespace mm {
//    extern static const std::string TEST_LOGGER;
//    extern const std::string APP_LOGGER;
//
//    // extern const spdlog::level::level_enum DEFAULT_LOG_LEVEL;
//}

#endif //XCTEST_STDAFX_H


