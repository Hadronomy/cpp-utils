@PACKAGE_INIT@

include("${CMAKE_CURRENT_LIST_DIR}/@PROJECT_NAME@-targets.cmake")

check_required_components(@PROJECT_NAME@)
string(TOUPPER "@PROJECT_NAME@_LIB" LIB_NAME)
add_compile_definitions("${LIB_NAME}")
