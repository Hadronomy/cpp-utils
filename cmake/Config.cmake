@PACKAGE_INIT@

include("${CMAKE_CURRENT_LIST_DIR}/@PROJECT_NAME@Targets.cmake")

check_required_components(@PROJECT_NAME@)
string(TOUPPER "@PROJECT_NAME@_LIB" lib_name)
add_compile_definitions("${lib_name}")