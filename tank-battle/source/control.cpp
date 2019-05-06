#include "../include/control.h"
#include "../include/map.h"
#include "../include/utils.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <conio.h>


Controller::Controller(int map) : game_map(map) {
    this->face = new Hello();
}

Controller::Controller(const Controller &new_one) {
    if (this->face == nullptr) this->face = new Hello();
    if (new_one.face != nullptr) {
        *(this->face) = *(new_one.face);
    }
    else {
        delete this->face;
        this->face = nullptr;
    }
}

Controller & Controller::operator=(const Controller &new_one) {
    if (this != &new_one) {
        if (this->face == nullptr) this->face = new Hello();
        if (new_one.face != nullptr) {
            *(this->face) = *(new_one.face);
        }
        else {
            delete this->face;
            this->face = nullptr;
        }
    }
    return *this;
}

Controller::~Controller() {
    if (this->face != nullptr) delete this->face;
}

void Controller::keyboardEvent() {
    int key;
    if (_kbhit()) {
        key = _getch();
        // 玩家数量为 1，使用 8 4 5 6 L 控制游戏，玩家数量为 2，玩家 1 使用 w a s d space 控制游戏，玩家 2 使用 8 4 5 6 L 控制游戏
        switch (this->game_map.getPlayerNums()) {
        case 1:
            if (key == 56) {
                this->game_map.getThePlayerTanks().at(0).changeDirection(UP);
                this->game_map.getThePlayerTanks().at(0).setOverlapStatus(false);
            }
            else if (key == 53) {
                this->game_map.getThePlayerTanks().at(0).changeDirection(DOWN);
                this->game_map.getThePlayerTanks().at(0).setOverlapStatus(false);
            }
            else if (key == 52) {
                this->game_map.getThePlayerTanks().at(0).changeDirection(LEFT);
                this->game_map.getThePlayerTanks().at(0).setOverlapStatus(false);
            }
            else if (key == 54) {
                this->game_map.getThePlayerTanks().at(0).changeDirection(RIGHT);
                this->game_map.getThePlayerTanks().at(0).setOverlapStatus(false);
            }
            else if (key == 108) {
                bool generate = true;
                short the_pattern = this->game_map.getThePlayerTanks().at(0).getMyPattern();
                Direction the_direction = this->game_map.getThePlayerTanks().at(0).getMyDirection();
                short m_x = this->game_map.getThePlayerTanks().at(0).getScope().getX();
                short m_y = this->game_map.getThePlayerTanks().at(0).getScope().getY();
                switch (the_direction) {
                case UP:
                    ++m_x;
                    --m_y;
                    if (m_y <= 0) generate = false;  // 产生子弹的时候已经在边界之外了，就直接不产生了
                    break;
                case DOWN:
                    ++m_x;
                    m_y += 3;
                    if (m_y >= 52) generate = false;
                    break;
                case LEFT:
                    --m_x;
                    ++m_y;
                    if (m_x <= 0) generate = false;
                    break;
                case RIGHT:
                    m_x += 3;
                    ++m_y;
                    if (m_x >= 68) generate = false;
                    break;
                }
                if (generate) {
                    if (the_pattern == 0) this->game_map.addBulletToMap(WEAK, "player_1", the_direction, m_x, m_y, 0xB);
                }
                }
            break;
        case 2:
            // 玩家 1 键盘检测
            if (key == 119) {
                this->game_map.getThePlayerTanks().at(0).changeDirection(UP);
                this->game_map.getThePlayerTanks().at(0).setOverlapStatus(false);
            }
            else if (key == 115) {
                this->game_map.getThePlayerTanks().at(0).changeDirection(DOWN);
                this->game_map.getThePlayerTanks().at(0).setOverlapStatus(false);
            }
            else if (key == 97) {
                this->game_map.getThePlayerTanks().at(0).changeDirection(LEFT);
                this->game_map.getThePlayerTanks().at(0).setOverlapStatus(false);
            }
            else if (key == 100) {
                this->game_map.getThePlayerTanks().at(0).changeDirection(RIGHT);
                this->game_map.getThePlayerTanks().at(0).setOverlapStatus(false);
            }
            else if (key == 32) {
                bool generate = true;
                short the_pattern = this->game_map.getThePlayerTanks().at(0).getMyPattern();
                Direction the_direction = this->game_map.getThePlayerTanks().at(0).getMyDirection();
                short m_x = this->game_map.getThePlayerTanks().at(0).getScope().getX();
                short m_y = this->game_map.getThePlayerTanks().at(0).getScope().getY();
                switch (the_direction) {  // 根据坦克的位置决定炸弹出现的位置
                case UP:
                    ++m_x;
                    --m_y;
                    if (m_y <= 0) generate = false;
                    break;
                case DOWN:
                    ++m_x;
                    m_y += 3;
                    if (m_y >= 52) generate = false;
                    break;
                case LEFT:
                    --m_x;
                    ++m_y;
                    if (m_x <= 0) generate = false;
                    break;
                case RIGHT:
                    m_x += 3;
                    ++m_y;
                    if (m_x >= 68) generate = false;
                    break;
                }
                if (generate) {
                    if (the_pattern == 0) this->game_map.addBulletToMap(WEAK, "player_1", the_direction, m_x, m_y, 0xB);
                }
            }
            // 玩家 2 键盘检测
            else if (key == 56) {
                this->game_map.getThePlayerTanks().at(1).changeDirection(UP);
                this->game_map.getThePlayerTanks().at(1).setOverlapStatus(false);
            }
            else if (key == 53) {
                this->game_map.getThePlayerTanks().at(1).changeDirection(DOWN);
                this->game_map.getThePlayerTanks().at(1).setOverlapStatus(false);
            }
            else if (key == 52) {
                this->game_map.getThePlayerTanks().at(1).changeDirection(LEFT);
                this->game_map.getThePlayerTanks().at(1).setOverlapStatus(false);
            }
            else if (key == 54) {
                this->game_map.getThePlayerTanks().at(1).changeDirection(RIGHT);
                this->game_map.getThePlayerTanks().at(1).setOverlapStatus(false);
            }
            else if (key == 108) {
                bool generate = true;
                short the_pattern = this->game_map.getThePlayerTanks().at(1).getMyPattern();
                Direction the_direction = this->game_map.getThePlayerTanks().at(1).getMyDirection();
                short m_x = this->game_map.getThePlayerTanks().at(1).getScope().getX();
                short m_y = this->game_map.getThePlayerTanks().at(1).getScope().getY();
                switch (the_direction) {
                case UP:
                    ++m_x;
                    --m_y;
                    if (m_y <= 0) generate = false;
                    break;
                case DOWN:
                    ++m_x;
                    m_y += 3;
                    if (m_y >= 52) generate = false;
                    break;
                case LEFT:
                    --m_x;
                    ++m_y;
                    if (m_x <= 0) generate = false;
                    break;
                case RIGHT:
                    m_x += 3;
                    ++m_y;
                    if (m_x >= 68) generate = false;
                    break;
                }
                if (generate) {
                    if (the_pattern == 0) this->game_map.addBulletToMap(WEAK, "player_2", the_direction, m_x, m_y, 0xB);
                }
            }
            break;
        }
    }
}

void Controller::congratulations() {
    for (int i = 10; i < 40; ++i) {
        for (int j = 10; j < 30; ++j) {
            Utils::setCursorPosition(i, j);
            std::cout << "  ";
        }
    }
    Utils::setCursorPosition(15, 20);
    Utils::setTextColor(0xC);
    std::cout << "Congratulations, you win the game!";
    Utils::setTextColor(7);
    Utils::hideCursor();
}

void Controller::whatAShame() {
    for (int i = 10; i < 50; ++i) {
        for (int j = 10; j < 30; ++j) {
            Utils::setCursorPosition(i, j);
            std::cout << "  ";
        }
    }
    Utils::setCursorPosition(13, 20);
    Utils::setTextColor(0xC);
    std::cout << "What a shame, you lost the game, but no problem, keep going!";
    Utils::setTextColor(7);
    Utils::hideCursor();
}

void Controller::go() {
    Utils::hideCursor();
    // 设置控制台名称
    SetConsoleTitleA("Tank Battle");

    // 首先只显示游戏界面，然后开始做抉择是游戏还是离开
    this->game_map.displayOnlyBoundary();
    this->face->show();
    Utils::hideCursor();

    // 获取游戏难度的过程，只有得到难度消息才能初始化敌方坦克
    const string level = this->face->getTheGameLevel();
    this->game_map.setGameLevel(level);
    this->game_map.initializeEnemyTanks();

    // 获取玩家人数，至于得到玩家消息才能初始化玩家坦克
    short player_nums = this->face->getThePlayerNums();
    this->game_map.setPlayerNums(player_nums);
    this->game_map.initializePlayerTanks();
    //
    short go_next = this->face->getWhoArePressed();
    if (go_next == 3) {  // Exit 被按下
        exit(0);
    }
    else if (go_next == 2) {  // Play 被按下
        system("cls");

        // 接下来调用固定显示资源（游戏过程中不会发生改变的资源）
        this->game_map.displayOnlyBoundary();
        this->game_map.displayOnlyPlayerInfo();

        // 然后调用非固定显示资源（游戏过程中会随时间发生变化的资源）
        while (true) {
            // 向地图中添加新的坦克
            this->game_map.addNewEnemyTanks();
            // 向地图中添加敌方坦克的炸弹
            this->game_map.addEnemyTankBullets();
            
            // 碰撞检测
            collisionDetection(this->game_map);
            
            // 检查是否输掉游戏或者赢下游戏
            bool win = this->game_map.win();
            bool lose = this->game_map.lose();
            if (win) {
                this->congratulations();
                break;
            }
            if (lose) {
                this->whatAShame();
                break;
            }

            // 显示
            this->game_map.display();
            Sleep(50);
            Utils::hideCursor();

            // 键盘事件检测全在该函数内实现
            this->keyboardEvent();
            // 增加时间
            this->game_map.addTime();
        }
    }
}
