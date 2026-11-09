#ifndef ENEMYPLANEPOOL_H
#define ENEMYPLANEPOOL_H
#include "enemyplane.h"
#include "config.h"
#include "QQueue"
#include "QList"



class EnemyPlane;

class EnemyPlanePool//直接复制粘贴玩家子弹池，对把出现的bullet改成敌机便可
{
public:
    EnemyPlanePool(QGraphicsScene* level_scene);
    EnemyPlanePool(QGraphicsScene* level_scene, int init_size);

    EnemyPlane* get_new_enemyplane();
    void return_enemyplane(EnemyPlane* enemyplane);

public:
    QQueue<EnemyPlane*>* enemyplane_pool_queue = nullptr;
    QList<EnemyPlane*>* enemyplane_pool_list = nullptr;

    QGraphicsScene* level_scene = nullptr;
};

#endif // ENEMYPLANEPOOL_H
