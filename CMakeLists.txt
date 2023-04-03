cmake_minimum_required(VERSION 3.23.2)
project(Project1DA)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project1DA
        main.cpp graph.cpp graph.h Station.h TrainNetwork.h TrainNetwork.cpp Menu.cpp Menu.h VertexEdge.cpp VertexEdge.h MutablePriorityQueue.h Line.h)
