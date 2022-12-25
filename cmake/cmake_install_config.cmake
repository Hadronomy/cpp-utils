# DEBUG
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")
include(GNUInstallDirs)

# INSTALLATION
macro(configure_install_export _INSTALL_EXPORT_TARGET)

  if(NOT TARGET ${_INSTALL_EXPORT_TARGET})
    message(FATAL_ERROR "Tried to configure non-existant target \"${_INSTALL_EXPORT_TARGET}\"")
  endif()

  get_target_property(_IAE_PATH ${_INSTALL_EXPORT_TARGET} PUBLIC_HEADERS_DIR)

  if(NOT _IAE_PATH)
    message(FATAL_ERROR "Target \"${_INSTALL_EXPORT_TARGET}\" does not name a PUBLIC_HEADERS_DIR")
  endif()

  if(DEFINED CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
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

  file(GLOB_RECURSE PUBLIC_HEADERS "${_IAE_PATH}/*.h")
  message(STATUS "Found public headers:")
  foreach(HEADER ${PUBLIC_HEADERS})
    message(STATUS ${HEADER})
  endforeach()
  set_target_properties(${_INSTALL_EXPORT_TARGET} PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADERS}")

  install(TARGETS ${_INSTALL_EXPORT_TARGET}
    EXPORT "${_INSTALL_EXPORT_TARGET}-targets"
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

  install(EXPORT "${_INSTALL_EXPORT_TARGET}-targets"
    FILE "${_INSTALL_EXPORT_TARGET}-targets.cmake"
    NAMESPACE ${PROJECT_NAMESPACE}::
    DESTINATION cmake
  )

  include(CMakePackageConfigHelpers)

  set(PROJECT_VERSION "1.0.0")

  write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY AnyNewerVersion
  )

  set(CMAKE_CONFIG_DIR cmake)

  configure_package_config_file("${CMAKE_SOURCE_DIR}/${CMAKE_CONFIG_DIR}/config-template.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
    INSTALL_DESTINATION cmake
  )

  install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${_INSTALL_EXPORT_TARGET}-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${_INSTALL_EXPORT_TARGET}-config-version.cmake"
    DESTINATION cmake
  )

  export(EXPORT "${_INSTALL_EXPORT_TARGET}-targets"
    FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${_INSTALL_EXPORT_TARGET}-targets.cmake"
    NAMESPACE ${PROJECT_NAMESPACE}::
  )

  # uninstall target
  if(NOT TARGET uninstall)
    configure_file(
      "${CMAKE_SOURCE_DIR}/${CMAKE_CONFIG_DIR}/cmake_uninstall.cmake"
      "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
      IMMEDIATE @ONLY
    )

    add_custom_target(uninstall
      COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
    )
  endif()

endmacro()
