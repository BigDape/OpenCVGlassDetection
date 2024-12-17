cmake_minimum_required(VERSION 3.16)

project(hikvision VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("当前路径为：${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/main)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tool)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/jsoncpp)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/algorithm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/gpulib)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/camare)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/socket)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/database)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/log)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/unittest)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
enable_testing()
add_test(test_app ${CMAKE_SOURCE_DIR}/build/test/test_app)


