#include "../include/bloodwall.h"
#include <string>

using std::string;


BloodWall::BloodWall(short x, short y, short h, short w, const string &type, short blood) : Wall(x, y, h, w, type) {
    this->blood_volume = blood;
}

short BloodWall::getBloodVolume() {
    return this->blood_volume;
}

void BloodWall::decreaseBloodVolume(short blood) {
    this->blood_volume -= blood;
    if (this->blood_volume <= 0) this->should_disappear = true;
}
