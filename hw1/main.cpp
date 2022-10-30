#include <string>
#include "include/State.h"
#include "include/Automaton.h"

void add(Automaton& a, std::string first, std::string second, char letter) {
    const State& from = a.AddState(first);
    const State& to = a.AddState(second);
    Transition transition(letter, to);
    a.AddTransition(from, transition);
}

void mark_term(Automaton& a, std::string state) {
    a.MakeTerminal(state);
}

void test1_a(Automaton& test2) {
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

int main(int argc, char** argv) {
    std::ofstream out;
    out.open(argv[1]);

    Automaton test1({'a', 'b'}, "1");
    std::set<std::string> test{"1", "2", "3"};

    Automaton test2({'a', 'b'}, "1");

    test_3(test2);

    auto dfa = test2.GetDFA();
    auto complete_dfa = dfa.GetCompleteDFA();
    auto min_dfa = complete_dfa.GetMinimizedCDFA();

    min_dfa.PrintToDoa(out);

    out.close();
    return 0;
}