cmake_minimum_required(VERSION 3.0)

# set version
set(MAIN_PROJ_MAJOR_VERSION 1)
set(MAIN_PROJ_MINOR_VERSION 0)
set(MAIN_PROJ_PATCH_VERSION 0)
set(MAIN_PROJ_VERSION
    ${MAIN_PROJ_MAJOR_VERSION}.${MAIN_PROJ_MINOR_VERSION}.${MAIN_PROJ_PATCH_VERSION}
)
# set project name
project(
  TestGoogleTest
  VERSION ${MAIN_PROJ_VERSION}
  LANGUAGES CXX)

# ##############################################################################
# policys

# CMP0074: find_package uses PackageName_ROOT variables.
if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

# ##############################################################################
# Conan:
# ##############################################################################
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup(TARGETS)
elseif(EXISTS ${PROJECT_SOURCE_DIR}/conan/conanbuildinfo.cmake)
  include(${PROJECT_SOURCE_DIR}/conan/conanbuildinfo.cmake)
  conan_basic_setup(TARGETS)
elseif()
  message(FATAL "CONAN targets NOT FOUND!")
endif()

# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# silent some warnings
add_definitions(
  -DHAVE_CURL -DBOOST_ALL_NO_LIB -DBOOST_BIND_GLOBAL_PLACEHOLDERS
  -D_USING_INSTANCE_OVERRIDE -D_SCL_SECURE_NO_WARNINGS
  -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
if(WIN32)
  message(STATUS "Using unicode")
  add_definitions(-D_WIN32_WINNT=0x0601 -D_CRT_SECURE_NO_WARNINGS)
endif()

# find gtest packages
find_package(GTest REQUIRED)
find_package(GMock REQUIRED)

# need to set this if we want to find the latest boost libraries (current
# v1.72)!
set(Boost_USE_STATIC_LIBS ON)
# find boost
find_package(Boost 1.60 COMPONENTS system filesystem regex REQUIRED)

# add directories
add_subdirectory(src)
