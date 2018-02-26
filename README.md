# install_and_export macro

This defines a macro for easy installation/exporting of executables and libraries.

Exports are created locally for easy build testing, and are also installed for easy importing by other projects.\
And of course it is also added to install targets.

The macro should work on any executable created with `add_executable()`, and any lib created with `add_library()`

**Note:** It's necessary when using this to use generator expressions on your local includes because of how export works.\
See the example usage in CMakeLists.txt in `target_include_directories`.

## Usage

Put `list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/install_and_export")` before the `include()`. Make sure to change the path based on your project structure.

After appending the path to `CMAKE_MODULE_PATH`, you run `include(install_and_export)` to initialize the macro.

Then the macro can be run with `install_and_export(mylibexename)`

### As a git submodule

I would recommend using this as a submodule so that you can update it under version control.

Run `git submodule add https://github.com/sum01/install_and_export.git` in the preferred folder location of your project.

#### Example usage in CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(Example VERSION "1.2.3" LANGUAGES CXX)

# Remember to change the path to fit your folder layout!
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/install_and_export")

# Include the macro to initialize it
include(install_and_export)

# Example executable
add_executable(my_exe main.cpp)

# It's necessary when using install_and_export() to use generator expressions on your local includes because of how export works
target_include_directories(my_exe
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PUBLIC $<INSTALL_INTERFACE:include>
)

# Actually using the macro. The executable will be installed, its local export created, and the export also installed.
install_and_export(my_exe)
```
