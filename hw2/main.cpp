#include <string>
#include <iostream>
#include "include/Grammar.h"

int main(int argc, char** argv) {
    std::set<char> nTerm = {'S', 'A'};
    std::set<char> term = {'a', 'b'};

    std::vector<std::string> rules;//    rules.emplace_back("S->AT");
//    rules.emplace_back("S->AD");
//    rules.emplace_back("F->AT");
//    rules.emplace_back("")
    rules.emplace_back("S->a");

    Grammar gr('S', nTerm, term, rules);

    std::cout << gr.checkIsWordInCYK("a");
    return 0;
}