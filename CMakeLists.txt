cmake_minimum_required(VERSION 3.23)

project(streamstat VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release)

option(STREAMSTAT_WARNINGS_AS_ERRORS "Treat warnings as errors" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(project_options)
include(compiler_warnings)
include(sanitizers)

include(FetchContent)

set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/third_party/_fc" CACHE PATH "")
set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "")

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.14.1
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
    cli11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.4.2
)
FetchContent_MakeAvailable(cli11)

add_library(streamstat_lib
    src/lib/streamstat/cli/cli.cpp
    src/lib/streamstat/logging/logging.cpp
)

target_include_directories(streamstat_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lib
)

target_link_libraries(streamstat_lib PUBLIC
    spdlog::spdlog
    CLI11::CLI11
)

# Mark third-party headers as SYSTEM to avoid /WX failures on vendor code
get_target_property(_cli11_includes CLI11::CLI11 INTERFACE_INCLUDE_DIRECTORIES)
if(_cli11_includes)
    target_include_directories(streamstat_lib SYSTEM PRIVATE ${_cli11_includes})
endif()

get_target_property(_spdlog_includes spdlog::spdlog INTERFACE_INCLUDE_DIRECTORIES)
if(_spdlog_includes)
    target_include_directories(streamstat_lib SYSTEM PRIVATE ${_spdlog_includes})
endif()

streamstat_set_project_options(streamstat_lib)
streamstat_set_warnings(streamstat_lib)
streamstat_enable_sanitizers(streamstat_lib)

add_executable(streamstat
    src/app/main.cpp
)

target_link_libraries(streamstat PRIVATE streamstat_lib)

streamstat_set_project_options(streamstat)
streamstat_set_warnings(streamstat)
streamstat_enable_sanitizers(streamstat)
