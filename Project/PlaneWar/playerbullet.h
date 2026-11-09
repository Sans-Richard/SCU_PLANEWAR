#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H
#include "bullet.h"
#include "playerweapon.h"
#include "enemyplanepool.h"

class EnemyPlane;


class PlayerBullet:public Bullet
{
public:
    PlayerBullet();
    void init(int bullet_kind, PlayerWeapon* playerweapon);
    void init1();
    void init2();
    void init3();
    void init4();
    int kind;

    void move();
    void move1();
    void move2();
    void move3();
    void move4();

    void destroy();

     void collide_with_enemyplane(EnemyPlane* enemyplane);
    int owner = 0;
};

#endif // PLAYERBULLET_H
