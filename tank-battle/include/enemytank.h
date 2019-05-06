#ifndef TANK_BATTLE_ENEMYTANK_H
#define TANK_BATTLE_ENEMYTANK_H

#include "tank.h"


const short MAX_STEPS = 20;  // 走多少步换方向
const short CHOICES[4] = { 10, 20, 25, 30 };  // 决定一个坦克走多少步发射炸弹（随机选择）

class EnemyTank final : public Tank {
private:
    short my_type;  // 表示属于哪种敌方坦克（目前只有一种）
    short steps = 0;  // 记录是否达到 MAX_STEPS
    short my_steps_to_have_bullet = 0;  // 每次 record_steps 为 0 时，随机从 CHOICES 中选择一个
    short record_steps = 0;
    bool launch_bullet = false;

    virtual void showUp();
    virtual void showDown();
    virtual void showLeft();
    virtual void showRight();
    void setRandomDirection(int which_situation);  // 设置随机方向

public:
    EnemyTank(short x = 1, short y = 1, short h = 3, short w = 3, Direction d = DOWN, short blood = 100, short life = 1, bool attack = false, short speed = 1, short my_type = 0);
    virtual ~EnemyTank() = default;

    virtual void move();
    void setTheLaunchStatus();
    bool getTheLaunchStatus();
};

#endif //TANK_BATTLE_ENEMYTANK_H
