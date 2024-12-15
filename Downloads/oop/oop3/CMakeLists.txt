# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(FiguresM)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Collect all source and header files
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/include/*.h)

# Create a library from the source files
add_library(FiguresLib STATIC ${SOURCES} ${HEADERS})

# Set include directories for the library
target_include_directories(FiguresLib PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Create an executable for the main application
add_executable(FiguresApp ${PROJECT_SOURCE_DIR}/main.cpp)

# Link the main application with the FiguresLib library
target_link_libraries(FiguresApp FiguresLib)

# Enable testing
enable_testing()

# Find Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Create an executable for the tests
add_executable(FiguresTests test/FigureTests.cpp)

# Link the test executable with FiguresLib and GTest
target_link_libraries(FiguresTests FiguresLib GTest::GTest GTest::Main pthread)

# Add the test executable to ctest
add_test(NAME FiguresTests COMMAND FiguresTests)
