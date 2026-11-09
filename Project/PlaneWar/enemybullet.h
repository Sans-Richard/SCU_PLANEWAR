#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#include "bullet.h"
#include "enemyweapon.h"
#include "playerplane.h"


class PlayerPlane;
class EnemyBullet:public Bullet
{
public:
    EnemyBullet();
    void init(int bullet_kind, EnemyWeapon* enemyweapon);
    void init1();
    void init2();
    void init3();
    void init4();
    void init5();//pvp玩家2
    int kind;
    int bullet4_kind = 0;

    void move(PlayerPlane* playerplane1, PlayerPlane* playerplane2, int kind,int bullet4_kind);
    void move1();
    void move2();
    void move3(PlayerPlane* playerplane1, PlayerPlane* playerplane2);
    void move4(int bullet4_kind);
    void move5();
    void move_boss(); // boss子弹自定义方向移动


    void destroy();

    void collide_with_playerplane();


    qint64 borntime;
    double finalDirX = 0;
    double finalDirY = 1; // 默认向下

};

#endif // ENEMYBULLET_H
