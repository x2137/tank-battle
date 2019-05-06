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
    short who_has_color;  // 打印 player num, game level，Play，Exit 时谁需要背景色
    bool press_enter = false;
    string game_level = "Easy";
    short players = 1;

    void setColorStatus(short who);
    void setGameLevel(const string &level);
    void showWhoseColor();
    void chooseToPlayOrLeave();  // 选择进行游戏还是离开游戏
    void selectGameLeval();
    void selectPlayerNums();
    // void music();  // 暂时没实现

public:
    Hello(short who = 0);
    virtual ~Hello() = default;

    void show();  // 显示欢迎界面
    short getWhoArePressed();  // 确定是 Play 还是 Exit 被按下
    short getThePlayerNums();
    const string getTheGameLevel();
};

#endif //TANK_BATTLE_WELCOME_H
