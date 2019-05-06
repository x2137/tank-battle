#ifndef TANK_BATTLE_TANK_H
#define TANK_BATTLE_TANK_H

#include "rect.h"
#include "enums.h"
#include <string>


class Tank {
protected:
    Rect scope;  // 表示坦克所占据的空间范围
    Rect* pre_scope = nullptr;
    Direction my_direction;  // 表示当前坦克的方向
    short blood_volume;  // 表示坦克的生命值
    short life;  // 表示此时坦克具有几条生命
    short speed;
    bool is_attacked;
    bool is_overlapped = false;

    virtual void showUp() = 0;  // 当处于当前方向时，坦克应该怎么样进行合理地打印操作
    virtual void showDown() = 0;
    virtual void showLeft() = 0;
    virtual void showRight() = 0;

public:
    Tank(short x, short y, short h, short w, Direction d, short blood, short life, bool attack, short speed);
    virtual ~Tank() = default;

    bool operator==(const Tank &new_one);

    void clear();
    virtual void move();
    void show();

    void decreaseBloodVolume(short value);  // 减少自身血量（受到攻击后）
    void decreaseLife();  // 每次减少生命次数（每次减少 1 次）
    void changeDirection(Direction new_direction);
    
    void setOverlapStatus(bool status);
    void setScope(const Rect &new_one);

    short getBloodVolume();
    short getLife();
    bool getStatus();  // 返回是否受到攻击的状态
    bool getOverlapStatus();
    Rect getScope();
    Rect getPreScope();
    Direction getMyDirection();
};

#endif //TANK_BATTLE_TANK_H
