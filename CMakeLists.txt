cmake_minimum_required(VERSION 3.11)
set(namespace "utils")
project(utils
	VERSION 0.1.0
	DESCRIPTION "A little usefull library for c++"
	LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
	message(STATUS "Top level project detected")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cc")
message(STATUS "Found sources: ${SOURCES}")

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
	PRIVATE
		${SOURCES}
)

target_include_directories(
	${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		# $<BUILD_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# DEBUG

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")

# INSTALLATION

if (DEFINED CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	message(
			STATUS
			"CMAKE_INSTALL_PREFIX is not set\n"
			"Default value: ${CMAKE_INSTALL_PREFIX}\n"
			"Will set it to ${CMAKE_SOURCE_DIR}/install"
	)
	set(CMAKE_INSTALL_PREFIX
		"${CMAKE_SOURCE_DIR}/install"
		CACHE PATH "Where the library will be installed to" FORCE
	)
else()
	message(
			STATUS
			"CMAKE_INSTALL_PREFIX was already set\n"
			"Current value: ${CMAKE_INSTALL_PREFIX}"
	)
endif()

file(GLOB_RECURSE PUBLIC_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "include/*.h")
message(STATUS "Found public headers: ${PUBLIC_HEADERS}")

# set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADERS}")

include(GNUInstallDirs)

foreach(header ${PUBLIC_HEADERS})
	file(REAL_PATH ${header} absolute_header_path)
	file(RELATIVE_PATH header_path "${CMAKE_CURRENT_SOURCE_DIR}/include" "${absolute_header_path}")
	get_filename_component(header_directory_path "${header_path}" DIRECTORY)
	install(
			FILES ${header}
			DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${header_directory_path}"
	)
endforeach()

install(TARGETS ${PROJECT_NAME}
	EXPORT "${PROJECT_NAME}Targets"
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT "${PROJECT_NAME}Targets"
		FILE "${PROJECT_NAME}Targets.cmake"
		NAMESPACE ${namespace}::
		DESTINATION .cmake)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
		VERSION "${version}"
		COMPATIBILITY AnyNewerVersion
)

set(CMAKE_CONFIG_DIR .cmake)

configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_CONFIG_DIR}/Config.cmake.in"
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
		INSTALL_DESTINATION cmake)

install(FILES
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
		DESTINATION cmake)

export(EXPORT "${PROJECT_NAME}Targets"
		FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Targets.cmake"
		NAMESPACE ${namespace}::)