#include "playerbulletpool.h"

PlayerBulletPool::PlayerBulletPool(QGraphicsScene* level_scene)
{
    this->level_scene = level_scene;

    playerbullet_pool_list = new QList<PlayerBullet*>;
    playerbullet_pool_queue = new QQueue<PlayerBullet*>;

}

PlayerBulletPool::PlayerBulletPool(QGraphicsScene* level_scene, int init_size)
{
    this->level_scene = level_scene;

    playerbullet_pool_list = new QList<PlayerBullet*>();
    playerbullet_pool_queue = new QQueue<PlayerBullet*>();
    for (int i = 0; i < init_size; i++){
        PlayerBullet* new_playerbullet = new PlayerBullet();
        playerbullet_pool_list->append(new_playerbullet);
        playerbullet_pool_queue->append(new_playerbullet);
        new_playerbullet->status = 1;//等待态
        new_playerbullet->setVisible(false);
        level_scene->addItem(new_playerbullet);
    }
}
PlayerBullet *PlayerBulletPool::get_new_playerbullet()
{
    PlayerBullet* res = nullptr;
    if (playerbullet_pool_queue->isEmpty()){
        PlayerBullet* new_playerbullet = new PlayerBullet();
        playerbullet_pool_list->append(new_playerbullet);
        level_scene->addItem(new_playerbullet);
        res = new_playerbullet;
    }
    else{
        res = playerbullet_pool_queue->dequeue();
    }
    res->setVisible(true);
    res->status = 2;
    return res;
}

void PlayerBulletPool::return_playerbullet(PlayerBullet *playerbullet)
{
    playerbullet->status = 1;
    playerbullet_pool_queue->append(playerbullet);
}
