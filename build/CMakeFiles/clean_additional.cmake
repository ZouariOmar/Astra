# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Astra_autogen"
  "CMakeFiles/Astra_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Astra_autogen.dir/ParseCache.txt"
  )
endif()
