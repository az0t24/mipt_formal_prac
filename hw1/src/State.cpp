//
// Created by az0t24 on 26.10.22.
//

#include "../include/State.h"

State::State(std::string name) {
    name_ = name;
    is_terminated_ = false;
}

State::State(std::string name, bool is_term) {
    name_ = name;
    is_terminated_ = is_term;
}

std::string State::GetName() const {
    return name_;
}

bool State::IsTerm() const {
    return is_terminated_;
}

bool State::operator==(const State& state) const {
    return name_ == state.GetName();
}

bool State::operator<(const State& state) const {
    return GetName() < state.GetName();
}

State operator+(const State& first, const State& second) {
    return State(first.GetName() + second.GetName(), first.IsTerm() + second.IsTerm());
}

const std::list<Transition>& State::GetTransFrom() const {
    return trans_;
}

void State::DeleteTransition(const Transition& transition) {
    trans_.remove(transition);
}

void State::AddTransition(const Transition& transition) {
    trans_.emplace_back(transition);
}

State& State::operator=(const State& other) {
    is_terminated_ = other.IsTerm();
    name_ = other.GetName();
    if (other.GetTransFrom().empty()) {
        return *this;
    }
    trans_ = const_cast<std::list<Transition>&>(other.GetTransFrom());

    return *this;
}

void State::MakeTerminal() {
    is_terminated_ = true;
}

Transition::Transition(char letter, const State& to) : to_(const_cast<State&>(to)) {
    letter_ = letter;
}

bool Transition::operator==(const Transition& transition) const {
    return letter_ == transition.GetLetter() && to_.GetName() == transition.GetTo().GetName();
}

char Transition::GetLetter() const {
    return letter_;
}

const State& Transition::GetTo() const {
    return to_;
}

bool Transition::operator<(const Transition& transition) const {
    return GetTo() < transition.GetTo() || (GetTo() == transition.GetTo() && letter_ < transition.GetLetter());
}

Transition& Transition::operator=(const Transition& other) {
    letter_ = other.GetLetter();
    to_ = other.GetTo();

    return *this;
}
