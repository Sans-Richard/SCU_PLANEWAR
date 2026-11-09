#ifndef PLAYERWEAPON_H
#define PLAYERWEAPON_H
#include "weapon.h"

class PlayerWeapon:public Weapon
{
public:
    PlayerWeapon();
    ~PlayerWeapon();
    void init(int kind);
    int kind;
    QTimer* weapon_timer = nullptr;

    void init1();
    void init2();
    void init3();
    void init4();

};

#endif // PLAYERWEAPON_H
