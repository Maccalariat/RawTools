# RawToolsLib
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

message("cmake - RawToolsLib")

project(RawToolsLib CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# LIBTIFF
add_library(RawToolsLib SHARED
        include/RawTools.hpp
        src/FileBuffer.cpp
        src/FileBuffer.hpp
        src/FileMetaData.cpp
        src/FileMetaData.hpp
        src/RawImage.cpp
        src/RawImage.hpp
        src/RawTools.cpp
        src/RawToolsImpl.hpp
        src/Sony.cpp
        src/Sony.hpp
        src/TiffFile.cpp
        src/TiffFile.hpp)
# target_link_libraries is fucking positional! it MUST be after add-library
target_link_libraries(RawToolsLib )

set_target_properties(RawToolsLib PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        LINKER_LANGUAGE CXX
        COMPILE_OPTIONS "-Wall" "-Wextra" "-Wconversion"
        )

install(TARGETS RawToolsLib
        EXPORT RawToolsLibConfig
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(DIRECTORY include/ DESTINATION include)

install(EXPORT RawToolsLibConfig
        DESTINATION share/RawToolsLib/cmake)

export(TARGETS RawToolsLib
        FILE RawToolsLibConfig.cmake)
