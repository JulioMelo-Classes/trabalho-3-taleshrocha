# Snaze: a SNAke trapped in a MaZE, programming project
cmake_minimum_required(VERSION 3.5)

project(Snaze VERSION 0.1 LANGUAGES CXX )

FILE(GLOB SOURCE_FILES src/*.cpp) #Get all the source files

include_directories(include)
add_executable(
  Snaze
  ${SOURCE_FILES})

set(CMAKE_CXX_FLAGS "-Wall -g -fsanitize=address -std=c++20 -lm")
