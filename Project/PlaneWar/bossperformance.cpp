#include "bossperformance.h"
#include <QtMath>
//行为模式为下面被直线夹起来的注释，请看清楚，不过有很多废案，读者自行分辨
BossPerformance::BossPerformance()
{
}

void BossPerformance::build_boss2()
{
    actions.clear();

    const int frames_per_sec = 1000 / GAME_PERIOD; // = 100

    // ============================================================
    // 行为1: 从最上方进入屏幕，慢速移动到地图上1/4处
    // 移动：从上往下，持续移动直到到达目标位置
    // 攻击：最前2个直线向下，其余12个45°向下斜射
    // ============================================================
    {
        BossAction action;
        action.move_type = BossMoveType::EnterScreen;
        // 目的地改为上1/4处（原为地图中央，太靠下）
        action.target_pos = QPointF(GAME_WIDTH / 2.0, GAME_HEIGHT / 4.0);
        action.move_speed = 2.0;
        action.attack_type = BossAttackType::Boss2_Enter;
        action.bullet_speed = ENEMYWEAPON1_SPEED;
        action.bullet_damage = 25;
        action.shoot_interval = 15;
        action.duration_frames = 5 * frames_per_sec;
        actions.append(action);
    }

    // ============================================================
    // 行为2: 到达位置后停留2秒，不发射
    // ============================================================
    {
        BossAction action;
        action.move_type = BossMoveType::Stay;
        action.attack_type = BossAttackType::None;
        action.duration_frames = 2 * frames_per_sec;
        actions.append(action);
    }

    // ============================================================
    // 行为3: 只保留4个发射源随机方向发射（最前2个+最后2个）
    // ============================================================
    {
        BossAction action;
        action.move_type = BossMoveType::Stay;
        action.attack_type = BossAttackType::Boss2_RandomDir;
        action.bullet_speed = ENEMYWEAPON1_SPEED;
        action.bullet_damage = 25;
        action.shoot_interval = 20;
        action.duration_frames = 3 * frames_per_sec;
        actions.append(action);
    }

    // ============================================================
    // 行为4: 只保留2个发射源发射追踪弹（最前2个）
    // ============================================================
    {
        BossAction action;
        action.move_type = BossMoveType::Stay;
        action.attack_type = BossAttackType::Boss2_Track;
        action.bullet_speed = ENEMYWEAPON1_SPEED * 0.5;
        action.bullet_damage = 25;
        action.shoot_interval = 25;
        action.duration_frames = 3 * frames_per_sec;
        actions.append(action);
    }

    // ============================================================
    // 行为5: 只保留1个发射源向玩家方向发射 + 玩家位置出现danger
    // ============================================================
    {
        BossAction action;
        action.move_type = BossMoveType::Stay;
        action.attack_type = BossAttackType::Boss2_AimPlayer;
        action.bullet_speed = ENEMYWEAPON1_SPEED;
        action.bullet_damage = 25;
        action.shoot_interval = 20;
        action.duration_frames = 3 * frames_per_sec;
        actions.append(action);
    }

    // 行为7       确认是废案

    // 重置到开头
    reset();

}



void BossPerformance::build_boss1()

{
    actions.clear();

    const int frames_per_sec = 1000 / GAME_PERIOD; // = 100

    // ============================================================
    // 行为1: 从最上方进入屏幕，快速移动到地图上1/3位置
    // 移动：从上往下，持续1秒
    // 攻击：战斗机两翼+机头，总共向前（向下）高速发射三束子弹
    // ============================================================
    {
        BossAction action;
        action.move_type = BossMoveType::EnterScreen;
        // 目标位置：地图上1/3处，减去图片大小的一半使boss中心对齐
        action.target_pos = QPointF(GAME_WIDTH / 2.0, GAME_HEIGHT / 3.0);
        action.move_speed = 8.0; // 快速进入
        action.attack_type = BossAttackType::Forward;
        action.bullet_speed = ENEMYWEAPON1_SPEED * 2; // 普通直线弹两倍
        action.bullet_damage = 25;
        action.shoot_interval = 3;
        action.duration_frames = 1 * frames_per_sec; // 1秒
        actions.append(action);
    }

    // ============================================================
    // 行为2: 到达位置后停留1秒，随后移动到地图中央
    // 无攻击
    // ============================================================
    {
        // 2a: 停留1秒
        BossAction action;
        action.move_type = BossMoveType::Stay;
        action.attack_type = BossAttackType::None;
        action.duration_frames = 1 * frames_per_sec;
        actions.append(action);

        // 2b: 移动到地图中央
        BossAction action2;
        action2.move_type = BossMoveType::MoveTo;
        // 目标位置：地图中央，减去图片大小的一半使boss中心对齐
        action2.target_pos = QPointF(GAME_WIDTH / 2.0, GAME_HEIGHT / 2.0);
        action2.move_speed = 3.0;
        action2.attack_type = BossAttackType::None;
        action2.duration_frames = 2 * frames_per_sec; // 最多2秒，到达后自动切换
        actions.append(action2);
    }


    // ============================================================
    // 行为3: 1个发射源（前），持续发射1秒，停1秒
    // ============================================================
    {
        // 3a: 发射1秒
        BossAction action;
        action.move_type = BossMoveType::Stay;
        action.attack_type = BossAttackType::Forward;
        action.bullet_speed = ENEMYWEAPON1_SPEED * 2;
        action.bullet_damage = 25;
        action.shoot_interval = 3;
        action.duration_frames = 1 * frames_per_sec;
        actions.append(action);

        // 3b: 停1秒
        BossAction action2;
        action2.move_type = BossMoveType::Stay;
        action2.attack_type = BossAttackType::None;
        action2.duration_frames = 1 * frames_per_sec;
        actions.append(action2);
    }

    // ============================================================
    // 行为4: 2个发射源（前后），持续发射1秒，停1秒
    // ============================================================
    {
        // 4a: 发射1秒
        BossAction action;
        action.move_type = BossMoveType::Stay;
        action.attack_type = BossAttackType::ForwardBack;
        action.bullet_speed = ENEMYWEAPON1_SPEED * 2;
        action.bullet_damage = 25;
        action.shoot_interval = 3;
        action.duration_frames = 1 * frames_per_sec;
        actions.append(action);

        // 4b: 停1秒
        BossAction action2;
        action2.move_type = BossMoveType::Stay;
        action2.attack_type = BossAttackType::None;
        action2.duration_frames = 1 * frames_per_sec;
        actions.append(action2);
    }

    // ============================================================
    // 行为5: 4个发射源（前后左右），持续发射1秒，停1秒
    // ============================================================
    {
        // 5a: 发射1秒
        BossAction action;
        action.move_type = BossMoveType::Stay;
        action.attack_type = BossAttackType::FourDir;
        action.bullet_speed = ENEMYWEAPON1_SPEED * 2;
        action.bullet_damage = 25;
        action.shoot_interval = 3;
        action.duration_frames = 1 * frames_per_sec;
        actions.append(action);

        // 5b: 停1秒
        BossAction action2;
        action2.move_type = BossMoveType::Stay;
        action2.attack_type = BossAttackType::None;
        action2.duration_frames = 1 * frames_per_sec;
        actions.append(action2);
    }

    // ============================================================
    // 行为6: 1个发射源旋转360度，持续8秒，停1秒
    // ============================================================
    {
        // 6a: 旋转发射8秒
        BossAction action;
        action.move_type = BossMoveType::Stay;
        action.attack_type = BossAttackType::Rotate1;
        action.bullet_speed = ENEMYWEAPON1_SPEED * 2;
        action.bullet_damage = 25;
        action.shoot_interval = 3;
        action.rotate_speed = 180.0 / frames_per_sec; // 180°/秒（45°的4倍）
        action.duration_frames = 8 * frames_per_sec;
        actions.append(action);

        // 6b: 停1秒
        BossAction action2;
        action2.move_type = BossMoveType::Stay;
        action2.attack_type = BossAttackType::None;
        action2.duration_frames = 1 * frames_per_sec;
        actions.append(action2);
    }

    // ============================================================
    // 行为7: 2个发射源旋转360度，持续8秒，停1秒
    // ============================================================
    {
        // 7a: 旋转发射8秒
        BossAction action;
        action.move_type = BossMoveType::Stay;
        action.attack_type = BossAttackType::Rotate2;
        action.bullet_speed = ENEMYWEAPON1_SPEED * 2;
        action.bullet_damage = 25;
        action.shoot_interval = 3;
        action.rotate_speed = 180.0 / frames_per_sec; // 180°/秒（45°的4倍）
        action.duration_frames = 8 * frames_per_sec;
        actions.append(action);

        // 7b: 停1秒
        BossAction action2;
        action2.move_type = BossMoveType::Stay;
        action2.attack_type = BossAttackType::None;
        action2.duration_frames = 1 * frames_per_sec;
        actions.append(action2);
    }

    // ============================================================
    // 行为8: 4个发射源旋转360度，持续8秒，停1秒
    // ============================================================
    {
        // 8a: 旋转发射8秒
        BossAction action;
        action.move_type = BossMoveType::Stay;
        action.attack_type = BossAttackType::Rotate4;
        action.bullet_speed = ENEMYWEAPON1_SPEED * 2;
        action.bullet_damage = 25;
        action.shoot_interval = 3;
        action.rotate_speed = 180.0 / frames_per_sec; // 180°/秒（45°的4倍）
        action.duration_frames = 8 * frames_per_sec;
        actions.append(action);

        // 8b: 停1秒
        BossAction action2;
        action2.move_type = BossMoveType::Stay;
        action2.attack_type = BossAttackType::None;
        action2.duration_frames = 1 * frames_per_sec;
        actions.append(action2);
    }


    // ============================================================
    // 行为9: 先移动到左上角，然后俯冲表演
    // 从左上角开始，高速向下俯冲到底部，回到顶部右移一点，重复
    // 总共8次，到达右下角后传送回最上方初始位置
    // ============================================================
    {
        // 9a: 先移动到左上角（x=0, y=-100）
        BossAction action_move;
        action_move.move_type = BossMoveType::MoveTo;
        action_move.target_pos = QPointF(0, -100);
        action_move.move_speed = 8.0;
        action_move.attack_type = BossAttackType::None;
        action_move.duration_frames = 2 * frames_per_sec;
        actions.append(action_move);

        // 9b: 俯冲表演
        BossAction action;
        action.move_type = BossMoveType::Dive;
        action.dive_count = 8;
        // 地图宽度540，从x=0到x=540，8次俯冲，每次右移 540/8 ≈ 67.5
        action.dive_speed_x = GAME_WIDTH / 8.0;
        action.move_speed = 12.0; // 高速俯冲
        action.attack_type = BossAttackType::None;
        action.duration_frames = 10 * frames_per_sec; // 给足够时间完成8次俯冲
        actions.append(action);
    }


    // 重置到开头
    reset();
}

const BossAction* BossPerformance::get_current_action() const
{
    if (current_index < 0 || current_index >= actions.size())
        return nullptr;
    return &actions[current_index];
}

bool BossPerformance::update()
{
    if (actions.isEmpty())
        return true;

    elapsed_frames++;

    const BossAction* action = get_current_action();
    if (!action)
        return true;

    // 检查当前行为是否结束
    if (elapsed_frames >= action->duration_frames) {
        // 切换到下一个行为
        current_index++;
        elapsed_frames = 0;

        // 如果到达末尾，循环回开头
        if (current_index >= actions.size()) {
            current_index = 0;
        }
        return true; // 行为已切换
    }

    return false; // 当前行为还在进行中
}

void BossPerformance::reset()
{
    current_index = 0;
    elapsed_frames = 0;
}
