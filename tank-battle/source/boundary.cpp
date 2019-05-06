#include "../include/boundary.h"
#include "../include/utils.h"
#include <string>
#include <iostream>


Boundary::Boundary(short x, short y, const std::string &shape) :pos(x, y) {
    this->shape = shape;
}

void Boundary::show() {
    Utils::setCursorPosition(this->pos.getX(), this->pos.getY());
    std::cout << this->shape;
}
