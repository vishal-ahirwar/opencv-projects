cmake_minimum_required(VERSION 3.1)
project(sample)
find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}/opencv4)
add_executable(main ./src/main.cpp)
target_link_libraries(main ${OpenCV_LIBS})
