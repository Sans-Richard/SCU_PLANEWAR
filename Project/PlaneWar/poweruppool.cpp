#include "poweruppool.h"

PowerUpPool::PowerUpPool(QGraphicsScene *level_scene)
{
    this->level_scene = level_scene;
    powerup_pool_list = new QList<PowerUp*>();
    powerup_pool_queue = new QQueue<PowerUp*>();
}

PowerUpPool::PowerUpPool(QGraphicsScene *level_scene, int init_size)
{
    this->level_scene = level_scene;
    powerup_pool_list = new QList<PowerUp*>();
    powerup_pool_queue = new QQueue<PowerUp*>();

    for (int i = 0; i < init_size; i++) {
        PowerUp* new_powerup = new PowerUp();
        powerup_pool_list->append(new_powerup);
        powerup_pool_queue->append(new_powerup);
        new_powerup->status = 1;
        new_powerup->setVisible(false);
        level_scene->addItem(new_powerup);
    }
}

PowerUp* PowerUpPool::get_new_powerup()
{
    PowerUp* res = nullptr;
    if (powerup_pool_queue->isEmpty()) {
        PowerUp* new_powerup = new PowerUp();
        powerup_pool_list->append(new_powerup);
        level_scene->addItem(new_powerup);
        res = new_powerup;
    } else {
        res = powerup_pool_queue->dequeue();
    }
    res->setVisible(true);
    res->status = 2;
    return res;
}

void PowerUpPool::return_powerup(PowerUp *powerup)
{
    powerup->status = 1;
    powerup_pool_queue->append(powerup);
}