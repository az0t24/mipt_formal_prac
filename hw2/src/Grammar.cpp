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

bool Grammar::checkIsEmptyWordIn() const {
    for (const auto& rule : rules_) {
        if (rule.getFrom() == start_ && rule.getTo() == "0") {
            return true;
        }
    }
    return false;
}

bool Grammar::checkIsWordInCYK(const std::string& word) const {
    if (!isCorrect_) {
        return false;
    }

    if (word == "0") {
        return checkIsEmptyWordIn();
    }

    size_t len = word.length();
    size_t n = 27; // всего букв 26 + может быть другая стартовая
    std::vector<std::vector<std::vector<bool>>>d(n);
    for (size_t i = 0; i < n; ++i) {
        d[i].assign(len + 1, std::vector<bool>(len + 1, false));
    }

    // Обработаем одиночные правила
    for (const auto& rule : rules_) {
        if (rule.isOrdinary()) {
            for (size_t i = 0; i < len; ++i) {
                if (rule.getTo()[0] == word[i]) {
                    d[rule.getFrom().getChar() - 'A'][i][i + 1] = true;
                }
            }
        }
    }

    // Остались двойные правила
    for (size_t l = 2; l <= len; ++l) {
        for (size_t i = 0; i <= len - l; ++i) {
            size_t j = i + l;
            for (size_t k = i + 1; k <= j - 1; ++k) {
                for (const auto& rule : rules_) {
                    if (!rule.isOrdinary()) {
                        if (d[rule.getTo()[0] - 'A'][i][k] && d[rule.getTo()[1] - 'A'][k][j]) {
                            d[rule.getFrom().getChar() - 'A'][i][j] = true;
                        }
                    }
                }
            }
        }
    }

    if (d[start_.getChar() - 'A'][0][len]) {
        return true;
    }
    return false;
}