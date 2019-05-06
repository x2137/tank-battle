#include "../include/bullet.h"
#include "../include/utils.h"
#include <iostream>

using std::cout;


Bullet::Bullet(BombType type, std::string who_own_me, Direction the_direction, short x, short y, int color, short speed, short h, short w, const std::string &shape) : scope(x, y, h, w), pre_scope(x, y, h, w) {
    this->type = type;
    this->who_own_me = who_own_me;
    this->my_direction = the_direction;
    this->my_shape = shape;
    this->speed = speed;
    this->color = color;
}

bool Bullet::operator==(const Bullet &new_one) {
    // 通过归属，方向以及位置就可以判断是不是同一个炸弹
    if ((this->who_own_me == new_one.who_own_me) && (this->my_direction == new_one.my_direction) && (this->scope == new_one.scope)) {
        return true;
    }

    return false;
}

bool Bullet::getMyStatus() {
    return this->should_disappear;
}

Rect Bullet::getMyScope() {
    return this->scope;
}

Rect Bullet::getPreScope() {
    return this->pre_scope;
}

BombType Bullet::getMyType() {
    return this->type;
}

Direction Bullet::getMyDirection() {
    return this->my_direction;
}

std::string Bullet::getTheOwner() {
    return this->who_own_me;
}

void Bullet::setMyStatus(bool status) {
    this->should_disappear = status;
}

void Bullet::setMyType(BombType the_type) {
    this->type = the_type;
}

void Bullet::clear() {
    short m_x = this->pre_scope.getX();
    short m_y = this->pre_scope.getY();

    Utils::setCursorPosition(m_x, m_y);
    cout << " ";
}

void Bullet::move() {
    short m_x = this->scope.getX();
    short m_y = this->scope.getY();
    // 改变位置之前需要记住当前位置
    this->pre_scope.setX(m_x);
    this->pre_scope.setY(m_y);

    switch (this->my_direction) {
    case UP:
        if(this->scope.getY() - this->speed > 0) this->scope.setY(m_y - this->speed);
        else this->should_disappear = true;  // 超出边界，消失理所当然
        break;
    case DOWN:
        if (this->scope.getY() + this->speed < 52) this->scope.setY(m_y + this->speed);
        else this->should_disappear = true;
        break;
    case LEFT:
        if (this->scope.getX() - this->speed > 0) this->scope.setX(m_x - this->speed);
        else this->should_disappear = true;
        break;
    case RIGHT:
        if (this->scope.getX() +  this->speed < 69) this->scope.setX(m_x + this->speed);
        else this->should_disappear = true;
        break;
    }
}

void Bullet::show() {
    short m_x = this->scope.getX();
    short m_y = this->scope.getY();
    Utils::setCursorPosition(m_x, m_y);
    Utils::setTextColor(this->color);  // 需要颜色，否则不怎么看得清楚 
    cout << this->my_shape;
    Utils::setTextColor(0x7);
    Utils::hideCursor();
}
