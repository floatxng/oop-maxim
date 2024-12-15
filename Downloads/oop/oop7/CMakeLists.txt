cmake_minimum_required(VERSION 3.10)
project(BalagurFate3Editor)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB TEST_SOURCES ${PROJECT_SOURCE_DIR}/test/*.cpp)


add_executable(BalagurFate3Editor ${HEADERS} ${SOURCES})


target_include_directories(BalagurFate3Editor PRIVATE ${PROJECT_SOURCE_DIR}/include)
