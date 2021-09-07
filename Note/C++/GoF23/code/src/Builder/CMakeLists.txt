cmake_minimum_required(VERSION 3.8)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

aux_source_directory(. BuilderFile)

add_library(Builder ${BuilderFile})