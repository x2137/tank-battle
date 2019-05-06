#include "../include/enemytank.h"
#include "../include/utils.h"
#include <iostream>
#include <time.h>

using std::cout;


EnemyTank::EnemyTank(short x, short y, short h, short w, Direction d, short blood, short life, bool attack, short speed, short my_type) : Tank(x, y, h, w, d, blood, life, attack, speed) {
    this->my_type = my_type;
}

void EnemyTank::showUp() {
    short left = this->scope.getX();
    short top = this->scope.getY();

    switch (this->my_type) {
    case 0:
        Utils::setCursorPosition(left, top);
        cout << "  " << "■" << "  ";
        Utils::setCursorPosition(left, top + 1);
        cout << "  " << "■" << "  ";
        Utils::setCursorPosition(left, top + 2);
        cout << "■" << "■" << "■";
        break;
    case 1:
        //
        break;
    case 2:
        //
        break;
    }
}

void EnemyTank::showDown() {
    short left = this->scope.getX();
    short top = this->scope.getY();

    switch (this->my_type) {
    case 0:
        Utils::setCursorPosition(left, top);
        cout << "■" << "■" << "■";
        Utils::setCursorPosition(left, top + 1);
        cout << "  " << "■" << "  ";
        Utils::setCursorPosition(left, top + 2);
        cout << "  " << "■" << "  ";
        break;
    case 1:
        //
        break;
    case 2:
        //
        break;
    }
}

void EnemyTank::showLeft() {
    short left = this->scope.getX();
    short top = this->scope.getY();

    switch (this->my_type) {
    case 0:
        Utils::setCursorPosition(left, top);
        cout << "  " << "  " << "■";
        Utils::setCursorPosition(left, top + 1);
        cout << "■" << "■" << "■";
        Utils::setCursorPosition(left, top + 2);
        cout << "  " << "  " << "■";
        break;
    case 1:
        //
        break;
    case 2:
        //
        break;
    }
}

void EnemyTank::showRight() {
    short left = this->scope.getX();
    short top = this->scope.getY();

    switch (this->my_type) {
    case 0:
        Utils::setCursorPosition(left, top);
        cout << "■" << "  " << "  ";
        Utils::setCursorPosition(left, top + 1);
        cout << "■" << "■" << "■";
        Utils::setCursorPosition(left, top + 2);
        cout << "■" << "  " << "  ";
        break;
    case 1:
        //
        break;
    case 2:
        //
        break;
    }
}

void EnemyTank::move() {
    // 炸弹发射检测
    if (this->record_steps == 0) {
        srand((unsigned)time(0));
        short i = (rand() % 4);
        this->my_steps_to_have_bullet = CHOICES[i];
    }
    else if (this->record_steps >= this->my_steps_to_have_bullet) this->launch_bullet = true;

    *(this->pre_scope) = this->scope;

    short step = this->speed;
    short m_left = this->scope.getX();
    short m_top = this->scope.getY();

    switch (this->my_direction) {  // 条件判断是否超出边界
    case UP:
        if ((this->steps >= MAX_STEPS) || this->is_overlapped) {
            this->setRandomDirection(1);
            this->is_overlapped = false;
        }
        else if (this->scope.getY() - step > 0) {
            this->scope.setY(m_top - step);
            ++ this->steps;  // 成功 move 一次，步数 +1
            ++ this->record_steps;
        }
        else this->setRandomDirection(0);  // 否则就设置新方向
        break;
    case DOWN:
        if ((this->steps >= MAX_STEPS) || this->is_overlapped) {
            this->setRandomDirection(1);
            this->is_overlapped = false;
        }
        else if (this->scope.getY() + step < 52) {
            this->scope.setY(m_top + step);
            ++ this->steps;
            ++ this->record_steps;
        }
        else this->setRandomDirection(0);
        break;
    case LEFT:
        if ((this->steps >= MAX_STEPS) || this->is_overlapped) {
            this->setRandomDirection(1);
            this->is_overlapped = false;
        }
        else if (this->scope.getX() - step > 0) {
            this->scope.setX(m_left - step);
            ++ this->steps;
            ++ this->record_steps;
        }
        else this->setRandomDirection(0);
        break;
    case RIGHT:
        if ((this->steps >= MAX_STEPS) || this->is_overlapped) {
            this->setRandomDirection(1);
            this->is_overlapped = false;
        }
        else if (this->scope.getX() + step < 67) {
            this->scope.setX(m_left + step);
            ++ this->steps;
            ++ this->record_steps;
        }
        else this->setRandomDirection(0);
        break;
    }
}

void EnemyTank::setRandomDirection(int which_situation) {
    srand((unsigned)time(0));  // 随机数种子
    switch (which_situation) {
    case 0:  // 0 表示撞墙
        Direction new_direction;
        while ((new_direction = (Direction)(UP + (rand() % 4))) == this->my_direction) {}
        this->my_direction = new_direction;
        break;
    case 1:  // 1 表示沿一个方向走了最大步数
        this->my_direction = (Direction)(UP + (rand() % 4));
        this->steps = 0;  // 更换新方向后步数置零
        break;
    }
}

void EnemyTank::setTheLaunchStatus() {
    this->record_steps = 0;
    this->launch_bullet = false;
}

bool EnemyTank::getTheLaunchStatus() {
    return this->launch_bullet;
}
