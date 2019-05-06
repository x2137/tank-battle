#include "../include/map.h"
#include "../include/utils.h"
#include "../include/playertank.h"
#include <iostream>
#include <algorithm>

using std::cout;


Map::Map(int map) : which_map(map) {
    // 初始化地图中边界信息
    Utils::setWindowSize(0, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1);
    for (short x = 0; x < WINDOW_WIDTH - 1; ++x) {  // 上边界
        this->boundaries.emplace_back(Boundary(x, 0));
    }
    for (short y = 1; y < WINDOW_HEIGHT - 1; ++y) {  // 右边界
        this->boundaries.emplace_back(Boundary(WINDOW_WIDTH - 1, y, "|"));
    }
    for (short x = 0; x < WINDOW_WIDTH - 1; ++x) {  // 下边界
        this->boundaries.emplace_back(Boundary(x, WINDOW_HEIGHT - 1, "——"));
    }
    for (short y = 1; y < WINDOW_HEIGHT - 1; ++y) {  // 左边界
        this->boundaries.emplace_back(Boundary(0, y, "|"));
    }
    for (short y = 1; y < WINDOW_HEIGHT - 1; ++y) {  // 中间分割线
        this->boundaries.emplace_back(Boundary(69, y, "|"));
    }

    // 初始化目标
    this->my_target = new Target();

    // 初始化保护目标的墙
    this->target_defence_walls.emplace_back(SoftWall(31, 49, 1, 2, "◆", 10));
    this->target_defence_walls.emplace_back(SoftWall(33, 49, 1, 2, "◆", 10));
    this->target_defence_walls.emplace_back(SoftWall(35, 49, 1, 2, "◆", 10));
    this->target_defence_walls.emplace_back(SoftWall(37, 49, 1, 2, "◆", 10));
    this->target_defence_walls.emplace_back(SoftWall(31, 50, 2, 1, "◆", 10));
    this->target_defence_walls.emplace_back(SoftWall(31, 52, 2, 1, "◆", 10));
    this->target_defence_walls.emplace_back(SoftWall(38, 50, 2, 1, "◆", 10));
    this->target_defence_walls.emplace_back(SoftWall(38, 52, 2, 1, "◆", 10));

    // 初始化地图中玩家信息显示界面中需要显示的坦克
    this->show_tanks.emplace_back(PlayerTank(71, 6, 3, 3, RIGHT, "show", 100, 2, false, 1, 1));
    this->show_tanks.emplace_back(PlayerTank(71, 10, 3, 3, RIGHT, "show", 100, 2, false, 1, 1));

    // 开始根据信息选择初始化哪张地图
    switch (this->which_map) {
    case 0:  // 地图 1
        this->constructMap_1(this->soft_walls, this->hard_walls);  // 初始化地图资源
        break;
    case 1:  // 地图 2
        //
        break;
    case 2:  // 地图 3
        //
        break;
    // and so on
    }
}

Map::~Map() {
    if(this->my_target != nullptr) delete this->my_target;
}

void Map::initializeEnemyTanks() {
    this->pos1_enemy_tanks.emplace_back(EnemyTank(1, 1, 3, 3, DOWN, 100, 1, false, 1, 0));
    this->pos2_enemy_tanks.emplace_back(EnemyTank(33, 1, 3, 3, DOWN, 100, 1, false, 1, 0));
    this->pos3_enemy_tanks.emplace_back(EnemyTank(66, 1, 3, 3, DOWN, 100, 1, false, 1, 0));

    if (this->game_level == "Easy") {
        this->identified = 1;
        this->enemy_nums[0] = 0;  // 已经初始化了 1 个，所以数量会减少 1
        this->enemy_nums[1] = 0;
        this->enemy_nums[2] = 0;
    }
    else if (this->game_level == "Normal") {
        this->identified = 5;
        this->enemy_nums[0] = 4;
        this->enemy_nums[1] = 4;
        this->enemy_nums[2] = 4;
    }
    else if (this->game_level == "Hard") {
        this->identified = 10;
        this->enemy_nums[0] = 9;
        this->enemy_nums[1] = 9;
        this->enemy_nums[2] = 9;
    }
    else if (this->game_level == "Hell") {
        this->identified = 20;
        this->enemy_nums[0] = 19;
        this->enemy_nums[1] = 19;
        this->enemy_nums[2] = 19;
    }
}

void Map::initializePlayerTanks() {
    switch (this->player_nums) {
    case 1:
        this->player_tanks.emplace_back(PlayerTank());
        break;
    case 2:
        this->player_tanks.emplace_back(PlayerTank());
        this->player_tanks.emplace_back(PlayerTank(40, 51, 3, 3, UP, "player_2"));
        break;
    }
}

void Map::setGameLevel(const string &level) {
    this->game_level = level;
}

void Map::setPlayerNums(short players) {
    this->player_nums = players;
}

void Map::addBulletToMap(BombType type, const string &who_own_me, Direction the_direction, short x, short y, int color, short speed) {
    Bullet a_bullet(type, who_own_me, the_direction, x, y, color, speed);
    this->my_bullets.emplace_back(a_bullet);
}

void Map::addTime() {
    ++ this->count_time[0];
    ++ this->count_time[1];
    ++ this->count_time[2];
}

void Map::addNewEnemyTanks() {
    // position 1（没初始化的坦克数量大于 0，而且当前位置还存在的坦克数量小于已经初始化的数量
    if (this->enemy_nums[0] > 0) {
        if ((this->pos1_enemy_tanks.size() < (this->identified - this->enemy_nums[0])) || (this->count_time[0] >= MAX_TIME)) {
            this->pos1_enemy_tanks.emplace_back(EnemyTank(1, 1, 3, 3, DOWN, 100, 1, false, 1, 0));
            -- this->enemy_nums[0];
            this->count_time[0] = 0;  // 初始化新的坦克，计时归零
        }
    }
    if (this->enemy_nums[1] > 0) {
        if ((this->pos2_enemy_tanks.size() < (this->identified - this->enemy_nums[1])) || (this->count_time[1] >= MAX_TIME)) {
            this->pos2_enemy_tanks.emplace_back(EnemyTank(33, 1, 3, 3, DOWN, 100, 1, false, 1, 0));
            -- this->enemy_nums[1];
            this->count_time[1] = 0;
        }
    }
    if (this->enemy_nums[2] > 0) {
        if ((this->pos3_enemy_tanks.size() < (this->identified - this->enemy_nums[2])) || (this->count_time[2] >= MAX_TIME)) {
            this->pos3_enemy_tanks.emplace_back(EnemyTank(66, 1, 3, 3, DOWN, 100, 1, false, 1, 0));
            -- this->enemy_nums[2];
            this->count_time[2] = 0;
        }
    }
}

void Map::addEnemyTankBullets() {
    for (auto &tank : this->pos1_enemy_tanks) {
        if (tank.getTheLaunchStatus()) {
            bool generate = true;
            Direction direction = tank.getMyDirection();
            short m_x = tank.getScope().getX();
            short m_y = tank.getScope().getY();
            if (Utils::helpEnemyTanksToLaunch(direction, m_x, m_y)) this->addBulletToMap(WEAK, "enemy", direction, m_x, m_y);
            tank.setTheLaunchStatus();  // 发射以后，需要将发射状态重置
        }
    }
    for (auto &tank : this->pos2_enemy_tanks) {
        if (tank.getTheLaunchStatus()) {
            bool generate = true;
            Direction direction = tank.getMyDirection();
            short m_x = tank.getScope().getX();
            short m_y = tank.getScope().getY();
            if (Utils::helpEnemyTanksToLaunch(direction, m_x, m_y)) this->addBulletToMap(WEAK, "enemy", direction, m_x, m_y);
            tank.setTheLaunchStatus();
        }
    }
    for (auto &tank : this->pos3_enemy_tanks) {
        if (tank.getTheLaunchStatus()) {
            bool generate = true;
            Direction direction = tank.getMyDirection();
            short m_x = tank.getScope().getX();
            short m_y = tank.getScope().getY();
            if (Utils::helpEnemyTanksToLaunch(direction, m_x, m_y)) this->addBulletToMap(WEAK, "enemy", direction, m_x, m_y);
            tank.setTheLaunchStatus();
        }
    }
}

void Map::deleteBullet() {
    for (size_t i = 0; i < this->my_bullets.size(); ++i) {
        if (this->my_bullets.at(i).getMyStatus()) {
            this->my_bullets.at(i).clear();
            this->my_bullets.erase(this->my_bullets.begin() + i);
            --i;
        }
    }
}

void Map::deleteEnemyTank() {
    for (size_t i = 0; i < this->pos1_enemy_tanks.size(); ++i) {
        if (this->pos1_enemy_tanks.at(i).getBloodVolume() <= 0) {
            this->pos1_enemy_tanks.at(i).clear();
            this->pos1_enemy_tanks.erase(this->pos1_enemy_tanks.begin() + i);
            --i;
        }
    }
    for (size_t i = 0; i < this->pos2_enemy_tanks.size(); ++i) {
        if (this->pos2_enemy_tanks.at(i).getBloodVolume() <= 0) {
            this->pos2_enemy_tanks.at(i).clear();
            this->pos2_enemy_tanks.erase(this->pos2_enemy_tanks.begin() + i);
            --i;
        }
    }
    for (size_t i = 0; i < this->pos3_enemy_tanks.size(); ++i) {
        if (this->pos3_enemy_tanks.at(i).getBloodVolume() <= 0) {
            this->pos3_enemy_tanks.at(i).clear();
            this->pos3_enemy_tanks.erase(this->pos3_enemy_tanks.begin() + i);
            --i;
        }
    }
}

void Map::deletePlayerTank() {
    switch (this->player_nums) {
    case 1:
        if (this->player_tanks.at(0).getBloodVolume() <= 0) {
            this->player_tanks.at(0).clear();
            this->player_tanks.at(0).decreaseLife();
            if (this->player_tanks.at(0).getLife() <= 0) this->player_tanks.erase(this->player_tanks.begin());
            else {
                this->player_tanks.at(0).setScope(Rect(27, 51, 3, 3));  // 转移到复活点
                this->player_tanks.at(0).initializeBloodVolume();  // 重生需要重新初始化血量
            }
        }
        break;
    case 2:
        for (size_t i = 0; i < this->player_tanks.size(); ++i) {
            string name = this->player_tanks.at(i).getMyName();
            
            if (this->player_tanks.at(i).getBloodVolume() <= 0) {
                this->player_tanks.at(i).clear();
                this->player_tanks.at(i).decreaseLife();
                if (this->player_tanks.at(i).getLife() <= 0) this->player_tanks.erase(this->player_tanks.begin() + i);
                else {
                    if (name == "player_1") this->player_tanks.at(i).setScope(Rect(27, 51, 3, 3));
                    else if(name == "player_2") this->player_tanks.at(i).setScope(Rect(40, 51, 3, 3));
                    this->player_tanks.at(i).initializeBloodVolume();
                }
            }
        }
        break;
    }
}

void Map::deleteWall() {
    for (size_t i = 0; i < this->soft_walls.size(); ++i) {
        if (this->soft_walls.at(i).getTheStatus()) {
            this->soft_walls.at(i).clear();
            this->soft_walls.erase(this->soft_walls.begin() + i);
            --i;
        }
    }
    for (size_t i = 0; i < this->hard_walls.size(); ++i) {
        if (this->hard_walls.at(i).getTheStatus()) {
            this->hard_walls.at(i).clear();
            this->hard_walls.erase(this->hard_walls.begin() + i);
            --i;
        }
    }
    for (size_t i = 0; i < this->target_defence_walls.size(); ++i) {
        if (this->target_defence_walls.at(i).getTheStatus()) {
            this->target_defence_walls.at(i).clear();
            this->target_defence_walls.erase(this->target_defence_walls.begin() + i);
            --i;
        }
    }
}

vector<PlayerTank> & Map::getThePlayerTanks() {
    return this->player_tanks;
}

int Map::getPlayerNums() {
    return this->player_nums;
}

void Map::displayOnlyBoundary() {
    for (auto d : this->boundaries) {
        d.show();
    }
    Utils::hideCursor();
}

bool Map::win() {
    short s_num1 = this->enemy_nums[0];
    short s_num2 = this->enemy_nums[1];
    short s_num3 = this->enemy_nums[2];
    size_t n_num1 = this->pos1_enemy_tanks.size();
    size_t n_num2 = this->pos2_enemy_tanks.size();
    size_t n_num3 = this->pos3_enemy_tanks.size();

    if (s_num1 <= 0 && s_num2 <= 0 && s_num3 <= 0 && n_num1 <= 0 && n_num2 <= 0 && n_num3 <= 0) {
        return true;
    }
    return false;
}

bool Map::lose() {
    if ((this->player_tanks.size() <= 0) || this->my_target->getStatus()) return true;
    return false;
}

void Map::displayOnlyPlayerInfo() {
    int i = 0;
    Utils::setTextColor(0xB);
    for (auto info_tank : this->show_tanks) {
        info_tank.show();
        short my_x = info_tank.getScope().getX();
        short my_y = info_tank.getScope().getY();
        Utils::setCursorPosition(my_x + 3, my_y + 1); 
        string print_info = "Player " + std::to_string(i) + ":";
        cout << print_info;
        ++i;
    }
    Utils::setTextColor(0x7);
}

void Map::displayOnlyPlayerScore() {
    for (size_t i : { 0, 1 }) {
        short my_x = this->show_tanks.at(i).getScope().getX();
        short my_y = this->show_tanks.at(i).getScope().getY();
        Utils::setCursorPosition(my_x + 8, my_y + 1);
        Utils::setTextColor(0xC);
        if (i < this->player_tanks.size()) {
            cout << this->player_tanks.at(i).getMyScore();
        }
        else {
            cout << "Not exist";
        }
        Utils::setTextColor(0x7);
    }
}

void Map::displayOnlyTargetAndDefenceWalls() {
    this->my_target->show();
    for (auto defence_wall : this->target_defence_walls) {
        defence_wall.show();
        Utils::hideCursor();
    }
}

void Map::displayOnlyPlayerTanks() {
    for (auto &tank : this->player_tanks) tank.clear();
    for (auto &tank : this->player_tanks) {  // 必须使用引用，否则无法改变其中的值
        tank.show();
        Utils::hideCursor();
        tank.move();
    }
}

void Map::displayOnlyMyMap() {
    for (auto &the_wall : this->soft_walls) {
        the_wall.show();
        Utils::hideCursor();
    }
    for (auto &the_wall : this->hard_walls) {
        the_wall.show();
        Utils::hideCursor();
    }
}

void Map::displayOnlyEnemyTanks() {
    // 先集体将之前的打印痕迹擦除，避免每个位置调用时正当两个坦克靠得很近，因为这样会造成打印不完全
    for (auto &tank : this->pos1_enemy_tanks) tank.clear();
    for (auto &tank : this->pos2_enemy_tanks) tank.clear();
    for (auto &tank : this->pos3_enemy_tanks) tank.clear();
    
    for (auto &tank : this->pos1_enemy_tanks) {
        tank.show();
        Utils::hideCursor();
        tank.move();
    }
    for (auto &tank : this->pos2_enemy_tanks) {
        tank.show();
        Utils::hideCursor();
        tank.move();
    }
    for (auto &tank : this->pos3_enemy_tanks) {
        tank.show();
        Utils::hideCursor();
        tank.move();
    }
}

void Map::displayOnlyAllBullets() {
    for (auto &bullet : this->my_bullets) bullet.clear();
    for (auto &bullet : this->my_bullets) {
        bullet.show();
        Utils::hideCursor();
        bullet.move();
    }
}

void Map::display() {
    // 在显示资源之前，需要检查这些资源是否还应该存在
    // 删除应该消失的炸弹
    this->deleteBullet();
    this->deleteWall();
    this->deleteEnemyTank();
    this->deletePlayerTank();

    // 显示地图资源
    this->displayOnlyMyMap();
    // 显示目标和目标防护墙
    this->displayOnlyTargetAndDefenceWalls();
    // 显示炸弹（应该在玩家坦克之前显示，避免显示玩家坦克时造成缺失）
    this->displayOnlyAllBullets();
    // 显示玩家坦克
    this->displayOnlyPlayerTanks();
    // 显示玩家得分
    this->displayOnlyPlayerScore();
    // 显示敌方坦克
    this->displayOnlyEnemyTanks();
}
