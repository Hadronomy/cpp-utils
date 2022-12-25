cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
set(PROJECT_NAMESPACE "Hadronomy")
project(
	toffee
	VERSION 1.0.0
	DESCRIPTION "A little usefull library for c++"
	LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_SHORTNAME toffee)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(PROJECT_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Metadata
set(META_PROJECT_NAME toffee)
set(META_PROJECT_DESCRIPTION A lovely description)
set(META_PROJECT_VARNAME CPP_UTILS)
set(META_APP_NAME "Toffee")
set(META_APP_AUTHOR "Hadronomy")

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
	message(STATUS "Top level project detected")
endif()

add_subdirectory(src)
# enable_testing()
add_subdirectory(test)

# EXAMPLE PROJECT TARGET

option(BUILD_EXAMPLES "Whether or not to build the included examples" ON)

if(BUILD_EXAMPLES)
	message(STATUS "Building project examples...")
	# add_subdirectory(example)
endif()

# INSTALL CONFIG
include(cmake_install_config)
