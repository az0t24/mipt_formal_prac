//
// Created by az0t24 on 26.10.22.
//

#include "../include/Automaton.h"

const State& Automaton::AddState(const std::string& name) {
    auto result = states_.insert(State(name));
    return *result.first;
}

void Automaton::DeleteState(const State& state) {
    states_.erase(state);
}

void Automaton::AddTransition(const State& from, const Transition& transition) {
    auto st = states_.find(from);
    const_cast<State&>(*st).AddTransition(transition);
}

void Automaton::DeleteTransition(State& state, const Transition& transition) {
    state.DeleteTransition(transition);
}

std::set<State>& Automaton::GetStates() {
    return states_;
}

const std::set<char>& Automaton::GetAlphabet() const {
    return alphabet_;
}

const std::string& Automaton::GetStart() const {
    return start_;
}

void Automaton::DeleteEpsTransitions() {
    bool is_all_eps_deleted = false;

    while (!is_all_eps_deleted) {
        is_all_eps_deleted = true;

        for (const State& state : GetStates()) {
            const std::list<Transition> trans_from = state.GetTransFrom();

            for (auto& trans : trans_from) {
                if (trans.GetLetter() == '0') {
                    is_all_eps_deleted = false;
                    auto& state_to = trans.GetTo();

                    if (state_to.IsTerm()) {
                        MakeTerminal(state.GetName());
                    }

                    for (auto trans_to : state_to.GetTransFrom()) {
                        AddTransition(const_cast<State&>(state), trans_to);
                    }

                    DeleteTransition(const_cast<State&>(state), trans);
                }
            }
        }
    }
}

std::set<int> Automaton::ParseStateName(const std::string& name) {
    // Парсим имя состояния (например, 2_5 получено через 2+5), чтобы рассматривать исходящие ребра
    std::stringstream ss(name);
    int initial_state = 0;
    std::set<int> states_from;

    while (ss >> initial_state) {
        states_from.insert(initial_state);
        if (ss.peek() == '_') {
            ss.ignore();
        }
    }

    return states_from;
}

Automaton Automaton::GetDFA() {
    Automaton dfa(alphabet_, start_);
    Automaton copy_auto(*this);

    copy_auto.DeleteEpsTransitions();

    size_t states_num = copy_auto.GetStates().size();
    size_t i = 0;
    std::set<State> old_states = copy_auto.GetStates();
    auto begin = old_states.begin();
    std::set<State> diff;  // Чтобы смотреть, какие новые состояния появились и их нужно рассмотреть
    while (i != states_num) {
        const State& state = *begin;

        // Парсим имя состояния (например, 2_5 получено через 2+5), чтобы рассматривать исходящие ребра
        std::set<int> states_from = ParseStateName(state.GetName());
        std::map<char, std::set<int>> transitions_from;

        for (int initial_state : states_from) {
            const State& state_from = *copy_auto.GetStates().find(State(std::to_string(initial_state)));
            for (const Transition& trans : state_from.GetTransFrom()) {
                const char letter = trans.GetLetter();

                std::set<int> states_to = ParseStateName(trans.GetTo().GetName());

                for (int elem : states_to) {
                    transitions_from[letter].insert(elem);
                }
            }
        }

        if (!dfa.GetStates().contains(State(state.GetName()))) {
            dfa.AddState(state.GetName());
        }

        State& state_dfa = const_cast<State&>(*dfa.GetStates().find(State(state.GetName())));

        if (state.IsTerm()) {
            dfa.MakeTerminal(state.GetName());
        }

        for (char symbol : alphabet_) {
            if (!transitions_from[symbol].empty()) {
                std::string name;
                bool is_term = false;

                for (auto elem : transitions_from[symbol]) {
                    name += std::to_string(elem) + '_';
                    is_term |= copy_auto.GetStates().find(State(std::to_string(elem)))->IsTerm();
                }

                if (*(--name.end()) == '_') {
                    name = name.substr(0, name.size() - 1);
                }

                if (!dfa.GetStates().contains(State(name))) {
                    dfa.AddState(name);
                }
                const State& new_state = *dfa.GetStates().find(State(name));

                if (is_term) {
                    dfa.MakeTerminal(new_state.GetName());
                }

                Transition new_transition(symbol, new_state);
                dfa.AddTransition(state_dfa, new_transition);
            }
        }

        i++;
        begin++;
        if (i == states_num) {
            states_num = dfa.GetStates().size();
            old_states.merge(diff);
            std::set_difference(dfa.GetStates().begin(), dfa.GetStates().end(), old_states.begin(), old_states.end(),
                                std::inserter(diff, diff.begin()));
            begin = diff.begin();
        }
    }

    dfa.DeleteNotReachable();

    return dfa;
}

void Automaton::MakeTerminal(const std::string& name) {
    (const_cast<State&>(*states_.find(State(name)))).MakeTerminal();
}

void DFS(const State& state, std::set<State>& reachable) {
    for (auto& transition : state.GetTransFrom()) {
        const State& to = transition.GetTo();

        if (!reachable.contains(to)) {
            reachable.insert(to);
            DFS(to, reachable);
        }
    }
}

void Automaton::DeleteNotReachable() {
    std::set<State> reachable;

    const State& state = *states_.find(State(start_));
    reachable.insert(state);

    // поиском в глубину находим все достижимые, дальше оставляем в качестве states_ достижимые, остальные удаляем.
    DFS(state, reachable);

    std::set<State> diff;
    std::set_difference(states_.begin(), states_.end(), reachable.begin(), reachable.end(),
                        std::inserter(diff, diff.begin()));

    for (auto elem : diff) {
        states_.erase(elem);
    }
}

void Automaton::PrintToDoa(std::ofstream& out) {
    out << "DOA: v1\n"
        << "Start: " << start_ << '\n';

    out << "Acceptance: ";
    std::string acceptance;
    for (auto elem : states_) {
        if (elem.IsTerm()) {
            acceptance += elem.GetName() + " & ";
        }
    }
    if (!acceptance.empty()) {
        acceptance = acceptance.substr(0, acceptance.size() - 3);
    }
    out << acceptance << '\n';

    out << "--BEGIN--" << '\n';

    for (auto elem : states_) {
        out << "State: " << elem.GetName() << '\n';
        for (auto trans : elem.GetTransFrom()) {
            out << "-> " << trans.GetLetter() << ' ' << trans.GetTo().GetName() << '\n';
        }
    }

    out << "--END--" << '\n';
}

Automaton Automaton::GetCompleteDFA() {
    Automaton complete_dfa(*this);

    const State& stock = complete_dfa.AddState("Stock");
    bool is_stock_req = false;

    for (auto elem : complete_dfa.GetStates()) {
        std::set<char> letter_used;

        for (auto trans : elem.GetTransFrom()) {
            letter_used.insert(trans.GetLetter());
        }

        std::set<char> differ;
        std::set_difference(alphabet_.begin(), alphabet_.end(), letter_used.begin(), letter_used.end(),
                            std::inserter(differ, differ.begin()));

        if (!differ.empty() && elem.GetName() != "Stock") {
            is_stock_req = true;
        }

        for (char symbol : differ) {
            Transition trans(symbol, stock);
            complete_dfa.AddTransition(elem, trans);
        }
    }

    if (!is_stock_req) {
        complete_dfa.DeleteState(stock);
    }

    return complete_dfa;
}

Automaton Automaton::GetMinimizedCDFA() {
    Automaton minimized(alphabet_, "0");

    std::map<std::pair<std::string, char>, std::set<State>> invert = GetReversedTransition();

    std::map<std::string, int> class_of_equiv;
    std::map<int, std::set<State>> partitioning_classes;

    for (auto state : states_) {
        if (state.IsTerm()) {
            partitioning_classes[1].insert(state);
            class_of_equiv[state.GetName()] = 1;
        } else {
            partitioning_classes[0].insert(state);
            class_of_equiv[state.GetName()] = 0;
        }
    }

    std::queue<std::pair<std::set<State>, char>> queue;

    for (char c : alphabet_) {
        queue.push(std::make_pair(partitioning_classes[1], c));
        queue.push(std::make_pair(partitioning_classes[0], c));
    }

    while (!queue.empty()) {
        std::set<State> states = queue.front().first;
        char c = queue.front().second;
        queue.pop();

        std::map<int, std::set<State>> involved;

        for (auto from : states) {
            for (auto to : invert[{from.GetName(), c}]) {
                int class_to = class_of_equiv[to.GetName()];
                if (involved[class_to].empty()) {
                    involved[class_to] = {};
                }

                involved[class_to].insert(to);
            }
        }

        for (int state_class = 0; state_class < class_of_equiv.size(); ++state_class) {
            if (!involved[state_class].empty()) {
                if (involved[state_class].size() < partitioning_classes[state_class].size()) {
                    partitioning_classes[partitioning_classes.size()] = {};
                }

                int new_state_class = partitioning_classes.size();
                for (auto state : involved[state_class]) {
                    partitioning_classes[state_class].erase(state);
                    partitioning_classes[new_state_class].insert(state);
                }

                if (partitioning_classes[new_state_class].size() > partitioning_classes[state_class].size()) {
                    std::swap(partitioning_classes[state_class], partitioning_classes[new_state_class]);
                }

                for (auto state : partitioning_classes[new_state_class]) {
                    class_of_equiv[state.GetName()] = new_state_class;
                }

                for (char symbol : alphabet_) {
                    queue.push({partitioning_classes[new_state_class], symbol});
                }
            }
        }
    }

    for (int i = 0; i < partitioning_classes.size(); ++i) {
        if (partitioning_classes[i].empty()) {
            continue;
        }

        auto state = *partitioning_classes[i].begin();
        for (auto trans : state.GetTransFrom()) {
            int class_to = class_of_equiv[trans.GetTo().GetName()];
            char letter = trans.GetLetter();
            const State& from = minimized.AddState(std::to_string(i));
            if (state.IsTerm()) {
                minimized.MakeTerminal(from.GetName());
            }
            const State& to = minimized.AddState(std::to_string(class_to));
            Transition transition(letter, to);
            minimized.AddTransition(from, transition);
        }
    }

    return minimized;
}
std::map<std::pair<std::string, char>, std::set<State>> Automaton::GetReversedTransition() {
    std::map<std::pair<std::string, char>, std::set<State>> result;

    for (auto& state : states_) {
        for (auto trans : state.GetTransFrom()) {
            result[std::make_pair(trans.GetTo().GetName(), trans.GetLetter())].insert(state);
        }
    }

    return result;
}
