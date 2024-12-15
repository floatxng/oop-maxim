cmake_minimum_required(VERSION 3.10)

project(PMR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/include/*.h)

add_library(PMRLib STATIC ${SOURCES} ${HEADERS})

target_include_directories(PMRLib PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_executable(PMRApp ${PROJECT_SOURCE_DIR}/main.cpp)

target_link_libraries(PMRApp FiguresLib)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(PMRTests test/pmrQueueTest.cpp)

target_link_libraries(PMRTests PMRLib GTest::GTest GTest::Main pthread)

add_test(NAME PMRTests COMMAND PMRTests)
