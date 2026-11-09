#ifndef PLANE_H
#define PLANE_H
#include <QGraphicsPixmapItem>
#include "config.h"

class Plane:public QGraphicsPixmapItem
{
public:
    Plane();

    double speed = 0;
    int status = 0;

    double health = 0;

    double max_health = 0;

    double damage = 0 ;


    double get_hp_rate();
};

#endif // PLANE_H
