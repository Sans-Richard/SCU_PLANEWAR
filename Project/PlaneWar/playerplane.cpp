#include "playerplane.h"

PlayerPlane::PlayerPlane()
{

}

PlayerPlane::~PlayerPlane()
{
    if (weapon1) delete weapon1;
    if (weapon2) delete weapon2;
    if (weapon3) delete weapon3;//护盾不用delete，护盾和pp绑定了父子关系，自动析构
    if (shield_timer) {
        shield_timer->stop();
        delete shield_timer;
    }
}

void PlayerPlane::init(int kind)
{
    this->kind = kind;


    //护盾
    shield = new QGraphicsPixmapItem();
    shield->setParentItem(this);
    shield->setPixmap(QPixmap(SHIELD_PICTURE));
    shield->setScale(0.3);
    shield->setOpacity(0.5);
    shield->setPos(-4, -12);
    shield->setVisible(false);

    shield_timer = new QTimer();
    shield_timer->setSingleShot(true);



    status = 2;
    switch(kind){
    case 1:
        init_1();
        break;
    case 2:
        init_2();
        break;
    }
}

void PlayerPlane::init_1()
{
    speed = PLAYERPLANE1_SPEED;
    health = PLAYERPLANE1_HEALTH;
    max_health = PLAYERPLANE1_HEALTH;
    damage = PLAYERPLANE1_DAMAGE;
    bomb_count = 1;
    setPixmap(QPixmap(PLAYERPLANE1_PICTURE));
    weapon1 = new PlayerWeapon();
    weapon1->init(1);
}

void PlayerPlane::init_2()
{
    speed = PLAYERPLANE2_SPEED;
    health = PLAYERPLANE2_HEALTH;
    max_health = PLAYERPLANE2_HEALTH;
    damage = PLAYERPLANE2_DAMAGE;
    bomb_count = 1;
    setPixmap(QPixmap(PLAYERPLANE2_PICTURE));
    weapon1 = new PlayerWeapon();
    weapon1->init(2);

}
void PlayerPlane::weapon1_shoot(PlayerBulletPool* playerbullet_pool, QGraphicsScene* level_scene)
{
    if (!weapon1 || weapon1->weapon_timer->isActive())return;
    PlayerBullet* playerbullet = playerbullet_pool->get_new_playerbullet();
    playerbullet->owner = this->kind;
    playerbullet->init(weapon1->kind, weapon1);
    playerbullet->setPos(pos().x() + pixmap().width() / 2.0 - 8, pos().y() - 18);
    //重新计时
    weapon1->weapon_timer->start();
}

void PlayerPlane::weapon2_shoot(PlayerBulletPool *playerbullet_pool, QGraphicsScene *level_scene)
{
    if (!weapon2 || weapon2->weapon_timer->isActive())return;
    PlayerBullet* playerbullet = playerbullet_pool->get_new_playerbullet();
    playerbullet->owner = this->kind;
    playerbullet->init(weapon2->kind, weapon2);
    playerbullet->setPos(pos().x(), pos().y());
    //重新计时
    weapon2->weapon_timer->start();
}

void PlayerPlane::weapon3_shoot(PlayerBulletPool *playerbullet_pool, QGraphicsScene *level_scene)
{
    if (!weapon3 || weapon3->weapon_timer->isActive())return;
    PlayerBullet* playerbullet = playerbullet_pool->get_new_playerbullet();
    playerbullet->init(weapon3->kind, weapon3);
    playerbullet->setPos(pos().x(), pos().y());
    //重新计时
    weapon3->weapon_timer->start();
}

void PlayerPlane::collide_with_enemybullet(EnemyBullet *enemybullet)
{
    switch(enemybullet->kind){
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }
    if(shield_timer->isActive())return;
    health -= enemybullet->damage;
    shield_timer->setInterval(SHIELD_PERIOD_1);
    shield_timer->start();

}

void PlayerPlane::collide_with_enemyplane(EnemyPlane *enemyplane)
{
    switch(enemyplane->plane_kind){
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }
    if(shield_timer->isActive())return;
    health -= enemyplane->damage;
    shield_timer->setInterval(SHIELD_PERIOD_1);
    shield_timer->start();

}



