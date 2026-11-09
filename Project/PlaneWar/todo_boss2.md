# Boss2 实现计划

## 需要修改的文件

### 1. config.h
- 添加 BOSS2_HEALTH = 1500
- 添加 BOSS2_DAMAGE = 50
- 添加 BOSS_BOMB_DAMAGE = 40
- 添加 DANGER_PICTURE 和 BOSS_BOMB_PICTURE

### 2. bossperformance.h
- 添加新的攻击类型：Track（追踪弹）、AimPlayer（向玩家方向）、Bomb（爆炸）
- 添加发射源数组定义（14个发射源位置）

### 3. bossperformance.cpp
- 实现 build_boss2() 演出列表

### 4. enemyplane.h
- 添加 boss2 相关成员：爆炸列表、danger列表、玩家指针等

### 5. enemyplane.cpp
- 实现 boss2 的爆炸攻击、danger信号等
- 修改 boss_attack_by_action 支持新攻击类型

### 6. widget.cpp
- 在 level2_update 中传递玩家指针给boss
- 处理爆炸效果显示

### 7. res.qrc
- 添加 danger.png 和 boss_bomb.png
