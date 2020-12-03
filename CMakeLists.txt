cmake_minimum_required(VERSION 3.14...3.18)
project(
    Joystick
    VERSION 1.0
    DESCRIPTION "Cross-platform Joystick library"
    LANGUAGES CXX
)

include(FetchContent)

add_subdirectory(src)