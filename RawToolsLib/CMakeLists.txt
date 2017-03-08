# RawToolsLib
cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

message (" cmake - RawToolsLib")

project(RawToolsLib CXX)

add_library(RawToolsLib
        FileBuffer.cpp
        FileBuffer.h
        FileMetaData.cpp
        FileMetaData.h
        ProcessBlock.cpp
        ProcessBlock.h
        RawImage.cpp
        RawImage.h
        RawTools.cpp
        RawTools.h
        Sony.cpp
        Sony.h)

set_target_properties(RawToolsLib PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
  )

install(TARGETS RawToolsLib 
		ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
install (FILES RawTools.h DESTINATION ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/include)
install (FILES RawToolsLib-config.cmake DESTINATION ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)

add_custom_target(install_${PROJECT_NAME}
        $(MAKE) install
        DEPENDS(${PROJECT_NAME})
        COMMENT "Installing ${PROJECT_NAME}")
