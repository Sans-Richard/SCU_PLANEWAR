#include "enemyweapon.h"

EnemyWeapon::EnemyWeapon()
{
    weapon_timer = new QTimer();//目的同敌机

}
void EnemyWeapon::init(int kind)
{
    this->kind = kind;
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
    case 5:
        init5();
        break;
        }
        weapon_timer->setInterval(interval);
        weapon_timer->setSingleShot(true);
        weapon_timer->start();
}


void EnemyWeapon::init1()
{
    interval = ENEMYWEAPON1_INTERVAL;
    speed = ENEMYWEAPON1_SPEED;
    damage = ENEMYWEAPON1_DAMAGE;

}
void EnemyWeapon::init2()
{
    interval = ENEMYWEAPON2_INTERVAL;
    speed = ENEMYWEAPON2_SPEED;
    damage = ENEMYWEAPON2_DAMAGE;


}
void EnemyWeapon::init3()
{
    interval = ENEMYWEAPON3_INTERVAL;
    speed = ENEMYWEAPON3_SPEED;
    damage = ENEMYWEAPON3_DAMAGE;
}
void EnemyWeapon::init4()
{
    interval = ENEMYWEAPON4_INTERVAL;
    speed = ENEMYWEAPON4_SPEED;
    damage = ENEMYWEAPON4_DAMAGE;
}
void EnemyWeapon::init5()
{
    interval = PLAYERWEAPON1_INTERVAL;
    speed = PLAYERWEAPON1_SPEED;
    damage = PLAYERWEAPON1_DAMAGE + 5;

}


