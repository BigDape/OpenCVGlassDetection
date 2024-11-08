cmake_minimum_required(VERSION 3.0)

project(hikvision VERSION 0.1 LANGUAGES CXX)

# 添加要编译的源文件
set(SRC_FILES
        ElemMatch.h
	HSSocketInterface.cpp
	HSSocketInterface.h
	ParamComm.cpp
	ParamComm.h
	RegParasComm.cpp
	RegParasComm.h
	SignalControlData.cpp
	SignalControlData.h
	Tcp.cpp
	Tcp.h
	TcpPackComm.cpp
	TcpPackComm.h)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network)


# 设置生成动态链接库
add_library(socket SHARED ${SRC_FILES})

# 添加头文件目录
target_include_directories(socket PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 如果有其他依赖项，可以在这里添加
target_link_libraries(socket Qt6::Core Qt6::Widgets Qt6::Network HSTool)
