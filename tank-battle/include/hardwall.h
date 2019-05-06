#ifndef TANK_BATTLE_HARDWALL_H
#define TANK_BATTLE_HARDWALL_H

#include "bloodwall.h"
#include <string>

using std::string;


class HardWall : public BloodWall {
public:
    HardWall(int x = 0, int y = 0, int h = 0, int w = 0, const string &type = "¡ù", int blood = 0);
};

#endif //TANK_BATTLE_HARDWALL_H
