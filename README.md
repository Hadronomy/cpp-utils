# install_and_export Cmake macro

This defines a macro for easy installation/exporting of executables and libraries.

Exports are created locally for build testing and are installed for importing by other projects.\
Header files can be installed by using [set_target_properties()](https://cmake.org/cmake/help/latest/command/set_target_properties.html) and setting [PUBLIC_HEADER](https://cmake.org/cmake/help/latest/prop_tgt/PUBLIC_HEADER.html) or [PRIVATE_HEADER](https://cmake.org/cmake/help/latest/prop_tgt/PRIVATE_HEADER.html).

The macro should work on any executable created with `add_executable()`, and any lib created with `add_library()`

**Note:** It's necessary when using this to use generator expressions on your local includes because of how export works.\
See the example usage in CMakeLists.txt in `target_include_directories()`.

## Usage

Run `include(modules/install_and_export/install_and_export.cmake)` to initialize the macro.\
Make sure to change the include path based on your project structure.

Then the macro can be used like so: `install_and_export(mylibexename)`

### Defining Custom Folder Structures

These are only really useful for libraries, as an executable doesn't install anything but itself.

You can define custom properties with `set_target_properties()` to allow for custom installed folder layouts.\
See the example CMakeLists.txt below for usage on a library.

`CUSTOM_LEADING_FOLDERS` is used to define leading folder structure. Make sure to only use forward-slashes!\
`CUSTOM_FOLDER_NAME` is used to define a different output folder for your target.

Only set these properties to help name your folders, never define relative or OS-specific paths!

### Example usage in CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(Example VERSION 1.2.3 LANGUAGES CXX)

# Example executable
add_executable(my_exe main.cpp)

# It's necessary when using install_and_export() to use generator expressions on your local includes because of how export works
# More reading: https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html
target_include_directories(my_exe PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:src>
)

# Include the macro to initialize it
# Remember to change the path to fit your folder layout!
include(modules/install_and_export/install_and_export.cmake)

# Actually using the macro.
install_and_export(my_exe)

# Creating an example library
add_library(my_lib STATIC lib.cpp)

target_include_directories(my_lib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:src>
)

# Define some properties for installing headers and changing folder structure
set_target_properties(my_lib PROPERTIES
	# Telling it where your headers are for installation
	PUBLIC_HEADER "src/headerexample.hpp;src/anotherheader.hpp;src/moreheaders.hpp"
	# Using the custom properties to define a different installed folder structure
	CUSTOM_LEADING_FOLDERS "leadproject/subproject"
	# Changing the library's folder name
	CUSTOM_FOLDER_NAME "example-lib"
)

# Install the lib
install_and_export(my_lib)

# Because of how we defined our properties, the install path resolves to...
# "${CMAKE_INSTALL_LIBDIR}/leadproject/subproject/example-lib/libmy_lib.a"
# And headers are at this path...
# "${CMAKE_INSTALL_INCLUDEDIR}/leadproject/subproject/example-lib/headerswouldbehere.hpp"
```
