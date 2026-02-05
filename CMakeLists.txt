cmake_minimum_required(VERSION 3.23)

project(streamstat VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(ProjectOptions)
include(Sanitizers)

option(STREAMSTAT_WARNINGS_AS_ERRORS "Treat warnings as errors" ON)

add_executable(streamstat
    src/app/main.cpp
)

target_compile_features(streamstat PRIVATE cxx_std_23)

streamstat_set_project_options(streamstat)

if (NOT STREAMSTAT_WARNINGS_AS_ERRORS)
    if (MSVC)
        target_compile_options(streamstat PRIVATE /WX-)
    else()
        target_compile_options(streamstat PRIVATE -Wno-error)
    endif()
endif()

streamstat_enable_sanitizers(streamstat)
