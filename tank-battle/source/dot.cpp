#include "../include/pch.h"
#include "../include/dot.h"


Dot::Dot(short x, short y) {
    this->x = x;
    this->y = y;
}

short Dot::getX() {
    return this->x;
}

short Dot::getY() {
    return this->y;
}

void Dot::setX(short x) {
    this->x = x;
}

void Dot::setY(short y) {
    this->y = y;
}
