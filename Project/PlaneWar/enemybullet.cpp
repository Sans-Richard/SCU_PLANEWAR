#include "enemybullet.h"
#include "math.h"
EnemyBullet::EnemyBullet()
{

}

void EnemyBullet::init(int kind, EnemyWeapon* enemyweapon)
{
    this->kind = kind;
    switch(kind){
    case 1:
        bullet4_kind = 0;
        init1();
        break;
    case 2:
        bullet4_kind = 0;
        init2();
        break;
    case 3:
        bullet4_kind = 0;
        init3();
        break;
    case 4:
        init4();
        break;
    case 5:
        init5();
        break;
    }
    //武器数值赋值给子弹
    speed = enemyweapon->speed;
    damage = enemyweapon->damage;

}

void EnemyBullet::init1() //直线普通弹
{
    setPixmap(QPixmap(ENEMYBULLET_PICTURE1));
}

void EnemyBullet::init2() //高速穿甲弹
{
    setPixmap(QPixmap(ENEMYBULLET_PICTURE2));
}

void EnemyBullet::init3() //追踪弹
{
    setPixmap(QPixmap(ENEMYBULLET_PICTURE3));
}

void EnemyBullet::init4() //散射弹
{
    setPixmap(QPixmap(ENEMYBULLET_PICTURE4));
}

void EnemyBullet::init5()
{
    setPixmap(QPixmap(ENEMYBULLET_PICTURE1));
}

void EnemyBullet::move(PlayerPlane* playerplane1, PlayerPlane* playerplane2, int kind,int bullet4_kind)
{
    // 如果是boss子弹（kind=6），使用自定义方向移动
    if (kind == 6) {
        move_boss();
    } else {
        switch(kind){
        case 1:
            move1();
            break;
        case 2:
            move2();
            break;
        case 3:
            move3(playerplane1,playerplane2);
            break;
        case 4:
            move4(bullet4_kind);
            break;
        case 5:
            move5();
            break;
        }
    }

    //判断子弹是否超出边界
    double x = pos().x(), y = pos().y();
    if (x < -100 || x > GAME_WIDTH + 100 || y < -100 || y > GAME_HEIGHT + 100){
        destroy();
    }
}

// boss子弹：沿自定义方向移动
void EnemyBullet::move_boss()
{
    moveBy(finalDirX * speed, finalDirY * speed);
}

void EnemyBullet::move1()//直线向xia

{
    moveBy(0, speed);
}

void EnemyBullet::move2()
{
    moveBy(0, speed);
}

void EnemyBullet::move3(PlayerPlane* playerplane1, PlayerPlane* playerplane2)
{
    qint64 nowtime = QDateTime::currentMSecsSinceEpoch();
    qint64 alivetime = nowtime - borntime;
    if (alivetime < TRACK_DURATION)
    {
        double bx = pos().x();
        double by = pos().y();
        double h1x = playerplane1->x() + 30;
        double h1y = playerplane1->y() + 50;
        double distance_player1 = sqrt((bx - h1x) * (bx - h1x) + (by - h1y) * (by - h1y));

        double targetX = 0;
        double targetY = 0;

        if (playerplane2)
        {
            double h2x = playerplane2->x() + 30;
            double h2y = playerplane2->y() + 50;
            double distance_player2 = sqrt((bx - h2x) * (bx - h2x) + (by - h2y) * (by - h2y));

            if(distance_player1 < distance_player2)
            {
                targetX = h1x;
                targetY = h1y;
            }
            else
            {
                targetX = h2x;
                targetY = h2y;
            }

            double dx = targetX - bx;
            double dy = targetY - by;
            double len = sqrt(dx*dx + dy*dy);
            if(len > 0.001)
            {
                finalDirX = dx / len;
                finalDirY = dy / len;
                moveBy(finalDirX * speed * TRACK_RATE, finalDirY * speed * TRACK_RATE);
            }
        }
        else
        {
            targetX = h1x;
            targetY = h1y;
            double dx = targetX - bx;
            double dy = targetY - by;
            double len = sqrt(dx*dx + dy*dy);
            if(len > 0.001)
            {
                finalDirX = dx / len;
                finalDirY = dy / len;
                moveBy(finalDirX * speed * TRACK_RATE, finalDirY * speed * TRACK_RATE);
            }
        }
    }
    else
    {
        moveBy(finalDirX * speed * TRACK_RATE, finalDirY * speed * TRACK_RATE);
    }

}

void EnemyBullet::move4(int bullet4_kind)
{
    int dx = 5;
    moveBy(dx * (bullet4_kind), speed);
}

void EnemyBullet::move5()
{
    moveBy(0, speed);
}

void EnemyBullet::destroy()
{
    status = 0;
    setVisible(false);
}

void EnemyBullet::collide_with_playerplane()
{
    switch(kind){
    case 1:
        destroy();
        break;
    case 2:
        //穿甲弹不消失
        break;
    case 3:
        destroy();
        break;
    case 4:
        destroy();
        break;
    }
}
