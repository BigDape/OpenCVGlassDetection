cmake_minimum_required(VERSION 3.0)

project(hikvision VERSION 0.1 LANGUAGES CXX)

# 添加要编译的源文件
set(SRC_FILES
    HSTool.h)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(OpenCV 4.10.0 REQUIRED)

# 设置生成动态链接库
add_library(HSTool SHARED ${SRC_FILES}
    HSTool.cpp)

# 添加头文件目录
target_include_directories(HSTool PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 如果有其他依赖项，可以在这里添加
target_link_libraries(HSTool Qt6::Core ${OpenCV_LIBS})
