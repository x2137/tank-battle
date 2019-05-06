#ifndef TANK_BATTLE_WALLS_H
#define TANK_BATTLE_WALLS_H

#include "rect.h"
#include <string>

using std::string;


class Wall {
protected:
    Rect coverage;
    string type;
    bool should_disappear = false;

public:
    Wall(short x = 0, short y = 0, short h = 0, short w = 0, const string &type = "¡ö");
    virtual ~Wall() = default;

    string getWallType();
    Rect getScope();
    bool getTheStatus();
    void setTheStatus(bool status);
    void clear();
    void show();
};

#endif //TANK_BATTLE_WALLS_H
