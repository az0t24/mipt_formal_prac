cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME project1)
project(${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${project1_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_CXX_STANDARD 20)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_INCLUDES})

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp)
add_library(project1_lib ${SRC_FILES})

add_executable(runProgram ${PROJECT_SOURCE_DIR}/main.cpp)
target_link_libraries(runProgram project1_lib)

########################################
# Testing
########################################

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -lgtest")

add_subdirectory(./googletest)
enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/Test.cpp)

add_executable(runUnitTests ${TEST_SRC_FILES})
target_link_libraries(runUnitTests gtest gtest_main)

target_link_libraries(runUnitTests project1_lib)
add_test(UnitTests runUnitTests)