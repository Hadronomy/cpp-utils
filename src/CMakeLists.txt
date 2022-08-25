project(${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cc")
message(STATUS "Found sources: ${SOURCES}")

add_library(${PROJECT_NAME} STATIC)
# Add namespaced alias
add_library(${PROJECT_NAMESPACE}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Add compiler definitions for the library
string(TOUPPER "${PROJECT_NAME}_LIB" CAPS_PROJECT_NAME)
target_compile_definitions(${PROJECT_NAME} PUBLIC ${CAPS_PROJECT_NAME})

target_sources(${PROJECT_NAME}
        PRIVATE
            ${SOURCES}
        )

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
            # $<BUILD_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)