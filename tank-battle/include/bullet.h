#ifndef TANK_BATTLE_BULLET_H
#define TANK_BATTLE_BULLET_H

#include "rect.h"
#include "enums.h"
#include <string>


class Bullet {
private:
    Rect scope;
    Rect pre_scope;
    BombType type = WEAK;  // ����ǿ��ը��������ը��
    Direction my_direction;  // ը�����򣬴ӷ���ը����̹�����ϻ�ȡ
    std::string my_shape;  // ը����״
    std::string who_own_me;  // ��ʾ��ʱը����˭������������ң����ߵ��ˣ�
    int color;
    short speed;
    bool should_disappear = false;  // �Ƿ�Ӧ����ʧ����ʵ�����Ƿ���������巢����ײ��

public:
    Bullet(BombType type, std::string who_own_me, Direction the_direction, short x, short y, int color = 0xA, short speed = 2, short h = 1, short w = 1, const std::string &shape = "��");
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
    void clear();  // ���֮ǰ�ĺۼ�
    void move();  // �ƶ�
    void show();  // ��ӡ����
};

#endif //TANK_BATTLE_BULLET_H
