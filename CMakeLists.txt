﻿# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("AdventOfCode2021")

set (CMAKE_CXX_STANDARD 20)

# Include sub-projects.
add_subdirectory ("AdventOfCode2021")

add_subdirectory ("Day1")

add_subdirectory ("Day2")

add_subdirectory ("Day3")

add_subdirectory ("Day4")

add_subdirectory ("Day5")

add_subdirectory ("Day6")

add_subdirectory ("Day7")

add_subdirectory ("Day8")

add_subdirectory ("Day9")

add_subdirectory ("Day10")