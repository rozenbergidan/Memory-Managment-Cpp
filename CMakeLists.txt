cmake_minimum_required(VERSION 3.17)
project(spl1)

set(CMAKE_CXX_STANDARD 11)

add_executable(spl1 main.cpp Session.cpp Session.h Graph.cpp Graph.h Agent.cpp Agent.h Tree.cpp Tree.h)