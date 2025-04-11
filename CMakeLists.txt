cmake_minimum_required(VERSION 3.30)
project(L3)

set(CMAKE_CXX_STANDARD 14)

include_directories(Queue)

add_executable(L3
    Queue/App.cpp
    Queue/ExtendedTest.cpp
    Queue/ExtendedTest.h
    Queue/Queue.cpp
    Queue/Queue.h
    Queue/ShortTest.cpp
    Queue/ShortTest.h
        Labyrinth/Labyrinth.h
        main.cpp)
