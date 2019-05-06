#ifndef TANK_BATTLE_WELCOME_H
#define TANK_BATTLE_WELCOME_H

#include "wall.h"
#include "playertank.h"
#include <Windows.h>
#include <vector>
#include <string>


const SHORT PLAYER_NUM_X = 3;
const SHORT LEVEL_POS_X = 14;
const SHORT PLAY_POS_X = 45;
const SHORT EXIT_POS_X = 53;
const SHORT PUBLIC_Y = 29;

class Hello {
private:
    std::vector<Wall> my_wall;
    std::vector<PlayerTank> my_tank;
    short who_has_color;  // ��ӡ player num, game level��Play��Exit ʱ˭��Ҫ����ɫ
    bool press_enter = false;
    string game_level = "Easy";
    short players = 1;

    void setColorStatus(short who);
    void setGameLevel(const string &level);
    void showWhoseColor();
    void chooseToPlayOrLeave();  // ѡ�������Ϸ�����뿪��Ϸ
    void selectGameLeval();
    void selectPlayerNums();
    // void music();  // ��ʱûʵ��

public:
    Hello(short who = 0);
    virtual ~Hello() = default;

    void show();  // ��ʾ��ӭ����
    short getWhoArePressed();  // ȷ���� Play ���� Exit ������
    short getThePlayerNums();
    const string getTheGameLevel();
};

#endif //TANK_BATTLE_WELCOME_H
