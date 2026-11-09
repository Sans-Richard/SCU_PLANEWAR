#include "powerup.h"
#include "playerplane.h"
#include <QObject>
#include <random>

PowerUp::PowerUp()
{
    effect_timer = new QTimer();
    effect_timer->setSingleShot(true);
}

PowerUp::~PowerUp()
{
    if (effect_timer) {
        effect_timer->stop();
        delete effect_timer;
        effect_timer = nullptr;
    }
}

void PowerUp::init(double x, double y, int type)
{
    powerup_type = type;
    setPos(x, y);
    setVisible(true);
    status = 2;
    speed = POWERUP_SPEED;

    switch (type) {
    case POWERUP_TYPE_FIREPOWER:
        init_firepower();
        break;
    case POWERUP_TYPE_HEALTH:
        init_health();
        break;
    case POWERUP_TYPE_BOMB:
        init_bomb();
        break;
    default:
        init_firepower();
        break;
    }
}

void PowerUp::init_firepower()
{
    setPixmap(QPixmap(POWERUP_TYPE_FIREPOWER_PICTURE));
    effect_duration = POWERUP_FIREPOWER_DURATION;
}

void PowerUp::init_health()
{
    setPixmap(QPixmap(POWERUP_TYPE_HEALTH_PICTURE));
    health_restore = POWERUP_HEALTH_RESTORE;
}

void PowerUp::init_bomb()
{
    setPixmap(QPixmap(POWERUP_TYPE_BOMB_PICTURE));
}

void PowerUp::destroy()
{
    status = 0;
    setVisible(false);
    if (effect_timer) {
        QObject::disconnect(effect_timer, nullptr, nullptr, nullptr);
        effect_timer->stop();
    }
    effect_target = nullptr;
}

void PowerUp::move()
{
    double x = pos().x(), y = pos().y();
    y += speed;
    setPos(x, y);
}

void PowerUp::is_live()
{
    double x = pos().x(), y = pos().y();
    if ((y >= GAME_HEIGHT || x <= -50 || x >= GAME_WIDTH + 50) && status == 2) {
        destroy();
    }
}

void PowerUp::apply_effect(PlayerPlane* playerplane)
{
    if (!playerplane || playerplane->status != 2) return;

    switch (powerup_type) {
    case POWERUP_TYPE_FIREPOWER:
    {
        // 记录原始伤害
        effect_target = playerplane;
        if (playerplane->weapon1) {
            original_w1_damage = playerplane->weapon1->damage;
            playerplane->weapon1->damage *= 1.5;
        }
        if (playerplane->weapon2) {
            original_w2_damage = playerplane->weapon2->damage;
            playerplane->weapon2->damage *= 1.5;
        }
        if (playerplane->weapon3) {
            original_w3_damage = playerplane->weapon3->damage;
            playerplane->weapon3->damage *= 1.5;
        }

        // 效果到期后恢复
        QObject::connect(effect_timer, &QTimer::timeout, effect_timer, [this]() {
            if (effect_target) {
                if (effect_target->weapon1 && original_w1_damage > 0)
                    effect_target->weapon1->damage = original_w1_damage;
                if (effect_target->weapon2 && original_w2_damage > 0)
                    effect_target->weapon2->damage = original_w2_damage;
                if (effect_target->weapon3 && original_w3_damage > 0)
                    effect_target->weapon3->damage = original_w3_damage;
                effect_target = nullptr;
            }
        });
        effect_timer->start(effect_duration);
        break;
    }

    case POWERUP_TYPE_HEALTH:
    {
        playerplane->health += health_restore;
        if (playerplane->health > playerplane->max_health) {
            playerplane->health = playerplane->max_health;
        }
        break;
    }

    case POWERUP_TYPE_BOMB:
    {
        if (playerplane->bomb_count < playerplane->max_bomb_count) {
            playerplane->bomb_count++;
        }
        break;
    }
    }

    // 道具被拾取后销毁
    destroy();
}
