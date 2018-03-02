# install_and_export - version 1.1.0
# Author: sum01 <sum01@protonmail.com>
# Git: https://github.com/sum01/install_and_export
# Read the README.md for full info!

# Defines standardized defaults for install paths
include(GNUInstallDirs)

macro(install_and_export _INSTALL_EXPORT_TARGET)
	# Gives "Make install" esque operations a location to install to...
	# and creates a .cmake file for other projects to import.
	install(TARGETS ${_INSTALL_EXPORT_TARGET}
		EXPORT "${_INSTALL_EXPORT_TARGET}-targets"
		RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
		LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
		ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
		# Tells it where to put your headers if any set by set_target_properties
		PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
		PRIVATE_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
		# Tells export where your includes folder is
		INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
	)

	# "The install(TARGETS) and install(EXPORT) commands work together to install a target and a file to help import it"
	# Installs a cmake file which external projects can import.
	# This will point towards the pre-compiled binary after installation, but be treated as if it had been compiled inside the external project.
	install(EXPORT "${_INSTALL_EXPORT_TARGET}-targets"
	  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME}"
	)

	# "The export command is used to generate a file exporting targets from a project build tree"
	# Creates an import file for external projects which are aware of the build tree.
	# This will not be installed, and is only usefull in certain situations.
	export(TARGETS ${_INSTALL_EXPORT_TARGET}
	  FILE "${_INSTALL_EXPORT_TARGET}-exports.cmake"
	)
endmacro()
