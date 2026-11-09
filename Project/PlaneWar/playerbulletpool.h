#ifndef PLAYERBULLETPOOL_H
#define PLAYERBULLETPOOL_H
#include "playerbullet.h"
#include "config.h"
#include "QQueue"
#include "QList"


class PlayerBullet;
class PlayerBulletPool
{
public:
    PlayerBulletPool(QGraphicsScene* level_scene);
    PlayerBulletPool(QGraphicsScene* level_scene, int init_size);

    PlayerBullet* get_new_playerbullet();
    void return_playerbullet(PlayerBullet* playerbullet);

    QQueue<PlayerBullet*>* playerbullet_pool_queue = nullptr;//等待队列
    QList<PlayerBullet*>* playerbullet_pool_list = nullptr;//所有创建过的指针列表

    QGraphicsScene* level_scene = nullptr;
};

#endif // PLAYERBULLETPOOL_H
