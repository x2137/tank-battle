#ifndef TANK_BATTLE_SOFTWALL_H
#define TANK_BATTLE_SOFTWALL_H

#include "bloodwall.h"
#include <string>

using std::string;


class SoftWall final : public BloodWall {
public:
    SoftWall(int x = 0, int y = 0, int h = 0, int w = 0, const string &type = "¡ö", int blood = 0);
    virtual ~SoftWall() = default;
};

#endif //TANK_BATTLE_SOFTWALL_H
