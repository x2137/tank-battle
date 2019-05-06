#ifndef TANK_BATTLE_BOUNTARY_H
#define TANK_BATTLE_BOUNTARY_H

#include "dot.h"
#include <string>


class Boundary final {
private:
    Dot pos;
    std::string shape;

public:
    Boundary(short x = 0, short y = 0, const std::string &shape = "¡ª¡ª");
    virtual ~Boundary() = default;

    void show();
};

#endif //TANK_BATTLE_BOUNTARY_H
