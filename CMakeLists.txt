cmake_minimum_required(VERSION 3.10)
project(cavestory CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL2_PATH "~/Documents/SDL2-2.0.3/build/sdl2_local")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(cavestory main.cpp)

target_link_libraries(${cavestory} ${SDL2_LIBRARY})
