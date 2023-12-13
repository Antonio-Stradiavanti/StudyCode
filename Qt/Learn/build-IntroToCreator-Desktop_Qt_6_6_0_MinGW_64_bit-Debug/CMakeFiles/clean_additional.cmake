# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\IntroToCreator_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\IntroToCreator_autogen.dir\\ParseCache.txt"
  "IntroToCreator_autogen"
  )
endif()
