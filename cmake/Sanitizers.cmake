option(STREAMSTAT_ENABLE_ASAN "Enable AddressSanitizer (Clang/GCC)" OFF)
option(STREAMSTAT_ENABLE_UBSAN "Enable UndefinedBehaviorSanitizer (Clang/GCC)" OFF)

function(streamstat_enable_sanitizers target_name)
    if (MSVC)
        return()
    endif()

    if (STREAMSTAT_ENABLE_ASAN)
        target_compile_options(${target_name} PRIVATE -fsanitize=address)
        target_link_options(${target_name} PRIVATE -fsanitize=address)
    endif()

    if (STREAMSTAT_ENABLE_UBSAN)
        target_compile_options(${target_name} PRIVATE -fsanitize=undefined)
        target_link_options(${target_name} PRIVATE -fsanitize=undefined)
    endif()
endfunction()
