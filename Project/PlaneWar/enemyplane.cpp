#include "enemyplane.h"
#include "playerplane.h"
#include "playerbullet.h"

#include "math.h"
#include <QtMath>
#include <QRandomGenerator>



EnemyPlane::EnemyPlane()
{
    weapon = new EnemyWeapon();//在这里new而不是初始化的时候new：复用性和解决武器bug
    boss_performance = new BossPerformance();
}


void EnemyPlane::init(int plane_kind)
{
    this->plane_kind = plane_kind;
    switch(plane_kind){
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
    case 5:
        init5();
        break;
    }
    killer = 0;
}

void EnemyPlane::init1()
{
    setPixmap(QPixmap(ENEMYPLANE1_PICTURE));
    speed = ENEMYPLANE1_SPEED;
    health = ENEMYPLANE1_HEALTH;
    score = ENEMYPLANE1_SCORE;
    experience = ENEMYPLANE1_EXPERIENCE;
    damage = ENEMYPLANE1_DAMAGE;
    weapon->init(1);
}

void EnemyPlane::init2()
{
    setPixmap(QPixmap(ENEMYPLANE2_PICTURE));
    speed = ENEMYPLANE2_SPEED;
    health = ENEMYPLANE2_HEALTH;
    score = ENEMYPLANE2_SCORE;
    experience = ENEMYPLANE2_EXPERIENCE;
    damage = ENEMYPLANE2_DAMAGE;
    weapon->init(2);
}

void EnemyPlane::init3()
{
    setPixmap(QPixmap(ENEMYPLANE3_PICTURE));
    speed = ENEMYPLANE3_SPEED;
    health = ENEMYPLANE3_HEALTH;
    score = ENEMYPLANE3_SCORE;
    experience = ENEMYPLANE3_EXPERIENCE;
    damage = ENEMYPLANE3_DAMAGE;
    weapon->init(3);
}

void EnemyPlane::init4()
{
    setPixmap(QPixmap(ENEMYPLANE4_PICTURE));
    speed = ENEMYPLANE4_SPEED;
    health = ENEMYPLANE4_HEALTH;
    score = ENEMYPLANE4_SCORE;
    experience = ENEMYPLANE4_EXPERIENCE;
    damage = ENEMYPLANE4_DAMAGE;
    weapon->init(4);
    wave_time = 0;
    wave_amp = 70;
    wave_speed = 0.03;
}


void EnemyPlane::init_boss(int boss_kind)
{
    if (boss_kind == 1) {
        setPixmap(QPixmap(BOSS_PICTURE1));
        // 放大boss图片
        setTransform(QTransform().scale(1.5, 1.5));
    } else {
        setPixmap(QPixmap(BOSS_PICTURE2));
        setTransform(QTransform().scale(1.5, 1.5));
    }
    speed = BOSS_SPEED;
    health = BOSS_HEALTH;
    max_health = BOSS_HEALTH;
    damage = BOSS_DAMAGE;
    score = BOSS_SCORE;
    experience = 0;
    weapon->init(1); // boss使用普通武器
    plane_kind = 10 + boss_kind; // 标记为boss

    // 初始化boss演出列表
    if (boss_performance) {
        boss_performance->reset();
        if (boss_kind == 1) {
            boss_performance->build_boss1();
        } else if (boss_kind == 2) {
            // Boss2（无畏舰）特殊属性
            health = BOSS2_HEALTH;
            max_health = BOSS2_HEALTH;
            damage = BOSS2_DAMAGE;
            boss_performance->build_boss2();
            boss2_init_emitters();
            // 初始化随机角度
            for (int i = 0; i < BOSS2_EMITTER_COUNT; i++) {
                boss2_random_angles[i] = QRandomGenerator::global()->bounded(360);
            }
            boss2_aim_bomb_spawned = false;
            boss2_front_bomb_spawned = false;
        }
    }

    // boss层级设高，让子弹显示在boss下面
    setZValue(10);

    // 重置boss状态
    boss_rotate_angle = 0;
    boss_dive_current = 0;
    boss_dive_start_y = 0;
    boss_dive_going_down = true;

}



void EnemyPlane::init5()//玩家2继承的敌机，没有护盾，加强一下吧
{
    speed = PLAYERPLANE1_SPEED + 2;
    health = PLAYERPLANE1_HEALTH + 20;
    max_health = PLAYERPLANE1_HEALTH + 20;
    damage = PLAYERPLANE1_DAMAGE ;
    setPixmap(QPixmap(PLAYERPLANE1_PICTURE));
    setTransform(QTransform().scale(1, -1));
    weapon->init(5);
}

void EnemyPlane::move()
{
    if (isPlayerControl){
        return;
    }
    switch(plane_kind){
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
    default:
        // boss类型（10+）也向下移动
        moveBy(0, speed);
        break;
    }

    //判断敌机是否超出边界（boss从y=-150开始，允许其进入屏幕）
    double x = pos().x(), y = pos().y();
    if (x < -200 || x > GAME_WIDTH + 200 || y < -200 || y > GAME_HEIGHT + 200){
        destroy();
    }
}

void EnemyPlane::move1()
{
   //直线移动
    moveBy(0, speed);
}

void EnemyPlane::move2()
{
    moveBy(0 , speed);
}

void EnemyPlane::move3()
{
    moveBy(0 , speed);
}

void EnemyPlane::move4()
{
    wave_time += wave_speed;
    float dx = cos(wave_time) * wave_speed * wave_amp;
    float dy = speed;
    moveBy(dx, dy);
}


void EnemyPlane::destroy()
{
    weapon->weapon_timer->stop();
    status = 0;
    setVisible(false);
}

void EnemyPlane::weapon_shoot(EnemyBulletPool *enemybullet_pool, QGraphicsScene *level_scene,int kind)
{
    if(kind != 4){
        if (!weapon || weapon->weapon_timer->isActive())return;
            EnemyBullet* enemybullet = enemybullet_pool->get_new_enemybullet();
            enemybullet->init(weapon->kind, weapon);
            enemybullet->setPos(pos().x() + pixmap().width() / 2.0 - 8, pos().y() + 18);
            //冷却
            weapon->weapon_timer->start();
    }
    if(kind == 4){
        if (!weapon || weapon->weapon_timer->isActive())return;
            EnemyBullet* enemybullet1 = enemybullet_pool->get_new_enemybullet();
            EnemyBullet* enemybullet2 = enemybullet_pool->get_new_enemybullet();
            EnemyBullet* enemybullet3 = enemybullet_pool->get_new_enemybullet();
            enemybullet1->bullet4_kind = -1;
            enemybullet2->bullet4_kind = 0;
            enemybullet3->bullet4_kind = 1;
            enemybullet1->init(weapon->kind, weapon);
            enemybullet2->init(weapon->kind, weapon);
            enemybullet3->init(weapon->kind, weapon);
            enemybullet1->setPos(pos().x() + pixmap().width() / 2.0 - 38, pos().y() + 18);
            enemybullet2->setPos(pos().x() + pixmap().width() / 2.0 - 8, pos().y() + 18);
            enemybullet3->setPos(pos().x() + pixmap().width() / 2.0 + 22, pos().y() + 18);
            //冷却
            weapon->weapon_timer->start();
    }

}


void EnemyPlane::collide_with_playerbullet(PlayerBullet *playerbullet)
{
    switch(playerbullet->kind){
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }
    health -= playerbullet->damage;

}

void EnemyPlane::collide_with_playerplane(PlayerPlane *playerplane)
{
    switch(playerplane->kind){
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }

    health -= playerplane->damage;

}

void EnemyPlane::is_live()
{
    if(health <= 0){
        destroy();
    }
}


// 为了华丽演出，boss不能简单继承敌人，因此我设置了演出系统

void EnemyPlane::boss_perform(EnemyBulletPool* enemybullet_pool, QGraphicsScene* level_scene)
{
    if (!boss_performance) return;

    // 记录切换前的行为索引
    int prev_index = boss_performance->get_current_index();

    // 更新演出状态（切换行为等）
    bool switched = boss_performance->update();

    const BossAction* action = boss_performance->get_current_action();
    if (!action) return;

    // 检测行为切换：如果索引变了，说明切换到了新行为
    int new_index = boss_performance->get_current_index();
    if (new_index != prev_index) {
        // 进入新行为时，重置对应的标记
        BossAttackType new_type = action->attack_type;

        // 行为5（Boss2_AimPlayer）：重置标记
        if (new_type == BossAttackType::Boss2_AimPlayer) {
            boss2_aim_bomb_spawned = false;
        }
    }

    // 执行移动
    boss_move_by_action(action);

    // 执行攻击
    boss_attack_by_action(action, enemybullet_pool, level_scene);
}


//boss1
void EnemyPlane::boss_move_by_action(const BossAction* action)
{
    if (!action) return;

    double bx = pos().x();
    double by = pos().y();

    switch (action->move_type) {

    case BossMoveType::EnterScreen:
    case BossMoveType::MoveTo: {

        double half_w = pixmap().width() / 2.0;
        double half_h = pixmap().height() / 2.0;
        double target_left = action->target_pos.x() - half_w;
        double target_top = action->target_pos.y() - half_h;
        double dx = target_left - bx;
        double dy = target_top - by;
        double dist = sqrt(dx * dx + dy * dy);
        if (dist > action->move_speed) {
            moveBy(dx / dist * action->move_speed, dy / dist * action->move_speed);
        } else {
            setPos(target_left, target_top);
        }
        break;
    }


    case BossMoveType::Stay: {
        // 不动
        break;
    }

    case BossMoveType::Dive: {

        double speed = action->move_speed;

        if (boss_dive_going_down) {
            // 向下俯冲
            moveBy(0, speed);
            if (pos().y() > GAME_HEIGHT + 50) {
                boss_dive_going_down = false;
                boss_dive_start_y = -100; // 回到顶部
                // 设置回到顶部的位置（右移）
                double new_x = pos().x() + action->dive_speed_x;
                setPos(new_x, boss_dive_start_y);
                boss_dive_current++;
            }
        } else {

            boss_dive_going_down = true;
        }

        // 如果完成了所有俯冲，传送回初始位置
        if (boss_dive_current >= action->dive_count) {
            setPos(GAME_WIDTH / 2.0 - pixmap().width() / 2.0, -150);
            boss_dive_current = 0;
            boss_dive_going_down = true;
        }
        break;
    }

    default:
        break;
    }
}


// Boss1

void EnemyPlane::boss_attack_by_action(const BossAction* action,
                                        EnemyBulletPool* enemybullet_pool,
                                        QGraphicsScene* level_scene)
{
    if (!action || action->attack_type == BossAttackType::None) return;

    // 根据发射间隔控制射速
    int elapsed = boss_performance->get_elapsed_frames();
    if (elapsed % action->shoot_interval != 0) return;

    double bx = pos().x() + pixmap().width() / 2.0;
    double by = pos().y() + pixmap().height() / 2.0;
    double speed = action->bullet_speed;
    double damage = action->bullet_damage;

    switch (action->attack_type) {

    case BossAttackType::Forward: {
        // 3束向前（向下=0,1）：机头+两翼
        // 机头
        boss_shoot_bullet(bx + BossAction::OFFSET_FRONT_X,
                          by + BossAction::OFFSET_FRONT_Y,
                          0, 1, speed, damage, enemybullet_pool, level_scene);
        // 左翼
        boss_shoot_bullet(bx + BossAction::OFFSET_FRONT_X - 20,
                          by + BossAction::OFFSET_FRONT_Y + 10,
                          0, 1, speed, damage, enemybullet_pool, level_scene);
        // 右翼
        boss_shoot_bullet(bx + BossAction::OFFSET_FRONT_X + 20,
                          by + BossAction::OFFSET_FRONT_Y + 10,
                          0, 1, speed, damage, enemybullet_pool, level_scene);
        break;
    }

    case BossAttackType::ForwardBack: {
        // 前（向下0,1）+ 后（向上0,-1）
        boss_shoot_bullet(bx + BossAction::OFFSET_FRONT_X,
                          by + BossAction::OFFSET_FRONT_Y,
                          0, 1, speed, damage, enemybullet_pool, level_scene);
        boss_shoot_bullet(bx + BossAction::OFFSET_BACK_X,
                          by + BossAction::OFFSET_BACK_Y,
                          0, -1, speed, damage, enemybullet_pool, level_scene);
        break;
    }

    case BossAttackType::FourDir: {
        // 前（向下0,1）+ 后（向上0,-1）+ 左（向左-1,0）+ 右（向右1,0）
        boss_shoot_bullet(bx + BossAction::OFFSET_FRONT_X,
                          by + BossAction::OFFSET_FRONT_Y,
                          0, 1, speed, damage, enemybullet_pool, level_scene);
        boss_shoot_bullet(bx + BossAction::OFFSET_BACK_X,
                          by + BossAction::OFFSET_BACK_Y,
                          0, -1, speed, damage, enemybullet_pool, level_scene);
        boss_shoot_bullet(bx + BossAction::OFFSET_LEFT_X,
                          by + BossAction::OFFSET_LEFT_Y,
                          -1, 0, speed, damage, enemybullet_pool, level_scene);
        boss_shoot_bullet(bx + BossAction::OFFSET_RIGHT_X,
                          by + BossAction::OFFSET_RIGHT_Y,
                          1, 0, speed, damage, enemybullet_pool, level_scene);
        break;
    }

    case BossAttackType::Rotate1: {
        // 1个发射源旋转，初始方向向下（0,1）
        double angle_rad = qDegreesToRadians(boss_rotate_angle);
        double dir_x = sin(angle_rad);
        double dir_y = cos(angle_rad);
        boss_shoot_bullet(bx + BossAction::OFFSET_FRONT_X,
                          by + BossAction::OFFSET_FRONT_Y,
                          dir_x, dir_y, speed, damage, enemybullet_pool, level_scene);
        boss_rotate_angle += action->rotate_speed;
        if (boss_rotate_angle >= 360) boss_rotate_angle -= 360;
        break;
    }

    case BossAttackType::Rotate2: {
        // 2个发射源（前后）旋转，初始方向向下（0,1）
        double angle_rad = qDegreesToRadians(boss_rotate_angle);
        double dir_x = sin(angle_rad);
        double dir_y = cos(angle_rad);
        // 前
        boss_shoot_bullet(bx + BossAction::OFFSET_FRONT_X,
                          by + BossAction::OFFSET_FRONT_Y,
                          dir_x, dir_y, speed, damage, enemybullet_pool, level_scene);
        // 后（方向相反）
        boss_shoot_bullet(bx + BossAction::OFFSET_BACK_X,
                          by + BossAction::OFFSET_BACK_Y,
                          -dir_x, -dir_y, speed, damage, enemybullet_pool, level_scene);
        boss_rotate_angle += action->rotate_speed;
        if (boss_rotate_angle >= 360) boss_rotate_angle -= 360;
        break;
    }

    case BossAttackType::Rotate4: {
        // 4个发射源（前后左右）旋转，初始方向向下（0,1）
        double angle_rad = qDegreesToRadians(boss_rotate_angle);
        double dir_x = sin(angle_rad);
        double dir_y = cos(angle_rad);
        // 前
        boss_shoot_bullet(bx + BossAction::OFFSET_FRONT_X,
                          by + BossAction::OFFSET_FRONT_Y,
                          dir_x, dir_y, speed, damage, enemybullet_pool, level_scene);
        // 后
        boss_shoot_bullet(bx + BossAction::OFFSET_BACK_X,
                          by + BossAction::OFFSET_BACK_Y,
                          -dir_x, -dir_y, speed, damage, enemybullet_pool, level_scene);
        // 左（方向旋转90度）
        double left_angle = boss_rotate_angle + 90;
        double left_rad = qDegreesToRadians(left_angle);
        double left_dir_x = sin(left_rad);
        double left_dir_y = cos(left_rad);
        boss_shoot_bullet(bx + BossAction::OFFSET_LEFT_X,
                          by + BossAction::OFFSET_LEFT_Y,
                          left_dir_x, left_dir_y, speed, damage, enemybullet_pool, level_scene);
        // 右（方向旋转-90度）
        double right_angle = boss_rotate_angle - 90;
        double right_rad = qDegreesToRadians(right_angle);
        double right_dir_x = sin(right_rad);
        double right_dir_y = cos(right_rad);
        boss_shoot_bullet(bx + BossAction::OFFSET_RIGHT_X,
                          by + BossAction::OFFSET_RIGHT_Y,
                          right_dir_x, right_dir_y, speed, damage, enemybullet_pool, level_scene);
        boss_rotate_angle += action->rotate_speed;
        if (boss_rotate_angle >= 360) boss_rotate_angle -= 360;
        break;
    }


    // Boss2专用攻击类型

    case BossAttackType::Boss2_Enter: {
        boss2_enter_attack(enemybullet_pool, bx, by, speed, damage);
        break;
    }

    case BossAttackType::Boss2_RandomDir: {
        boss2_random_dir_attack(enemybullet_pool, bx, by, speed, damage);
        break;
    }

    case BossAttackType::Boss2_Track: {
        boss2_track_attack(enemybullet_pool, bx, by, speed, damage);
        break;
    }

    case BossAttackType::Boss2_AimPlayer: {
        boss2_aim_player_attack(enemybullet_pool, level_scene, bx, by, speed, damage);
        break;
    }



    default:
        break;
    }
}


void EnemyPlane::boss_shoot_bullet(double x, double y, double dir_x, double dir_y,
                                    double speed, double damage,
                                    EnemyBulletPool* enemybullet_pool,
                                    QGraphicsScene* level_scene)
{
    if (!enemybullet_pool) return;

    EnemyBullet* bullet = enemybullet_pool->get_new_enemybullet();
    // 使用kind=6标记为boss子弹，使用自定义方向移动
    bullet->kind = 6;
    bullet->init1(); // 使用普通子弹图片
    bullet->speed = speed;
    bullet->damage = damage;
    bullet->setPos(x, y);

    // 设置子弹的移动方向
    double len = sqrt(dir_x * dir_x + dir_y * dir_y);
    if (len > 0.001) {
        bullet->finalDirX = dir_x / len;
        bullet->finalDirY = dir_y / len;
    } else {
        bullet->finalDirX = 0;
        bullet->finalDirY = 1;
    }

}


//  BOSS2
//
//
//

// 每侧7个，沿boss纵向分布
void EnemyPlane::boss2_init_emitters()
{
    // boss图片高度258，缩放1.5倍后约387
    // 发射源分布在boss两侧，从顶部到底部均匀分布
    double half_h = pixmap().height() / 2.0;  // 约193
    double half_w = pixmap().width() / 2.0;   // 约38

    // 每侧7个，从顶部到底部均匀分布
    for (int i = 0; i < 7; i++) {
        double t = (i + 0.5) / 7.0; // 0.07 ~ 0.93
        double y_offset = -half_h + t * pixmap().height();

        // 左侧发射源
        emitter_offsets_x[i] = -half_w - 5;  // 左侧偏外
        emitter_offsets_y[i] = y_offset;

        // 右侧发射源
        emitter_offsets_x[i + 7] = half_w + 5;  // 右侧偏外
        emitter_offsets_y[i + 7] = y_offset;
    }
}

// 行为1：进入屏幕攻击
// 最前2个（索引6和13，最下方）直线向下
// 其余12个45°向下斜射
void EnemyPlane::boss2_enter_attack(EnemyBulletPool* enemybullet_pool,
                                     double bx, double by,
                                     double speed, double damage)
{
    for (int i = 0; i < BOSS2_EMITTER_COUNT; i++) {
        double ex = bx + emitter_offsets_x[i];
        double ey = by + emitter_offsets_y[i];

        if (i == 6 || i == 13) {
            // 最前面两个（最下方），直线向下
            boss_shoot_bullet(ex, ey, 0, 1, speed, damage, enemybullet_pool, nullptr);
        } else {
            if (i < 7) {
                // 左侧：向右下 (0.707, 0.707)
                boss_shoot_bullet(ex, ey, 0.707, 0.707, speed, damage, enemybullet_pool, nullptr);
            } else {
                // 右侧：向左下 (-0.707, 0.707)
                boss_shoot_bullet(ex, ey, -0.707, 0.707, speed, damage, enemybullet_pool, nullptr);
            }
        }
    }
}

// 行为3：只保留4个发射源随机方向发射（最前2个索引6,13 + 最后2个索引0,7）
void EnemyPlane::boss2_random_dir_attack(EnemyBulletPool* enemybullet_pool,
                                          double bx, double by,
                                          double speed, double damage)
{
    // 只使用4个发射源：最前2个（6,13）+ 最后2个（0,7）
    int indices[4] = {0, 6, 7, 13};
    for (int i = 0; i < 4; i++) {
        int idx = indices[i];
        double ex = bx + emitter_offsets_x[idx];
        double ey = by + emitter_offsets_y[idx];

        // 每个发射源各自随机方向
        double angle = QRandomGenerator::global()->bounded(360);
        double rad = qDegreesToRadians(angle);
        double dir_x = sin(rad);
        double dir_y = cos(rad);

        boss_shoot_bullet(ex, ey, dir_x, dir_y, speed, damage, enemybullet_pool, nullptr);
    }
}

// 行为4：只保留2个发射源发射追踪弹（最前2个索引6和13）
void EnemyPlane::boss2_track_attack(EnemyBulletPool* enemybullet_pool,
                                     double bx, double by,
                                     double speed, double damage)
{
    // 只使用最前2个发射源（索引6和13，最下方）
    int indices[2] = {6, 13};
    for (int i = 0; i < 2; i++) {
        int idx = indices[i];
        double ex = bx + emitter_offsets_x[idx];
        double ey = by + emitter_offsets_y[idx];

        // 使用kind=3追踪弹
        EnemyBullet* bullet = enemybullet_pool->get_new_enemybullet();
        bullet->kind = 3;  // 追踪弹
        bullet->init3();   // 使用追踪弹图片
        bullet->speed = speed;
        bullet->damage = damage;
        bullet->setPos(ex, ey);
        // 初始方向向下
        bullet->finalDirX = 0;
        bullet->finalDirY = 1;
        bullet->borntime = QDateTime::currentMSecsSinceEpoch();
    }
}


// 行为5：只保留1个发射源向玩家方向发射 + 玩家位置出现danger，1秒后爆炸
void EnemyPlane::boss2_aim_player_attack(EnemyBulletPool* enemybullet_pool,
                                          QGraphicsScene* level_scene,
                                          double bx, double by,
                                          double speed, double damage)
{
    if (!level_scene) return;

    // 确定目标玩家
    PlayerPlane* target = player1;
    if (!target && player2) target = player2;
    if (!target) return;

    double px = target->x() + target->pixmap().width() / 2.0;
    double py = target->y() + target->pixmap().height() / 2.0;

    // 只保留1个发射源（最前1个索引6，最下方左侧）
    int idx = 6;
    double ex = bx + emitter_offsets_x[idx];
    double ey = by + emitter_offsets_y[idx];

    double dx = px - ex;
    double dy = py - ey;
    double len = sqrt(dx * dx + dy * dy);
    if (len > 0.001) {
        boss_shoot_bullet(ex, ey, dx/len, dy/len, speed, damage, enemybullet_pool, nullptr);
    }


}







