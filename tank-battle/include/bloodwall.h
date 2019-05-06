#ifndef TANK_BATTLE_BLOODWALL_H
#define TANK_BATTLE_BLOODWALL_H

#include "wall.h"
#include <string>

using std::string;


class BloodWall : public Wall {
protected:
    short blood_volume;

public:
    BloodWall(short x = 0, short y = 0, short h = 0, short w = 0, const string &type = "¡ö", short blood = 100);
    virtual ~BloodWall() = default;

    short getBloodVolume();
    void decreaseBloodVolume(short blood = 50);
};

#endif //TANK_BATTLE_BLOODWALL_H
