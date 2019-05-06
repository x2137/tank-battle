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
        // �������Ϊ 1��ʹ�� 8 4 5 6 L ������Ϸ���������Ϊ 2����� 1 ʹ�� w a s d space ������Ϸ����� 2 ʹ�� 8 4 5 6 L ������Ϸ
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
                    if (m_y <= 0) generate = false;  // �����ӵ���ʱ���Ѿ��ڱ߽�֮���ˣ���ֱ�Ӳ�������
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
            // ��� 1 ���̼��
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
                switch (the_direction) {  // ����̹�˵�λ�þ���ը�����ֵ�λ��
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
            // ��� 2 ���̼��
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
    // ���ÿ���̨����
    SetConsoleTitleA("Tank Battle");

    // ����ֻ��ʾ��Ϸ���棬Ȼ��ʼ����������Ϸ�����뿪
    this->game_map.displayOnlyBoundary();
    this->face->show();
    Utils::hideCursor();

    // ��ȡ��Ϸ�ѶȵĹ��̣�ֻ�еõ��Ѷ���Ϣ���ܳ�ʼ���з�̹��
    const string level = this->face->getTheGameLevel();
    this->game_map.setGameLevel(level);
    this->game_map.initializeEnemyTanks();

    // ��ȡ������������ڵõ������Ϣ���ܳ�ʼ�����̹��
    short player_nums = this->face->getThePlayerNums();
    this->game_map.setPlayerNums(player_nums);
    this->game_map.initializePlayerTanks();
    //
    short go_next = this->face->getWhoArePressed();
    if (go_next == 3) {  // Exit ������
        exit(0);
    }
    else if (go_next == 2) {  // Play ������
        system("cls");

        // ���������ù̶���ʾ��Դ����Ϸ�����в��ᷢ���ı����Դ��
        this->game_map.displayOnlyBoundary();
        this->game_map.displayOnlyPlayerInfo();

        // Ȼ����÷ǹ̶���ʾ��Դ����Ϸ�����л���ʱ�䷢���仯����Դ��
        while (true) {
            // ���ͼ������µ�̹��
            this->game_map.addNewEnemyTanks();
            // ���ͼ����ӵз�̹�˵�ը��
            this->game_map.addEnemyTankBullets();
            
            // ��ײ���
            collisionDetection(this->game_map);
            
            // ����Ƿ������Ϸ����Ӯ����Ϸ
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

            // ��ʾ
            this->game_map.display();
            Sleep(50);
            Utils::hideCursor();

            // �����¼����ȫ�ڸú�����ʵ��
            this->keyboardEvent();
            // ����ʱ��
            this->game_map.addTime();
        }
    }
}
