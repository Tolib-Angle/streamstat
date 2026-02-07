cmake_minimum_required(VERSION 3.23)

set(extra_args "")
set(i 0)

while(i LESS CMAKE_ARGC)
    if(CMAKE_ARGV${i} STREQUAL "--")
        math(EXPR i "${i}+1")
        break()
    endif()
    math(EXPR i "${i}+1")
endwhile()

while(i LESS CMAKE_ARGC)
    list(APPEND extra_args "${CMAKE_ARGV${i}}")
    math(EXPR i "${i}+1")
endwhile()

set(src_dir "${CMAKE_CURRENT_LIST_DIR}/..")
cmake_path(ABSOLUTE_PATH src_dir)

set(build_dir "${src_dir}/out/build/bootstrap")
file(MAKE_DIRECTORY "${build_dir}")

message(STATUS "src_dir:   ${src_dir}")
message(STATUS "build_dir: ${build_dir}")

execute_process(
    COMMAND "${CMAKE_COMMAND}" -S "${src_dir}" -B "${build_dir}" ${extra_args}
    RESULT_VARIABLE rc
)
if(NOT rc EQUAL 0)
    message(FATAL_ERROR "configure failed: ${rc}")
endif()

set(BOOTSTRAP_BUILD OFF CACHE BOOL "")
set(CONFIG "" CACHE STRING "")

if(BOOTSTRAP_BUILD)
    set(cmd "${CMAKE_COMMAND}" --build "${build_dir}")
    if(NOT CONFIG STREQUAL "")
        list(APPEND cmd --config "${CONFIG}")
    endif()

    execute_process(
        COMMAND ${cmd}
        RESULT_VARIABLE brc
    )
    if(NOT brc EQUAL 0)
        message(FATAL_ERROR "build failed: ${brc}")
    endif()
endif()
