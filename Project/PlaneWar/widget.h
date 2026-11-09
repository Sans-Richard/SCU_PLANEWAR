#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "config.h"
#include <QPushButton>
#include <QSize>
#include <QTimer>
#include <QScrollBar>
#include "playerplane.h"
#include <QEvent>
#include <QKeyEvent>
#include <QList>
#include "enemyplanepool.h"
#include <random>
#include  "enemybulletpool.h"
#include "poweruppool.h"
#include <QProgressBar>
#include "QLineEdit"
#include "blenderstylefilter.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //初始化游戏
    void  init_game();

    //加载函数
    //总加载函数
    void load_resources();
    //开始游戏加载函数
    void load_startgame();
    //主界面加载函数
    void load_menu();
    //
    void load_tip();
    //
    void load_topscore();
    //
    void load_endless();
    void load_coop();
    void load_pvp();

    void load_clevel();
    void load_level1();
    void load_level2();
    //计时器加载函数
    void load_timer();

    void load_pause();

    void load_end();

    //对象池加载
    void load_pool(QGraphicsScene* scene);
    //玩家飞机加载函数
    void load_playerplane1(int kind,int x,QGraphicsScene* scene);
    void load_playerplane2(int kind,int x,QGraphicsScene* scene);


    //更新函数
    //不同关卡更新函数
    void endless_update();
    void coop_update();
    void level1_update();
    void level2_update();
    void pvp_update();
    //通用更新函数
    void general_update();


    void turn_to_menu();
    void turn_to_endless();
    void turn_to_coop();
    void turn_to_pvp();
    void turn_to_level1();
    void turn_to_level2();



    //键盘输入
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    //玩家移动函数
    void playerplane1_move();
    void playerplane2_move();

    void player_enemy_move();

    //碰撞检测
    void collision_detection();//总
    void collision_detection_playerbullet_with_enemyplane();
    void collision_detection_enemybullet_with_playerplane();
    void collision_detection_playerplane_with_enemyplane();
    void collision_detection_playerplane_with_powerup();

    //炸弹效果
    void playerplane_release_bomb(PlayerPlane* playerplane);
    void bomb_damage();

    void game_pause();

    void game_end();
    void game_victory();

    void save_score();
    int load_score();

    void delete_level();




    //使用炸弹时显示的图片
    QGraphicsPixmapItem* bomb_picture = nullptr;

    //view
    QGraphicsView* view = nullptr;

    //scene
    QGraphicsScene* startgame_scene = nullptr;
    QGraphicsScene* menu_scene = nullptr;
    QGraphicsScene* tip_scene = nullptr;
    QGraphicsScene* topscore_scene = nullptr;
    QGraphicsScene* endless_scene = nullptr;
    QGraphicsScene* coop_scene = nullptr;
    QGraphicsScene* pvp_scene = nullptr;
    QGraphicsScene* clevel_scene = nullptr;
    QGraphicsScene* level1_scene = nullptr;
    QGraphicsScene* level2_scene = nullptr;

    //背景图
    QGraphicsPixmapItem* startgame_background = nullptr;
    QGraphicsPixmapItem* menu_background = nullptr;
    QGraphicsPixmapItem* tip_background = nullptr;
    QGraphicsPixmapItem* topscore_background = nullptr;
    QGraphicsPixmapItem* level1_background1 = nullptr, *level1_background2 = nullptr;
    QGraphicsPixmapItem* level2_background1 = nullptr, *level2_background2 = nullptr;
    QGraphicsPixmapItem* clevel_background = nullptr;


    //关卡ui
    //血量
    QProgressBar* playerplane1_health_bar = nullptr , *playerplane2_health_bar = nullptr;
    QLineEdit* playerplane1_health_text = nullptr , *playerplane2_health_text = nullptr;
    //炸弹数量
    QLineEdit* playerplane1_bomb_text = nullptr , *playerplane2_bomb_text = nullptr;

    //按钮
    //开始界面按钮
    QPushButton* startgame_button = nullptr;
    //tip和top用的关闭按钮
    QPushButton* close_button = nullptr;
    //主菜单按钮
    QPushButton* menu_pve_button = nullptr;
    QPushButton* menu_pvp_button = nullptr;
    QPushButton* menu_coop_button = nullptr;
    QPushButton* menu_end_button = nullptr;
    QPushButton* menu_tip_button = nullptr;
    QPushButton* menu_exit_button = nullptr;
    QPushButton* menu_top_button = nullptr;

    //选关按钮
    QPushButton* level1_button = nullptr;
    QPushButton* level2_button = nullptr;

    //计时器
    QTimer* game_timer = nullptr;


    //玩家飞机
    PlayerPlane* playerplane1 = nullptr, *playerplane2 = nullptr;
    //pvp下的玩家2
    EnemyPlane* player_enemy = nullptr;
    bool player_enemy_shoot_flag = false;

    int pvp_win_flag = 0;

    //玩家飞机移动链表
    QList<int> move_list_WASD;//玩家1
    QList<int> move_list_ARROW;//玩家2


    //对象池
    //玩家子弹池
    PlayerBulletPool* playerbullet_pool = nullptr;
    //敌机对象池
    EnemyPlanePool* enemyplane_pool = nullptr;
    //敌机子弹对象池
    EnemyBulletPool* enemybullet_pool = nullptr;
    //道具对象池
    PowerUpPool* powerup_pool = nullptr;


    //暂停界面
    QGraphicsPixmapItem* pause_picture = nullptr;
    QGraphicsRectItem* pause_background = nullptr;
    //结束
     QGraphicsPixmapItem* end_picture = nullptr;
    //胜利
     QGraphicsPixmapItem* victory_picture = nullptr;
    //游戏状态
    int status = 2;//0 游戏结束  1 游戏暂停 2游戏正常运行

    //分数
    int score = 0;
    QLineEdit* high_score_text = nullptr;
    QLineEdit* score_text = nullptr;
    int score1 = 0;
    int score2 = 0;
    QLineEdit* score1_text = nullptr;
    QLineEdit* score2_text = nullptr;

    //关卡模式状态
    EnemyPlane* level_boss = nullptr;
    int level_kill_count = 0;
    bool level_boss_spawned = false;
    bool level_victory = false;

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
