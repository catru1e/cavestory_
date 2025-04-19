cmake_minimum_required(VERSION 3.10)
project(cavestory)

set(CMAKE_CXX_STANDARD 17)

# SDL2 and SDL2_image are installed in /usr/local
set(CMAKE_PREFIX_PATH "/usr/local/lib/cmake")

# Find SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Include SDL2 and SDL2_image headers
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

# Add source files
add_executable(cavestory
        main.cpp
        game.cpp
        input.cpp
        graphics.cpp
)

# Link SDL2 and SDL2_image libraries
target_link_libraries(cavestory ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

