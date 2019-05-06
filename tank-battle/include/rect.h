#ifndef TANK_BATTLE_RECT_H
#define TANK_BATTLE_RECT_H

#include "dot.h"


class Rect final : public Dot {
private:
    short h;  // 表示矩形的高
    short w;  // 表示矩形的宽

public:
    Rect(short x = 0, short y = 0, short h = 0, short w = 0);
    Rect(const Rect &new_one);
    virtual ~Rect() = default;

    Rect & operator=(const Rect &new_one);
    bool operator==(const Rect &new_one);

    short getH();
    short getW();
    void setH(short h = 0);
    void setW(short w = 0);
};

#endif //TANK_BATTLE_RECT_H
