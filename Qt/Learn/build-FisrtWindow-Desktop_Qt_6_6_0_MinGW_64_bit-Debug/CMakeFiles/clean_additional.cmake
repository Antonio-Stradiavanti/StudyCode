# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\FisrtWindow_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\FisrtWindow_autogen.dir\\ParseCache.txt"
  "FisrtWindow_autogen"
  )
endif()
