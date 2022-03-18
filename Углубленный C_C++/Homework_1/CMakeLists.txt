cmake_minimum_required(VERSION 3.0.0)

project(animals VERSION 0.1.0)

file(GLOB SOURCES "main.c" "funcs/*/*.c")
file(GLOB INCLUDE_DIRS "funcs/*/")

add_executable(${PROJECT_NAME} ${SOURCES}) # создай исполняемый файл из src
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS}) # добавь возможность искать инклуды

message("SOURCES = ${SOURCES}")
message("INCLUDE_DIRS = ${INCLUDE_DIRS}")