# RawToolsLib
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

message("cmake - RawToolsLib")

project(RawToolsLib CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# LIBTIFF
link_directories("${MY_BUILDS_PATH}/lib")
include_directories("${MY_BUILDS_PATH}/include")
find_library(TIFFLIB libtiff.a
        HINTS "${MY_BUILDS_PATH}/lib")
find_library(JPEGLIB libjpeg.a
        HINTS "${MY_BUILDS_PATH}/lib")
find_library(LIBZLIB libzlibstatic.a
        HINTS "${MY_BUILDS_PATH}/lib")
find_library(LIBLZMA liblzma.a
        HINTS "${MY_BUILDS_PATH}/lib")

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
target_link_libraries(RawToolsLib ${TIFFLIB} ${JPEGLIB} ${LIBZLIB} ${LIBLZMA})

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
