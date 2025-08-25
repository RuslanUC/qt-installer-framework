include_guard(GLOBAL)

option(IFW_ENABLE_LTO "Enable link-time optimization" ON)

if(IFW_ENABLE_LTO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT LTO_SUPPORTED OUTPUT error)

    if(LTO_SUPPORTED)
        function(target_enable_lto target)
            set_property(TARGET ${target} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
        endfunction()
        message(STATUS "LTO enabled")
    else()
        function(target_enable_lto target)
        endfunction()
        message(STATUS "LTO not supported: <${error}>")
    endif()
endif()