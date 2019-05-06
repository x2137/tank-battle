#include "../include/map.h"
#include "../include/utils.h"
#include "../include/playertank.h"
#include <iostream>
#include <algorithm>

using std::cout;


Map::Map(int map) : which_map(map) {
    // ��ʼ����ͼ�б߽���Ϣ
    Utils::setWindowSize(0, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1);
    for (short x = 0; x < WINDOW_WIDTH - 1; ++x) {  // �ϱ߽�
        this->boundaries.emplace_back(Boundary(x, 0));
    }
    for (short y = 1; y < WINDOW_HEIGHT - 1; ++y) {  // �ұ߽�
        this->boundaries.emplace_back(Boundary(WINDOW_WIDTH - 1, y, "|"));
    }
    for (short x = 0; x < WINDOW_WIDTH - 1; ++x) {  // �±߽�
        this->boundaries.emplace_back(Boundary(x, WINDOW_HEIGHT - 1, "����"));
    }
    for (short y = 1; y < WINDOW_HEIGHT - 1; ++y) {  // ��߽�
        this->boundaries.emplace_back(Boundary(0, y, "|"));
    }
    for (short y = 1; y < WINDOW_HEIGHT - 1; ++y) {  // �м�ָ���
        this->boundaries.emplace_back(Boundary(69, y, "|"));
    }

    // ��ʼ��Ŀ��
    this->my_target = new Target();

    // ��ʼ������Ŀ���ǽ
    this->target_defence_walls.emplace_back(SoftWall(31, 49, 1, 2, "��", 10));
    this->target_defence_walls.emplace_back(SoftWall(33, 49, 1, 2, "��", 10));
    this->target_defence_walls.emplace_back(SoftWall(35, 49, 1, 2, "��", 10));
    this->target_defence_walls.emplace_back(SoftWall(37, 49, 1, 2, "��", 10));
    this->target_defence_walls.emplace_back(SoftWall(31, 50, 2, 1, "��", 10));
    this->target_defence_walls.emplace_back(SoftWall(31, 52, 2, 1, "��", 10));
    this->target_defence_walls.emplace_back(SoftWall(38, 50, 2, 1, "��", 10));
    this->target_defence_walls.emplace_back(SoftWall(38, 52, 2, 1, "��", 10));

    // ��ʼ����ͼ�������Ϣ��ʾ��������Ҫ��ʾ��̹��
    this->show_tanks.emplace_back(PlayerTank(71, 6, 3, 3, RIGHT, "show", 100, 2, false, 1, 1));
    this->show_tanks.emplace_back(PlayerTank(71, 10, 3, 3, RIGHT, "show", 100, 2, false, 1, 1));

    // ��ʼ������Ϣѡ���ʼ�����ŵ�ͼ
    switch (this->which_map) {
    case 0:  // ��ͼ 1
        this->constructMap_1(this->soft_walls, this->hard_walls);  // ��ʼ����ͼ��Դ
        break;
    case 1:  // ��ͼ 2
        //
        break;
    case 2:  // ��ͼ 3
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
        this->enemy_nums[0] = 0;  // �Ѿ���ʼ���� 1 ����������������� 1
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
    // position 1��û��ʼ����̹���������� 0�����ҵ�ǰλ�û����ڵ�̹������С���Ѿ���ʼ��������
    if (this->enemy_nums[0] > 0) {
        if ((this->pos1_enemy_tanks.size() < (this->identified - this->enemy_nums[0])) || (this->count_time[0] >= MAX_TIME)) {
            this->pos1_enemy_tanks.emplace_back(EnemyTank(1, 1, 3, 3, DOWN, 100, 1, false, 1, 0));
            -- this->enemy_nums[0];
            this->count_time[0] = 0;  // ��ʼ���µ�̹�ˣ���ʱ����
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
            tank.setTheLaunchStatus();  // �����Ժ���Ҫ������״̬����
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
                this->player_tanks.at(0).setScope(Rect(27, 51, 3, 3));  // ת�Ƶ������
                this->player_tanks.at(0).initializeBloodVolume();  // ������Ҫ���³�ʼ��Ѫ��
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
    for (auto &tank : this->player_tanks) {  // ����ʹ�����ã������޷��ı����е�ֵ
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
    // �ȼ��彫֮ǰ�Ĵ�ӡ�ۼ�����������ÿ��λ�õ���ʱ��������̹�˿��úܽ�����Ϊ��������ɴ�ӡ����ȫ
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
    // ����ʾ��Դ֮ǰ����Ҫ�����Щ��Դ�Ƿ�Ӧ�ô���
    // ɾ��Ӧ����ʧ��ը��
    this->deleteBullet();
    this->deleteWall();
    this->deleteEnemyTank();
    this->deletePlayerTank();

    // ��ʾ��ͼ��Դ
    this->displayOnlyMyMap();
    // ��ʾĿ���Ŀ�����ǽ
    this->displayOnlyTargetAndDefenceWalls();
    // ��ʾը����Ӧ�������̹��֮ǰ��ʾ��������ʾ���̹��ʱ���ȱʧ��
    this->displayOnlyAllBullets();
    // ��ʾ���̹��
    this->displayOnlyPlayerTanks();
    // ��ʾ��ҵ÷�
    this->displayOnlyPlayerScore();
    // ��ʾ�з�̹��
    this->displayOnlyEnemyTanks();
}
