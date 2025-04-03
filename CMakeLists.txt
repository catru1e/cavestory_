cmake_minimum_required(VERSION 3.10)
project(cavestory)

set(CMAKE_CXX_STANDARD 17)

# Пути к SDL2
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
add_executable(cavestory main.cpp)
target_link_libraries(cavestory ${SDL2_LIBRARIES})
