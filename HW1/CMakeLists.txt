cmake_minimum_required(VERSION 3.20)
project(HW1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HW1
        Cabinet.cpp
        Cabinet.h
        Chemical.cpp
        Chemical.h
        HW1.cpp
        LabOrganizer.cpp
        LabOrganizer.h)
