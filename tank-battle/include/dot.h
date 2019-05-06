#ifndef TANK_BATTLE_DOT_H
#define TANK_BATTLE_DOT_H


class Dot {
protected:
    short x;  // ��ʾ�����꣨���Ͻ���ԭ�㣩
    short y;  // ��ʾ������

public:
    Dot(short x = 0, short y = 0);
    virtual ~Dot() = default;

    short getX();
    short getY();
    void setX(short x = 0);
    void setY(short y = 0);
};

#endif //TANK_BATTLE_DOT_H
