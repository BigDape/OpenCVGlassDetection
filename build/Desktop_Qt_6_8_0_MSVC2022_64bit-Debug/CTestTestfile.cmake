# CMake generated Testfile for 
# Source directory: D:/code/hivision
# Build directory: D:/code/hivision/build/Desktop_Qt_6_8_0_MSVC2022_64bit-Debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_app "D:/code/hivision/build/test/test_app")
set_tests_properties(test_app PROPERTIES  _BACKTRACE_TRIPLES "D:/code/hivision/CMakeLists.txt;26;add_test;D:/code/hivision/CMakeLists.txt;0;")
subdirs("main")
subdirs("tool")
subdirs("jsoncpp")
subdirs("algorithm")
subdirs("gpulib")
subdirs("camare")
subdirs("socket")
subdirs("database")
subdirs("log")
subdirs("unittest")
subdirs("test")
