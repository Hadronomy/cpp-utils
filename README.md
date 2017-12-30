# install_and_export macro

[install_and_export](./install_and_export.cmake) defines a simple macro for easy installation & exporting of executables/libraries in your CmakeLists.txt.

The macro should work on any executable created with `add_executable()`, and any lib created with `add_library()`

## What it does

1. Adds the target to be installed when `make install`-esque Cmake commands are used.
2. Exports the target both locally for testing, and installs the export for easy importing.

## Usage

I recommend making a `cmake/modules` at your project's root to hold modules.

### As a git submodule

`git submodule add https://github.com/sum01/install_and_export.git` into your preferred folder location in your project.  
I would recommend doing this so that you can update the module under version control.

## In CmakeLists.txt

Put `list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/install_and_export")` before using the functionality (making sure to change the path based on where you placed it).

Example after including: `install_and_export(exe_name_here)`

**Example usage in CmakeLists.txt**

```cmake
CMAKE_MINIMUM_REQUIRED(VERSION 3.0 FATAL_ERROR)
project(Example VERSION "1.2.3" LANGUAGES CXX)

# Remember to change the path to fit your folder layout
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/install_and_export")

# Include the macro so it can be called
include(install_and_export)

# Example executable
add_executable(my_exe main.cpp)

# It's necessary when using install_and_export() to use generator expressions on includes because of how export works
target_include_directories(my_exe
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
install_and_export(my_exe)
```
