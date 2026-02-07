#pragma once

#include <string>

namespace streamstat::cli {

    struct args {
        std::string config_path;
        bool show_help = false;
    };

    args parse(int argc, char** argv);

} // namespace streamstat::cli
