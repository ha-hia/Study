cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)
project(GoF23)

###################### Targets #########################
add_subdirectory(src)
add_subdirectory(src/Singleton)
########################################################