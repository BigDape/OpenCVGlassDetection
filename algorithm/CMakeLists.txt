cmake_minimum_required(VERSION 3.10)

project(hikvision VERSION 0.1 LANGUAGES CXX)

# 添加要编译的源文件
set(SRC_FILES
        algorithm.cpp
	algorithm.h
	HSAlgorithmInterface.cpp
	HSAlgorithmInterface.h
	processtile.cpp
        processtile.h)

find_package(Qt6 REQUIRED COMPONENTS Core)

set(CUDA_PATH "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.5")

# 设置生成动态链接库
add_library(algorithm SHARED ${SRC_FILES})

# 添加头文件目录
target_include_directories(algorithm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CUDA_PATH}/include)

find_package(OpenCV 4.10.0 REQUIRED)
# 如果有其他依赖项，可以在这里添加
target_link_libraries(algorithm Qt6::Core ${OpenCV_LIBS} HSTool)
