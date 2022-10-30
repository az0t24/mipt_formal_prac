cmake_minimum_required(VERSION 3.20)
project(mipt_formal_prac_hw1)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(
        ${mipt_formal_prac_hw1_SOURCE_DIR}/include
        ${mipt_formal_prac_hw1_SOURCE_DIR}/src
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${mipt_formal_prac_hw1_SOURCE_DIR}/bin)

add_executable(mipt_formal_prac_hw1
        ${mipt_formal_prac_hw1_SOURCE_DIR}/src/Automaton.cpp
        ${mipt_formal_prac_hw1_SOURCE_DIR}/include/Automaton.h
        main.cpp
        ${mipt_formal_prac_hw1_SOURCE_DIR}/src/State.cpp
        ${mipt_formal_prac_hw1_SOURCE_DIR}/include/State.h
        ${mipt_formal_prac_hw1_SOURCE_DIR}/src/Transition.cpp
        ${mipt_formal_prac_hw1_SOURCE_DIR}/include/Transition.h)
