cmake_minimum_required(VERSION 3.11)
set(namespace "Hadronomy")
project(utils
	VERSION 0.1.0
	DESCRIPTION "A little usefull library for c++"
	LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
	message(STATUS "Top level project detected")
endif()

set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_subdirectory(src)

# EXAMPLE PROJECT TARGET

option(BUILD_EXAMPLES "Whether or not to build the included examples" ON)

if(BUILD_EXAMPLES)
	message(STATUS "Building project examples...")
	add_subdirectory(example)
endif()

# INSTALL CONFIG
include(cmake_install_config)