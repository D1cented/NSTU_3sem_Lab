cmake_minimum_required(VERSION 3.10)
project(DataStructures)

set(CMAKE_CXX_STANDARD 17)

add_executable(DataStructures
    main.cpp
    Array.h Array.cpp
    SinglyList.h SinglyList.cpp
    DoublyList.h DoublyList.cpp
    Stack.h Stack.cpp
    Queue.h Queue.cpp
    CompleteBinaryTree.h CompleteBinaryTree.cpp
)
