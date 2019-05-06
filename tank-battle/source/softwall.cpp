#include "../include/softwall.h"
#include <string>


SoftWall::SoftWall(int x, int y, int h, int w, const std::string &type, int blood) : BloodWall(x, y, h, w, type, blood) {}
