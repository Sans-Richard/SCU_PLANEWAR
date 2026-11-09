#ifndef ENEMYWEAPON_H
#define ENEMYWEAPON_H
#include "weapon.h"

class EnemyWeapon:public Weapon
{
public:
    EnemyWeapon();
    void init(int kind);
    int kind;
    QTimer* weapon_timer = nullptr;

    void init1();
    void init2();
    void init3();
    void init4();
    void init5();
};

#endif // ENEMYWEAPON_H
