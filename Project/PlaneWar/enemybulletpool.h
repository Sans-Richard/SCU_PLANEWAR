#ifndef ENEMYBULLETPOOL_H
#define ENEMYBULLETPOOL_H
#include "config.h"
#include "QQueue"
#include "QList"
#include "enemybullet.h"
#include "QDateTime"



class EnemyBullet;

class EnemyBulletPool
{
public:
    EnemyBulletPool(QGraphicsScene* level_scene);
    EnemyBulletPool(QGraphicsScene* level_scene, int init_size);

    EnemyBullet* get_new_enemybullet();
    void return_enemybullet(EnemyBullet* enemybullet);

    QList<EnemyBullet*>* enemybullet_pool_list = nullptr;//等待队列
    QQueue<EnemyBullet*>* enemybullet_pool_queue = nullptr;//所有创建过的指针列表


    QGraphicsScene* level_scene = nullptr;
};

#endif // ENEMYBULLETPOOL_H


//依旧复制粘贴玩家子弹池的代码，注意看有没有改对
