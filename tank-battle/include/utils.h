#ifndef TANK_BATTLE_UTILS_H
#define TANK_BATTLE_UTILS_H

#include "rect.h"
#include "tank.h"
#include "wall.h"
#include "target.h"
#include "boundary.h"
#include "bullet.h"
#include <Windows.h>


class Utils {
public:
    static void setWindowSize(SHORT left, SHORT top, SHORT right, SHORT bottem);  // 设置游戏窗口大小
    static void setCursorPosition(SHORT x, SHORT y);  // 设置打印时光标的位置
    static void setTextColor(WORD color);  // 设置打印的字符的颜色，color 用 16 进制
    static void hideCursor();  // 隐藏光标
    
    static void testTheTextColor();  // 测试颜色
    static void testTheKeyValue();  // 测试键值
    
    static bool isPointPassThroughObject(Bullet &bullet, Rect &rect);  // 判断点是否越过物体
    static bool isPointInRect(short x, short y, Rect &rect);  // 判断点是否位于一个矩形内部
    static bool isOverlapped(Rect &rect_1, Rect &rect_2);  // 判断两个矩形是否重叠
    
    static bool hasCollisionTankWithTank(Tank &tank_1, Tank &tank_2);
    static bool hasCollisionTankWithWall(Tank &tank, Wall &wall);
    static bool hasCollisionTankWithTarget(Tank &tank, Target &target);   
    static bool hasCollisionBulletWithTank(Bullet &bullet, Tank &tank);
    static bool hasCollisionBulletWithWall(Bullet &bullet, Wall &wall);
    static bool hasCollisionBulletWithTarget(Bullet &bullet, Target &target);
    // 纯粹是为了另一个敌方节省空间
    static bool helpEnemyTanksToLaunch(Direction direction, short &x, short &y);
};

#endif //TANK_BATTLE_UTILS_H
