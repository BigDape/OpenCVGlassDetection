cmake_minimum_required(VERSION 3.0)

project(hikvision VERSION 0.1 LANGUAGES CUDA CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 添加要编译的源文件
set(SRC_FILES
    kernel.h
        kernel.cu)

find_package(Qt6 REQUIRED COMPONENTS Core)

set(CUDA_DIR "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.5/include")
enable_language(CUDA)
if(${CUDA_FOUND})
        set(CUDA_SOURCE_PROPERTY_FORMAT OBJ)
        set(CUDA_SEPARABLE_COMPILATION ON)
        include_directories(${CUDA_INCLUDE_DIRS})
        set(CUDA_PROPAGATE_HOST_FLAGS ON)
        # set(CUDA_NVCC_FLAGS -arch=sm_61;-O3;-G;-g;-std=c++17)#根据具体GPU性能更改算力参数
        SET(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-gencode arch=compute_61,code=sm_61;-std=c++17;-O3;-G;-g)
        link_directories($ENV{CUDA_PATH}/lib/x64)
else(${CUDA_FOUND})
        MESSAGE(STATUS "cuda not found!")
endif(${CUDA_FOUND})

# 设置生成动态链接库
add_library(gpulib SHARED ${SRC_FILES})

# 添加头文件目录
target_include_directories(gpulib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CUDA_DIR})

find_package(OpenCV 4.10.0 REQUIRED)
# 如果有其他依赖项，可以在这里添加
target_link_libraries(gpulib Qt6::Core ${OpenCV_LIBS} HSTool CUDA)
