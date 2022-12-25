cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
set(PROJECT_NAMESPACE "Hadronomy")
project(toffee VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_SHORTNAME toffee)
set(PROJECT_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_MODULE_PATH}")
set(PROJECT_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Metadata
set(META_PROJECT_NAME toffee)
set(META_PROJECT_DESCRIPTION A lovely description)
set(META_PROJECT_VARNAME TOFFEE)
set(META_APP_NAME "Toffee")
set(META_APP_AUTHOR "Hadronomy")

add_subdirectory(src)
add_subdirectory(test)

# EXAMPLE PROJECT TARGET

option(BUILD_EXAMPLES "Whether or not to build the included examples" OFF)

if(BUILD_EXAMPLES)
	message(STATUS "Building project examples...")
	# add_subdirectory(example)
endif()
