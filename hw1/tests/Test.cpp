//
// Created by az0t24 on 30.10.22.
//

#include "Test.h"

TEST_F(StateTest, Equals) {
    State a("1");
    State b("1");

    ASSERT_EQ(a, b);
}

TEST_F(StateTest, GetName) {
    State a("1", true);

    ASSERT_EQ(a.GetName(), "1");
}

TEST_F(StateTest, IsTerm) {
    State a("1", true);
    State b = a;

    ASSERT_TRUE(b.IsTerm());
}

TEST_F(StateTest, Less) {
    State a("1", true);
    State b("2");

    ASSERT_LT(a, b);
}

TEST_F(StateTest, Sum) {
    State a("1", true);
    State b("2", false);
    State c = a + b;

    ASSERT_TRUE(c.IsTerm());
    ASSERT_EQ(c.GetName(), "12");
}

TEST_F(StateTest, MakeTerminal) {
    State a("1", false);
    a.MakeTerminal();

    ASSERT_TRUE(a.IsTerm());
}

TEST_F(StateTest, AddTransition) {
    State a("1", false);
    State b("2");
    Transition trans('b', b);

    ASSERT_TRUE(a.GetTransFrom().empty());
    a.AddTransition(trans);

    ASSERT_FALSE(a.GetTransFrom().empty());
}

TEST_F(StateTest, DeleteTransition) {
    State a("1", false);
    State b("2");
    Transition trans('b', b);
    a.AddTransition(trans);

    a.DeleteTransition(trans);

    ASSERT_TRUE(a.GetTransFrom().empty());
}

TEST_F(StateTest, AssignmentEmpty) {
    State a("1", false);
    State b("2");
    a = b;

    ASSERT_EQ(a, b);
}

TEST_F(StateTest, AssignmentNotEmpty) {
    State a("1", false);
    State c("3");
    Transition trans('b', c);
    a.AddTransition(trans);
    State b("2");
    b = a;

    ASSERT_EQ(a, b);
}

TEST_F(StateTest, AssignmentTrans) {
    State a("1", false);
    State b("2");
    Transition trans1('b', b);
    Transition trans2('b', a);

    trans1 = trans2;

    ASSERT_EQ(trans1, trans2);
}

TEST_F(StateTest, TransCmp) {
    State a("1", false);
    State b("2");
    Transition trans1('b', b);
    Transition trans2('b', a);

    ASSERT_LT(trans2, trans1);
}

TEST_F(StateTest, Constructors) {
    Automaton a({'a'}, "1");
    
    Automaton b({'a'}, "1", {"1", "2"});

    ASSERT_EQ(a.GetAlphabet(), b.GetAlphabet());
    ASSERT_EQ(a.GetStart(), b.GetStart());
    ASSERT_TRUE(a.GetStates().empty());
    ASSERT_FALSE(b.GetStates().empty());
}

TEST_F(AutomatonTest, AddState) {
    Automaton a({'a'}, "1");

    auto new_state = a.AddState("1");
    auto state = *a.GetStates().find(State("1"));

    ASSERT_EQ(new_state, state);
}

TEST_F(AutomatonTest, ConstructDFA1) {
    Automaton a({'a', 'b'}, "1");

    test_1(a);

    a = a.GetDFA();

    std::ofstream out("DFA_test.doa");
    a.PrintToDoa(out);
    out.close();

    ASSERT_TRUE(compare_doa("DFA_test.doa", "DFA1_right.doa"));
}

TEST_F(AutomatonTest, ConstructDFA2) {
    Automaton a({'a', 'b'}, "1");

    test_2(a);

    a = a.GetDFA();

    std::ofstream out("DFA_test.doa");
    a.PrintToDoa(out);
    out.close();

    ASSERT_TRUE(compare_doa("DFA_test.doa", "DFA2_right.doa"));
}

TEST_F(AutomatonTest, ConstructDFA3) {
    Automaton a({'a', 'b'}, "1");

    test_3(a);

    a = a.GetDFA();

    std::ofstream out("DFA_test.doa");
    a.PrintToDoa(out);
    out.close();

    ASSERT_TRUE(compare_doa("DFA_test.doa", "DFA3_right.doa"));
}

TEST_F(AutomatonTest, ConstructCDFA1) {
    Automaton a({'a', 'b'}, "1");

    test_1(a);

    a = a.GetDFA().GetCompleteDFA();

    std::ofstream out("DFA_test.doa");
    a.PrintToDoa(out);
    out.close();

    ASSERT_TRUE(compare_doa("DFA_test.doa", "CDFA1_right.doa"));
}

TEST_F(AutomatonTest, ConstructCDFA2) {
    Automaton a({'a', 'b'}, "1");

    test_2(a);

    a = a.GetDFA().GetCompleteDFA();

    std::ofstream out("DFA_test.doa");
    a.PrintToDoa(out);
    out.close();

    ASSERT_TRUE(compare_doa("DFA_test.doa", "CDFA2_right.doa"));
}

TEST_F(AutomatonTest, ConstructCDFA3) {
    Automaton a({'a', 'b'}, "1");

    test_3(a);

    a = a.GetDFA().GetCompleteDFA();

    std::ofstream out("DFA_test.doa");
    a.PrintToDoa(out);
    out.close();

    ASSERT_TRUE(compare_doa("DFA_test.doa", "CDFA3_right.doa"));
}

TEST_F(AutomatonTest, ConstructMCDFA1) {
    Automaton a({'a', 'b'}, "1");

    test_1(a);

    a = a.GetDFA().GetCompleteDFA().GetMinimizedCDFA();

    std::ofstream out("DFA_test.doa");
    a.PrintToDoa(out);
    out.close();

    ASSERT_TRUE(compare_doa("DFA_test.doa", "MCDFA1_right.doa"));
}

TEST_F(AutomatonTest, ConstructMCDFA2) {
    Automaton a({'a', 'b'}, "1");

    test_2(a);

    a = a.GetDFA().GetCompleteDFA().GetMinimizedCDFA();

    std::ofstream out("DFA_test.doa");
    a.PrintToDoa(out);
    out.close();

    ASSERT_TRUE(compare_doa("DFA_test.doa", "MCDFA2_right.doa"));
}

TEST_F(AutomatonTest, ConstructMCDFA3) {
    Automaton a({'a', 'b'}, "1");

    test_3(a);

    a = a.GetDFA().GetCompleteDFA().GetMinimizedCDFA();

    std::ofstream out("DFA_test.doa");
    a.PrintToDoa(out);
    out.close();

    ASSERT_TRUE(compare_doa("DFA_test.doa", "MCDFA3_right.doa"));
}