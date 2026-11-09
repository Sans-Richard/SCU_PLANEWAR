#ifndef BULLET_H
#define BULLET_H
#include "config.h"

class Bullet:public QGraphicsPixmapItem
{
public:
    Bullet();
    int status = 0;//对象池实现：0:失效态, 1:等待态, 2:激活态


    double speed = 0;

    double damage = 0;
};

#endif // BULLET_H
