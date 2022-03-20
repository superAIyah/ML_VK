cmake_minimum_required(VERSION 3.0.0)
project(fib)

add_subdirectory(funcs)

message("FIB_LIB_INCLUDE_DIRS = ${FIB_LIB_INCLUDE_DIRS}")
message("FIB_LIB_LIBRARIES = ${FIB_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.c) # создай исполняемый файл с таким названием

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${FIB_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${FIB_LIB_LIBRARIES})

add_subdirectory(tests)