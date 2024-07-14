cmake_minimum_required(VERSION 3.27)
project(src)

set(CMAKE_CXX_STANDARD 14)

add_executable(main src/main.cpp
        src/Pelicula.h
        src/DataManager.h
        src/DataManager.cpp
        src/Recommender.h)
