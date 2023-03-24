//
// Created by az0t24 on 02.12.22.
//

#include "Rule.h"

Rule::Rule(const std::string& rule) : notTerminal_(rule.at(0)) {
    exprTo_ = rule.substr(3);
}

[[nodiscard]] const NotTerminalCharacter& Rule::getFrom() const {
    return notTerminal_;
}

[[nodiscard]] const std::string& Rule::getTo() const {
    return exprTo_;
}

[[nodiscard]] bool Rule::isOrdinary() const {
    return exprTo_.size() == 1;
}