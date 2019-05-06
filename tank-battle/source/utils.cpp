#include "../include/utils.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <conio.h>


void Utils::setWindowSize(SHORT left, SHORT top, SHORT right, SHORT bottem) {
    HANDLE h_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD buffer_size = { right - left + 1, bottem - top + 1 };
    BOOL is_succeeded = SetConsoleScreenBufferSize(h_stdout, buffer_size);

    SMALL_RECT window_size = { left, top, right, 2 * bottem + 1 };  // ×2 道理同下
    BOOL res = SetConsoleWindowInfo(h_stdout, TRUE, &window_size);
    if (res == 0) {
        int cols = 2 * (right - left + 1);
        int lines = bottem - top + 1;
        std::string op = "mode con cols=" + std::to_string(cols) + " lines=" + std::to_string(lines);
        system(op.c_str());
    }
}

void Utils::setCursorPosition(SHORT x, SHORT y) {
    HANDLE h_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cooredinate = { 2 * x, y };  // ×2 是因为横着的距离比竖着的更窄，所以需要补全
    SetConsoleCursorPosition(h_stdout, cooredinate);
}

void Utils::setTextColor(WORD color) {  // 控制台输出默认颜色是 0x7（记得每次转换之后需要及时转回来）
    HANDLE h_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h_stdout, color);
}

void Utils::hideCursor() {
    HANDLE h_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(h_stdout, &cursor);
    cursor.bVisible = FALSE;
    SetConsoleCursorInfo(h_stdout, &cursor);
}

void Utils::testTheTextColor() {
    Utils::setCursorPosition(20, 0);
    for (int i = 0; i < 16; ++i) {
        Utils::setTextColor(i);
        switch (i) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            std::cout << i << ": " << 100 << std::endl;
            break;
        case 10:
            std::cout << "A" << ": " << 100 << std::endl;
            break;
        case 11:
            std::cout << "B" << ": " << 100 << std::endl;
            break;
        case 12:
            std::cout << "C" << ": " << 100 << std::endl;
            break;
        case 13:
            std::cout << "D" << ": " << 100 << std::endl;
            break;
        case 14:
            std::cout << "E" << ": " << 100 << std::endl;
            break;
        case 15:
            std::cout << "F" << ": " << 100 << std::endl;
            break;
        }
    }
}

void Utils::testTheKeyValue() {
    int key;
    while (true) {
        if (_kbhit()) {
            key = _getch();
            if (key == 13) break;  // enter 键退出
            std::cout << key << std::endl;
            key = 0;
        }
    }
}

bool Utils::isPointInRect(short x, short y, Rect &rect) {
    short r_x = rect.getX();
    short r_y = rect.getY();
    short r_h = rect.getH();
    short r_w = rect.getW();

    if ((x >= r_x && x < (r_x + r_w)) && (y >= r_y && y < (r_y + r_h))) return true;
    else return false;
}

bool Utils::isOverlapped(Rect &rect_1, Rect &rect_2) {
    short x_1 = rect_1.getX();
    short y_1 = rect_1.getY();
    short h_1 = rect_1.getH();
    short w_1 = rect_1.getW();

    short x_2 = rect_2.getX();
    short y_2 = rect_2.getY();
    short h_2 = rect_2.getH();
    short w_2 = rect_2.getW();

    bool one_in_two = false;
    bool two_in_one = false;
    // 判断矩形 1 是否有部分位于矩形 2 中
    if (Utils::isPointInRect(x_1, y_1, rect_2) || Utils::isPointInRect(x_1, y_1 + h_1 - 1, rect_2) ||
        Utils::isPointInRect(x_1 + w_1 - 1, y_1, rect_2) || Utils::isPointInRect(x_1 + w_1 - 1, y_1 + h_1 - 1, rect_2)) {
        one_in_two = true;
    }
    // 判断矩形 2 是否有部分位于矩形 1 中
    if (Utils::isPointInRect(x_2, y_2, rect_1) || Utils::isPointInRect(x_2, y_2 + h_2 - 1, rect_1) ||
        Utils::isPointInRect(x_2 + w_2 - 1, y_2, rect_1) || Utils::isPointInRect(x_2 + w_2 - 1, y_2 + h_2 - 1, rect_1)) {
        two_in_one = true;
    }

    return (one_in_two || two_in_one);
}

bool Utils::hasCollisionTankWithTank(Tank &tank_1, Tank &tank_2) {
    Rect scope_tank_1 = tank_1.getScope();
    Rect scope_tank_2 = tank_2.getScope();

    return Utils::isOverlapped(scope_tank_1, scope_tank_2);
}

bool Utils::hasCollisionTankWithWall(Tank &tank, Wall &wall) {
    Rect tank_scope = tank.getScope();
    Rect wall_scope = wall.getScope();

    return Utils::isOverlapped(tank_scope, wall_scope);
}

bool Utils::hasCollisionTankWithTarget(Tank &tank, Target &target) {
    Rect tank_scope = tank.getScope();
    Rect target_scope = target.getScope();

    return Utils::isOverlapped(tank_scope, target_scope);
}

bool Utils::isPointPassThroughObject(Bullet &bullet, Rect &rect) {
    bool yes = false;
    Direction direction = bullet.getMyDirection();
    short p_x = bullet.getPreScope().getX();
    short p_y = bullet.getPreScope().getY();
    short n_x = bullet.getMyScope().getX();
    short n_y = bullet.getMyScope().getY();

    short x = rect.getX();
    short y = rect.getY();
    short h = rect.getH();
    short w = rect.getW();

    switch (direction) {
    case UP:
        if ((p_x >= x && p_x <= (x + w - 1)) && (p_y >= (y + h - 1))) {
            if (n_y <= (y + h - 1)) yes = true;
        }
        break;
    case DOWN:
        if ((p_x >= x && p_x <= (x + w - 1)) && (p_y <= y)) {
            if (n_y >= y) yes = true;
        }
        break;
    case LEFT:
        if ((p_y >= y && p_y <= (y + h - 1)) && (p_x >= (x + w - 1))) {
            if (n_x <= (x + w - 1)) yes = true;
        }
        break;
    case RIGHT:
        if ((p_y >= y && p_y <= (y + h - 1)) && (p_x <= x)) {
            if (n_x >= x) yes = true;
        }
        break;
    }

    return yes;
}

bool Utils::hasCollisionBulletWithTank(Bullet &bullet, Tank &tank) {
    Rect bullect_scope = bullet.getMyScope();
    Rect tank_scope = tank.getScope();

    bool judge_1 = Utils::isPointPassThroughObject(bullet, tank_scope);
    bool judge_2 = Utils::isOverlapped(bullect_scope, tank_scope);

    return (judge_1 || judge_2);
}

bool Utils::hasCollisionBulletWithTarget(Bullet &bullet, Target &target) {
    Rect bullect_scope = bullet.getMyScope();
    Rect target_scope = target.getScope();

    bool judge_1 = Utils::isPointPassThroughObject(bullet, target_scope);
    bool judge_2 = Utils::isOverlapped(bullect_scope, target_scope);

    return (judge_1 || judge_2);
}

bool Utils::hasCollisionBulletWithWall(Bullet &bullet, Wall &wall) {
    Rect bullect_scope = bullet.getMyScope();
    Rect wall_scope = wall.getScope();

    bool judge_1 = Utils::isPointPassThroughObject(bullet, wall_scope);
    bool judge_2 = Utils::isOverlapped(bullect_scope, wall_scope);

    return (judge_1 || judge_2);
}

bool::Utils::helpEnemyTanksToLaunch(Direction direction, short &m_x, short &m_y) {
    bool generate = true;
    switch (direction)
    {
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

    return generate;
}
