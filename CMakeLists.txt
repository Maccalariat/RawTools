# Root of the project
cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
message("cmake - Root Build")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(RawToolsLib)
add_subdirectory(RawToolsTest)
