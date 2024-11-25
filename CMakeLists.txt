# Minimum CMake version requirement
cmake_minimum_required(VERSION 3.15)

# Project name and version
project(sudsol VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Main project files.
add_subdirectory(source)

# Testing.
add_subdirectory(test)