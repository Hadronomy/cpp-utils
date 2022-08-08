if(NOT EXISTS "@CMAKE_BINARY_DIR@/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: @CMAKE_BINARY_DIR@/install_manifest.txt")
endif()

file(READ "@CMAKE_BINARY_DIR@/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach(file ${files})
  set(file_path "$ENV{DESTDIR}${file}")
  if(IS_SYMLINK "${file_path}" OR EXISTS "${file_path}")
    message(STATUS "Uninstalling: ${file_path}")
    execute_process(
      COMMAND "@CMAKE_COMMAND@" "-E" "remove" "${file_path}"
      RESULT_VARIABLE rm_retval
      ERROR_VARIABLE err_out
      OUTPUT_STRIP_TRAILING_WHITESPACE
      )
    if(DEFINED ${err_out})
      message(FATAL_ERROR ${err_out})
    endif()
    if(NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing $ENV{DESTDIR}${file}\n"
              "${rm_retval}")
    endif()
  else()
    message(STATUS "Nonexistent: $ENV{DESTDIR}${file}")
  endif()
endforeach()
