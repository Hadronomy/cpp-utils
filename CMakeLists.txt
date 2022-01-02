cmake_minimum_required(VERSION 3.11)
project(utils
	VERSION 1.0
	DESCRIPTION "A little usefull library for c++"
	LANGUAGES CXX)
set(CMAKE_C_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cc")

add_library(libutils ${SOURCES})

target_include_directories(
	libutils
	PUBLIC includes
	PRIVATE src includes/utils
)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR}})
  add_executable(runTests test/main.cc ${SOURCES})
endif()

include_directories(
	includes
	includes/utils
	src
)
