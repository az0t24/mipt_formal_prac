//
// Created by az0t24 on 03.12.22.
//

#ifndef PROJECT1_GRAMMAR_H
#define PROJECT1_GRAMMAR_H

#include "Rule.h"
#include "Character.h"
#include <set>
#include <vector>
#include <string>
#include <map>
#include <queue>

class Grammar {
public:
    Grammar(char start, const std::set<char>& notTerminals, const std::set<char>& terminals,
            const std::vector<std::string>& rules);

    [[nodiscard]] bool checkIsWordInCYK(const std::string& word) const;

private:
    NotTerminalCharacter start_;
    std::vector<Rule> rules_;
    std::set<NotTerminalCharacter> notTerminals_;
    std::set<TerminalCharacter> terminals_;
    bool isCorrect_ = true;

    [[nodiscard]] bool checkIsEmptyWordIn() const;
};

#endif //PROJECT1_GRAMMAR_H
