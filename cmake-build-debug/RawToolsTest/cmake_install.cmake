# Install script for directory: E:/projects/CPP/RawTools/RawToolsTest

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Project")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "E:/projects/CPP/RawTools/cmake-build-debug/RawToolsTest/Debug/bin/RawToolsTest.exe")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "E:/projects/CPP/RawTools/cmake-build-debug/RawToolsTest/Debug/bin" TYPE EXECUTABLE FILES "E:/projects/CPP/RawTools/cmake-build-debug/RawToolsTest/RawToolsTest.exe")
  if(EXISTS "$ENV{DESTDIR}/E:/projects/CPP/RawTools/cmake-build-debug/RawToolsTest/Debug/bin/RawToolsTest.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/E:/projects/CPP/RawTools/cmake-build-debug/RawToolsTest/Debug/bin/RawToolsTest.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "D:/TDM-GCC-64/bin/strip.exe" "$ENV{DESTDIR}/E:/projects/CPP/RawTools/cmake-build-debug/RawToolsTest/Debug/bin/RawToolsTest.exe")
    endif()
  endif()
endif()

