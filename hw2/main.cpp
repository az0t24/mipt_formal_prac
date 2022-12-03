#include <string>
#include <iostream>
#include "include/Grammar.h"

int main(int argc, char** argv) {
    std::set<char> nTerm = {'S', 'A'};
    std::set<char> term = {'a', 'b'};

    std::vector<std::string> rules;
    rules.emplace_back("S->a");

    Grammar gr('S', nTerm, term, rules);

    std::cout << gr.checkIsWordInCYK("a");
    return 0;
}