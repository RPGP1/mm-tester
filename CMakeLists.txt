cmake_minimum_required(VERSION 3.0)


# flags for executable file
add_compile_options(
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Debug>:-Og\ -g>
    $<$<CONFIG:RelWithDebgInfo>:-O3\ -g>
    )
# flags for compile errors
add_compile_options(
    "-ftemplate-backtrace-limit=0"
    "-fmax-errors=10"
    )
# flags for warnings
set(WARNING_FLAGS
    all
    extra
    conversion
    switch-default
    disabled-optimization
    format
    init-self
    overloaded-virtual
    float-equal
    old-style-cast
    return-type
    )
foreach(FLAG IN LISTS WARNING_FLAGS)
    add_compile_options(
        -W${FLAG}
        )
endforeach()


add_subdirectory(mm-problem)


project(MM_TESTER CXX)

add_library(cmdline INTERFACE)
target_include_directories(cmdline SYSTEM INTERFACE
    "cmdline")


file(GLOB_RECURSE MM_TESTER_SOURCES
    "src/*.cpp")
add_library(mm_tester INTERFACE)
target_sources(mm_tester INTERFACE
    "${MM_TESTER_SOURCES}")
target_include_directories(mm_tester INTERFACE
    "include")
target_link_libraries(mm_tester INTERFACE
    mm_problem cmdline)
