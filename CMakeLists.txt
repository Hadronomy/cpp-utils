cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
set(PROJECT_NAMESPACE "Hadronomy")
project(cpputils
	VERSION 0.1.0
	DESCRIPTION "A little usefull library for c++"
	LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_SHORTNAME utils)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_BINARY_DIR}")

# Metadata
set(META_PROJECT_NAME c++utils)
set(META_PROJECT_DESCRIPTION A lovely description)
set(META_PROJECT_VARNAME CPP_UTILS)
set(META_APP_NAME  "C++ Utils")
set(META_APP_AUTHOR "Hadronomy")

# Conan
include(conan_paths)

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
	message(STATUS "Top level project detected")
endif()

add_subdirectory(src)
enable_testing()
add_subdirectory(tests)

# EXAMPLE PROJECT TARGET

option(BUILD_EXAMPLES "Whether or not to build the included examples" ON)

if(BUILD_EXAMPLES)
	message(STATUS "Building project examples...")
	add_subdirectory(example)
endif()

# INSTALL CONFIG
include(cmake_install_config)

configure_install(PROJECT ${PROJECT_NAME})
