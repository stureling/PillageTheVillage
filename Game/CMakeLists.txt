cmake_minimum_required(VERSION 3.10)
project(VillagePillage)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g")

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

add_executable(VillagePillage
    main.cc)

target_link_libraries(VillagePillage ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
