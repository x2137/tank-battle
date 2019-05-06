#include "../include/softwall.h"
#include "../include/hardwall.h"
#include "../include/map.h"
#include <vector>


// 此文件是第 1 幅地图的构造文件
void Map::constructMap_1(vector<SoftWall> &wall_1, vector<HardWall> &wall_2) {
    wall_1.emplace_back(SoftWall(5, 6, 2, 2, "■", 50));
    wall_2.emplace_back(HardWall(7, 6, 2, 2, "※", 50));  // 虽然血量是一样的，但是需要特殊子弹才能打碎
    wall_1.emplace_back(SoftWall(9, 6, 2, 2, "■", 50));
    wall_1.emplace_back(SoftWall(5, 11, 2, 2, "■", 50));
    wall_2.emplace_back(HardWall(7, 11, 2, 2, "※", 50));
    wall_1.emplace_back(SoftWall(9, 11, 2, 2, "■", 50));

    wall_1.emplace_back(SoftWall(32, 6, 2, 2, "■", 50));
    wall_2.emplace_back(HardWall(34, 6, 2, 2, "※", 50));
    wall_1.emplace_back(SoftWall(36, 6, 2, 2, "■", 50));
    wall_1.emplace_back(SoftWall(32, 11, 2, 2, "■", 50));
    wall_2.emplace_back(HardWall(34, 11, 2, 2, "※", 50));
    wall_1.emplace_back(SoftWall(36, 11, 2, 2, "■", 50));

    wall_1.emplace_back(SoftWall(58, 6, 2, 2, "■", 50));
    wall_2.emplace_back(HardWall(60, 6, 2, 2, "※", 50));
    wall_1.emplace_back(SoftWall(62, 6, 2, 2, "■", 50));
    wall_1.emplace_back(SoftWall(58, 11, 2, 2, "■", 50));
    wall_2.emplace_back(HardWall(60, 11, 2, 2, "※", 50));
    wall_1.emplace_back(SoftWall(62, 11, 2, 2, "■", 50));
    //
    wall_1.emplace_back(SoftWall(18, 18, 2, 2, "■", 50));
    wall_2.emplace_back(HardWall(20, 18, 2, 2, "※", 50));
    wall_1.emplace_back(SoftWall(22, 18, 2, 2, "■", 50));
    wall_1.emplace_back(SoftWall(18, 23, 2, 2, "■", 50));
    wall_2.emplace_back(HardWall(20, 23, 2, 2, "※", 50));
    wall_1.emplace_back(SoftWall(22, 23, 2, 2, "■", 50));

    wall_1.emplace_back(SoftWall(45, 18, 2, 2, "■", 50));
    wall_2.emplace_back(HardWall(47, 18, 2, 2, "※", 50));
    wall_1.emplace_back(SoftWall(49, 18, 2, 2, "■", 50));
    wall_1.emplace_back(SoftWall(45, 23, 2, 2, "■", 50));
    wall_2.emplace_back(HardWall(47, 23, 2, 2, "※", 50));
    wall_1.emplace_back(SoftWall(49, 23, 2, 2, "■", 50));
    //
    wall_1.emplace_back(SoftWall(5, 30, 2, 2, "■", 50));
    wall_2.emplace_back(HardWall(7, 30, 2, 2, "※", 50));
    wall_1.emplace_back(SoftWall(9, 30, 2, 2, "■", 50));
    wall_1.emplace_back(SoftWall(5, 35, 2, 2, "■", 50));
    wall_2.emplace_back(HardWall(7, 35, 2, 2, "※", 50));
    wall_1.emplace_back(SoftWall(9, 35, 2, 2, "■", 50));

    wall_1.emplace_back(SoftWall(32, 30, 2, 2, "■", 50));
    wall_2.emplace_back(HardWall(34, 30, 2, 2, "※", 50));
    wall_1.emplace_back(SoftWall(36, 30, 2, 2, "■", 50));
    wall_1.emplace_back(SoftWall(32, 35, 2, 2, "■", 50));
    wall_2.emplace_back(HardWall(34, 35, 2, 2, "※", 50));
    wall_1.emplace_back(SoftWall(36, 35, 2, 2, "■", 50));

    wall_1.emplace_back(SoftWall(58, 30, 2, 2, "■", 50));
    wall_2.emplace_back(HardWall(60, 30, 2, 2, "※", 50));
    wall_1.emplace_back(SoftWall(62, 30, 2, 2, "■", 50));
    wall_1.emplace_back(SoftWall(58, 35, 2, 2, "■", 50));
    wall_2.emplace_back(HardWall(60, 35, 2, 2, "※", 50));
    wall_1.emplace_back(SoftWall(62, 35, 2, 2, "■", 50));
}
