//
// Created by az0t24 on 02.12.22.
//

#ifndef MIPT_FORMAL_PRAC_RULE_H
#define MIPT_FORMAL_PRAC_RULE_H

#include "Character.h"
#include <set>
#include <vector>
#include <string>
#include <map>
#include <queue>

class Rule {
public:
    explicit Rule(const std::string& rule);

    [[nodiscard]] const NotTerminalCharacter& getFrom() const;
    [[nodiscard]] const std::string& getTo() const;
    [[nodiscard]] bool isOrdinary() const;

private:
    NotTerminalCharacter notTerminal_;
    std::string exprTo_;
};

#endif //MIPT_FORMAL_PRAC_RULE_H
