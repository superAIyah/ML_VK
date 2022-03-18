cmake_minimum_required(VERSION 3.0.0)
project(funcs)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")

file(GLOB SOURCES "*/*.c")
file(GLOB INCLUDE_DIRS "*/")

add_library(${PROJECT_NAME} STATIC ${SOURCES})

set(FIB_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE) # в такой папке будет собрана библиотека
set(FIB_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS}) # для инклудов между заголовочными файлами