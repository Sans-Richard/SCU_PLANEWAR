#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include "plane.h"
#include "enemyweapon.h"
#include "enemybulletpool.h"
#include "bossperformance.h"
#include <QGraphicsScene>
#include <QRandomGenerator>

class PlayerBullet;
class PlayerPlane;
class EnemyBulletPool;



class EnemyPlane:public Plane
{
public:
    EnemyPlane();

    void init(int plane_kind);
    void init1();
    void init2();
    void init3();
    void init4();
    void init5();
    void init_boss(int boss_kind);

    void move();
    void move1();
    void move2();
    void move3();
    void move4();

    // Boss演出系统
    void boss_perform(EnemyBulletPool* enemybullet_pool, QGraphicsScene* level_scene);
    void boss_move_by_action(const BossAction* action);
    void boss_attack_by_action(const BossAction* action, EnemyBulletPool* enemybullet_pool, QGraphicsScene* level_scene);
    void boss_shoot_bullet(double x, double y, double dir_x, double dir_y,
                           double speed, double damage, EnemyBulletPool* enemybullet_pool, QGraphicsScene* level_scene);

    // Boss2专用函数
    void boss2_init_emitters();  // 初始化14个发射源位置
    void boss2_enter_attack(EnemyBulletPool* enemybullet_pool, double bx, double by, double speed, double damage);
    void boss2_random_dir_attack(EnemyBulletPool* enemybullet_pool, double bx, double by, double speed, double damage);
    void boss2_track_attack(EnemyBulletPool* enemybullet_pool, double bx, double by, double speed, double damage);
    void boss2_aim_player_attack(EnemyBulletPool* enemybullet_pool, QGraphicsScene* level_scene,
                                  double bx, double by, double speed, double damage);
    void boss2_front_aim_bomb_attack(EnemyBulletPool* enemybullet_pool, QGraphicsScene* level_scene,
                                      double bx, double by, double speed, double damage);
    void boss2_update_bombs(QGraphicsScene* level_scene);  // 每帧更新爆炸效果

    void destroy();

    void weapon_shoot(EnemyBulletPool* enemybullet_pool, QGraphicsScene* level_scene,int kind);


public:
    //种类
    int plane_kind = 1;
    //武器槽
    EnemyWeapon* weapon = nullptr;
    //分数
    int score = 0;
    //经验值
    int experience = 0;

    bool isPlayerControl = false;
    int killer = 0;


    // 三角函数
    float wave_time = 0;
    float wave_amp = 80;
    float wave_speed = 1;

    // Boss演出系统
    BossPerformance* boss_performance = nullptr;

    // Boss旋转发射的当前角度（度）
    double boss_rotate_angle = 0;

    // Boss俯冲状态
    int boss_dive_current = 0;      // 当前第几次俯冲
    double boss_dive_start_y = 0;   // 当前俯冲起始Y
    bool boss_dive_going_down = true; // 正在向下俯冲还是回到顶部

    // Boss2（无畏舰）专用成员
    // 14个发射源位置（相对于boss中心的偏移量）
    // 每侧7个，左列和右列
    static constexpr int BOSS2_EMITTER_COUNT = 14;
    double emitter_offsets_x[BOSS2_EMITTER_COUNT]; // 每个发射源的x偏移
    double emitter_offsets_y[BOSS2_EMITTER_COUNT]; // 每个发射源的y偏移



    // 玩家指针（由widget设置）
    PlayerPlane* player1 = nullptr;
    PlayerPlane* player2 = nullptr;

    // Boss2随机方向种子
    double boss2_random_angles[BOSS2_EMITTER_COUNT];

    // Boss2行为5标记（AimPlayer）
    bool boss2_aim_bomb_spawned = false;

    // Boss2行为7标记（已取消行为的前端炸弹）
    bool boss2_front_bomb_spawned = false;


    void collide_with_playerbullet(PlayerBullet* playerbullet);

    void collide_with_playerplane(PlayerPlane* playerplane);

    void is_live();

};



#endif // ENEMYPLANE_H
