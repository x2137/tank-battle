#include "../include/pch.h"
#include "../include/wall.h"
#include "../include/utils.h"
#include <string>
#include <iostream>


Wall::Wall(short x, short y, short h, short w, const std::string &type) : coverage(x, y, h, w) {
    this->type = type;
}

std::string Wall::getWallType() {
    return this->type;
}

Rect Wall::getScope() {
    return this->coverage;
}

bool Wall::getTheStatus() {
    return this->should_disappear;
}

void Wall::setTheStatus(bool status) {
    this->should_disappear = status;
}

void Wall::show() {
    short m_left = this->getScope().getX();
    short m_top = this->getScope().getY();
    short m_right = this->getScope().getW() + m_left;
    short m_bottem = this->getScope().getH() + m_top;
    for (short i = m_left; i < m_right; ++i) {
        for (short j = m_top; j < m_bottem; ++j) {
            Utils::setCursorPosition(i, j);  // 设置光标位置，然后打印
            std::cout << this->type;
        }
    }
}

void Wall::clear() {
    short m_left = this->getScope().getX();
    short m_top = this->getScope().getY();
    short m_right = this->getScope().getW() + m_left;
    short m_bottem = this->getScope().getH() + m_top;
    for (short i = m_left; i < m_right; ++i) {
        for (short j = m_top; j < m_bottem; ++j) {
            Utils::setCursorPosition(i, j);
            std::cout << "  ";
        }
    }
}
