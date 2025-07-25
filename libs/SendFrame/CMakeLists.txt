project(SendLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} 
    SendToDisk.cpp
    SendToWindow.cpp
)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
