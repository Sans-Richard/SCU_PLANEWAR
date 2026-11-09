#ifndef CONFIG_H
#define CONFIG_H

//头文件加载
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>

#define GAME_WIDTH 540
#define GAME_HEIGHT 1003
//图片，音频

//背景图片加载
#define STARTGAME_BACKGROUND ":/resource/startgame_background.png"
#define MENU_BACKGROUND ":/resource/startgame_background.png"
#define TIP_BACKGROUND ":/resource/tip_background.png"
#define TOP_BACKGROUND ":/resource/topscore_background.png"
#define LEVEL1_BACKGROUND ":/resource/img_bg_level_1.png" //第一关的背景
#define LEVEL2_BACKGROUND ":/resource/img_bg_level_2.png" //第二关的背景
#define CLEVEL_BACKGROUND ":/resource/clevel_background.png"

//暂停界面
#define PAUSE_PICTURE ":/resource/pause_picture.png"

//结束界面
#define END_PICTURE ":/resource/endbackground.png"
#define WIN1_PICTURE ":/resource/endbackground.png"//图片还没做，之后画
#define WIN2_PICTURE ":/resource/pause_picture.png"

//胜利界面
#define VICTORY_PICTURE ":/resource/victory_baclkground.png"

//Boss属性
#define BOSS_SPEED 0.5
#define BOSS_HEALTH 1000
#define BOSS_DAMAGE 50
#define BOSS_SCORE 500
#define BOSS_PICTURE1 ":/resource/img-boss_1.png"
#define BOSS_PICTURE2 ":/resource/img-boss_2.png"
// Boss2（无畏舰）属性
#define BOSS2_HEALTH 1500
#define BOSS2_DAMAGE 50
#define BOSS2_BOMB_DAMAGE 40
// Boss子弹速度（普通直线弹的两倍）
#define BOSS_BULLET_SPEED (ENEMYWEAPON1_SPEED * 2)


//关卡常量
#define LEVEL1_KILL_TARGET 10  // 击杀10个普通敌人后出boss
#define LEVEL2_KILL_TARGET 15  // 击杀15个普通敌人后出boss

//按钮图片加载
#define STARTGAME_BUTTON ":/resource/startgame_button.png"

//玩家飞机图片加载
#define PLAYERPLANE1_PICTURE ":/resource/playerplane1.png"
#define PLAYERPLANE2_PICTURE ":/resource/playerplane2.png"

//敌机图片加载
#define ENEMYPLANE1_PICTURE ":/resource/img-plane_1.png"
#define ENEMYPLANE2_PICTURE ":/resource/img-plane_3.png"
#define ENEMYPLANE3_PICTURE ":/resource/img-plane_5.png"
#define ENEMYPLANE4_PICTURE ":/resource/img-plane_7.png"

//子弹图片加载
//玩家子弹图片
#define PLAYERBULLET_PICTURE1 ":/resource/player_bullet1.png"
#define PLAYERBULLET_PICTURE2 ":/resource/player_bullet2.png"
#define PLAYERBULLET_PICTURE3 ":/resource/bullet_8.png"
#define PLAYERBULLET_PICTURE4 ":/resource/bullet_8.png"

//敌机子弹图片
#define ENEMYBULLET_PICTURE1 ":/resource/bullet_1.png"
#define ENEMYBULLET_PICTURE2 ":/resource/bullet_2.png"
#define ENEMYBULLET_PICTURE3 ":/resource/bullet_5.png"
#define ENEMYBULLET_PICTURE4 ":/resource/bullet_4.png"
//护盾图片
#define SHIELD_PICTURE ":/resource/shield.png"


//道具图片加载
#define POWERUP_TYPE_FIREPOWER_PICTURE  ":/resource/powerup_atk.png"  //火力增强
#define POWERUP_TYPE_HEALTH_PICTURE ":/resource/powerup_hp.png"  //生命恢复
#define POWERUP_TYPE_BOMB_PICTURE ":/resource/powerup_bomb.png"        //炸弹


//游戏周期
#define GAME_PERIOD 10 //(ms)

//游戏常量

//玩家飞机的属性
//1战斗机
#define PLAYERPLANE1_SPEED 5
#define PLAYERPLANE1_HEALTH 100
#define PLAYERPLANE1_DAMAGE 30

//2侦察机
#define PLAYERPLANE2_SPEED 8
#define PLAYERPLANE2_HEALTH 200
#define PLAYERPLANE2_DAMAGE 30

//玩家武器
//1战斗机
#define PLAYERWEAPON1_INTERVAL 300
#define PLAYERWEAPON1_SPEED 25
#define PLAYERWEAPON1_DAMAGE 25

//2侦察机
#define PLAYERWEAPON2_INTERVAL 350
#define PLAYERWEAPON2_SPEED 20
#define PLAYERWEAPON2_DAMAGE 20

//3
#define PLAYERWEAPON3_INTERVAL 1200
#define PLAYERWEAPON3_SPEED 10
#define PLAYERWEAPON3_DAMAGE 80

//4
#define PLAYERWEAPON4_INTERVAL 1000
#define PLAYERWEAPON4_SPEED 10
#define PLAYERWEAPON4_DAMAGE 120

//1：普通直线弹
//2：高速穿甲
//3：追踪
//4：散弹


//炸弹
#define BOMB_PICTURE ":/resource/bomb_picture.png"
//敌机
//第一种敌机
#define ENEMYPLANE1_SPEED 1 //移动速度
#define ENEMYPLANE1_HEALTH 100 //敌机的生命
#define ENEMYPLANE1_DAMAGE 10 //碰撞伤害
#define ENEMYPLANE1_SCORE 100 //分数
#define ENEMYPLANE1_EXPERIENCE 100 //经验值

#define ENEMYPLANE2_SPEED 0.8 //移动速度
#define ENEMYPLANE2_HEALTH 120 //敌机的生命
#define ENEMYPLANE2_DAMAGE 20 //碰撞伤害
#define ENEMYPLANE2_SCORE 120 //分数
#define ENEMYPLANE2_EXPERIENCE 120 //经验值

#define ENEMYPLANE3_SPEED 1 //移动速度
#define ENEMYPLANE3_HEALTH 100 //敌机的生命h
#define ENEMYPLANE3_DAMAGE 10 //碰撞伤害
#define ENEMYPLANE3_SCORE 110 //分数
#define ENEMYPLANE3_EXPERIENCE 110 //经验值

#define ENEMYPLANE4_SPEED 1 //移动速度
#define ENEMYPLANE4_HEALTH 80 //敌机的生命
#define ENEMYPLANE4_DAMAGE 5 //碰撞伤害
#define ENEMYPLANE4_SCORE 100 //分数
#define ENEMYPLANE4_EXPERIENCE 100 //经验值


//第一种敌机武器的属性
#define ENEMYWEAPON1_INTERVAL 2000 //发射间隔2000ms
#define ENEMYWEAPON1_SPEED 10 //发射出的子弹的移动速度
#define ENEMYWEAPON1_DAMAGE 10 //子弹伤害

#define ENEMYWEAPON2_INTERVAL 1300
#define ENEMYWEAPON2_SPEED 18 //发射出的子弹的移动速度
#define ENEMYWEAPON2_DAMAGE 20 //子弹伤害

#define ENEMYWEAPON3_INTERVAL 2000
#define ENEMYWEAPON3_SPEED 4 //发射出的子弹的移动速度
#define ENEMYWEAPON3_DAMAGE 10 //子弹伤害

#define ENEMYWEAPON4_INTERVAL 2500
#define ENEMYWEAPON4_SPEED 10 //发射出的子弹的移动速度
#define ENEMYWEAPON4_DAMAGE 5 //子弹伤害


//受伤后护盾的持续时间
#define SHIELD_PERIOD_1 1000 //1000ms


//道具数值常数
#define POWERUP_SPEED 3                    //道具下降速度
#define POWERUP_HEALTH_RESTORE 30          //生命恢复道具的恢复量
#define POWERUP_FIREPOWER_DURATION 10000   //火力增强持续时间(ms)
#define POWERUP_DROP_CHANCE 30             //道具掉落概率(百分比)

//道具效果类型
#define POWERUP_TYPE_FIREPOWER 1    //火力增强
#define POWERUP_TYPE_HEALTH 2       //生命恢复
#define POWERUP_TYPE_BOMB 3         //炸弹



#define TRACK_DURATION 3000
#define TRACK_RATE 0.40



#endif // CONFIG_H


