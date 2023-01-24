cmake_minimum_required(VERSION 3.21)
project(Ex4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Ex4
        AlgorithmKnn.cpp
        AlgorithmKnn.h
        DB.cpp
        DB.h
        DistanceFuncManager.cpp
        DistanceFuncManager.h
        InputManager.cpp
        InputManager.h
        Neighbor.cpp
        Neighbor.h
        DefaultIO.h StandardIO.cpp StandardIO.h Command.h Command.cpp CLI.cpp CLI.h Update.cpp Update.h Change.cpp Change.h Classify.cpp Classify.h Display.cpp Display.h Download.cpp Download.h main.cpp)
