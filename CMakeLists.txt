cmake_minimum_required(VERSION 3.11)
project(utils)
set(CMAKE_C_STANDARD 14)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cc")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/includes/utils
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)
add_library(utils ${SOURCES})

set_property(GLOBAL PROPERTY LINKER_LANGUAGE CXX)
