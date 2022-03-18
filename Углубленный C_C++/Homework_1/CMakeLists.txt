cmake_minimum_required(VERSION 3.0.0)
include(GoogleTest)

project(animals VERSION 0.1.0)

file(GLOB SOURCES "src/*.c" "src/*/*.c")
file(GLOB INCLUDE_DIRS "src/*/")

add_executable(${PROJECT_NAME} ${SOURCES}) # создай исполняемый файл из src
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS}) # добавь возможность искать инклуды

message("SOURCES = ${SOURCES}")