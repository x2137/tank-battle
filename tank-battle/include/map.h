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


const SHORT WINDOW_HEIGHT = 55;  // ���ڸ߶�Ϊ 55
const SHORT WINDOW_WIDTH = 85;  // ���ڿ��Ϊ 170
const int MAX_TIME = 70;  // ѭ�����ٴκ������µ�̹��

class Map {
private:
    int which_map = 0;  // ��ʼ�����ŵ�ͼ
    int player_nums = 1;  // �������
    string game_level = "Easy";  // ��Ϸ�Ѷ�
    vector<Boundary> boundaries;
    Target* my_target = nullptr;
    vector<SoftWall> target_defence_walls;  // ����Ŀ���ǽ
    vector<PlayerTank> show_tanks;  // �����Ϣ��ʾ����̹��
    vector<PlayerTank> player_tanks;  // ���̹��
    vector<Bullet> my_bullets;  // ��ʾ̹�˷�����ը��
    // Ϊ�˷��㣬���з�̹�˳�ʼ��λ������Ϊ 3 ���ط�����ô��ʹ�� 3 ��������������
    unsigned int enemy_nums[3] = { 1 };  // ��¼��Ӧ�ó�ʼ����̹������
    unsigned int identified = 0;  // ȷ�����Ѷ�ģʽ�£�ÿ��λ��Ӧ��ȷ����̹������
    unsigned int count_time[3] = { 0 };  // ��¼ÿ��λ�þ���ǰһ��̹�˳�ʼ�������ʱ���ˣ��ó�ʼ���µ�̹���ˣ�
    vector<EnemyTank> pos1_enemy_tanks;  // λ�� 1 �з�̹��
    vector<EnemyTank> pos2_enemy_tanks;  // position 2
    vector<EnemyTank> pos3_enemy_tanks;  // position 3
    vector<SoftWall> soft_walls;  // ��ͼ���ܴ����ǽ
    vector<HardWall> hard_walls;  // ��ͼ�в��ܴ����ǽ

    void deleteBullet();
    void deletePlayerTank();
    void deleteEnemyTank();
    void deleteWall();

    void constructMap_1(vector<SoftWall> &wall_1, vector<HardWall> &wall_2);  // �����ͼ 1
    void constructMap_2(vector<SoftWall> &wall_1, vector<HardWall> &wall_2);  // �����ͼ 2

public:
    Map(int map = 0);
    virtual ~Map();

    friend void collisionDetection(Map &map);

    bool win();
    bool lose();

    void addNewEnemyTanks();
    void addEnemyTankBullets();  // ���з�̹���Ƿ���Ҫ����ը��
    void addBulletToMap(BombType type, const string &who_own_me, Direction the_direction, short x, short y, int color = 0xA, short speed = 3);  // ���ͼ֮�����ը�����ɵ�ͼ������ʾ��
    void addTime();  //

    void initializeEnemyTanks();  // �ø�����Ϸ�Ѷȳ�ʼ���з�̹�˵�����
    void initializePlayerTanks();
        
    void setGameLevel(const string &level);  // �õ���Ϸ�Ѷ�
    void setPlayerNums(short players);
    
    vector<PlayerTank> & getThePlayerTanks();
    int getPlayerNums();  // ����������
    
    void displayOnlyBoundary();
    void displayOnlyPlayerInfo();
    void display();  // ���ڴ˺�������ĺ�������Ҫ�����ڵ���
    void displayOnlyPlayerScore();  // ��ʾ��ҵ÷�
    void displayOnlyTargetAndDefenceWalls();  // ��ʾĿ��ͱ���Ŀ���ǽ
    void displayOnlyPlayerTanks();  // ��ʾ���̹��
    void displayOnlyMyMap();  // ��ʾ��ͼ��Դ��Ҳ���Ǹ������͵�ǽ��
    void displayOnlyEnemyTanks();  // ��ʾ�з�̹��
    void displayOnlyAllBullets();  // ��ʾ����ը��
};

#endif //TANK_BATTLE_MAP_H
