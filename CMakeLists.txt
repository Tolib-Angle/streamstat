cmake_minimum_required(VERSION 3.23)

project(streamstat VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(streamstat
    src/app/main.cpp
)

target_compile_features(streamstat PRIVATE cxx_std_23)
