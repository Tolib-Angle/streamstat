function(streamstat_set_project_options target_name)
    if (MSVC)
        target_compile_options(${target_name} PRIVATE
            /permissive-
            /Zc:__cplusplus
            /utf-8
            /EHsc
            /MP
        )
    endif()
endfunction()
