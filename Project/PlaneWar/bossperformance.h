#ifndef BOSSPERFORMANCE_H
#define BOSSPERFORMANCE_H

#include <QVector>
#include <QPointF>
#include <QString>
#include "config.h"


//移动行为类型

enum class BossMoveType {
    None,           // 无移动（静止）
    EnterScreen,    // 从上方进入屏幕到指定位置
    MoveTo,         // 移动到指定位置
    MoveDown,       // 向下移动
    SineWave,       // 正弦波左右摆动 + 向下
    Dive,           // 俯冲（从左上到右下反复俯冲）
    Stay,           // 停留
};


//攻击行为类型

enum class BossAttackType {
    None,           // 无攻击
    Forward,        // 向前发射（1个发射源）
    ForwardBack,    // 前后发射（2个发射源）
    FourDir,        // 前后左右发射（4个发射源）
    Rotate1,        // 1个发射源旋转360度
    Rotate2,        // 2个发射源旋转360度
    Rotate4,        // 4个发射源旋转360度

    // Boss2
    Boss2_Enter,        // 进入屏幕：最前2个直线向下，其余12个45°向下斜射
    Boss2_RandomDir,    // 14个发射源各自随机方向
    Boss2_Track,        // 14个发射源发射追踪弹
    Boss2_AimPlayer,    // 向玩家方向发射 + 玩家位置danger爆炸
    Boss2_FrontAimBomb, // 最前2个向玩家发射 + 子弹位置持续爆炸//这里有一堆废案，我已经无法分清。。。。
};


//演出行为
struct BossAction {
    BossMoveType move_type = BossMoveType::None;

    QPointF target_pos;

    double move_speed = 3.0;
    // 正弦波
    double wave_amp = 80;
    double wave_speed = 0.05;

    // 俯冲参数
    int dive_count = 8;          // 俯冲次数
    double dive_speed_x = 10;    // 每次俯冲右移量
    BossAttackType attack_type = BossAttackType::None;

    static constexpr double OFFSET_FRONT_X = 0;
    static constexpr double OFFSET_FRONT_Y = 0;
    static constexpr double OFFSET_BACK_X = 0;
    static constexpr double OFFSET_BACK_Y = 0;
    static constexpr double OFFSET_LEFT_X = 0;
    static constexpr double OFFSET_LEFT_Y = 0;
    static constexpr double OFFSET_RIGHT_X = 0;
    static constexpr double OFFSET_RIGHT_Y = 0;



    double bullet_speed = ENEMYWEAPON1_SPEED * 2;

    // 子弹伤害
    double bullet_damage = 25;


    double rotate_speed = 45.0 / (1000.0 / GAME_PERIOD);

    int shoot_interval = 3; // 每3帧射一次


    int duration_frames = 0;
};

// Boss演出列表
class BossPerformance
{
public:
    BossPerformance();

    void build_boss1();
    void build_boss2();



    const BossAction* get_current_action() const;


    bool update();

    void reset();

    int get_current_index() const { return current_index; }

    int get_elapsed_frames() const { return elapsed_frames; }

    const QVector<BossAction>& get_actions() const { return actions; }

private:
    QVector<BossAction> actions;
    int current_index = 0;
    int elapsed_frames = 0;
};

#endif // BOSSPERFORMANCE_H
