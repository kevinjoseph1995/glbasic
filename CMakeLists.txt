cmake_minimum_required(VERSION 3.17)

project(gl_basic)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
if (CCACHE_FOUND)
    message(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif (CCACHE_FOUND)

find_program(CCACHE_FOUND ccache)


add_subdirectory(apps)
add_subdirectory(glbasic)
add_subdirectory(thirdparty)
