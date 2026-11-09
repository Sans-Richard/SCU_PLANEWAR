#ifndef POWERUPPOOL_H
#define POWERUPPOOL_H

#include "powerup.h"
#include "config.h"
#include <QQueue>
#include <QList>
#include <QGraphicsScene>

class PowerUpPool
{
public:
    PowerUpPool(QGraphicsScene* level_scene);
    PowerUpPool(QGraphicsScene* level_scene, int init_size);

    PowerUp* get_new_powerup();
    void return_powerup(PowerUp* powerup);

public:
    QQueue<PowerUp*>* powerup_pool_queue = nullptr;
    QList<PowerUp*>* powerup_pool_list = nullptr;
    QGraphicsScene* level_scene = nullptr;
};

#endif // POWERUPPOOL_H