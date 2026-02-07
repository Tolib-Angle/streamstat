#include "streamstat/cli/cli.hpp"

#include <CLI/CLI.hpp>

#include <cstring>
#include <string>
#include <vector>

namespace streamstat::cli {

    static std::vector<std::string> normalize_args(int argc, char** argv) {
        std::vector<std::string> out;
        out.reserve(static_cast<size_t>(argc));

        for (int i = 0; i < argc; ++i) {
            std::string s = (argv[i] != nullptr) ? std::string(argv[i]) : std::string{};

            if (s == "-config") {
                s = "--config";
            }
            else if (s == "-cfg") {
                s = "--cfg";
            }

            out.push_back(std::move(s));
        }

        return out;
    }

    args parse(int argc, char** argv) {
        args out{};
        out.config_path = "config.toml";

        CLI::App app{ "streamstat" };
        app.allow_extras(false);

        std::string c1;
        std::string c2;

        app.add_option("--config", c1, "path to config.toml");
        app.add_option("--cfg", c2, "alias for --config");

        const auto norm = normalize_args(argc, argv);

        std::vector<char*> argv2;
        argv2.reserve(norm.size());
        for (const auto& s : norm) {
            argv2.push_back(const_cast<char*>(s.c_str()));
        }

        try {
            app.parse(static_cast<int>(argv2.size()), argv2.data());
        }
        catch (const CLI::CallForHelp&) {
            out.show_help = true;
            return out;
        }
        catch (const CLI::ParseError&) {
            throw;
        }

        if (!c1.empty()) {
            out.config_path = c1;
        }
        else if (!c2.empty()) {
            out.config_path = c2;
        }

        return out;
    }

} // namespace streamstat::cli
