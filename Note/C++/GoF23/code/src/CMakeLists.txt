cmake_minimum_required(VERSION 3.8)


##搜索路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

## 当前路径所有源文件
aux_source_directory(. SRCFile)

## 生成物
add_executable(GoF23 ${SRCFile})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Result)

## 依赖后续生成
target_link_libraries(GoF23
                      # Singleton
                      # Prototype
                      # Factory
                      Builder )




