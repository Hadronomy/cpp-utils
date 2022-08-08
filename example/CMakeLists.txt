cmake_minimum_required(VERSION 3.11)
project(external
        VERSION 1.0.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_executable(${PROJECT_NAME} main.cc)

include(FetchContent)

FetchContent_Declare(
        utils
        GIT_REPOSITORY https://github.com/hadronomy/cpp-utils.git
)

FetchContent_MakeAvailable(utils)
# find_package(utils CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} utils)