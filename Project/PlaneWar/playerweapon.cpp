#include "playerweapon.h"

PlayerWeapon::PlayerWeapon()
{


}

PlayerWeapon::~PlayerWeapon()
{
    weapon_timer->stop();
    delete weapon_timer;
}
void PlayerWeapon::init(int kind)
{
    this->kind = kind;
    weapon_timer = new QTimer();
    switch(kind){
    case 1:
        init1();
        break;
    case 2:
        init2();
        break;
    case 3:
        init3();
        break;
    case 4:
        init4();
        break;
        }
        weapon_timer->setInterval(interval);
        weapon_timer->setSingleShot(true);
        weapon_timer->start();
}


void PlayerWeapon::init1()
{
    interval = PLAYERWEAPON1_INTERVAL;
    speed = PLAYERWEAPON1_SPEED;
    damage = PLAYERWEAPON1_DAMAGE;

}
void PlayerWeapon::init2()
{
    interval = PLAYERWEAPON2_INTERVAL;
    speed = PLAYERWEAPON2_SPEED;
    damage = PLAYERWEAPON2_DAMAGE;

}
void PlayerWeapon::init3()
{
    interval = PLAYERWEAPON3_INTERVAL;
    speed = PLAYERWEAPON3_SPEED;
    damage = PLAYERWEAPON3_DAMAGE;


}
void PlayerWeapon::init4()
{
    interval = PLAYERWEAPON4_INTERVAL;
    speed = PLAYERWEAPON4_SPEED;
    damage = PLAYERWEAPON4_DAMAGE;


}

