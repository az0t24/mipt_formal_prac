//
// Created by az0t24 on 03.12.22.
//

#include "Grammar.h"

Grammar::Grammar(char start, const std::set<char> &notTerminals, const std::set<char> &terminals,
                 const std::vector<std::string> &rules) : start_(start) {
    for (char character : notTerminals) {
        if (!NotTerminalCharacter::check(character)) {
            isCorrect_ = false;
        }

        notTerminals_.emplace(character);
    }

    for (char character : terminals) {
        if (!TerminalCharacter::check(character)) {
            isCorrect_ = false;
        }

        terminals_.emplace(character);
    }

    for (const std::string& rule : rules) {
        if (rule.size() < 4 || !NotTerminalCharacter::check(rule[0])
            || rule[1] != '-' || rule[2] != '>') {
            isCorrect_ = false;
        }

        for (size_t i = 3; i < rule.size(); ++i) {
            if (!NotTerminalCharacter::check(rule[i]) && !TerminalCharacter::check(rule[i])) {
                isCorrect_ = false;
            }
        }

        rules_.emplace_back(rule);
    }
}

bool Grammar::checkIsWordInEarley(const std::string& word) {
    if (!isCorrect_) {
        return false;
    }

    size_t wordLen = word.size();
    std::vector<std::set<State>> states(wordLen + 1);
    State start(Rule("$->S"), 0, 0, 0);
    State end(Rule("$->S"), 0, wordLen, 1);
    states[0] = {start};
    std::set<State> newStates;

    for (size_t currSymbol = 0; currSymbol <= wordLen; ++currSymbol) {
        newStates = states[currSymbol];

        while (!newStates.empty()) {
            State currState = *newStates.begin();
            newStates.erase(newStates.begin());

            if (checkForScannable(currState, word)) {
                scan(currState, states, newStates, currSymbol, wordLen);
            }

            for (const auto& rule: rules_) {
                if (checkForPredictable(currState, rule)) {
                    predict(currState, rule, currSymbol, states, newStates);
                }
            }

            for (const auto& anotherState: states[currSymbol]) {
                if (checkForCompletable(anotherState, currState)) {
                    complete(anotherState, currState, currSymbol, states, newStates);
                }
            }

            for (const auto& anotherState: states[currState.getPref()]) {
                if (checkForCompletable(currState, anotherState)) {
                    complete(currState, anotherState, currSymbol, states, newStates);
                }
            }

            states[currSymbol].insert(currState);
        }
    }

    return states[wordLen].find(end) != states[wordLen].end();
}
