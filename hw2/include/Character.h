//
// Created by az0t24 on 03.12.22.
//

#ifndef PROJECT1_CHARACTER_H
#define PROJECT1_CHARACTER_H

class Character {
protected:
    char character_;
public:
    explicit Character(char c) {
        character_ = c;
    }
    Character(const Character& character);

    [[nodiscard]] char getChar() const;
    bool operator<(const Character& another) const;
    bool operator==(const Character& another) const;
};

class NotTerminalCharacter : public Character {
public:
    explicit NotTerminalCharacter(char c) : Character(c) {
    }

    NotTerminalCharacter(const NotTerminalCharacter& c) : Character(c.getChar()) {
    }

    static bool check(char character) {
        if (character > 'Z' || character < 'A') {
            return false;
        }
        return true;
    }
};

class TerminalCharacter : public Character {
public:
    explicit TerminalCharacter(char c) : Character(c){
    }

    TerminalCharacter(const TerminalCharacter& c) : Character(c.getChar()) {
    }

    static bool check(char character) {
        if (character > 'z' || character < 'a') {
            if (character == '0') return true;
            return false;
        }
        return true;
    }
};

#endif //PROJECT1_CHARACTER_H
