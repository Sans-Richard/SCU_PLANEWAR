#ifndef POWERUP_H
#define POWERUP_H

#include "config.h"
#include <QTimer>

class PlayerPlane;

class PowerUp : public QGraphicsPixmapItem
{
public:
    PowerUp();
    ~PowerUp();

public:
    // 道具初始化
    void init(double x, double y, int type);
    void init_firepower();    // 火力增强道具初始化
    void init_health();       // 生命恢复道具初始化
    void init_bomb();         // 炸弹道具初始化

    // 道具销毁
    void destroy();

    // 道具移动
    void move();

    // 判断道具是否存活
    void is_live();

    // 与英雄机碰撞时的效果
    void apply_effect(PlayerPlane* playerplane);

public:
    int powerup_type = 1;     // 道具类型
    int status = 0;           // 0表示不可用（已被拾取/销毁），1表示已进入对象池未使用，2表示正在使用
    double speed = POWERUP_SPEED; // 移动速度

    // 道具效果相关
    int health_restore = POWERUP_HEALTH_RESTORE;   // 生命恢复量
    int effect_duration = 0;                       // 效果持续时间

    // 火力增强：记录原始伤害用于恢复
    double original_w1_damage = 0;
    double original_w2_damage = 0;
    double original_w3_damage = 0;
    PlayerPlane* effect_target = nullptr;

    // 效果计时器（用于持续性效果）
    QTimer* effect_timer = nullptr;
};

#endif // POWERUP_H
