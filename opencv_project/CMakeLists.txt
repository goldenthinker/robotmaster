cmake_minimum_required(VERSION 3.10.0)
project(cop VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenCV REQUIRED)

add_executable(cop main.cpp)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(cop ${OpenCV_LIBS})cmake_minimum_required(VERSION 3.10.0)

