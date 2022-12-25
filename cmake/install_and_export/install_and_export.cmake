# install_and_export - version 2.0.0
# Author: sum01 <sum01@protonmail.com>
# Git: https://github.com/sum01/install_and_export
# Read the README.md for full info!

# Defines standardized defaults for install paths
include(GNUInstallDirs)

macro(install_and_export _INSTALL_EXPORT_TARGET)
	# Safety check the passed target
	IF(NOT TARGET ${_INSTALL_EXPORT_TARGET})
		message(FATAL_ERROR "You can't use the install_and_export macro on the non-existant target \"${_INSTALL_EXPORT_TARGET}\"")
	ENDIF()

	# Allow for leading dir(s) for everything to be appended into
	# So the project can be /usr/lib/MYMAINPROJ/MYLIB1 & /usr/lib/MYMAINPROJ/MYLIB2 etc.
	get_target_property(_IAE_PATHS ${_INSTALL_EXPORT_TARGET} CUSTOM_LEADING_FOLDERS)
	# Allow for the user to rename the target's folder
	get_target_property(_IAE_NAME ${_INSTALL_EXPORT_TARGET} CUSTOM_FOLDER_NAME)

	IF(NOT _IAE_NAME)
		# If they didn't specify a special folder name, use last project name
		set(_IAE_NAME "${CMAKE_PROJECT_NAME}")
	ENDIF()

	IF(NOT _IAE_PATHS)
		# Use project name if no custom path provided
		set(_IAE_PATHS "${_IAE_NAME}")
	ELSE()
		# If they did supply leading dirs, append project name into it
		set(_IAE_PATHS "${_IAE_PATHS}/${_IAE_NAME}" FORCE)
	ENDIF()

	# Gives "Make install" esque operations a location to install to...
	# and creates a .cmake file for other projects to import.
	install(TARGETS ${_INSTALL_EXPORT_TARGET}
		EXPORT "${_INSTALL_EXPORT_TARGET}-targets"
		RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
		LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/${_IAE_PATHS}"
		ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}/${_IAE_PATHS}"
		# Tells it where to put your headers if any set by set_target_properties
		PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${_IAE_PATHS}"
		PRIVATE_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${_IAE_PATHS}"
		# Tells export where your includes folder is | Note that the private include path is not needed here
		INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${_IAE_PATHS}"
	)

	# "The install(TARGETS) and install(EXPORT) commands work together to install a target and a file to help import it"
	# Installs a cmake file which external projects can import.
	# This will point towards the pre-compiled binary after installation, but be treated as if it had been compiled inside the external project.
	install(EXPORT "${_INSTALL_EXPORT_TARGET}-targets"
	  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${_IAE_PATHS}"
	)

	# "The export command is used to generate a file exporting targets from a project build tree"
	# Creates an import file for external projects which are aware of the build tree.
	# This will not be installed, and is only usefull in certain situations.
	export(TARGETS ${_INSTALL_EXPORT_TARGET}
	  FILE "${_INSTALL_EXPORT_TARGET}-exports.cmake"
	)

	# Make sure our vars don't carry over through multiple macro calls
	unset(_IAE_PATHS)
	unset(_IAE_NAME)
endmacro()
