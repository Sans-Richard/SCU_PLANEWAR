#include "playerbullet.h"

PlayerBullet::PlayerBullet()
{

}

void PlayerBullet::init(int kind, PlayerWeapon* playerweapon)
{
    this->kind = kind;
    switch(kind){
    case 1:
        init1();
        break;
    case 2:
        init2();
        break;
    case 3:
        init3();
        break;
    case 4:
        init4();
        break;
    }
    //武器数值赋值给子弹
    speed = playerweapon->speed;
    damage = playerweapon->damage;

}

void PlayerBullet::init1()
{
    setPixmap(QPixmap(PLAYERBULLET_PICTURE1));
}

void PlayerBullet::init2()
{
    setPixmap(QPixmap(PLAYERBULLET_PICTURE2));
}

void PlayerBullet::init3()
{
    setPixmap(QPixmap(PLAYERBULLET_PICTURE3));
}

void PlayerBullet::init4()
{
    setPixmap(QPixmap(PLAYERBULLET_PICTURE4));
}

void PlayerBullet::move()
{
    switch(kind){
    case 1:
        move1();
        break;
    case 2:
        move2();
        break;
    case 3:
        move3();
        break;
    case 4:
        move4();
        break;

    }

    //判断子弹是否超出边界
    double x = pos().x(), y = pos().y();
    if (x < -100 || x > GAME_WIDTH + 100 || y < -100 || y > GAME_HEIGHT + 100){
        destroy();
    }
}
void PlayerBullet::move1()//直线向上
{
    moveBy(0, -speed);
}

void PlayerBullet::move2()
{
    moveBy(0, -speed);
}

void PlayerBullet::move3()
{

}

void PlayerBullet::move4()
{

}

void PlayerBullet::destroy()
{
    status = 0;
    setVisible(false);
}

void PlayerBullet::collide_with_enemyplane(EnemyPlane* enemyplane)
{
    switch(kind){
    case 1:
        moveBy(0, -enemyplane->pixmap().height() + 5);
        break;
    case 2:
        destroy();
        break;
    case 3:
        destroy();
        break;
    case 4:
        destroy();
        break;
    }
}
