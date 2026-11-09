#ifndef PLAYERPLANE_H
#define PLAYERPLANE_H
#include "plane.h"
#include "playerweapon.h"
#include "playerbullet.h"
#include "playerbulletpool.h"

class EnemyBullet;
class EnemyPlane;
class PlayerBulletPool;

class PlayerPlane:public Plane
{
public:
    PlayerPlane();
    ~PlayerPlane();//防止内存泄露
    int kind=1;
    //三个等级武器
    PlayerWeapon *weapon1 = nullptr, *weapon2 = nullptr, *weapon3 = nullptr;
    void init(int kind);
    void init_1();
    void init_2();


    //驱动武器发射子弹
    void weapon1_shoot(PlayerBulletPool* playerbullet_pool, QGraphicsScene* level_scene);
    void weapon2_shoot(PlayerBulletPool* playerbullet_pool, QGraphicsScene* level_scene);
    void weapon3_shoot(PlayerBulletPool* playerbullet_pool, QGraphicsScene* level_scene);



    void collide_with_enemybullet(EnemyBullet* enemybullet);

    void collide_with_enemyplane(EnemyPlane* enemyplane);

    //护盾对象
    QGraphicsPixmapItem* shield = nullptr;
    //护盾的计时器
    QTimer* shield_timer = nullptr;



    int bomb_count = 1;  // 初始炸弹数量
    int max_bomb_count = 5;  // 最大炸弹数量

};

#endif // PLAYERPLANE_H
