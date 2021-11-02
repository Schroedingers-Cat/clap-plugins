cmake_minimum_required(VERSION 3.17)
cmake_policy(SET CMP0100 NEW)  # handle .hh files
if (WIN32)
    set(CMAKE_TOOLCHAIN_FILE "./vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

project(CLAP_PLUGINS C CXX)

add_subdirectory(clap)
add_subdirectory(clap-helpers)
add_subdirectory(plugins)
