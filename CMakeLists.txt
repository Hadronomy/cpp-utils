cmake_minimum_required(VERSION 2.8.11)
project(utils)
set(CMAKE_C_STANDARD 14)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cc")
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/includes/utils
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)
add_library(utils ${SOURCES})

set_target_properties(utils PROPERTIES LINKER_LANGUAGE CXX)