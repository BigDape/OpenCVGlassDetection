cmake_minimum_required(VERSION 3.0)

project(test VERSION 0.1 LANGUAGES CXX)

# 添加要编译的源文件
set(SRC_FILES
        main.cpp)

# 设置宏变量 DEBUG_MODE
add_definitions(-DTEST_ALGORITHM=1)

if(POLICY CMP0146)
    cmake_policy(SET CMP0146 OLD)
endif()
find_package(OpenCV 4.10.0 REQUIRED)

# INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/include")
add_executable(test_app ${SRC_FILES})

find_package(Qt6 REQUIRED COMPONENTS Core )

# 如果有其他依赖项，可以在这里添加
target_link_libraries(test_app Qt6::Core ${OpenCV_LIBS} algorithm)

