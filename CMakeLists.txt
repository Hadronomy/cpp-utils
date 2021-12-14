cmake_minimum_required(VERSION 3.11)
project(utils
	VERSION 1.0
	DESCRIPTION "A little usefull library for c++"
	LANGUAGES CXX)
set(CMAKE_C_STANDARD 14)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cc")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/includes/utils
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)
add_library(utils ${SOURCES})

