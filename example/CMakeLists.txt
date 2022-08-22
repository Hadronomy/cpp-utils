cmake_minimum_required(VERSION 3.11)
project(example
        VERSION 1.0.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_executable(${PROJECT_NAME} main.cc)

# When using this library in an external project, you should first install it or
# fetch it by using the following CMake project
#
# include(FetchContent)
#
# FetchContent_Declare(
#         utils
#         GIT_REPOSITORY https://github.com/hadronomy/cpp-utils.git
# )
#
# FetchContent_MakeAvailable(utils)

target_link_libraries(${PROJECT_NAME} utils)