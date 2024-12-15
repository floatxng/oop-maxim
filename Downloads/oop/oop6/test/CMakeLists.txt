cmake_minimum_required(VERSION 3.10)

project(BalagurFate3EditorTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB TEST_SOURCES ${PROJECT_SOURCE_DIR}/test/*.cpp)

add_executable(BalagurFate3EditorTests ${TEST_SOURCES} ${SOURCES})

target_link_libraries(BalagurFate3EditorTests GTest::GTest GTest::Main pthread)

enable_testing()
include(GoogleTest)
gtest_discover_tests(BalagurFate3EditorTests)
add_test(NAME AllTests COMMAND BalagurFate3EditorTests)