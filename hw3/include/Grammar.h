//
// Created by az0t24 on 03.12.22.
//

#ifndef PROJECT1_GRAMMAR_H
#define PROJECT1_GRAMMAR_H

#include "Rule.h"
#include "Character.h"
#include "State.h"
#include <set>
#include <vector>
#include <string>
#include <map>
#include <queue>

class Grammar {
public:
    Grammar(char start, const std::set<char>& notTerminals, const std::set<char>& terminals,
            const std::vector<std::string>& rules);

    bool checkIsWordInEarley(const std::string& word);

private:
    NotTerminalCharacter start_;
    std::vector<Rule> rules_;
    std::set<NotTerminalCharacter> notTerminals_;
    std::set<TerminalCharacter> terminals_;
    bool isCorrect_ = true;

    static bool checkForScannable(const State& state, const std::string& word) {
        return state.getDotPos() < state.getRule().getTo().size()
               && (state.getRule().getTo()[state.getDotPos()] == '0'
                   || (state.getLength() < word.size()
                       && state.getRule().getTo()[state.getDotPos()] == word[state.getLength()]));
    }

    static bool checkForPredictable(const State& state, const Rule& rule) {
        return state.getDotPos() < state.getRule().getTo().size()
               && state.getRule().getTo()[state.getDotPos()] == rule.getFrom().getChar();
    }

    static bool checkForCompletable(const State& firstState, const State& secondState) {
        return firstState.getDotPos() == firstState.getRule().getTo().size()
               && firstState.getPref() == secondState.getLength()
               && secondState.getDotPos() < secondState.getRule().getTo().size()
               && secondState.getRule().getTo()[secondState.getDotPos()] == firstState.getRule().getFrom().getChar();
    }

    static void scan(const State& state, std::vector<std::set<State>>& states,
                     std::set<State>& newStates, size_t len, size_t wordLen) {
        int delta = (state.getRule().getTo()[state.getDotPos()] == '0') ? 0 : 1;
        State newState(state.getRule(), state.getPref(),
                             state.getLength() + delta, state.getDotPos() + 1);

        if (newState.getLength() == len
            && states[len].find(newState) == states[len].end()) {
            newStates.insert(newState);
        } else if (newState.getLength() == len + 1 && len + 1 <= wordLen) {
            states[len + 1].insert(newState);
        }
    }

    static void predict(const State& state, const Rule& rule, size_t len,
                        const std::vector<std::set<State>>& states, std::set<State>& newStates) {
        State newState(rule, state.getLength(), state.getLength(), 0);

        if (states[len].find(newState) == states[len].end()) {
            newStates.insert(newState);
        }
    }

    static void complete(const State& firstState, const State& secondState, size_t len,
                         const std::vector<std::set<State>>& states, std::set<State>& newStates) {
        State newState(secondState.getRule(), secondState.getPref(),
                       firstState.getLength(), secondState.getDotPos() + 1);

        if (states[len].find(newState) == states[len].end()) {
            newStates.insert(newState);
        }
    }
};

#endif //PROJECT1_GRAMMAR_H
