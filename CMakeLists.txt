project (Platform)
cmake_minimum_required (VERSION 2.8)
find_package (Qt5 COMPONENTS Widgets Network)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -std=c++11")

include_directories (${Qt5Widgets_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS} ${Platform_SOURCE_DIR}/src)
#set (EXECUTABLE_OUTPUT_PATH "${Platform_BINARY_DIR}/bin")

set (Platform_SRCS src/main.cpp src/server.cpp src/socket.cpp src/window.cpp)
set (Platform_HDRS src/server.h src/socket.h src/window.h)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${Platform_BINARY_DIR}/bin")

add_subdirectory (src)

install (DIRECTORY data DESTINATION "${Platform_BINARY_DIR}")
