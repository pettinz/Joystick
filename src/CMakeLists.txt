cmake_minimum_required(VERSION 3.5)

if(APPLE)
    find_library(IOKIT_LIB IOKit)
    mark_as_advanced(IOKIT_LIB)

    find_library(FOUNDATION_LIB Foundation)
    mark_as_advanced(FOUNDATION_LIB)

    find_library(APPKIT_LIB AppKit)
    mark_as_advanced(APPKIT_LIB)
endif()


set(HEADERS
    "${Joystick_SOURCE_DIR}/include/joystick/element.hpp"
    "${Joystick_SOURCE_DIR}/include/joystick/axis.hpp"
    "${Joystick_SOURCE_DIR}/include/joystick/button.hpp"
    "${Joystick_SOURCE_DIR}/include/joystick/callback.hpp"
    "${Joystick_SOURCE_DIR}/include/joystick/exception.hpp"
    "${Joystick_SOURCE_DIR}/include/Joystick.hpp")
set (SOURCES "")
if (APPLE)
    list(APPEND SOURCES
        "${Joystick_SOURCE_DIR}/src/macos/Joystick.cpp")
endif()

add_library(joystick ${SOURCES} ${HEADERS})
add_library(Joystick::Joystick ALIAS joystick)
target_include_directories(joystick PUBLIC "${Joystick_SOURCE_DIR}/include")

if (APPLE)
    target_link_libraries(joystick ${IOKIT_LIB} ${FOUNDATION_LIB} ${APPKIT_LIB})
endif()

target_compile_features(joystick PUBLIC cxx_std_11)