# DEBUG
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")

# INSTALLATION

if (DEFINED CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(
            STATUS
            "CMAKE_INSTALL_PREFIX is not set\n"
            "Default value: ${CMAKE_INSTALL_PREFIX}\n"
            "Will set it to /usr/local"
    )
    set(CMAKE_INSTALL_PREFIX
            "/usr/local"
            CACHE PATH "Where the library will be installed to" FORCE
            )
else()
    message(
            STATUS
            "CMAKE_INSTALL_PREFIX was already set\n"
            "Current value: ${CMAKE_INSTALL_PREFIX}"
    )
endif()

file(GLOB_RECURSE PUBLIC_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "include/*.h")
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
        NAMESPACE ${PROJECT_NAMESPACE}::
        DESTINATION cmake)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION "${version}"
        COMPATIBILITY AnyNewerVersion
)

set(CMAKE_CONFIG_DIR cmake)

configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_CONFIG_DIR}/Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION cmake)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION cmake)

export(EXPORT "${PROJECT_NAME}Targets"
        FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Targets.cmake"
        NAMESPACE ${PROJECT_NAMESPACE}::)

# uninstall target
if(NOT TARGET uninstall)
    configure_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_CONFIG_DIR}/cmake_uninstall.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
            IMMEDIATE @ONLY)

    add_custom_target(uninstall
            COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()