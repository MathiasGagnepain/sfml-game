# How to use with mingw: (Windows)
#   cmake -S . -B Build -G "MinGW Makefiles"
#   cd Build
#   mingw32-make

# How to use with msys2: (Windows)
#   cmake -S . -B Build -G "MSYS Makefiles"
#   cd Build
#   make
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_COMPILER "g++")

project(
  Stickman-Exploration
  VERSION 0.0.1
  LANGUAGES CXX
)

find_package(Threads REQUIRED)

add_executable(game
    src/includes/menu.cc
    src/class/character.cc
    src/main.cpp
)

target_include_directories(game
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/includes"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/class"
)

target_link_libraries(game
  PRIVATE
    Threads::Threads
    sfml-graphics
    sfml-window
    sfml-system
)

target_compile_options(game
  PRIVATE
    -Wall -Wextra -pedantic -g -O2
)

set_target_properties(game
  PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)