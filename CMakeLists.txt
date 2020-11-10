cmake_minimum_required(VERSION 3.17)
project(spl1)

set(CMAKE_CXX_STANDARD 11)

add_executable(spl1 ../src/main.cpp ../src/Session.cpp ../include/Session.h ../src/Graph.cpp ../include/Graph.h ../src/Agent.cpp ../include/Agent.h ../src/Tree.cpp ../include/Tree.h)