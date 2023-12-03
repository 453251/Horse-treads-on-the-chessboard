cmake_minimum_required(VERSION 3.26)
project(MattackPan)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

set(CMAKE_EXE_LINKER_FLAGS -static)

add_executable(MattackPan
        ChessClassHead.h
        main.cpp
        Stack_Imp_class.cpp
        Warnsdorff_Imp.cpp
        DFS_Imp.cpp
        Backtracking_Imp.cpp)
