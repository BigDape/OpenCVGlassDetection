# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "algorithm\\CMakeFiles\\algorithm_autogen.dir\\AutogenUsed.txt"
  "algorithm\\CMakeFiles\\algorithm_autogen.dir\\ParseCache.txt"
  "algorithm\\algorithm_autogen"
  "camare\\CMakeFiles\\camera_autogen.dir\\AutogenUsed.txt"
  "camare\\CMakeFiles\\camera_autogen.dir\\ParseCache.txt"
  "camare\\camera_autogen"
  "database\\CMakeFiles\\database_autogen.dir\\AutogenUsed.txt"
  "database\\CMakeFiles\\database_autogen.dir\\ParseCache.txt"
  "database\\database_autogen"
  "gpulib\\CMakeFiles\\gpulib_autogen.dir\\AutogenUsed.txt"
  "gpulib\\CMakeFiles\\gpulib_autogen.dir\\ParseCache.txt"
  "gpulib\\gpulib_autogen"
  "jsoncpp\\CMakeFiles\\jsoncpp_autogen.dir\\AutogenUsed.txt"
  "jsoncpp\\CMakeFiles\\jsoncpp_autogen.dir\\ParseCache.txt"
  "jsoncpp\\jsoncpp_autogen"
  "log\\src\\log4qt\\CMakeFiles\\log4qt_autogen.dir\\AutogenUsed.txt"
  "log\\src\\log4qt\\CMakeFiles\\log4qt_autogen.dir\\ParseCache.txt"
  "log\\src\\log4qt\\log4qt_autogen"
  "main\\CMakeFiles\\hikvision_autogen.dir\\AutogenUsed.txt"
  "main\\CMakeFiles\\hikvision_autogen.dir\\ParseCache.txt"
  "main\\hikvision_autogen"
  "socket\\CMakeFiles\\socket_autogen.dir\\AutogenUsed.txt"
  "socket\\CMakeFiles\\socket_autogen.dir\\ParseCache.txt"
  "socket\\socket_autogen"
  "test\\CMakeFiles\\test_app_autogen.dir\\AutogenUsed.txt"
  "test\\CMakeFiles\\test_app_autogen.dir\\ParseCache.txt"
  "test\\test_app_autogen"
  "tool\\CMakeFiles\\HSTool_autogen.dir\\AutogenUsed.txt"
  "tool\\CMakeFiles\\HSTool_autogen.dir\\ParseCache.txt"
  "tool\\HSTool_autogen"
  )
endif()
