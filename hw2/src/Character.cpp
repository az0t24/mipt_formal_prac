//
// Created by az0t24 on 03.12.22.
//

#include "Character.h"

Character::Character(const Character& character) {
    character_ = character.getChar();
}

bool Character::operator<(const Character& another) const {
    return character_ < another.getChar();
}

[[nodiscard]] char Character::getChar() const {
    return character_;
}

bool Character::operator==(const Character &another) const {
    return character_ == another.getChar();
}
