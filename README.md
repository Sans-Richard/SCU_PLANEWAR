# PlaneWar —— 雷电风格飞机大战（Qt 5 C++）

一个基于 **Qt 5.14.2 + MinGW** 的桌面端 2D 飞机大战游戏，包含无尽、双人合作、PVP、关卡（含两个 Boss）四种玩法。

本仓库同时是一份**从零复刻教程**：跟着下面的步骤，你可以在自己的机器上开发出一模一样的项目。

## 目录

- [一、先看效果](#一看效果)
- [二、环境搭建与运行](#二环境搭建与运行)
- [三、操作说明](#三操作说明)
- [四、项目结构](#四项目结构)
- [五、架构总览](#五架构总览)
- [六、从零开发教程（18 步）](#六从零开发教程)
- [七、常见坑](#七常见坑)

---

## 一、先看效果

| 功能 | 说明 |
|---|---|
| 游戏模式 | 无尽模式（刷分）、CO-OP 双人合作、PVP 双人对战、关卡模式（Level 1 / Level 2） |
| 玩家机型 | 战斗机（快、血薄）/ 侦察机（慢、血厚），各自独立武器参数 |
| 子弹系统 | 直线弹、高速穿甲弹、追踪弹、散弹 共 4 种玩家弹型；敌机/敌方多套弹型 |
| 道具 | 火力增强（限时）、生命恢复、炸弹补充，敌机概率掉落 |
| 炸弹 | 全屏清弹+伤害，Space / 数字键 1 释放 |
| 护盾 | 受伤后短暂无敌（1000ms），显示护盾贴图 |
| Boss 演出 | 脚本化 Boss 行为序列（进场、正弦摆动、俯冲、旋转弹幕、追踪弹、定点轰炸等），Boss1 / Boss2（无畏舰，14 发射源） |
| 计分与存档 | 实时分数、最高分文件持久化（`game_scores.txt`） |
| 画面后处理 | `BlenderStyleFilter`：亮度/对比度/饱和度/泛光/色调的软渲染滤镜 |

## 二、环境搭建与运行

1. 安装 **Qt 5.14.2**（勾选 MinGW 7.3.0 32-bit 组件与 Qt Creator）：[qt-opensource-windows-x86-5.14.2.exe](https://download.qt.io/archive/qt/5.14/5.14.2/)
   > 其他 Qt 5.x + MinGW 版本也可，本项目只用了 `core gui widgets` 基础模块，无特殊依赖。
2. 用 Qt Creator 打开 `Project/PlaneWar/PlaneWar.pro`，选 Desktop Qt 5.14.2 MinGW 32-bit 套件。
3. 直接点绿色三角构建运行即可。

命令行方式（可选）：

```bat
cd Project\PlaneWar
qmake PlaneWar.pro
mingw32-make release
```

## 三、操作说明

| 按键 | 作用 |
|---|---|
| `W A S D` | 玩家 1 移动（支持八方向斜飞） |
| `J` | 玩家 1 射击 |
| `Space` | 玩家 1 释放炸弹 |
| `↑ ↓ ← →` | 玩家 2 移动（CO-OP）/ PVP 中敌方玩家移动 |
| `0` | 玩家 2 射击 |
| `1` | 玩家 2 释放炸弹 |
| `P` | 暂停 / 继续 |
| `R` | 暂停或结束后返回主菜单 |

## 四、项目结构

```
PLANE_WAR/
├── Project/
│   ├── PlaneWar/            # 源代码（Qt 工程根目录）
│   │   ├── PlaneWar.pro     # qmake 工程文件
│   │   ├── config.h         # ★ 全部数值/路径常量集中于此
│   │   ├── main.cpp         # 程序入口，创建 Widget
│   │   ├── widget.h/cpp     # ★ 游戏主控（场景管理/主循环/碰撞/输入，约 1800 行）
│   │   ├── plane.h/cpp      # 飞机基类
│   │   ├── playerplane.*    # 玩家飞机（武器槽/护盾/炸弹数）
│   │   ├── enemyplane.*     # 敌机（5 种初始化 + Boss 演出驱动）
│   │   ├── bullet.h/cpp     # 子弹基类（含对象池状态位）
│   │   ├── playerbullet.*   # 玩家子弹（4 种弹道）
│   │   ├── enemybullet.*    # 敌机子弹（含 Boss 自定义方向弹）
│   │   ├── weapon.h/cpp     # 武器基类（发射间隔/速度/伤害/连发标志）
│   │   ├── playerweapon.* / enemyweapon.*
│   │   ├── powerup.*        # 道具
│   │   ├── *pool.*          # 玩家子弹池 / 敌机池 / 敌机子弹池 / 道具池
│   │   ├── bossperformance.*# Boss 行为脚本系统（BossAction 序列）
│   │   ├── blenderstylefilter.* # 图片风格滤镜
│   │   ├── res.qrc          # 资源清单（嵌入 exe）
│   │   ├── resource/        # png 贴图
│   │   └── game_scores.txt  # 最高分存档
│   └── package_release.bat  # 发布打包脚本
└── SOURCE/                  # Photoshop 源文件（美术素材）
```

## 五、架构总览

复刻前先记住这 4 条设计主线，后面每一步都会展开：

1. **单 View 多 Scene**：一个 `QGraphicsView`，10 个 `QGraphicsScene`（开始/菜单/说明/排行/无尽/合作/PVP/选关/关卡1/关卡2），切场景就是 `view->setScene(xxx_scene)`。
2. **一个 QTimer 驱动主循环**：`GAME_PERIOD = 10ms`（100FPS），超时信号按当前模式接到对应的 `xxx_update()` 槽。
3. **三套基类继承链** + **四种对象池**：`Plane`、`Bullet`、`Weapon` 各派生玩家/敌机版本；子弹、敌机、道具全部走池化复用（`status: 0 失效 / 1 等待 / 2 激活`）。
4. **数据集中在 config.h**：所有血量、速度、伤害、分数、间隔、图片路径都是宏，调平衡 = 改一个文件。

## 六、从零开发教程

> 建议顺序：先跑通第 1~6 步得到一个能动的"最小可玩核心"，再按 7~18 逐步补齐功能。每个类都很小，直接对照仓库源码抄接口即可。

### 步骤 1：建工程 + 骨架

Qt Creator → New Project → Application (Qt Widgets) → 名称 `PlaneWar`，Kit 选 MinGW。生成的 `.pro` 只保留：

```pro
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
SOURCES += ...   # 按第四节的文件列表逐个添加
HEADERS += ...
FORMS += widget.ui
RESOURCES += res.qrc
```

`main.cpp` 三行核心：`QApplication a; Widget w; w.show(); return a.exec();`

### 步骤 2：写 config.h

把所有常量先定死（直接抄仓库 `config.h`，这是本项目"数值系统"的全部真相）：

```cpp
#define GAME_WIDTH 540
#define GAME_HEIGHT 1003
#define GAME_PERIOD 10                       // 主循环 10ms
#define PLAYERPLANE1_SPEED 5                 // 战斗机
#define PLAYERPLANE2_HEALTH 200              // 侦察机血量
#define ENEMYWEAPON1_INTERVAL 2000           // 敌机开火间隔
#define SHIELD_PERIOD_1 1000                 // 无敌时间
#define POWERUP_DROP_CHANCE 30               // 道具掉率%
#define BOSS2_HEALTH 1500                    // Boss2
// ……全部见源码
```

### 步骤 3：单 View 多 Scene 框架

在 `Widget` 构造函数里搭骨架（对应 `init_game()`）：

```cpp
view = new QGraphicsView(this);
startgame_scene = new QGraphicsScene(this);
menu_scene      = new QGraphicsScene(this);
// ……共 10 个 scene
view->setScene(startgame_scene);
view->setSceneRect(0, 0, 540, 1003);   // 固定逻辑分辨率
```

之后所有界面跳转函数（`turn_to_menu / turn_to_endless / ...`）只做三件事：**换 scene、重挂 timer 槽、初始化该局对象**。UI 元素用 `QPushButton / QProgressBar / QLineEdit` 直接 `move()` 到 view 上（控件浮在场景之上，不参与碰撞，血量条就是这么做的）。

### 步骤 4：资源系统

把 `resource/` 里的 png 全部登记进 `res.qrc`，代码里统一用 `:/resource/xxx.png` 宏加载：

```cpp
#define PLAYERPLANE1_PICTURE ":/resource/playerplane1.png"
```

贴图来源：仓库 `SOURCE/` 下的 psd 导出 png（或用任意同类素材替换，只要文件名一致即可跑）。

### 步骤 5：三条继承链的基类

```cpp
class Plane : public QGraphicsPixmapItem { public: double speed, health, max_health, damage; int status; };
class Bullet : public QGraphicsPixmapItem { public: int status; /* 0失效 1等待 2激活 */ double speed, damage; };
class Weapon : public QGraphicsPixmapItem { public: int interval; double speed, damage; bool is_continuously_shooting; };
```

派生类各司其职：

- `PlayerPlane`：`init_1()/init_2()` 按机型填属性，挂 3 个 `PlayerWeapon*` 武器槽、`shield` 贴图 + `QTimer` 无敌计时、`bomb_count`。
- `EnemyPlane`：`init1()~init4()` 四种小怪 + `init_boss(kind)`；`move1()~move4()` 不同弹道运动（直线 / 正弦横摆 `sin(wave_time)*wave_amp` / 俯冲等）；`weapon_shoot()` 开火。
- `PlayerBullet`：`move1()~move4()` 对应 **直线 / 高速穿甲 / 追踪（每帧向玩家坐标修正方向，`TRACK_RATE=0.40` 偏转系数，`TRACK_DURATION=3000ms` 后失效）/ 散弹**。
- `EnemyBullet`：额外有 `move_boss()`（用 `finalDirX/finalDirY` 自定义方向向量）和 `borntime`（追踪弹生命周期）。

### 步骤 6：对象池（本项目性能设计核心）

高频创建销毁的物体（子弹/敌机/道具）一律池化。池结构 = `QList`（持有全部对象，构造时一次性 new 并 `addToScene`）+ `QQueue`（空闲索引）：

```cpp
EnemyPlane* EnemyPlanePool::get_new_enemyplane() {
    if (enemyplane_pool_queue->isEmpty()) return nullptr; // 池满则本帧不刷
    EnemyPlane* p = enemyplane_pool_queue->dequeue();
    p->status = 2;                 // 激活
    p->setVisible(true);
    return p;
}
void EnemyPlanePool::return_enemyplane(EnemyPlane* p) {
    p->status = 1; p->setVisible(false); // 回收
    enemyplane_pool_queue->enqueue(p);
}
```

`Widget::load_pool(scene)` 在游戏开始时为每个场景建立 4 个池。**任何"销毁"都不 delete，只 setVisible(false) 归还**——这是雷电类弹幕游戏不掉帧的关键。

### 步骤 7：主循环

```cpp
game_timer = new QTimer(this);
game_timer->setInterval(GAME_PERIOD);
// 进入无尽模式时：
connect(game_timer, &QTimer::timeout, this, &Widget::endless_update, Qt::UniqueConnection);
game_timer->start();
```

每个 `xxx_update()` 内部套路完全一致（先调 `general_update()` 再补模式特有逻辑）：

```
1. 玩家移动(按按键链表) → 2. 武器按 interval 计时发弹(从池取)
→ 3. 所有激活物体 move() → 4. 出界/超时回收进池
→ 5. collision_detection() → 6. 刷怪计时/关卡目标判定 → 7. 刷新 UI 文本
```

`Qt::UniqueConnection` 必加：模式切换时同一 timer 换槽，不加会重复连接、游戏速度翻倍。

### 步骤 8：键盘输入与八方向移动

用两个 `QList<int>` 记录**当前按下**的键（`keyPressEvent` append、`keyReleaseEvent` removeAll）。每帧移动时遍历链表把 W/S 合成 vy、A/D 合成 vx，一次算出斜向位移——这就是"斜飞不卡顿"的实现：

```cpp
void Widget::playerplane1_move() {
    double dx = 0, dy = 0;
    for (int k : move_list_WASD) {
        if (k == Qt::Key_W) dy -= speed; if (k == Qt::Key_S) dy += speed;
        if (k == Qt::Key_A) dx -= speed; if (k == Qt::Key_D) dx += speed;
    }
    // 限幅到 [0, GAME_WIDTH-pixmap.width()]
}
```

射击键 `J` / `0` 只是把对应武器的 `is_continuously_shooting = true`，真正发射在主循环里按 `interval` 节流。

### 步骤 9：碰撞检测

四组两两遍历（池里的数量级完全够用，不需要空间划分）：

- 玩家子弹 × 敌机 → 敌机扣血、子弹回收；血量归零 → `destroy()`：加分数、概率掉道具、归还池
- 敌机子弹 × 玩家 → 有盾跳过；否则扣血 + 开启 `SHIELD_PERIOD_1` 无敌
- 玩家 × 敌机机体 → 双方互撞扣碰撞伤害
- 玩家 × 道具 → `apply_effect()`

判定一律用 AABB（`pos()` + `pixmap().rect()` 求交），不要走 `QGraphicsItem::collidesWith` 的路径匹配，像素图会误判且慢。

### 步骤 10：道具

`PowerUp::apply_effect(player)` 按类型分发：

- **火力增强**：先备份武器原伤害 `original_w1_damage`…再乘系数，挂 10s 的 `effect_timer` 到期恢复；
- **回血**：`health = min(max_health, health + POWERUP_HEALTH_RESTORE)`；
- **炸弹**：`bomb_count`（上限 5）。

掉落在敌机 `destroy()` 处：`rand() % 100 < POWERUP_DROP_CHANCE` 时从道具池取一个，随机 x 落在敌机死亡位置。

### 步骤 11：炸弹

`playerplane_release_bomb()`：数量校验 → `bomb_damage()`（对全屏激活敌机结算伤害、清空所有敌机子弹回池）→ 屏幕中央显示 `bomb_picture`，`QTimer::singleShot` 几百毫秒后隐藏。

### 步骤 12：护盾

受伤瞬间 `shield->setVisible(true)` + `shield_timer->start(SHIELD_PERIOD_1)`；`timeout` 槽里隐藏护盾并断开无敌标志。玩家子弹/敌机子弹碰撞函数开头都要检查无敌状态。

### 步骤 13：四种模式

在模式函数里复用同一套 update 管线，只改"刷怪表 + 玩家数 + 胜负判定"：

- **endless**：按波次计时随机刷 1~4 号敌机，玩家死 → `game_end()` → `save_score()`。
- **coop**：同 endless，多一个 `playerplane2`（方向键 + `0` + `1` 号键），双人分数 `score1/score2` 分列显示。
- **pvp**：玩家 2 用 `EnemyPlane` 扮演（`isPlayerControl = true`，方向键移动、`0` 射击），子弹阵营靠 `owner` 字段区分，命中对方即判胜。
- **level1/2**：`level_kill_count` 达到 `LEVELx_KILL_TARGET`（10/15）后从池取 `init_boss()` 生成 Boss，击杀 → `game_victory()`。

### 步骤 14：Boss 演出系统（本项目最有意思的模块）

Boss 行为不要写死在 if-else 里，用**脚本序列**：把 Boss 一整场拆成 `QVector<BossAction>`，每个 action = 移动方式 + 攻击方式 + 持续帧数，`BossPerformance::update()` 每帧推进，走完换下一条：

```cpp
enum class BossMoveType   { None, EnterScreen, MoveTo, MoveDown, SineWave, Dive, Stay };
enum class BossAttackType { None, Forward, ForwardBack, FourDir, Rotate1, Rotate2, Rotate4,
                            Boss2_Enter, Boss2_RandomDir, Boss2_Track, Boss2_AimPlayer, Boss2_FrontAimBomb };
struct BossAction { BossMoveType move_type; QPointF target_pos; int duration_frames; /*…*/ };
```

`EnemyPlane::boss_perform()` 每帧取 `get_current_action()`，分别执行 `boss_move_by_action()` 和 `boss_attack_by_action()`。

- **Boss1**：进场 → 正弦横摆 4 向射击 → 俯冲（`dive_count=8`，每次右移 `dive_speed_x`）→ 1/2/4 发射源 360° 旋转弹幕（`rotate_speed = 45°/s` 折算成"度/帧"）。
- **Boss2 无畏舰**：`emitter_offsets_x/y[14]` 定义 14 个发射源（每侧 7 个），支持随机方向弹幕、14 源追踪弹、瞄准玩家射击 + 落点区域爆炸（`boss2_update_bombs()` 每帧结算爆炸）。

想设计自己的 Boss：只需在 `build_bossX()` 里往 `actions` 追加新序列，游戏逻辑零改动。

### 步骤 15：分数持久化

`save_score()` / `load_score()`：文本文件 `game_scores.txt` 存最高分，结束界面读取显示，topscore 场景加载时展示。注意**工作目录问题**：Qt Creator 里运行时工作目录是构建目录，所以你在仓库里能看到两份 `game_scores.txt`——发布时要么用绝对路径（`QCoreApplication::applicationDirPath()`），要么把文件随 exe 一起拷。

### 步骤 16：暂停 / 结束 / 胜利界面

`status` 字段三态：`0 结束 / 1 暂停 / 2 运行`。update 函数第一行统一 `if (status != 2) return;` 即可实现暂停；`load_pause()/load_end()` 只是往当前 scene `addToScene` 一张居中背景图 + `QGraphicsRectItem` 半透明遮罩。

### 步骤 17：BlenderStyleFilter（可选美术增强）

一个纯静态工具类：`applyCompositeStyle(pixmap)` 对 QPixmap 做 亮度+对比度+饱和度调整 → boxBlur 提取亮部做 bloom 叠加 → 蓝色调 tint。加载贴图时套一层就能统一画风：

```cpp
QPixmap styled = BlenderStyleFilter::applyCompositeStyle(QPixmap(PLAYERPLANE1_PICTURE));
```

### 步骤 18：发布打包

Qt Creator 构建 Release 后，直接运行仓库里的 `Project/package_release.bat`，它会把 exe + 6 个必需 DLL + `platforms/qwindows.dll` + resource 拷进 `PlaneWar_Release/`，压 zip 即可分发：

- Qt5Core.dll / Qt5Gui.dll / Qt5Widgets.dll
- libgcc_s_dw2-1.dll / libstdc++-6.dll / libwinpthread-1.dll
- platforms/qwindows.dll（缺它必崩，报 "could not find or load the Qt platform plugin windows"）

> 等价做法：命令行 `windeployqt PlaneWar.exe` 一条命令全自动收集。

## 七、常见坑

1. **timer 重复 connect** → 换模式后游戏加速/子弹双发。解决：`Qt::UniqueConnection`。
2. **忘记 return 到池** → 池耗尽后不再刷怪。排查：把 `get_new_xxx()` 返回 nullptr 打日志。
3. **场景切换后指针悬空**：本项目对象按场景归属建立（`load_pool(scene)` 在 turn_to_xxx 里重建），切模式时旧对象要清出场景再归还。
4. **QProgressBar 放在 view 上而不是 scene 里**：它是 QWidget，不是 QGraphicsItem；`move()` 坐标是 view 视口坐标。
5. **像素图碰撞误判**：坚持手写 AABB，不要用 `collidesWith()`。
6. **`rand()` 分布**：本项目够用；要更均匀用 `QRandomGenerator`。

---

*素材：`SOURCE/` 下为 PSD 工程文件；代码结构围绕 `widget.cpp` 主控 + `config.h` 数据展开。欢迎提 Issue / PR。*
