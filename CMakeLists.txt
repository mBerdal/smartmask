cmake_minimum_required(VERSION 3.0)
project(smartmask)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

# Add executable
add_executable(${PROJECT_NAME}-test
    src/test.cpp
)