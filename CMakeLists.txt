cmake_minimum_required(VERSION 3.16)
project(Ink_robot)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Ink_robot
        main.cpp
        Robot.cpp
        Shelf.cpp)

add_executable(test
        Shelf.cpp
        Robot.cpp
        test.cpp)