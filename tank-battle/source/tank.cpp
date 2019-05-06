#include "../include/tank.h"
#include "../include/utils.h"
#include <iostream>


Tank::Tank(short x, short y, short h, short w, Direction d, short blood, short life, bool attack, short speed) : scope(x, y, h, w) {
    this->my_direction = d;
    this->blood_volume = blood;
    this->is_attacked = attack;
    this->life = life;
    this->speed = speed;
    this->pre_scope = new Rect(x, y, h, w);
}

/*
Tank::~Tank() {
    if (this->pre_scope != nullptr) delete this->pre_scope;
}
*/

bool Tank::operator==(const Tank &new_one) {
    if ((this->scope == new_one.scope) && (*(this->pre_scope) == *(new_one.pre_scope))) return true;
    else return false;
}

void Tank::show() {
    switch (this->my_direction) {
    case UP:
        this->showUp();
        break;
    case DOWN:
        this->showDown();
        break;
    case LEFT:
        this->showLeft();
        break;
    case RIGHT:
        this->showRight();
        break;
    }
}

void Tank::move() {
    // 在移动之前需要记录当前位置，为之后在显示新位置之前擦除旧位置的显示
    *(this->pre_scope) = this->scope;

    short step = this->speed;
    short m_left = this->scope.getX();
    short m_top = this->scope.getY();

    switch (this->my_direction) {  // 条件判断是否超出边界
    case UP:
        if (this->is_overlapped) break;
        if(this->scope.getY() - step > 0) this->scope.setY(m_top - step);
        break;
    case DOWN:
        if (this->is_overlapped) break;
        if(this->scope.getY() + step < 52) this->scope.setY(m_top + step);
        break;
    case LEFT:
        if (this->is_overlapped) break;
        if(this->scope.getX() - step > 0) this->scope.setX(m_left - step);
        break;
    case RIGHT:
        if (this->is_overlapped) break;
        if(this->scope.getX() + step < 67) this->scope.setX(m_left + step);
        break;
    }
}

void Tank::clear() {
    short p_left = this->pre_scope->getX();
    short p_top = this->pre_scope->getY();
    short p_right = this->pre_scope->getW() + p_left;
    short p_bottem = this->pre_scope->getH() + p_top;

    for (auto i = p_left; i < p_right; ++i) {
        for (auto j = p_top; j < p_bottem; ++j) {
            Utils::setCursorPosition(i, j);
            std::cout << "  ";  // 打印两个空格
        }
    }
}

void Tank::setOverlapStatus(bool status) {
    this->is_overlapped = status;
}

void Tank::setScope(const Rect &new_one) {
    this->scope = new_one;
}

void Tank::decreaseBloodVolume(short value) {
    this->blood_volume -= value;
}

void Tank::decreaseLife() {
    --(this->life);
}

void Tank::changeDirection(Direction new_direction) {
    this->my_direction = new_direction;
}

short Tank::getBloodVolume() {
    return this->blood_volume;
}

short Tank::getLife() {
    return this->life;
}

bool Tank::getStatus() {
    return this->is_attacked;
}

Rect Tank::getScope() {
    return this->scope;
}

Direction Tank::getMyDirection() {
    return this->my_direction;
}

Rect Tank::getPreScope() {
    return *(this->pre_scope);
}

bool Tank::getOverlapStatus() {
    return this->is_overlapped;
}
