//
// Created by az0t24 on 03.12.22.
//

#include "State.h"

State::State(Rule rule, size_t pref_len, size_t length, size_t dotPos) : rule_(std::move(rule)) {
    prefLen_ = pref_len;
    length_ = length;
    dotPos_ = dotPos;
}

[[nodiscard]] const Rule& State::getRule() const {
    return rule_;
}

[[nodiscard]] size_t State::getPref() const {
    return prefLen_;
}

[[nodiscard]] size_t State::getLength() const {
    return length_;
}

[[nodiscard]] size_t State::getDotPos() const {
    return dotPos_;
}

bool State::operator==(const State& other) const {
    return rule_ == other.getRule() && length_ == other.getLength() &&
           prefLen_ == other.getPref() && dotPos_ == other.getDotPos();
}

bool State::operator<(const State& other) const {
    if (rule_ == other.getRule()) {
        if (prefLen_ == other.getPref()) {
            if (dotPos_ == other.getDotPos()) {
                return length_ < other.getLength();
            }
            return dotPos_ < other.getDotPos();
        }
        return prefLen_ < other.getPref();
    }
    return rule_ < other.getRule();
}