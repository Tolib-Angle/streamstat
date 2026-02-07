#include "streamstat/logging/logging.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace streamstat::logging {

    void init() {
        auto lg = spdlog::stdout_color_mt("streamstat");
        spdlog::set_default_logger(lg);
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
        spdlog::set_level(spdlog::level::info);
    }

} // namespace streamstat::logging
