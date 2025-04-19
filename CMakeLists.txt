cmake_minimum_required(VERSION 3.15)
project(tetris)

set(CMAKE_CXX_STANDARD 17)

# Enable CMake's support for vcpkg
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# Add source files
add_executable(tetris src/main.cpp)

# Link SDL2
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(tetris PRIVATE SDL2::SDL2 SDL2::SDL2main)
