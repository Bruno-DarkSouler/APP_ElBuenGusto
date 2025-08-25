# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/ElBuenGusto_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/ElBuenGusto_autogen.dir/ParseCache.txt"
  "ElBuenGusto_autogen"
  )
endif()
