# CMake generated Testfile for 
# Source directory: D:/v0.0.2/hivision
# Build directory: D:/v0.0.2/hivision/build/Desktop_Qt_6_8_0_MSVC2022_64bit-Debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_app "D:/v0.0.2/hivision/build/test/test_app")
set_tests_properties(test_app PROPERTIES  _BACKTRACE_TRIPLES "D:/v0.0.2/hivision/CMakeLists.txt;26;add_test;D:/v0.0.2/hivision/CMakeLists.txt;0;")
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
