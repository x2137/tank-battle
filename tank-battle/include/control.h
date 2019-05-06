#ifndef TANK_BATTLE_CONTROL_H
#define TANK_BATTLE_CONTROL_H

#include "welcome.h"
#include "map.h"


class Controller {
private:
    Hello *face = nullptr;  // 欢迎界面
    Map game_map;  // 游戏地图

    void keyboardEvent();  // 游戏过程中的键盘事件
    void congratulations();  // win
    void whatAShame();  // lose

public:
    Controller(int map = 0);
    Controller(const Controller &new_one);
    virtual ~Controller();

    Controller & operator=(const Controller &new_one);

    void go();
};

#endif //TANK_BATTLE_CONTROL_H
