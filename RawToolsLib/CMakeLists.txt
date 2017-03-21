# RawToolsLib
cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

message ("cmake - RawToolsLib")

project(RawToolsLib CXX)
include_directories(${CMAKE_CURRENT_SOURCE_DIR/include})

add_library(RawToolsLib SHARED
		include/RawTools.hpp
		src/FileBuffer.cpp
		src/FileBuffer.hpp
		src/FileMetaData.cpp
		src/FileMetaData.hpp
		src/ProcessBlock.hpp
		src/ProcessBlock.cpp
		src/RawImage.cpp
		src/RawImage.hpp
		src/RawToolsImpl.hpp
		src/RawTools.cpp
		src/Sony.cpp
		src/Sony.hpp
)

set_target_properties(RawToolsLib PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
  LINKER_LANGUAGE CXX
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
