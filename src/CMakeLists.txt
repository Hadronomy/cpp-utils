project(${CMAKE_PROJECT_NAME})

add_library(${PROJECT_NAME} INTERFACE)
# Add namespaced alias
add_library(${PROJECT_NAMESPACE}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Add compiler definitions for the library
# string(TOUPPER "${PROJECT_NAME}_LIB" CAPS_PROJECT_NAME)
# target_compile_definitions(${PROJECT_NAME} PUBLIC ${CAPS_PROJECT_NAME})
if (DEFINED SOURCES)
  target_sources(
    ${PROJECT_NAME}
    PRIVATE
      ${SOURCES}
  )
endif()

target_include_directories(
  ${PROJECT_NAME}
  INTERFACE
      $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  PUBLIC_HEADERS_DIR "${CMAKE_SOURCE_DIR}/include"
)

include(cmake_install_config)

configure_install_export(${PROJECT_NAME})
