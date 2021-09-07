cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 17)
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
project(GoF23)

###################### Targets #########################
add_subdirectory(src)
# add_subdirectory(src/Singleton)
# add_subdirectory(src/Prototype)
# add_subdirectory(src/Factory)
add_subdirectory(src/Builder)


########################################################