//
// Created by az0t24 on 30.10.22.
//

#ifndef MIPT_FORMAL_PRAC_HW1_STATETEST_H
#define MIPT_FORMAL_PRAC_HW1_STATETEST_H
#pragma once

#include <gtest/gtest.h>
#include <fstream>
#include "../include/State.h"
#include "../include/Automaton.h"

class StateTest : public ::testing::Test {
public:
//    static void SetUpTestCase();
//    static void TearDownTestCase();

protected:
//    void SetUp() final;
//    void TearDown() final;
};

class AutomatonTest : public ::testing::Test {
public:
    void add(Automaton& a, std::string first, std::string second, char letter) {
        const State& from = a.AddState(first);
        const State& to = a.AddState(second);
        Transition transition(letter, to);
        a.AddTransition(from, transition);
    }

    void mark_term(Automaton& a, std::string state) {
        a.MakeTerminal(state);
    }

    void test_1(Automaton& test2) {
        add(test2, "1", "2", 'b');
        add(test2, "1", "3", 'b');
        add(test2, "2", "3", 'a');
        add(test2, "3", "3", 'b');
        add(test2, "3", "4", 'b');
        add(test2, "4", "3", 'a');
        add(test2, "3", "5", 'b');
        add(test2, "5", "6", 'a');
        add(test2, "6", "7", 'b');
        add(test2, "7", "8", 'a');
        add(test2, "7", "9", 'a');
        add(test2, "8", "9", 'b');
        add(test2, "9", "9", 'a');
        add(test2, "9", "10", 'a');
        add(test2, "10", "9", 'b');
        mark_term(test2, "9");
    }

    void test_2(Automaton& a) {
        add(a, "1", "1", 'a');
        add(a, "1", "1", 'b');
        add(a, "1", "2", 'b');
        add(a, "2", "3", 'b');
        add(a, "2", "5", 'a');
        add(a, "5", "6", 'b');
        add(a, "3", "3", 'a');
        add(a, "3", "3", 'b');
        add(a, "3", "4", 'a');
        add(a, "4", "6", 'a');
        add(a, "6", "6", 'b');
        add(a, "6", "7", 'b');
        add(a, "7", "7", 'a');
        mark_term(a, "7");
    }

    void test_3(Automaton& a) {
        add(a, "1", "2", 'a');
        add(a, "2", "3", 'b');
        add(a, "3", "2", '0');
        add(a, "2", "4", '0');
        add(a, "4", "5", 'a');
        add(a, "5", "6", 'b');
        add(a, "6", "4", 'a');
        add(a, "4", "7", 'a');
        add(a, "7", "8", 'a');
        add(a, "8", "7", 'b');
        add(a, "7", "2", 'a');
        mark_term(a, "2");
    }

    bool compare_doa(const std::string& first, const std::string& second) {
        std::ifstream in1(first);
        std::ifstream in2(second);

        std::string line1;
        std::string line2;

        while (getline(in1, line1) && getline(in2, line2)) {
            if (line1 != line2) {
                return false;
            }
        }

        if (getline(in1, line1) || getline(in2, line2)) {
            return false;
        }

        in1.close();
        in2.close();

        return true;
    }

protected:
    //    void SetUp() final;
    //    void TearDown() final;
};

#endif  // MIPT_FORMAL_PRAC_HW1_STATETEST_H
