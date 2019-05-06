#ifndef TANK_BATTLE_TARGET_H
#define TANK_BATTLE_TARGET_H

#include "rect.h"


class Target {
private:
    Rect coverage;
    bool is_attacked = false;

public:
    Target(short x = 32, short y = 50, short h = 4, short w = 6, bool is_attacked = false);
    virtual ~Target() = default;

    Rect getScope();
    bool getStatus();
    void setStatus(bool status);
    void show();
};

#endif //TANK_BATTLE_TARGET_H
