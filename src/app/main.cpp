#include "streamstat/cli/cli.hpp"
#include "streamstat/logging/logging.hpp"

#include <cstdlib>
#include <iostream>
#include <spdlog/spdlog.h>

int main(int argc, char** argv) {
    try {
        streamstat::logging::init();

        const auto a = streamstat::cli::parse(argc, argv);
        if (a.show_help) {
            std::cout
                << "streamstat\n"
                << "  streamstat -config <path>\n"
                << "  streamstat -cfg <path>\n"
                << "  streamstat -h\n";
            return EXIT_SUCCESS;
        }

        spdlog::info("config: {}", a.config_path);
        spdlog::info("done");
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
}
