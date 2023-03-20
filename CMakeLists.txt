cmake_minimum_required(VERSION 3.24)
project(Project1DA)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project1DA
        main.cpp graph.cpp graph.h Station.h TrainNetwork.h TrainNetwork.cpp)
