#ifndef TANK_BATTLE_ENEMYTANK_H
#define TANK_BATTLE_ENEMYTANK_H

#include "tank.h"


const short MAX_STEPS = 20;  // �߶��ٲ�������
const short CHOICES[4] = { 10, 20, 25, 30 };  // ����һ��̹���߶��ٲ�����ը�������ѡ��

class EnemyTank final : public Tank {
private:
    short my_type;  // ��ʾ�������ֵз�̹�ˣ�Ŀǰֻ��һ�֣�
    short steps = 0;  // ��¼�Ƿ�ﵽ MAX_STEPS
    short my_steps_to_have_bullet = 0;  // ÿ�� record_steps Ϊ 0 ʱ������� CHOICES ��ѡ��һ��
    short record_steps = 0;
    bool launch_bullet = false;

    virtual void showUp();
    virtual void showDown();
    virtual void showLeft();
    virtual void showRight();
    void setRandomDirection(int which_situation);  // �����������

public:
    EnemyTank(short x = 1, short y = 1, short h = 3, short w = 3, Direction d = DOWN, short blood = 100, short life = 1, bool attack = false, short speed = 1, short my_type = 0);
    virtual ~EnemyTank() = default;

    virtual void move();
    void setTheLaunchStatus();
    bool getTheLaunchStatus();
};

#endif //TANK_BATTLE_ENEMYTANK_H
