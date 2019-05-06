#include "../include/pch.h"
#include "../include/rect.h"


Rect::Rect(short x, short y, short h, short w) : Dot(x, y) {
    this->h = h;
    this->w = w;
}

Rect::Rect(const Rect &new_one) {
    this->x = new_one.x;
    this->y = new_one.y;
    this->h = new_one.h;
    this->w = new_one.w;
}

Rect & Rect::operator=(const Rect &new_one) {
    if (this != &new_one) {
        this->x = new_one.x;
        this->y = new_one.y;
        this->h = new_one.h;
        this->w = new_one.w;
    }
    return *this;
}

bool Rect::operator==(const Rect &new_one) {
    if ((this->x == new_one.x) && (this->y == new_one.y) && (this->h == new_one.h) && (this->w == new_one.w)) {
        return true;
    }
    else return false;
}

short Rect::getH() {
    return this->h;
}

short Rect::getW() {
    return this->w;
}

void Rect::setH(short h) {
    this->h = h;
}

void Rect::setW(short w) {
    this->w = w;
}
