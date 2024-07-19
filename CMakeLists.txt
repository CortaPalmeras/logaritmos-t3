
cmake_minimum_required(VERSION 3.20)

project(logs_t3
    DESCRIPTION "Tarea 3 de Diseño y Análisis de Algoritmos"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_BUILD_TYPE Release)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" 
    OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(
        "-Wall"
        "-Wextra"
        "-Wpedantic"
    )
endif()

add_executable(
    experimentacion1
    experimentacion1.cpp
    tarea.cpp
)

add_executable(
    experimentacion2
    experimentacion2.cpp
    tarea.cpp
)

