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
    static void setWindowSize(SHORT left, SHORT top, SHORT right, SHORT bottem);  // ������Ϸ���ڴ�С
    static void setCursorPosition(SHORT x, SHORT y);  // ���ô�ӡʱ����λ��
    static void setTextColor(WORD color);  // ���ô�ӡ���ַ�����ɫ��color �� 16 ����
    static void hideCursor();  // ���ع��
    
    static void testTheTextColor();  // ������ɫ
    static void testTheKeyValue();  // ���Լ�ֵ
    
    static bool isPointPassThroughObject(Bullet &bullet, Rect &rect);  // �жϵ��Ƿ�Խ������
    static bool isPointInRect(short x, short y, Rect &rect);  // �жϵ��Ƿ�λ��һ�������ڲ�
    static bool isOverlapped(Rect &rect_1, Rect &rect_2);  // �ж����������Ƿ��ص�
    
    static bool hasCollisionTankWithTank(Tank &tank_1, Tank &tank_2);
    static bool hasCollisionTankWithWall(Tank &tank, Wall &wall);
    static bool hasCollisionTankWithTarget(Tank &tank, Target &target);   
    static bool hasCollisionBulletWithTank(Bullet &bullet, Tank &tank);
    static bool hasCollisionBulletWithWall(Bullet &bullet, Wall &wall);
    static bool hasCollisionBulletWithTarget(Bullet &bullet, Target &target);
    // ������Ϊ����һ���з���ʡ�ռ�
    static bool helpEnemyTanksToLaunch(Direction direction, short &x, short &y);
};

#endif //TANK_BATTLE_UTILS_H
