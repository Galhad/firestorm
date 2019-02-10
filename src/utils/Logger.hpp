


#ifndef FIRESTORM_LOGGER_HPP
#define FIRESTORM_LOGGER_HPP

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>

namespace fs::utils
{
using Logger = spdlog::logger;
using LoggerPtr = std::shared_ptr<spdlog::logger>;

constexpr const char* CONSOLE_LOGGER_NAME = "console";
}

#endif //FIRESTORM_LOGGER_HPP
