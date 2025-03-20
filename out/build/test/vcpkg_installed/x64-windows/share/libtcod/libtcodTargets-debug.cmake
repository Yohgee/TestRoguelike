#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libtcod::libtcod" for configuration "Debug"
set_property(TARGET libtcod::libtcod APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(libtcod::libtcod PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/debug/lib/libtcod.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "utf8proc"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/bin/libtcod.dll"
  )

list(APPEND _cmake_import_check_targets libtcod::libtcod )
list(APPEND _cmake_import_check_files_for_libtcod::libtcod "${_IMPORT_PREFIX}/debug/lib/libtcod.lib" "${_IMPORT_PREFIX}/debug/bin/libtcod.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
