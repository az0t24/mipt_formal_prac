#include <string>
#include "include/State.h"
#include "include/Automaton.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "I need 2 files to work!" << std::endl;

        return 1;
    }

    std::ifstream in(argv[1]);
    Automaton automaton(in);
    in.close();

    auto dfa = automaton.GetDFA();
    auto complete_dfa = dfa.GetCompleteDFA();
    auto min_dfa = complete_dfa.GetMinimizedCDFA();

    std::ofstream out;
    out.open(argv[2]);
    min_dfa.PrintToDoa(out);
    out.close();

    return 0;
}