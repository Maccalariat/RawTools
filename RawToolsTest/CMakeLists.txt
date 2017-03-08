# RawToolsTest
cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

message(" cmake - RawToolsTest")

project(RawToolsTest CXX)

add_executable(RawToolsTest "")

target_sources(RawToolsTest
        PUBLIC
        RawToolsTest.cpp)

include_directories(${CMAKE_SOURCE_DIR}/RawToolsLib)

target_link_libraries(RawToolsTest RawToolsLib)

set_target_properties(RawToolsTest PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
  )


install(TARGETS RawToolsTest
        RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin
        )


