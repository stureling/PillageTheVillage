cmake_minimum_required(VERSION 2.8)
project(TheVillagePillager)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

if (DEFINED ENV{LOADEDMODULES} AND ("$ENV{LOADEDMODULES}" MATCHES ".*prog/gcc/6.1.0.*"))
    set(CMAKE_CXX_COMPILER /sw/gcc-6.1.0/bin/g++)
    if (DEFINED ENV{SFML_ROOT})
        list(APPEND CMAKE_MODULE_PATH "$ENV{SFML_ROOT}/share/SFML/cmake/Modules")
    endif()
endif()

if (DEFINED ENV{LOADEDMODULES} AND ("$ENV{LOADEDMODULES}" MATCHES ".*prog/gcc/7.1.0.*"))
    set(CMAKE_CXX_COMPILER /sw/gcc-7.1.0/bin/g++)

    if (DEFINED ENV{SFML_ROOT})
        list(APPEND CMAKE_MODULE_PATH "$ENV{SFML_ROOT}/share/SFML/cmake/Modules")
    endif()
endif()


set(SFML_MODULES graphics window system)
find_package(SFML 2 COMPONENTS ${SFML_MODULES})
include_directories(${SFML_INCLUDE_DIR})

if (NOT (${SFML_FOUND} STREQUAL "TRUE"))
    set(SFML_LIBRARIES "")
    foreach(i ${SFML_MODULES})
        list(APPEND SFML_LIBRARIES "sfml-${i}")
    endforeach(i)
endif()

set(SOURCE_FILES main.cc
    entities.cc
    entities.h
    state.cc
    state.h)
add_executable(VillagePillage ${SOURCE_FILES})

target_link_libraries(VillagePillage ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
