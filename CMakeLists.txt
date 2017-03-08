# Root of the project
cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
message("cmake - Root Build")

add_subdirectory(RawToolsTest)
add_subdirectory(RawToolsLib)

# clean command
add_custom_target(clean-all
   COMMAND ${CMAKE_BUILD_TOOL} clean
   COMMAND ${CMAKE_COMMAND} -P clean-all.cmake
)
