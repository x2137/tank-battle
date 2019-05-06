#ifndef TANK_BATTLE_CONTROL_H
#define TANK_BATTLE_CONTROL_H

#include "welcome.h"
#include "map.h"


class Controller {
private:
    Hello *face = nullptr;  // ��ӭ����
    Map game_map;  // ��Ϸ��ͼ

    void keyboardEvent();  // ��Ϸ�����еļ����¼�
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
