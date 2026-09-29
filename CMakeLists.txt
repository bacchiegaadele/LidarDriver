cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project (LidarDriver)

include_directories(include)

add_library(LidarDriver
   include/LidarDriver.h
   src/LidarDriver.cpp
)

add_executable(mainLidarDriver
   src/mainLidarDriver.cpp
)

target_link_libraries(mainLidarDriver
   LidarDriver
)

