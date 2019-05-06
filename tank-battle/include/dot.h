#ifndef TANK_BATTLE_DOT_H
#define TANK_BATTLE_DOT_H


class Dot {
protected:
    short x;  // 表示横坐标（左上角是原点）
    short y;  // 表示纵坐标

public:
    Dot(short x = 0, short y = 0);
    virtual ~Dot() = default;

    short getX();
    short getY();
    void setX(short x = 0);
    void setY(short y = 0);
};

#endif //TANK_BATTLE_DOT_H
