//
// Created by az0t24 on 26.10.22.
//

#ifndef MIPT_FORMAL_PRAC_STATE_H
#define MIPT_FORMAL_PRAC_STATE_H

class State;

#include <vector>
#include <string>
#include <list>
#include <set>
#include <map>

class Transition {
    char letter_;
    State& to_;

public:
    Transition(char letter, const State& to);

    Transition& operator=(const Transition& other);

    bool operator==(const Transition& transition) const;
    bool operator<(const Transition& transition) const;

    char GetLetter() const;
    const State& GetTo() const;
};

class State {
    bool is_terminated_;
    std::string name_;
    std::list<Transition> trans_;

public:
    explicit State(std::string name);
    explicit State(std::string name, bool is_term);
    ~State() = default;

    std::string GetName() const;
    bool IsTerm() const;
    const std::list<Transition>& GetTransFrom() const;

    bool operator==(const State& state) const;
    bool operator<(const State& state) const;
    State& operator=(const State& other);

    void MakeTerminal();
    void AddTransition(const Transition& transition);
    void DeleteTransition(const Transition& transition);

    friend State operator+(const State& first, const State& second);
};

#endif  // MIPT_FORMAL_PRAC_STATE_H
