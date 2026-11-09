#ifndef WEAPON_H
#define WEAPON_H
#include "config.h"

class Weapon:public QGraphicsPixmapItem
{
public:
    Weapon();

    int interval = 10;
    double speed = 0;
    //是否按下对应攻击键
    bool is_continuously_shooting = false;
    double damage = 0;
};

#endif // WEAPON_H
