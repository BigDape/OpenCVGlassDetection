cmake_minimum_required(VERSION 3.0)

project(hikvision VERSION 0.1 LANGUAGES CXX)

# 添加要编译的源文件
set(SRC_FILES
        allocator.h
        assertions.h
	config.h
	forwards.h
	json.h
	json_features.h
	json_reader.cpp
	json_tool.h
	json_value.cpp
	json_writer.cpp
	jsoncpp.cpp
	jsoncpp.h
	reader.h
	value.h
	version.h
        writer.h
        HSJsoncppInterface.h
        HSJsoncppInterface.cpp)

find_package(Qt6 REQUIRED COMPONENTS Core)


# 设置生成动态链接库
add_library(jsoncpp SHARED ${SRC_FILES})

# 添加头文件目录
target_include_directories(jsoncpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 如果有其他依赖项，可以在这里添加
target_link_libraries(jsoncpp Qt6::Core HSTool)
