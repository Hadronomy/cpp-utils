cmake_minimum_required(VERSION 3.11)
project(example
        VERSION 1.0.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cc")
add_executable(${PROJECT_NAME} ${SOURCES})

# Debug mode defines
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

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
find_package(OpenGL REQUIRED)
find_package(glfw NAMES glfw glfw3 REQUIRED)
add_subdirectory(thirdparty/imgui)

target_link_libraries(${PROJECT_NAME} Hadronomy::cpputils imgui::imgui glfw OpenGL::GL)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/data
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data)