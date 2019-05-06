#ifndef TANK_BATTLE_BULLET_H
#define TANK_BATTLE_BULLET_H

#include "rect.h"
#include "enums.h"
#include <string>


class Bullet {
private:
    Rect scope;
    Rect pre_scope;
    BombType type = WEAK;  // 属于强力炸弹还是弱炸弹
    Direction my_direction;  // 炸弹方向，从发出炸弹的坦克身上获取
    std::string my_shape;  // 炸弹形状
    std::string who_own_me;  // 表示此时炸弹归谁所属（包括玩家，或者敌人）
    int color;
    short speed;
    bool should_disappear = false;  // 是否应该消失（其实就是是否和其他物体发生碰撞）

public:
    Bullet(BombType type, std::string who_own_me, Direction the_direction, short x, short y, int color = 0xA, short speed = 2, short h = 1, short w = 1, const std::string &shape = "·");
    virtual ~Bullet() = default;

    bool operator==(const Bullet &new_one);

    bool getMyStatus();
    Rect getMyScope();
    Rect getPreScope();
    BombType getMyType();
    Direction getMyDirection();
    std::string getTheOwner();
    void setMyType(BombType the_type);
    void setMyStatus(bool status);
    void clear();  // 清除之前的痕迹
    void move();  // 移动
    void show();  // 打印自身
};

#endif //TANK_BATTLE_BULLET_H
