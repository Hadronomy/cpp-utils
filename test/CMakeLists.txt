project(${CMAKE_PROJECT_NAME})
enable_testing()

set(EXE_NAME ${PROJECT_SHORTNAME}_test)
add_executable(${EXE_NAME})

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cc")
target_sources(${EXE_NAME}
        PRIVATE ${SOURCES})

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

target_link_libraries(
        ${EXE_NAME}
        Hadronomy::toffee
        GTest::gtest_main
)

include(GoogleTest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
gtest_discover_tests(${EXE_NAME})
