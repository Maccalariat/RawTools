# RawToolsLib
cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

	message ("cmake - RawToolsLib")

project(RawToolsLib CXX)

add_library(RawToolsLib SHARED
		include/RawTools/RawTools.h
		src/FileBuffer.cpp
		src/FileBuffer.h
		src/FileMetaData.cpp
		src/FileMetaData.h
		src/RawImage.cpp
		src/RawImage.h
		src/RawTools.cpp
		src/Sony.cpp
		src/Sony.h
		 src/_RawTools.h)

set_target_properties(RawToolsLib PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
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
