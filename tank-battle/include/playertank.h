#ifndef TANK_BATTLE_PLAYERTANK_H
#define TANK_BATTLE_PLAYERTANK_H

#include "tank.h"
#include <string>


class PlayerTank final : public Tank {
private:
    short pattern;  // ��ʾ̹�˴�ʱ��������״̬���и�������ҩ����0 ��ʾ��̬��1 ��ʾ��������Ŀǰֻ�г�̬��
    int score = 0;  // ��Ϸ�÷�
    std::string who;

    virtual void showUp();
    virtual void showDown();
    virtual void showLeft();
    virtual void showRight();

public:
    PlayerTank(short x = 27, short y = 51, short h = 3, short w = 3, Direction d = UP, const std::string &who = "player_1", short blood = 150, short life = 2, bool attack = false, short speed = 1, short pattern = 0);
    virtual ~PlayerTank() = default;

    void changePattern(short new_pattern);
    void setMyScore(short enemy_type);
    void initializeBloodVolume();
    int getMyScore() const;  // ����÷֣������������øı������
    short getMyPattern();  // ����״̬
    std::string getMyName();
};

#endif //TANK_BATTLE_PLAYERTANK_H
