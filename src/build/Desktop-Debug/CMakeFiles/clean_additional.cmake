# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Utecflix_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Utecflix_autogen.dir/ParseCache.txt"
  "Utecflix_autogen"
  )
endif()
