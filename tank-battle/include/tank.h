#ifndef TANK_BATTLE_TANK_H
#define TANK_BATTLE_TANK_H

#include "rect.h"
#include "enums.h"
#include <string>


class Tank {
protected:
    Rect scope;  // ��ʾ̹����ռ�ݵĿռ䷶Χ
    Rect* pre_scope = nullptr;
    Direction my_direction;  // ��ʾ��ǰ̹�˵ķ���
    short blood_volume;  // ��ʾ̹�˵�����ֵ
    short life;  // ��ʾ��ʱ̹�˾��м�������
    short speed;
    bool is_attacked;
    bool is_overlapped = false;

    virtual void showUp() = 0;  // �����ڵ�ǰ����ʱ��̹��Ӧ����ô�����к���ش�ӡ����
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

    void decreaseBloodVolume(short value);  // ��������Ѫ�����ܵ�������
    void decreaseLife();  // ÿ�μ�������������ÿ�μ��� 1 �Σ�
    void changeDirection(Direction new_direction);
    
    void setOverlapStatus(bool status);
    void setScope(const Rect &new_one);

    short getBloodVolume();
    short getLife();
    bool getStatus();  // �����Ƿ��ܵ�������״̬
    bool getOverlapStatus();
    Rect getScope();
    Rect getPreScope();
    Direction getMyDirection();
};

#endif //TANK_BATTLE_TANK_H
