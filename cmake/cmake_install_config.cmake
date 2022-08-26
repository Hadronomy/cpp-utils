
FUNCTION(configure_install)
    set(prefix INS)
    set(flags " ")
    set(singleValues PROJECT)
    set(multiValues DEPENDS)

    include(CMakeParseArguments)
    cmake_parse_arguments(${prefix} ${flags} ${singleValues} ${multiValues} ${ARGN})
    # DEBUG
    set_target_properties(${INS_PROJECT} PROPERTIES DEBUG_POSTFIX "d")

    # INSTALLATION

    file(GLOB_RECURSE PUBLIC_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "include/*.h")
    message(STATUS "Found public headers: ${PUBLIC_HEADERS}")

    # set_target_properties(${INS_PROJECT} PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADERS}")

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

    install(TARGETS ${INS_PROJECT} ${INS_DEPENDS}
            EXPORT "${INS_PROJECT}Targets"
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${INS_PROJECT}
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            )

    install(EXPORT "${INS_PROJECT}Targets"
            FILE "${INS_PROJECT}Targets.cmake"
            NAMESPACE ${PROJECT_NAMESPACE}::
            DESTINATION cmake)

    include(CMakePackageConfigHelpers)

    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/${INS_PROJECT}ConfigVersion.cmake"
            VERSION "${version}"
            COMPATIBILITY AnyNewerVersion
    )

    set(CMAKE_CONFIG_DIR cmake)

    configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_CONFIG_DIR}/Config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/${INS_PROJECT}Config.cmake"
            INSTALL_DESTINATION cmake)

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/${INS_PROJECT}Config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/${INS_PROJECT}ConfigVersion.cmake"
            DESTINATION cmake)

    export(EXPORT "${INS_PROJECT}Targets"
            FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${INS_PROJECT}Targºets.cmake"
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

ENDFUNCTION()