//
// Created by az0t24 on 03.12.22.
//

#ifndef PROJECT1_STATE_H
#define PROJECT1_STATE_H

#include "Rule.h"

class State {
public:
    State(Rule rule, size_t prefLen_, size_t length, size_t dotPos);

    [[nodiscard]] const Rule& getRule() const;
    [[nodiscard]] size_t getPref() const;
    [[nodiscard]] size_t getLength() const;
    [[nodiscard]] size_t getDotPos() const;

    bool operator==(const State& other) const;
    bool operator<(const State& other) const;

private:
    Rule rule_;
    size_t prefLen_;
    size_t length_;
    size_t dotPos_;
};

#endif //PROJECT1_STATE_H
