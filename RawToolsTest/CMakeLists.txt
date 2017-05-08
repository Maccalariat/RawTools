# RawToolsTest
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

message("cmake - RawToolsTest")

project(RawToolsTest CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(RawToolsTest "")

target_sources(RawToolsTest
        PUBLIC
        RawToolsTest.cpp)

target_include_directories(RawToolsTest INTERFACE ${CMAKE_SOURCE_DIR}/RawToolsLib/include)
include_directories(${CMAKE_SOURCE_DIR}/libRawToolsLib)

target_link_libraries(RawToolsTest RawToolsLib)

set_target_properties(RawToolsTest PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        COMPILE_OPTIONS "-Wall" "-Wextra" "-Wconversion"
        )


install(TARGETS RawToolsTest
        RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin
        )


