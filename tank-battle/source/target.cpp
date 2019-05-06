#include "../include/target.h"
#include "../include/utils.h"
#include <iostream>


Target::Target(short x, short y, short h, short w, bool is_attacked) : coverage(x, y, h, w) {
    this->is_attacked = is_attacked;
}

Rect Target::getScope() {
    return this->coverage;
}

bool Target::getStatus() {
    return this->is_attacked;
}

void Target::setStatus(bool status) {
    this->is_attacked = status;
}

void Target::show() {
    short m_left = this->coverage.getX();
    short m_top = this->coverage.getY();
    short m_right = this->coverage.getW() + m_left;
    short m_bottem = this->coverage.getH() + m_top;

    switch (this->is_attacked) {
    case false:
        for (short i = m_left; i < m_right; ++i) {
            for (short j = m_top; j < m_bottem; ++j) {
                Utils::setCursorPosition(i, j);
                std::cout << "@";
            }
        }
        break;

    case true:
        for (short i = m_left; i < m_right; ++i) {
            for (short j = m_top; j < m_bottem; ++j) {
                Utils::setCursorPosition(i, j);
                std::cout << " ";
            }
        }
    }
}
