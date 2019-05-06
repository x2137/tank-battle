#include "../include/welcome.h"
#include "../include/utils.h"
#include <conio.h>
#include <iostream>

using std::cout;


Hello::Hello(short who) {
    this->who_has_color = who;

    for (short i = 1; i < 69; ++i) {  // ���ﹹ����Ҫ��ʾ�ķ��������
        this->my_wall.emplace_back(Wall(i, 25, 1, 1));
        this->my_wall.emplace_back(Wall(i, 40, 1, 1));
        this->my_wall.emplace_back(Wall(i, 43, 1, 1, "��"));
        this->my_wall.emplace_back(Wall(i, 46, 1, 1, "��"));
        this->my_wall.emplace_back(Wall(i, 49, 1, 1, "��"));
        this->my_wall.emplace_back(Wall(i, 52, 1, 1, "��"));
    }
    // �ϲ�����
    this->my_wall.emplace_back(Wall(23, 14, 1, 1, "��"));
    this->my_wall.emplace_back(Wall(29, 18, 1, 1, "��"));
    this->my_wall.emplace_back(Wall(37, 16, 1, 1, "��"));
    this->my_wall.emplace_back(Wall(43, 15, 1, 1, "��"));
    this->my_wall.emplace_back(Wall(34, 17, 1, 1, "��"));
    // �²�����
    this->my_wall.emplace_back(Wall(19, 37, 1, 1, "��"));
    this->my_wall.emplace_back(Wall(24, 36, 1, 1, "��"));
    this->my_wall.emplace_back(Wall(29, 34, 1, 1, "��"));
    this->my_wall.emplace_back(Wall(33, 32, 1, 1, "��"));
    this->my_wall.emplace_back(Wall(36, 30, 1, 1, "��"));
    this->my_wall.emplace_back(Wall(39, 32, 1, 1, "��"));
    this->my_wall.emplace_back(Wall(43, 34, 1, 1, "��"));
    this->my_wall.emplace_back(Wall(47, 36, 1, 1, "��"));
    this->my_wall.emplace_back(Wall(51, 37, 1, 1, "��"));
    this->my_wall.emplace_back(Wall(57, 38, 1, 1, "��"));

    this->my_tank.emplace_back(PlayerTank(9, 14, 3, 3, UP, "show", 100, 2, false, 0, 1));
    this->my_tank.emplace_back(PlayerTank(7, 17, 3, 3, UP, "show", 100, 2, false, 0, 1));
    this->my_tank.emplace_back(PlayerTank(11, 17, 3, 3, UP, "show", 100, 2, false, 0, 1));
    this->my_tank.emplace_back(PlayerTank(5, 20, 3, 3, UP, "show", 100, 2, false, 0, 1));
    this->my_tank.emplace_back(PlayerTank(9, 20, 3, 3, UP, "show", 100, 2, false, 0, 1));
    this->my_tank.emplace_back(PlayerTank(13, 20, 3, 3, UP, "show", 100, 2, false, 0, 1));

    this->my_tank.emplace_back(PlayerTank(57, 14, 3, 3, UP, "show", 100, 2, false, 0, 1));
    this->my_tank.emplace_back(PlayerTank(55, 17, 3, 3, UP, "show", 100, 2, false, 0, 1));
    this->my_tank.emplace_back(PlayerTank(59, 17, 3, 3, UP, "show", 100, 2, false, 0, 1));
    this->my_tank.emplace_back(PlayerTank(53, 20, 3, 3, UP, "show", 100, 2, false, 0, 1));
    this->my_tank.emplace_back(PlayerTank(57, 20, 3, 3, UP, "show", 100, 2, false, 0, 1));
    this->my_tank.emplace_back(PlayerTank(61, 20, 3, 3, UP, "show", 100, 2, false, 0, 1));
}

void Hello::setColorStatus(short who) {
    this->who_has_color = who;
}

void Hello::setGameLevel(const string &level) {
    this->game_level = level;
}

void Hello::selectPlayerNums() {
    short level = this->players;
    bool has_selected_players = false;

    while (true) {
        if (!has_selected_players) {
            Utils::setCursorPosition(PLAYER_NUM_X, PUBLIC_Y);
            Utils::setTextColor(0x73);
            cout << "Player Num:";
            Utils::setTextColor(0x7);
            cout << " " << this->players;
            Utils::hideCursor();
            switch (level)
            {
            case 1:
                Utils::setCursorPosition(PLAYER_NUM_X + 1, PUBLIC_Y + 2);
                Utils::setTextColor(0x73);
                cout << "1";
                Utils::setTextColor(0x7);
                Utils::setCursorPosition(PLAYER_NUM_X + 1, PUBLIC_Y + 4);
                cout << "2";
                Utils::hideCursor();
                break;
            case 2:
                Utils::setCursorPosition(PLAYER_NUM_X + 1, PUBLIC_Y + 2);
                cout << "1";
                Utils::setCursorPosition(PLAYER_NUM_X + 1, PUBLIC_Y + 4);
                Utils::setTextColor(0x73);
                cout << "2";
                Utils::setTextColor(0x7);
                Utils::hideCursor();
                break;
            }
            Utils::setCursorPosition(LEVEL_POS_X, PUBLIC_Y);
            cout << "Game Level:";
            cout << " " << this->game_level;
            Utils::setCursorPosition(PLAY_POS_X, PUBLIC_Y);
            cout << "Play";
            Utils::setCursorPosition(EXIT_POS_X, PUBLIC_Y);
            cout << "Exit";
            Utils::hideCursor();
        }
        else {
            this->press_enter = false;
            Utils::setCursorPosition(PLAYER_NUM_X, PUBLIC_Y);
            cout << "                  ";
            Utils::setCursorPosition(PLAYER_NUM_X + 1, PUBLIC_Y + 2);
            cout << "      ";
            Utils::setCursorPosition(PLAYER_NUM_X + 1, PUBLIC_Y + 4);
            cout << "      ";
            Utils::hideCursor();
            break;
        }
        // �������¼�
        int key;
        if (_kbhit()) {
            key = _getch();
            if (key == 224) {
                key = _getch();
                switch (key) {
                case 77:  // ��
                case 80:  // ��
                    if (level == 1) level = 2;
                    break;
                case 75:  // ��
                case 72:  // ��
                    if (level == 2) level = 1;
                    break;
                }
            }
            else if (key == 13) {
                has_selected_players = true;
                switch (level) {
                case 1:
                    this->players = 1;
                    break;
                case 2:
                    this->players = 2;
                    break;
                }
            }
        }
    }
}

void Hello::selectGameLeval() {
    int level = 0;  // ʵ�������ĸ�����ֻ�а��� enter ����ȷ����
    // ���� game_level ��ֵȷ����ʼ level ��ֵ
    if (this->game_level == "Easy") level = 0;
    else if (this->game_level == "Normal") level = 1;
    else if (this->game_level == "Hard") level = 2;
    else if (this->game_level == "Hell") level = 3;

    bool has_selected_level = false;
    while (true) {
        if (!has_selected_level) {
            Utils::setCursorPosition(PLAYER_NUM_X, PUBLIC_Y);
            cout << "Player Num:";
            cout << " " << this->players;
            Utils::setCursorPosition(LEVEL_POS_X, PUBLIC_Y);
            Utils::setTextColor(0x73);
            cout << "Game Level:";
            Utils::setTextColor(0x7);
            cout << " " << this->game_level;
            Utils::hideCursor();  // ���ع��
            switch (level) {
            case 0:
                Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 2);
                Utils::setTextColor(0x73);
                cout << "Easy";
                Utils::setTextColor(0x7);
                Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 4);
                cout << "Normal";
                Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 6);
                cout << "Hard";
                Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 8);
                cout << "Hell";
                Utils::hideCursor();  // ���ع��
                break;
            case 1:
                Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 2);
                cout << "Easy";
                Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 4);
                Utils::setTextColor(0x73);
                cout << "Normal";
                Utils::setTextColor(0x7);
                Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 6);
                cout << "Hard";
                Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 8);
                cout << "Hell";
                Utils::hideCursor();  // ���ع��
                break;
            case 2:
                Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 2);
                cout << "Easy";
                Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 4);
                cout << "Normal";
                Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 6);
                Utils::setTextColor(0x73);
                cout << "Hard";
                Utils::setTextColor(0x7);
                Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 8);
                cout << "Hell";
                Utils::hideCursor();  // ���ع��
                break;
            case 3:
                Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 2);
                cout << "Easy";
                Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 4);
                cout << "Normal";
                Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 6);
                cout << "Hard";
                Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 8);
                Utils::setTextColor(0x73);
                cout << "Hell";
                Utils::setTextColor(0x7);
                Utils::hideCursor();  // ���ع��
                break;
            }
            Utils::setCursorPosition(PLAY_POS_X, PUBLIC_Y);
            cout << "Play";
            Utils::setCursorPosition(EXIT_POS_X, PUBLIC_Y);
            cout << "Exit";
            Utils::hideCursor();  // ���ع��
        }
        else {
            this->press_enter = false;  // ��Ҫ�˳�ѡ���Ѷ�ѭ�����ʽ��������Ϊ false
            // ��Ҫ��ѡ��ʱ��������ʾ�����
            Utils::setCursorPosition(LEVEL_POS_X, PUBLIC_Y);
            cout << "                                  ";  // ������Ϊ��������Normal������ϳ��ĵ��ʵĴ�ӡЧ��
            Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 2);
            cout << "    ";
            Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 4);
            cout << "      ";
            Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 6);
            cout << "    ";
            Utils::setCursorPosition(LEVEL_POS_X + 1, PUBLIC_Y + 8);
            cout << "    ";
            break;
        }
        // �������¼�
        int key;
        if (_kbhit()) {
            key = _getch();
            if (key == 224) {
                key = _getch();
                switch (key) {
                case 77:  // ��
                case 80:  // ��
                    if (level < 3) ++level;
                    break;
                case 75:  // ��
                case 72:  // ��
                    if (level > 0) --level;
                    break;
                }
            }
            else if (key == 13) {
                has_selected_level = true;
                switch (level) {
                case 0:
                    this->setGameLevel("Easy");
                    break;
                case 1:
                    this->setGameLevel("Normal");
                    break;
                case 2:
                    this->setGameLevel("Hard");
                    break;
                case 3:
                    this->setGameLevel("Hell");
                    break;
                }
            }
        }
    }
}

void Hello::showWhoseColor() {
    switch (this->who_has_color) {
    case 0:  // Ĭ�Ϲ��λ��ѡ����Ϸ������
        if (this->press_enter) {  // �����괦�� level�����Ұ����� enter����ôչ�������������ѡ��
            this->selectPlayerNums();
        }
        else {
            Utils::setCursorPosition(PLAYER_NUM_X, PUBLIC_Y);
            Utils::setTextColor(0x73);
            cout << "Player Num:";
            Utils::setTextColor(0x7);
            cout << " " << this->players;
            Utils::setCursorPosition(LEVEL_POS_X, PUBLIC_Y);
            cout << "Game Level:";
            cout << " " << this->game_level;
            Utils::setCursorPosition(PLAY_POS_X, PUBLIC_Y);
            cout << "Play";
            Utils::setCursorPosition(EXIT_POS_X, PUBLIC_Y);
            cout << "Exit";
            Utils::hideCursor();
        }
        break;
    case 1:
        if (this->press_enter) {
            this->selectGameLeval();
        }
        else {
            Utils::setCursorPosition(PLAYER_NUM_X, PUBLIC_Y);
            cout << "Player Num:";
            cout << " " << this->players;
            Utils::setCursorPosition(LEVEL_POS_X, PUBLIC_Y);
            Utils::setTextColor(0x73);
            cout << "Game Level:";
            Utils::setTextColor(0x7);
            cout << " " << this->game_level;
            Utils::setCursorPosition(PLAY_POS_X, PUBLIC_Y);
            cout << "Play";
            Utils::setCursorPosition(EXIT_POS_X, PUBLIC_Y);
            cout << "Exit";
            Utils::hideCursor();
        }
        break;
    case 2:
        Utils::setCursorPosition(PLAYER_NUM_X, PUBLIC_Y);
        cout << "Player Num:";
        cout << " " << this->players;
        Utils::setCursorPosition(LEVEL_POS_X, PUBLIC_Y);
        cout << "Game Level: " << this->game_level;
        Utils::setCursorPosition(PLAY_POS_X, PUBLIC_Y);
        Utils::setTextColor(0x73);
        cout << "Play";
        Utils::setTextColor(0x7);
        Utils::setCursorPosition(EXIT_POS_X, PUBLIC_Y);
        cout << "Exit";
        Utils::hideCursor();
        break;
    case 3:
        Utils::setCursorPosition(PLAYER_NUM_X, PUBLIC_Y);
        cout << "Player Num:";
        cout << " " << this->players;
        Utils::setCursorPosition(LEVEL_POS_X, PUBLIC_Y);
        cout << "Game Level: " << this->game_level;
        Utils::setCursorPosition(PLAY_POS_X, PUBLIC_Y);
        cout << "Play";
        Utils::setCursorPosition(EXIT_POS_X, PUBLIC_Y);
        Utils::setTextColor(0x73);
        cout << "Exit";
        Utils::setTextColor(0x7);
        Utils::hideCursor();
        break;
    }
}

void Hello::chooseToPlayOrLeave() {
    int key;
    if (_kbhit()) {  // ����а�������
        key = _getch();
        if (!this->press_enter) {  // ��û�а���ȷ����ʱ�������Խ���ѡ��
            if (key == 224) {
                key = _getch();
                if (key == 77) {  // Ҫ����ʱ���λ�ںδ������� who_has_color �����üӻ��Ǹü�
                    switch (this->who_has_color) {
                    case 0:
                        setColorStatus(1);
                        break;
                    case 1:
                        setColorStatus(2);
                        break;
                    case 2:
                        setColorStatus(3);
                        break;
                    }
                }
                else if (key == 75) {
                    switch (this->who_has_color) {
                    case 3:
                        setColorStatus(2);
                        break;
                    case 2:
                        setColorStatus(1);
                        break;
                    case 1:
                        setColorStatus(0);
                        break;
                    }
                }
            }
            else if (key == 13) this->press_enter = true;
            else this->press_enter = false;  // ��������
        }
    }
}

void Hello::show() {  // �����ʼ������Ҫ��ʲô�����ݣ�ֻ������������������
    Utils::setCursorPosition(28, 5);
    Utils::setTextColor(0xA);
    cout << "Welcome to Tank Battle!";
    Utils::setCursorPosition(33, 7);
    Utils::setTextColor(0xA);
    cout << "�������� Hello, my dear players, enjoy yourselves!";
    Utils::setTextColor(0x7);
    for (auto wall : this->my_wall) {
        wall.show();
    }
    for (auto tank : this->my_tank) {
        tank.show();
    }

    while (true) {  // ���������ѡ����ô���޷�������һ��������ѡ��
        this->chooseToPlayOrLeave();
        this->showWhoseColor();

        if (this->press_enter && (this->who_has_color != 0 || this->who_has_color != 1)) break;
    }
}


short Hello::getWhoArePressed() {
    return this->who_has_color;
}

const string Hello::getTheGameLevel() {
    return this->game_level;
}

short Hello::getThePlayerNums() {
    return this->players;
}
