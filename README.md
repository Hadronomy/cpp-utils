# install_and_export macro

This defines a macro for easy installation/exporting of executables and libraries.\
Exports are created locally for build testing and are installed for importing by other projects.\
Header files can also be installed by setting them with [set_target_properties](https://cmake.org/cmake/help/latest/command/set_target_properties.html) using the [PUBLIC_HEADER](https://cmake.org/cmake/help/latest/prop_tgt/PUBLIC_HEADER.html) or [PRIVATE_HEADER](https://cmake.org/cmake/help/latest/prop_tgt/PRIVATE_HEADER.html) properties.

The macro should work on any executable created with `add_executable()`, and any lib created with `add_library()`

**Note:** It's necessary when using this to use generator expressions on your local includes because of how export works.\
See the example usage in CMakeLists.txt in `target_include_directories`.

## Usage

Run `include(modules/install_and_export/install_and_export.cmake)` to initialize the macro.\
Make sure to change the path based on your project structure.

Then the macro can be used like so: `install_and_export(mylibexename)`

### As a git submodule

I would recommend using this as a submodule so that you can update it under version control.

Run `git submodule add https://github.com/sum01/install_and_export.git` in the preferred folder location of your project.

#### Example usage in CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(Example VERSION 1.2.3 LANGUAGES CXX)

# Example executable
add_executable(my_exe main.cpp)

# It's necessary when using install_and_export() to use generator expressions on your local includes because of how export works
# More reading: https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html
target_include_directories(my_exe PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Telling it where your headers are for installation
# Normally you'd only do this with a shared library, but this is an example...
set_target_properties(my_exe PROPERTIES
	PUBLIC_HEADER "headerexample.hpp;anotherheader.hpp;moreheaders.hpp"
)

# Include the macro to initialize it
# Remember to change the path to fit your folder layout!
include(modules/install_and_export/install_and_export.cmake)

# Actually using the macro. The executable will be installed, its local export created, and the export also installed.
# The headers will also be installed into the correct folder, if any were set.
install_and_export(my_exe)
```
