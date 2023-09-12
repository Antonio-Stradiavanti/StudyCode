cmake_minimum_required(VERSION 3.24)
project(Lab5_clion C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab5_clion main.c)

target_link_libraries(Lab5_clion PRIVATE m)
