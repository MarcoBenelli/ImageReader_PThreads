cmake_minimum_required(VERSION 3.17)
project(ImageReader_PThreads)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ImageReader_PThreads main.cpp)

target_link_libraries(ImageReader_PThreads ${OpenCV_LIBS})