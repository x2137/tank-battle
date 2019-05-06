#ifndef TANK_BATTLE_PLAYERTANK_H
#define TANK_BATTLE_PLAYERTANK_H

#include "tank.h"
#include <string>


class PlayerTank final : public Tank {
private:
    short pattern;  // 表示坦克此时处于哪种状态（有各种神奇药剂，0 表示常态，1 表示变厉害，目前只有常态）
    int score = 0;  // 游戏得分
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
    int getMyScore() const;  // 计算得分，常函数（不得改变参数）
    short getMyPattern();  // 返回状态
    std::string getMyName();
};

#endif //TANK_BATTLE_PLAYERTANK_H
