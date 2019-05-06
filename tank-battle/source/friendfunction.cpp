#include "../include/map.h"
#include "../include/utils.h"


void changeStatus(Tank &tank, bool status = true) {
    tank.setOverlapStatus(status);
    tank.setScope(tank.getPreScope());  // 如果发生重叠，需要将当前坐标设置为之前的坐标
}

void collisionDetection(Map &map) {
    // 子弹和其他物体碰撞
    if (map.my_bullets.size() != 0) {
        for (auto &bullet : map.my_bullets) {
            BombType type = bullet.getMyType();
            string owner = bullet.getTheOwner();
            bool yes = false;
            // 和 soft wall
            for (auto &soft_wall : map.soft_walls) {
                if (Utils::hasCollisionBulletWithWall(bullet, soft_wall)) {
                    if (type == STRONG) soft_wall.setTheStatus(true);
                    else soft_wall.decreaseBloodVolume(50);
                    bullet.setMyStatus(true);
                    yes = true;
                    break;
                }
            }
            if (yes) continue;  // 一颗炸弹已经发生了碰撞，所以不可能再和其他东西碰撞
            // 和 hard wall
            for (auto &hard_wall : map.hard_walls) {
                if (Utils::hasCollisionBulletWithWall(bullet, hard_wall)) {
                    if (type == STRONG) hard_wall.setTheStatus(true);
                    bullet.setMyStatus(true);
                    yes = true;
                    break;
                }
            }
            if (yes) continue;
            // 和 defence wall
            for (auto &defence_wall : map.target_defence_walls) {
                if (Utils::hasCollisionBulletWithWall(bullet, defence_wall)) {
                    if (owner == "enemy") defence_wall.setTheStatus(true);
                    bullet.setMyStatus(true);
                    yes = true;
                    break;
                }
            }
            if (yes) continue;
            // 和 target
            if (Utils::hasCollisionBulletWithTarget(bullet, *(map.my_target))) {
                if (owner == "enemy") (map.my_target)->setStatus(true);
                bullet.setMyStatus(true);
                yes = true;
            }
            if (yes) continue;
            // 和 player tank
            for (auto &tank : map.player_tanks) {
                if (Utils::hasCollisionBulletWithTank(bullet, tank)) {
                    if (owner == "enemy")  tank.decreaseBloodVolume(50);
                    bullet.setMyStatus(true);
                    yes = true;
                    break;
                }
            }
            if (yes) continue;
            // 和 enemy tank
            for (auto &tank : map.pos1_enemy_tanks) {
                if (Utils::hasCollisionBulletWithTank(bullet, tank)) {
                    if (owner == "player_1") {
                        tank.decreaseBloodVolume(50);
                        if (tank.getBloodVolume() <= 0) {
                            map.player_tanks.at(0).setMyScore(0);  // 只有 0 类，其他类没实现
                        }
                    }
                    else if (owner == "player_2") {
                        tank.decreaseBloodVolume(50);
                        if (tank.getBloodVolume() <= 0) {
                            map.player_tanks.at(1).setMyScore(0);
                        }
                    }
                    bullet.setMyStatus(true);
                    yes = true;
                    break;
                }
            }
            if (yes) continue;

            for (auto &tank : map.pos2_enemy_tanks) {
                if (Utils::hasCollisionBulletWithTank(bullet, tank)) {
                    if (owner == "player_1") {
                        tank.decreaseBloodVolume(50);
                        if (tank.getBloodVolume() <= 0) {
                            map.player_tanks.at(0).setMyScore(0);
                        }
                    }
                    else if (owner == "player_2") {
                        tank.decreaseBloodVolume(50);
                        if (tank.getBloodVolume() <= 0) {
                            map.player_tanks.at(1).setMyScore(0);
                        }
                    }
                    bullet.setMyStatus(true);
                    yes = true;
                    break;
                }
            }
            if (yes) continue;

            for (auto &tank : map.pos3_enemy_tanks) {
                if (Utils::hasCollisionBulletWithTank(bullet, tank)) {
                    if (owner == "player_1") {
                        tank.decreaseBloodVolume(50);
                        if (tank.getBloodVolume() <= 0) {
                            map.player_tanks.at(0).setMyScore(0);
                        }
                    }
                    else if (owner == "player_2") {
                        tank.decreaseBloodVolume(50);
                        if (tank.getBloodVolume() <= 0) {
                            map.player_tanks.at(1).setMyScore(0);
                        }
                    }
                    bullet.setMyStatus(true);
                    yes = true;
                    break;
                }
            }
            if (yes) continue;
            // 和 bullet
            for (auto &another_bullet : map.my_bullets) {
                if (&bullet == &another_bullet) continue;
                string the_owner = another_bullet.getTheOwner();
                if (owner != the_owner) {
                    bullet.setMyStatus(true);
                    another_bullet.setMyStatus(true);
                }
                break;
            }
        }
    }

    // 玩家坦克和其他物体碰撞
    for (auto &tank : map.player_tanks) {
        bool yes = false;
        // 和 soft wall
        for (auto &soft_wall : map.soft_walls) {
            if (Utils::hasCollisionTankWithWall(tank, soft_wall)) {
                changeStatus(tank);
                yes = true;
                break;  // 已经和其中一块墙碰撞，就不可能和其他墙发生碰撞
            }
        }
        if (yes) continue;
        // 和 hard wall
        for (auto &hard_wall : map.hard_walls) {
            if (Utils::hasCollisionTankWithWall(tank, hard_wall)) {
                changeStatus(tank);
                yes = true;
                break;
            }
        }
        if (yes) continue;
        // 和 defence wall
        for (auto &defence_wall : map.target_defence_walls) {
            if (Utils::hasCollisionTankWithWall(tank, defence_wall)) {
                changeStatus(tank);
                yes = true;
                break;
            }
        }
        if (yes) continue;
        // 和 target
        if (Utils::hasCollisionTankWithTarget(tank, *(map.my_target))) {
            changeStatus(tank);
            yes = true;
        }
        if (yes) continue;
        // 和 player tank
        for (auto &another_tank : map.player_tanks) {
            if (tank == another_tank) continue;
            if (Utils::hasCollisionTankWithTank(tank, another_tank)) {
                changeStatus(tank);
                break;
            }
        }
        // 和 enemy tank
        for (auto &enemy_tank : map.pos1_enemy_tanks) {
            if (Utils::hasCollisionTankWithTank(tank, enemy_tank)) {
                changeStatus(tank);
            }
        }
        for (auto &enemy_tank : map.pos2_enemy_tanks) {
            if (Utils::hasCollisionTankWithTank(tank, enemy_tank)) {
                changeStatus(tank);
            }
        }
        for (auto &enemy_tank : map.pos3_enemy_tanks) {
            if (Utils::hasCollisionTankWithTank(tank, enemy_tank)) {
                changeStatus(tank);
            }
        }
    }

    // 敌方坦克和其他物体碰撞
    for (auto &tank : map.pos1_enemy_tanks) {
        // 和 soft wall
        for (auto &soft_wall : map.soft_walls) {
            if (Utils::hasCollisionTankWithWall(tank, soft_wall)) {
                changeStatus(tank);
                break;
            }
        }
        // 和 hard wall
        for (auto &hard_wall : map.hard_walls) {
            if (Utils::hasCollisionTankWithWall(tank, hard_wall)) {
                changeStatus(tank);
                break;
            }
        }
        // 和 defence wall
        for (auto &defence_wall : map.target_defence_walls) {
            if (Utils::hasCollisionTankWithWall(tank, defence_wall)) {
                changeStatus(tank);
                break;
            }
        }
        // 和 target
        if (Utils::hasCollisionTankWithTarget(tank, *(map.my_target))) {
            changeStatus(tank);
        }
        // 和 player tank
        for (auto &player_tank : map.player_tanks) {
            if (Utils::hasCollisionTankWithTank(tank, player_tank)) {
                changeStatus(tank);
            }
        }
        // 和 enemy tank
        for (auto &another_tank : map.pos1_enemy_tanks) {
            if (&tank == &another_tank) continue;
            if (Utils::hasCollisionTankWithTank(tank, another_tank)) {
                changeStatus(tank);
            }
        }
        for (auto &another_tank : map.pos2_enemy_tanks) {
            if (Utils::hasCollisionTankWithTank(tank, another_tank)) {
                changeStatus(tank);
            }
        }
        for (auto &another_tank : map.pos3_enemy_tanks) {
            if (Utils::hasCollisionTankWithTank(tank, another_tank)) {
                changeStatus(tank);
            }
        }
    }
    
    for (auto &tank : map.pos2_enemy_tanks) {
        // 和 soft wall
        for (auto &soft_wall : map.soft_walls) {
            if (Utils::hasCollisionTankWithWall(tank, soft_wall)) {
                changeStatus(tank);
                break;
            }
        }
        // 和 hard wall
        for (auto &hard_wall : map.hard_walls) {
            if (Utils::hasCollisionTankWithWall(tank, hard_wall)) {
                changeStatus(tank);
                break;
            }
        }
        // 和 defence wall
        for (auto &defence_wall : map.target_defence_walls) {
            if (Utils::hasCollisionTankWithWall(tank, defence_wall)) {
                changeStatus(tank);
                break;
            }
        }
        // 和 target
        if (Utils::hasCollisionTankWithTarget(tank, *(map.my_target))) {
            changeStatus(tank);
        }
        // 和 player tank
        for (auto &player_tank : map.player_tanks) {
            if (Utils::hasCollisionTankWithTank(tank, player_tank)) {
                changeStatus(tank);
            }
        }
        // 和 enemy tank
        for (auto &another_tank : map.pos1_enemy_tanks) {
            if (Utils::hasCollisionTankWithTank(tank, another_tank)) {
                changeStatus(tank);
            }
        }
        for (auto &another_tank : map.pos2_enemy_tanks) {
            if (&tank == &another_tank) continue;
            if (Utils::hasCollisionTankWithTank(tank, another_tank)) {
                changeStatus(tank);
            }
        }
        for (auto &another_tank : map.pos3_enemy_tanks) {
            if (Utils::hasCollisionTankWithTank(tank, another_tank)) {
                changeStatus(tank);
            }
        }
    }

    for (auto &tank : map.pos3_enemy_tanks) {
        // 和 soft wall
        for (auto &soft_wall : map.soft_walls) {
            if (Utils::hasCollisionTankWithWall(tank, soft_wall)) {
                changeStatus(tank);
                break;
            }
        }
        // 和 hard wall
        for (auto &hard_wall : map.hard_walls) {
            if (Utils::hasCollisionTankWithWall(tank, hard_wall)) {
                changeStatus(tank);
                break;
            }
        }
        // 和 defence wall
        for (auto &defence_wall : map.target_defence_walls) {
            if (Utils::hasCollisionTankWithWall(tank, defence_wall)) {
                changeStatus(tank);
                break;
            }
        }
        // 和 target
        if (Utils::hasCollisionTankWithTarget(tank, *(map.my_target))) {
            changeStatus(tank);
        }
        // 和 player tank
        for (auto &player_tank : map.player_tanks) {
            if (Utils::hasCollisionTankWithTank(tank, player_tank)) {
                changeStatus(tank);
            }
        }
        // 和 enemy tank
        for (auto &another_tank : map.pos1_enemy_tanks) {
            if (Utils::hasCollisionTankWithTank(tank, another_tank)) {
                changeStatus(tank);
            }
        }
        for (auto &another_tank : map.pos2_enemy_tanks) {
            if (Utils::hasCollisionTankWithTank(tank, another_tank)) {
                changeStatus(tank);
            }
        }
        for (auto &another_tank : map.pos3_enemy_tanks) {
            if (&tank == &another_tank) continue;
            if (Utils::hasCollisionTankWithTank(tank, another_tank)) {
                changeStatus(tank);
            }
        }
    }
}
