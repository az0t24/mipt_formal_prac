//
// Created by az0t24 on 30.10.22.
//

#include "Test.h"
#include "Grammar.h"

TEST_F(CharacterTest, Constructors) {
    Character c1('a');
    Character c2(c1);

    ASSERT_EQ(c1, c2);
    ASSERT_EQ(c1.getChar(), c2.getChar());
}

TEST_F(CharacterTest, ConstructorsNotTerm) {
    NotTerminalCharacter c1('A');
    NotTerminalCharacter c2(c1);

    ASSERT_EQ(c1, c2);
    ASSERT_EQ(c1.getChar(), c2.getChar());
}

TEST_F(CharacterTest, ConstructorsTerm) {
    TerminalCharacter c1('a');
    TerminalCharacter c2(c1);

    ASSERT_EQ(c1, c2);
    ASSERT_EQ(c1.getChar(), c2.getChar());
}

TEST_F(CharacterTest, CheckNotTerm) {
    ASSERT_FALSE(NotTerminalCharacter::check('a'));
    ASSERT_TRUE(NotTerminalCharacter::check('A'));
}

TEST_F(CharacterTest, CheckTerm) {
    ASSERT_FALSE(TerminalCharacter::check('A'));
    ASSERT_TRUE(TerminalCharacter::check('a'));
}

TEST_F(CharacterTest, Comparing) {
    Character c1('a');
    Character c2('b');

    ASSERT_TRUE(c1 < c2);
    ASSERT_TRUE(c1.getChar() < c2.getChar());
}

TEST_F(RuleTest, Constructor) {
    Rule rule("S->a");
    ASSERT_EQ(rule.getFrom().getChar(), 'S');
    ASSERT_EQ(rule.getTo(), "a");
}

TEST_F(RuleTest, OrdinaryRule) {
    Rule rule("S->a");
    ASSERT_TRUE(rule.isOrdinary());
}

TEST_F(RuleTest, NotOrdinaryRule) {
    Rule rule("S->AB");
    ASSERT_TRUE(!rule.isOrdinary());
}

TEST_F(RuleTest, NotOrdinaryRuleTo) {
    Rule rule("S->AB");
    ASSERT_EQ(rule.getTo(), "AB");
}

TEST_F(GrammarTest, CheckWordIn1) {
    std::set<char> nTerm = {'S', 'A'};
    std::set<char> term = {'a', 'b'};

    std::vector<std::string> rules;
    rules.emplace_back("S->a");

    Grammar gr('S', nTerm, term, rules);

    ASSERT_TRUE(gr.checkIsWordInCYK("a"));
}

TEST_F(GrammarTest, CheckWordIn2) {
    std::set<char> nTerm = {'S', 'A'};
    std::set<char> term = {'a', 'b'};

    std::vector<std::string> rules;
    rules.emplace_back("S->b");

    Grammar gr('S', nTerm, term, rules);

    ASSERT_FALSE(gr.checkIsWordInCYK("a"));
}

TEST_F(GrammarTest, CheckEmptyWord1) {
    std::set<char> nTerm = {'S'};
    std::set<char> term = {'a', 'b'};

    std::vector<std::string> rules;
    rules.emplace_back("S->0");

    Grammar gr('S', nTerm, term, rules);

    ASSERT_TRUE(gr.checkIsWordInCYK("0"));
}

TEST_F(GrammarTest, CheckEmptyWord2) {
    std::set<char> nTerm = {'S'};
    std::set<char> term = {'a', 'b'};

    std::vector<std::string> rules;
    rules.emplace_back("S->a");

    Grammar gr('S', nTerm, term, rules);

    ASSERT_FALSE(gr.checkIsWordInCYK("0"));
}

TEST_F(GrammarTest, WrongGrammar1) {
    std::set<char> nTerm = {'S'};
    std::set<char> term = {'a', 'b'};

    std::vector<std::string> rules;
    rules.emplace_back("S-a");

    Grammar gr('S', nTerm, term, rules);

    ASSERT_FALSE(gr.checkIsWordInCYK("a"));
}

TEST_F(GrammarTest, WrongGrammar2) {
    std::set<char> nTerm = {'s'};
    std::set<char> term = {'a', 'b'};

    std::vector<std::string> rules;
    rules.emplace_back("S->a");

    Grammar gr('S', nTerm, term, rules);

    ASSERT_FALSE(gr.checkIsWordInCYK("a"));
}

TEST_F(GrammarTest, WrongGrammar3) {
    std::set<char> nTerm = {'S'};
    std::set<char> term = {'a', 'b'};

    std::vector<std::string> rules;
    rules.emplace_back("S>>a");

    Grammar gr('S', nTerm, term, rules);

    ASSERT_FALSE(gr.checkIsWordInCYK("a"));
}

TEST_F(GrammarTest, WrongGrammar4) {
    std::set<char> nTerm = {'S'};
    std::set<char> term = {'A', 'b'};

    std::vector<std::string> rules;
    rules.emplace_back("S->a");

    Grammar gr('S', nTerm, term, rules);

    ASSERT_FALSE(gr.checkIsWordInCYK("a"));
}

TEST_F(GrammarTest, WrongGrammar5) {
    std::set<char> nTerm = {'S'};
    std::set<char> term = {'a', 'b'};

    std::vector<std::string> rules;
    rules.emplace_back("S->123");

    Grammar gr('S', nTerm, term, rules);

    ASSERT_FALSE(gr.checkIsWordInCYK("a"));
}

TEST_F(GrammarTest, DoubleRules) {
    std::set<char> nTerm = {'S', 'A'};
    std::set<char> term = {'a', 'b'};

    std::vector<std::string> rules;
    rules.emplace_back("S->AS");
    rules.emplace_back("S->0");
    rules.emplace_back("A->a");

    Grammar gr('S', nTerm, term, rules);

    ASSERT_FALSE(gr.checkIsWordInCYK("aaa"));
}

TEST_F(GrammarTest, BigTest1) {
    std::set<char> nTerm = {'S', 'A'};
    std::set<char> term = {'a', 'b'};

    std::vector<std::string> rules = {"S->AT", "S->AD", "F->AT", "F->AD", "D->FA", "T->BU",
                                      "T->CT", "U->VA", "U->CU", "V->BX", "V->a", "X->AY",
                                      "Y->VC", "A->a", "B->b", "C->c"};

    Grammar gr('S', nTerm, term, rules);

    ASSERT_TRUE(gr.checkIsWordInCYK("abcbaaca"));
}