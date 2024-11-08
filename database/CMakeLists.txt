cmake_minimum_required(VERSION 3.0)

project(hikvision VERSION 0.1 LANGUAGES CXX)

# 添加要编译的源文件
set(SRC_FILES
        database.cpp
        database.h
        HSDatabaseInterface.h
        HSDatabaseInterface.cpp)

find_package(Qt6 REQUIRED COMPONENTS Core Sql)

# 设置生成动态链接库
add_library(database SHARED ${SRC_FILES})

# 添加头文件目录
target_include_directories(database PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 如果有其他依赖项，可以在这里添加
target_link_libraries(database Qt6::Core Qt6::Sql HSTool)
