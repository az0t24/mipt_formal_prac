cmake_minimum_required(VERSION 3.20)
project(test_auto)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(../src)
include_directories(../include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -lgtest")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${test_SOURCE_DIR}/bin)

add_compile_options("-lgcov")
link_libraries("-lgcov")

enable_testing()
add_executable(test_auto main.cpp Test.cpp ../src/State.cpp ../include/State.h ../include/Automaton.h ../src/Automaton.cpp Test.h)
target_link_libraries(test_auto gtest)
