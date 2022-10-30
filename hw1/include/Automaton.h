//
// Created by az0t24 on 26.10.22.
//

#ifndef MIPT_FORMAL_PRAC_AUTOMATON_H
#define MIPT_FORMAL_PRAC_AUTOMATON_H

#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <queue>

#include "State.h"

class Automaton {
public:
    explicit Automaton(const std::set<char>& alphabet, const std::string& start) : start_(start), alphabet_(alphabet) {
    }
    explicit Automaton(const std::set<char>& alphabet, const std::string& start, const std::set<std::string>& input)
        : start_(start), alphabet_(alphabet) {
        for (auto& i : input) {
            states_.insert(State(i));
        }
    }
    ~Automaton() = default;

    const State& AddState(const std::string& name);
    void MakeTerminal(const std::string& name);
    void AddTransition(const State& from, const Transition& transition);

    std::set<State>& GetStates();

    Automaton GetDFA();
    Automaton GetCompleteDFA();
    Automaton GetMinimizedCDFA();

    void PrintToDoa(std::ofstream& out);

private:
    std::string start_;
    std::set<char> alphabet_{'a', 'b'};
    std::set<State> states_;

    void DeleteState(const State& state);
    void DeleteTransition(State& state, const Transition& transition);

    // TODO
    void Print() {
        for (auto state : states_) {
            std::cout << state.GetName() << ' ' << (state.IsTerm() ? "terminal" : "not terminal") << std::endl;
            for (auto& trans : state.GetTransFrom()) {
                std::cout << trans.GetLetter() << ' ' << trans.GetTo().GetName() << std::endl;
            }
        }
        std::cout << "/////////////////////////" << std::endl;
    }

    void DeleteNotReachable();
    std::map<std::pair<std::string, char>, std::set<State>> GetReversedTransition();
    void DeleteEpsTransitions();
    std::set<int> ParseStateName(const std::string& name);
};

#endif  // MIPT_FORMAL_PRAC_AUTOMATON_H
