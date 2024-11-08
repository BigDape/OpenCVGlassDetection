cmake_minimum_required(VERSION 3.0)

project(hikvision VERSION 0.1 LANGUAGES CXX)

# 添加要编译的源文件
set(SRC_FILES
        DushenBasicFunc.cpp
        DushenBasicFunc.h
	DVPCamera.h
	HSCameraInterface.cpp
	HSCameraInterface.h

    )

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# 设置生成动态链接库
add_library(camera SHARED ${SRC_FILES})

# 添加头文件目录
target_include_directories(camera PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 如果有其他依赖项，可以在这里添加
target_link_libraries(camera Qt6::Core Qt6::Widgets ${CMAKE_CURRENT_SOURCE_DIR}/lib_x86_64/DVPCamera64.lib)
