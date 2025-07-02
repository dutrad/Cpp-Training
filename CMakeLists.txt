cmake_minimum_required(VERSION 3.5)

project(app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
