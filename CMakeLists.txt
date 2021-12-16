cmake_minimum_required(VERSION 3.11)
project(utils
	VERSION 1.0
	DESCRIPTION "A little usefull library for c++"
	LANGUAGES CXX)
set(CMAKE_C_STANDARD 17)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cc")

add_library(utils ${SOURCES})

target_include_directories(
	utils
	PUBLIC includes/utils
	PRIVATE includes src
)

include_directories(
	includes
	includes/utils
	src
)
