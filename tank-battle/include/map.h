#ifndef TANK_BATTLE_MAP_H
#define TANK_BATTLE_MAP_H

#include "target.h"
#include "boundary.h"
#include "playertank.h"
#include "enemytank.h"
#include "softwall.h"
#include "hardwall.h"
#include "bullet.h"
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;


const SHORT WINDOW_HEIGHT = 55;  // 窗口高度为 55
const SHORT WINDOW_WIDTH = 85;  // 窗口宽度为 170
const int MAX_TIME = 70;  // 循环多少次后增加新的坦克

class Map {
private:
    int which_map = 0;  // 初始化哪张地图
    int player_nums = 1;  // 玩家人数
    string game_level = "Easy";  // 游戏难度
    vector<Boundary> boundaries;
    Target* my_target = nullptr;
    vector<SoftWall> target_defence_walls;  // 保护目标的墙
    vector<PlayerTank> show_tanks;  // 玩家信息显示界面坦克
    vector<PlayerTank> player_tanks;  // 玩家坦克
    vector<Bullet> my_bullets;  // 表示坦克发出的炸弹
    // 为了方便，将敌方坦克初始化位置设置为 3 个地方，那么便使用 3 个向量来简化设置
    unsigned int enemy_nums[3] = { 1 };  // 记录还应该初始化的坦克数量
    unsigned int identified = 0;  // 确定的难度模式下，每个位置应该确定的坦克数量
    unsigned int count_time[3] = { 0 };  // 记录每个位置距离前一个坦克初始化后多少时间了（该初始化新的坦克了）
    vector<EnemyTank> pos1_enemy_tanks;  // 位置 1 敌方坦克
    vector<EnemyTank> pos2_enemy_tanks;  // position 2
    vector<EnemyTank> pos3_enemy_tanks;  // position 3
    vector<SoftWall> soft_walls;  // 地图中能打碎的墙
    vector<HardWall> hard_walls;  // 地图中不能打碎的墙

    void deleteBullet();
    void deletePlayerTank();
    void deleteEnemyTank();
    void deleteWall();

    void constructMap_1(vector<SoftWall> &wall_1, vector<HardWall> &wall_2);  // 构造地图 1
    void constructMap_2(vector<SoftWall> &wall_1, vector<HardWall> &wall_2);  // 构造地图 2

public:
    Map(int map = 0);
    virtual ~Map();

    friend void collisionDetection(Map &map);

    bool win();
    bool lose();

    void addNewEnemyTanks();
    void addEnemyTankBullets();  // 检查敌方坦克是否需要发射炸弹
    void addBulletToMap(BombType type, const string &who_own_me, Direction the_direction, short x, short y, int color = 0xA, short speed = 3);  // 向地图之中添加炸弹（由地图调用显示）
    void addTime();  //

    void initializeEnemyTanks();  // 得根据游戏难度初始化敌方坦克的数量
    void initializePlayerTanks();
        
    void setGameLevel(const string &level);  // 得到游戏难度
    void setPlayerNums(short players);
    
    vector<PlayerTank> & getThePlayerTanks();
    int getPlayerNums();  // 获得玩家数量
    
    void displayOnlyBoundary();
    void displayOnlyPlayerInfo();
    void display();  // 排在此函数后面的函数都需要在其内调用
    void displayOnlyPlayerScore();  // 显示玩家得分
    void displayOnlyTargetAndDefenceWalls();  // 显示目标和保护目标的墙
    void displayOnlyPlayerTanks();  // 显示玩家坦克
    void displayOnlyMyMap();  // 显示地图资源（也就是各种类型的墙）
    void displayOnlyEnemyTanks();  // 显示敌方坦克
    void displayOnlyAllBullets();  // 显示所有炸弹
};

#endif //TANK_BATTLE_MAP_H
