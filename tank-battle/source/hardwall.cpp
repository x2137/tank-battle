#include "../include/hardwall.h"
#include <string>

using std::string;


HardWall::HardWall(int x, int y, int h, int w, const string &type, int blood) : BloodWall(x, y, h, w, type, blood) {}
