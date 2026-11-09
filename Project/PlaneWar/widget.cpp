#include "widget.h"
#include "ui_widget.h"

QString btnStyle = R"(
                   QPushButton{
                   background-color: transparent;
                   border: none;
                   padding: 0px;
                   outline: none;
                   }
                   /* 鼠标悬停 青绿色遮罩 */
                   QPushButton:hover{
                   background-color: rgba(0, 180, 60, 70);
                   }
                   /* 鼠标按下 加深 */
                   QPushButton:pressed{
                   background-color: rgba(0, 220, 80, 110);
                   }
                   )";
//按钮美化

QString  hbStyly = R"(
QProgressBar {
    border: 2px solid #006622;
    text-align: center;
    height: 30px;
    background-color: rgba(0, 0, 0, 0); /* 空白区域完全透明 */
}
QProgressBar::chunk {
    background-color: #00aa00; /* 纯色绿色进度 */
    margin: 1px;
}
)";
//血量条
QString htStyly = R"(
                  QLineEdit:read-only {
                  font-family: "Arial Black";
                  font-size: 20px;
                  font-weight: bold;
                  background-color: transparent;
                  border: none;
                  color: #00ccff;   /* 亮蓝色 */
                  }
                  )";
//文字

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("PLANE WAR");
    this->setWindowIcon(QIcon(":/resource/icon.png"));
    this->setMaximumSize(540,1003);
    this->setMinimumSize(540,1003);

    init_game();
    load_resources();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init_game()
{
    view = new QGraphicsView();
    view->setParent(this);
    startgame_scene = new QGraphicsScene();
    view->setScene(startgame_scene);


    //禁用水平，垂直滑动条
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //禁用鼠标滚轮滚动地图
    view->verticalScrollBar()->setEnabled(false);
    view->horizontalScrollBar()->setEnabled(false);
    //禁用方向键移动地图
    view->setDragMode(QGraphicsView::NoDrag);
    view->setSceneRect(0,0,540,1003);


    view->setFocusPolicy(Qt::NoFocus);//防止视图拿到键盘焦点
}

void Widget::load_resources()
{
    load_timer();
    load_startgame();
    load_menu();
    load_tip();
    load_topscore();
    load_clevel();
    load_pause();
    load_end();
}

void Widget::load_startgame()
{
    //picture
    startgame_background = new QGraphicsPixmapItem;
    {
        QPixmap original(STARTGAME_BACKGROUND);
        QPixmap filtered = BlenderStyleFilter::applyCompositeStyle(original, 26, 1.35, 1.35, 7, QColor(120, 90, 255, 34));
        startgame_background->setPixmap(filtered);
    }
    startgame_scene->addItem(startgame_background);


    //button
    startgame_button = new QPushButton();
    startgame_button->move(100,400);
    startgame_button->setFixedSize(320,70);
    startgame_button->setIcon(QIcon(":/resource/startgame_button.png"));
    startgame_button->setIconSize(QSize(320,70));
    startgame_button->setStyleSheet(btnStyle);
    startgame_button->setAttribute(Qt::WA_TranslucentBackground);

    startgame_scene->addWidget(startgame_button);
    //前往主界面
    connect(startgame_button, &QPushButton::clicked,this,[=](){
        view->setScene(menu_scene);
    });


}

void Widget::load_menu()
{
    menu_scene = new QGraphicsScene();
    menu_background = new QGraphicsPixmapItem();
    {
        QPixmap original(MENU_BACKGROUND);
        QPixmap filtered = BlenderStyleFilter::applyCompositeStyle(original, 28, 1.38, 1.40, 8, QColor(126, 90, 255, 36));
        menu_background->setPixmap(filtered);
    }
    menu_scene->addItem(menu_background);

    //button
    menu_pvp_button = new QPushButton();
    menu_pve_button = new QPushButton();
    menu_coop_button = new QPushButton();
    menu_end_button = new QPushButton();
    menu_tip_button = new QPushButton();
    menu_exit_button = new QPushButton();
    menu_top_button = new QPushButton();

    menu_pvp_button->move(85,350);
    menu_pvp_button->setFixedSize(84,29);
    menu_pvp_button->setIcon(QIcon(":/resource/PVP.png"));
    menu_pvp_button->setIconSize(QSize(84,29));
    menu_pvp_button->setStyleSheet(btnStyle);
    menu_pvp_button->setAttribute(Qt::WA_TranslucentBackground);//开启透明属性

    menu_pve_button->move(340,350);
    menu_pve_button->setFixedSize(86,29);
    menu_pve_button->setIcon(QIcon(":/resource/PVE.png"));
    menu_pve_button->setIconSize(QSize(86,29));
    menu_pve_button->setStyleSheet(btnStyle);
    menu_pve_button->setAttribute(Qt::WA_TranslucentBackground);

    menu_coop_button->move(85,450);
    menu_coop_button->setFixedSize(104,29);
    menu_coop_button->setIcon(QIcon(":/resource/COOP.png"));
    menu_coop_button->setIconSize(QSize(104,29));
    menu_coop_button->setStyleSheet(btnStyle);
    menu_coop_button->setAttribute(Qt::WA_TranslucentBackground);

    menu_end_button->move(340,450);
    menu_end_button->setFixedSize(168,27);
    menu_end_button->setIcon(QIcon(":/resource/END.png"));
    menu_end_button->setIconSize(QSize(168,27));
    menu_end_button->setStyleSheet(btnStyle);
    menu_end_button->setAttribute(Qt::WA_TranslucentBackground);

    menu_tip_button->move(85,550);
    menu_tip_button->setFixedSize(82,28);
    menu_tip_button->setIcon(QIcon(":/resource/TIPS.png"));
    menu_tip_button->setIconSize(QSize(82,28));
    menu_tip_button->setStyleSheet(btnStyle);
    menu_tip_button->setAttribute(Qt::WA_TranslucentBackground);

    menu_exit_button->move(85,650);
    menu_exit_button->setFixedSize(78,29);
    menu_exit_button->setIcon(QIcon(":/resource/EXIT.png"));
    menu_exit_button->setIconSize(QSize(78,29));
    menu_exit_button->setStyleSheet(btnStyle);
    menu_exit_button->setAttribute(Qt::WA_TranslucentBackground);

    menu_top_button->move(85,750);
    menu_top_button->setFixedSize(194,27);
    menu_top_button->setIcon(QIcon(":/resource/TOPSCORE.png"));
    menu_top_button->setIconSize(QSize(194,27));
    menu_top_button->setStyleSheet(btnStyle);
    menu_top_button->setAttribute(Qt::WA_TranslucentBackground);

    menu_scene->addWidget(menu_pvp_button);
    menu_scene->addWidget(menu_pve_button);
    menu_scene->addWidget(menu_coop_button);
    menu_scene->addWidget(menu_end_button);
    menu_scene->addWidget(menu_tip_button);
    menu_scene->addWidget(menu_exit_button);
    menu_scene->addWidget(menu_top_button);


    //主界面按钮功能实现

    connect(menu_exit_button, &QPushButton::clicked,this,[=](){
        QApplication::quit();
    });

    //前往tip
    connect(menu_tip_button, &QPushButton::clicked,this,[=](){
        view->setScene(tip_scene);
    });

    //前往top
    connect(menu_top_button, &QPushButton::clicked,this,[=](){
        view->setScene(topscore_scene);
    });

    //前往endless
    connect(menu_end_button, &QPushButton::clicked,this,[=](){
        turn_to_endless();
    });

    //前往coop
    connect(menu_coop_button, &QPushButton::clicked,this,[=](){
        turn_to_coop();
    });
    //前往pvp
    connect(menu_pvp_button, &QPushButton::clicked,this,[=](){
        turn_to_pvp();
    });
    //前往选关
    connect(menu_pve_button, &QPushButton::clicked,this,[=](){
        view->setScene(clevel_scene);
    });
}

void Widget::load_tip()
{
    tip_scene = new QGraphicsScene();
    tip_background = new QGraphicsPixmapItem();
    tip_background->setPixmap(QPixmap(TIP_BACKGROUND));
    tip_scene->addItem(tip_background);


    close_button = new QPushButton();
    close_button->move(495,4);
    close_button->setFixedSize(33,28);
    close_button->setIcon(QIcon(":/resource/close_button.png"));
    close_button->setIconSize(QSize(33,28));
    close_button->setStyleSheet(btnStyle);
    close_button->setAttribute(Qt::WA_TranslucentBackground);//开启透明属性

    tip_scene->addWidget(close_button);

    //回到主界面
    connect(close_button, &QPushButton::clicked,this,[=](){//按钮返回
        view->setScene(menu_scene);
    });
}

void Widget::load_topscore()
{
    topscore_scene = new QGraphicsScene();
    topscore_background = new QGraphicsPixmapItem();
    topscore_background->setPixmap(QPixmap(TOP_BACKGROUND));
    topscore_scene->addItem(topscore_background);


    close_button = new QPushButton();
    close_button->move(495,4);
    close_button->setFixedSize(33,28);
    close_button->setIcon(QIcon(":/resource/close_button.png"));
    close_button->setIconSize(QSize(33,28));
    close_button->setStyleSheet(btnStyle);
    close_button->setAttribute(Qt::WA_TranslucentBackground);//开启透明属性

    topscore_scene->addWidget(close_button);

    //回到主界面
    connect(close_button, &QPushButton::clicked,this,[=](){//按钮返回
        view->setScene(menu_scene);
    });





    high_score_text = new QLineEdit();
    high_score_text->setReadOnly(true);
    high_score_text->setFixedSize(200, 50);
    high_score_text->move(150, 170); // 调整位置
    high_score_text->setStyleSheet(htStyly);
    topscore_scene->addWidget(high_score_text);
    high_score_text->setVisible(false); // 初始隐藏
    connect(menu_top_button, &QPushButton::clicked, this, [=](){
        int highScore = load_score();
        high_score_text->setText(QString(" %1").arg(highScore));
        high_score_text->setVisible(true);
    });
}

void Widget::load_coop()
{
    coop_scene = new QGraphicsScene();
    level1_background1 = new QGraphicsPixmapItem();
    level1_background1->setPixmap(QPixmap(LEVEL1_BACKGROUND));
    level1_background2 = new QGraphicsPixmapItem();
    level1_background2->setPixmap(QPixmap(LEVEL1_BACKGROUND));
    level1_background2->setPos(0,-1003);

    coop_scene->addItem(level1_background1);
    coop_scene->addItem(level1_background2);

    //生命条
    playerplane1_health_bar = new QProgressBar();
    playerplane1_health_bar->move(0, GAME_HEIGHT - 160);
    playerplane1_health_bar->setFixedSize(40, 160);
    playerplane1_health_bar->setValue(80);
    playerplane1_health_bar->setOrientation(Qt::Vertical);//设置生命条垂直
    playerplane1_health_bar->setTextVisible(false);
    playerplane1_health_bar->setStyleSheet(hbStyly);

    coop_scene->addWidget(playerplane1_health_bar);

    playerplane2_health_bar = new QProgressBar();
    playerplane2_health_bar->move(GAME_WIDTH - 40, GAME_HEIGHT - 160);
    playerplane2_health_bar->setFixedSize(40, 160);
    playerplane2_health_bar->setValue(80);
    playerplane2_health_bar->setOrientation(Qt::Vertical);//设置生命条垂直
    playerplane2_health_bar->setTextVisible(false);
    playerplane2_health_bar->setStyleSheet(hbStyly);

    coop_scene->addWidget(playerplane2_health_bar);



    playerplane1_health_text = new QLineEdit();
    playerplane1_health_text->setReadOnly(true);
    playerplane1_health_text->move(0, GAME_HEIGHT - 90);
    playerplane1_health_text->setText("111");
    playerplane1_health_text->setStyleSheet(htStyly);

    coop_scene->addWidget(playerplane1_health_text);

    playerplane2_health_text = new QLineEdit();
    playerplane2_health_text->setReadOnly(true);
    playerplane2_health_text->move(GAME_WIDTH - 40, GAME_HEIGHT - 90);
    playerplane2_health_text->setText("111");
    playerplane2_health_text->setStyleSheet(htStyly);

    coop_scene->addWidget(playerplane2_health_text);

    score1_text = new QLineEdit();
    score1_text->setText("玩家1：0");
    score1_text->setReadOnly(true);
    score1_text->move(0, 0);
    score1_text->setStyleSheet(htStyly);
    coop_scene->addWidget(score1_text);

    score2_text = new QLineEdit();
    score2_text->setText("玩家2：0");
    score2_text->setReadOnly(true);
    score2_text->move(GAME_WIDTH - 160, 0);
    score2_text->setStyleSheet(score1_text->styleSheet());
    coop_scene->addWidget(score2_text);


    playerplane1_bomb_text = new QLineEdit();
    playerplane1_bomb_text->setReadOnly(true);
    playerplane1_bomb_text->move(0, GAME_HEIGHT - 160 - 30);
    playerplane1_bomb_text->setText("💣x1");
    playerplane1_bomb_text->setStyleSheet(htStyly);
    coop_scene->addWidget(playerplane1_bomb_text);

    playerplane2_bomb_text = new QLineEdit();
    playerplane2_bomb_text->setReadOnly(true);
    playerplane2_bomb_text->move(GAME_WIDTH - 60, GAME_HEIGHT - 160 - 30);
    playerplane2_bomb_text->setText("💣x1");
    playerplane2_bomb_text->setStyleSheet(htStyly);
    coop_scene->addWidget(playerplane2_bomb_text);

    //炸弹
    bomb_picture = new QGraphicsPixmapItem();
    bomb_picture->setPixmap(QPixmap(BOMB_PICTURE));
    bomb_picture->setVisible(false);
    bomb_picture->setPos(100, 250);
    bomb_picture->setZValue(89);//暂停界面90
    coop_scene->addItem(bomb_picture);

    if (pause_picture) coop_scene->addItem(pause_picture);
    if (pause_background) coop_scene->addItem(pause_background);
    if (end_picture) coop_scene->addItem(end_picture);
}

void Widget::load_pvp()
{
    pvp_scene = new QGraphicsScene();

    level1_background1 = new QGraphicsPixmapItem();
    level1_background1->setPixmap(QPixmap(LEVEL1_BACKGROUND));
    level1_background2 = new QGraphicsPixmapItem();
    level1_background2->setPixmap(QPixmap(LEVEL1_BACKGROUND));
    level1_background2->setPos(0,-1003);

    pvp_scene->addItem(level1_background1);
    pvp_scene->addItem(level1_background2);


    playerplane1_health_bar = new QProgressBar();
    playerplane1_health_bar->move(0, GAME_HEIGHT - 160);
    playerplane1_health_bar->setFixedSize(40, 160);
    playerplane1_health_bar->setValue(80);
    playerplane1_health_bar->setOrientation(Qt::Vertical);
    playerplane1_health_bar->setTextVisible(false);
    playerplane1_health_bar->setStyleSheet(hbStyly);
    pvp_scene->addWidget(playerplane1_health_bar);

    playerplane2_health_bar = new QProgressBar();
    playerplane2_health_bar->move(GAME_WIDTH - 40, 0);
    playerplane2_health_bar->setFixedSize(40, 160);
    playerplane2_health_bar->setValue(80);
    playerplane2_health_bar->setOrientation(Qt::Vertical);
    playerplane2_health_bar->setTextVisible(false);
    playerplane2_health_bar->setStyleSheet(hbStyly);
    pvp_scene->addWidget(playerplane2_health_bar);

    // 血量文字
    playerplane1_health_text = new QLineEdit();
    playerplane1_health_text->setReadOnly(true);
    playerplane1_health_text->move(0, GAME_HEIGHT - 90);
    playerplane1_health_text->setText("111");
    playerplane1_health_text->setStyleSheet(htStyly);
    pvp_scene->addWidget(playerplane1_health_text);

    playerplane2_health_text = new QLineEdit();
    playerplane2_health_text->setReadOnly(true);
    playerplane2_health_text->move(GAME_WIDTH - 40, 90);
    playerplane2_health_text->setText("111");
    playerplane2_health_text->setStyleSheet(htStyly);
    pvp_scene->addWidget(playerplane2_health_text);


    // 炸弹动画 暂停 结束遮罩
    bomb_picture = new QGraphicsPixmapItem();
    bomb_picture->setPixmap(QPixmap(BOMB_PICTURE));
    bomb_picture->setVisible(false);
    bomb_picture->setPos(100, 250);
    bomb_picture->setZValue(89);
    pvp_scene->addItem(bomb_picture);

    if (pause_picture) pvp_scene->addItem(pause_picture);
    if (pause_background) pvp_scene->addItem(pause_background);
    if (end_picture) pvp_scene->addItem(end_picture);



}

void Widget::load_clevel()
{
    clevel_scene = new QGraphicsScene();
    clevel_background = new QGraphicsPixmapItem();
    clevel_background->setPixmap(QPixmap(CLEVEL_BACKGROUND));
    clevel_scene->addItem(clevel_background);

    close_button = new QPushButton();
    close_button->move(495,4);
    close_button->setFixedSize(33,28);
    close_button->setIcon(QIcon(":/resource/close_button.png"));
    close_button->setIconSize(QSize(33,28));
    close_button->setStyleSheet(btnStyle);
    close_button->setAttribute(Qt::WA_TranslucentBackground);//开启透明属性
    clevel_scene->addWidget(close_button);

    level1_button = new QPushButton();
    level2_button = new QPushButton();

    level1_button->move(130,350);
    level1_button->setFixedSize(290,119);
    level1_button->setIcon(QIcon(":/resource/level1_button.png"));
    level1_button->setIconSize(QSize(290,119));
    level1_button->setStyleSheet(btnStyle);
    level1_button->setAttribute(Qt::WA_TranslucentBackground);//开启透明属性

    level2_button->move(130,469);
    level2_button->setFixedSize(290,119);
    level2_button->setIcon(QIcon(":/resource/level2_button.png"));
    level2_button->setIconSize(QSize(290,119));
    level2_button->setStyleSheet(btnStyle);
    level2_button->setAttribute(Qt::WA_TranslucentBackground);
    clevel_scene->addWidget(level1_button);
    clevel_scene->addWidget(level2_button);

    //回到主界面
    connect(close_button, &QPushButton::clicked,this,[=](){//按钮返回
        view->setScene(menu_scene);
    });

    connect(level1_button, &QPushButton::clicked,this,[=](){
        turn_to_level1();
    });
    connect(level2_button, &QPushButton::clicked,this,[=](){
        turn_to_level2();
    });
}

void Widget::load_level1()
{
    level1_scene = new QGraphicsScene();
    level1_background1 = new QGraphicsPixmapItem();
    level1_background1->setPixmap(QPixmap(LEVEL1_BACKGROUND));
    level1_background2 = new QGraphicsPixmapItem();
    level1_background2->setPixmap(QPixmap(LEVEL1_BACKGROUND));
    level1_background2->setPos(0,-1003);

    level1_scene->addItem(pause_background);
    level1_scene->addItem(pause_picture);
    level1_scene->addItem(end_picture);
    level1_scene->addItem(victory_picture);
    if (playerplane2_health_bar) {
        playerplane2_health_bar->setVisible(false);
    }
    if (playerplane2_health_text) {
        playerplane2_health_text->setVisible(false);
    }
    playerplane2 = nullptr;

    level1_scene->addItem(level1_background1);
    level1_scene->addItem(level1_background2);

    //生命条
    playerplane1_health_bar = new QProgressBar();
    playerplane1_health_bar->move(0, GAME_HEIGHT - 160);
    playerplane1_health_bar->setFixedSize(40, 160);
    playerplane1_health_bar->setValue(80);
    playerplane1_health_bar->setOrientation(Qt::Vertical);//设置生命条垂直
    playerplane1_health_bar->setTextVisible(false);
    playerplane1_health_bar->setStyleSheet(hbStyly);

    level1_scene->addWidget(playerplane1_health_bar);



    playerplane1_health_text = new QLineEdit();
    playerplane1_health_text->setReadOnly(true);
    playerplane1_health_text->move(0, GAME_HEIGHT - 90);
    playerplane1_health_text->setText("111");
    playerplane1_health_text->setStyleSheet(htStyly);
    level1_scene->addWidget(playerplane1_health_text);


    score_text = new QLineEdit();
    score_text->setText("得分：0");
    score_text->setReadOnly(true);
    score_text->move(GAME_WIDTH - 160, 0);
    score_text->setStyleSheet(htStyly);
    level1_scene->addWidget(score_text);


    playerplane1_bomb_text = new QLineEdit();
    playerplane1_bomb_text->setReadOnly(true);
    playerplane1_bomb_text->move(0, GAME_HEIGHT - 160 - 30);
    playerplane1_bomb_text->setText("💣x1");
    playerplane1_bomb_text->setStyleSheet(htStyly);
    level1_scene->addWidget(playerplane1_bomb_text);

    //炸弹
    bomb_picture = new QGraphicsPixmapItem();
    bomb_picture->setPixmap(QPixmap(BOMB_PICTURE));
    bomb_picture->setVisible(false);
    bomb_picture->setPos(100, 250);
    bomb_picture->setZValue(89);//暂停界面90
    level1_scene->addItem(bomb_picture);
}

void Widget::load_level2()
{
    level2_scene = new QGraphicsScene();
    level2_background1 = new QGraphicsPixmapItem();
    level2_background1->setPixmap(QPixmap(LEVEL2_BACKGROUND));
    level2_background2 = new QGraphicsPixmapItem();
    level2_background2->setPixmap(QPixmap(LEVEL2_BACKGROUND));
    level2_background2->setPos(0,-1003);

    level2_scene->addItem(pause_background);
    level2_scene->addItem(pause_picture);
    level2_scene->addItem(end_picture);
    level2_scene->addItem(victory_picture);
    if (playerplane2_health_bar) {
        playerplane2_health_bar->setVisible(false);
    }
    if (playerplane2_health_text) {
        playerplane2_health_text->setVisible(false);
    }
    playerplane2 = nullptr;

    level2_scene->addItem(level2_background1);
    level2_scene->addItem(level2_background2);

    //生命条
    playerplane1_health_bar = new QProgressBar();
    playerplane1_health_bar->move(0, GAME_HEIGHT - 160);
    playerplane1_health_bar->setFixedSize(40, 160);
    playerplane1_health_bar->setValue(80);
    playerplane1_health_bar->setOrientation(Qt::Vertical);//设置生命条垂直
    playerplane1_health_bar->setTextVisible(false);
    playerplane1_health_bar->setStyleSheet(hbStyly);

    level2_scene->addWidget(playerplane1_health_bar);



    playerplane1_health_text = new QLineEdit();
    playerplane1_health_text->setReadOnly(true);
    playerplane1_health_text->move(0, GAME_HEIGHT - 90);
    playerplane1_health_text->setText("111");
    playerplane1_health_text->setStyleSheet(htStyly);
    level2_scene->addWidget(playerplane1_health_text);


    score_text = new QLineEdit();
    score_text->setText("得分：0");
    score_text->setReadOnly(true);
    score_text->move(GAME_WIDTH - 160, 0);
    score_text->setStyleSheet(htStyly);
    level2_scene->addWidget(score_text);


    playerplane1_bomb_text = new QLineEdit();
    playerplane1_bomb_text->setReadOnly(true);
    playerplane1_bomb_text->move(0, GAME_HEIGHT - 160 - 30);
    playerplane1_bomb_text->setText("💣x1");
    playerplane1_bomb_text->setStyleSheet(htStyly);
    level2_scene->addWidget(playerplane1_bomb_text);

    //炸弹
    bomb_picture = new QGraphicsPixmapItem();
    bomb_picture->setPixmap(QPixmap(BOMB_PICTURE));
    bomb_picture->setVisible(false);
    bomb_picture->setPos(100, 250);
    bomb_picture->setZValue(89);//暂停界面90
    level2_scene->addItem(bomb_picture);
}

void Widget::load_endless()
{
    endless_scene = new QGraphicsScene();
    level1_background1 = new QGraphicsPixmapItem();
    level1_background1->setPixmap(QPixmap(LEVEL1_BACKGROUND));
    level1_background2 = new QGraphicsPixmapItem();
    level1_background2->setPixmap(QPixmap(LEVEL1_BACKGROUND));
    level1_background2->setPos(0,-1003);

    endless_scene->addItem(pause_background);
    endless_scene->addItem(pause_picture);
    endless_scene->addItem(end_picture);
    if (playerplane2_health_bar) {
        playerplane2_health_bar->setVisible(false);
    }
    if (playerplane2_health_text) {
        playerplane2_health_text->setVisible(false);
    }
    playerplane2 = nullptr;

    endless_scene->addItem(level1_background1);
    endless_scene->addItem(level1_background2);

    //生命条
    playerplane1_health_bar = new QProgressBar();
    playerplane1_health_bar->move(0, GAME_HEIGHT - 160);
    playerplane1_health_bar->setFixedSize(40, 160);
    playerplane1_health_bar->setValue(80);
    playerplane1_health_bar->setOrientation(Qt::Vertical);//设置生命条垂直
    playerplane1_health_bar->setTextVisible(false);
    playerplane1_health_bar->setStyleSheet(hbStyly);

    endless_scene->addWidget(playerplane1_health_bar);



    playerplane1_health_text = new QLineEdit();
    playerplane1_health_text->setReadOnly(true);
    playerplane1_health_text->move(0, GAME_HEIGHT - 90);
    playerplane1_health_text->setText("111");
    playerplane1_health_text->setStyleSheet(htStyly);

    endless_scene->addWidget(playerplane1_health_text);
    score_text = new QLineEdit();
    score_text->setText("得分：0");
    score_text->setReadOnly(true);
    score_text->move(GAME_WIDTH - 160, 0);
    score_text->setStyleSheet(htStyly);
    endless_scene->addWidget(score_text);


    playerplane1_bomb_text = new QLineEdit();
    playerplane1_bomb_text->setReadOnly(true);
    playerplane1_bomb_text->move(0, GAME_HEIGHT - 160 - 30);
    playerplane1_bomb_text->setText("💣x1");
    playerplane1_bomb_text->setStyleSheet(htStyly);
    endless_scene->addWidget(playerplane1_bomb_text);

    //炸弹
    bomb_picture = new QGraphicsPixmapItem();
    bomb_picture->setPixmap(QPixmap(BOMB_PICTURE));
    bomb_picture->setVisible(false);
    bomb_picture->setPos(100, 250);
    bomb_picture->setZValue(89);//暂停界面90
    endless_scene->addItem(bomb_picture);

}

void Widget::load_timer()
{
    game_timer = new QTimer(this);
    game_timer->setInterval(GAME_PERIOD);



}

void Widget::load_pause()
{
    pause_picture = new QGraphicsPixmapItem();
    pause_picture->setPixmap(QPixmap(PAUSE_PICTURE));
    pause_picture->setPos(GAME_WIDTH / 2 - pause_picture->pixmap().width() / 2, GAME_HEIGHT / 2 - pause_picture->pixmap().height() / 2);
    pause_picture->setZValue(91); //层级设置比pause_background要高
    pause_picture->setVisible(false);
    pause_background = new QGraphicsRectItem();
    pause_background->setRect(0, 0, GAME_WIDTH, GAME_HEIGHT);
    pause_background->setBrush(QColor(0, 0, 0, 128)); // 黑色半透明（alpha=128，0-255）
    pause_background->setZValue(90); // 层级设为次顶层
    pause_background->setVisible(false); // 默认隐藏
}

void Widget::load_end()
{
    end_picture = new QGraphicsPixmapItem();
    end_picture->setPixmap(QPixmap(END_PICTURE));
    end_picture->setPos(GAME_WIDTH / 2 - end_picture->pixmap().width() / 2, GAME_HEIGHT / 2 - end_picture->pixmap().height() / 2);
    end_picture->setZValue(91); //层级设置比pause_background要高
    end_picture->setVisible(false);

    //胜利界面，用的gameover，之后再改吧
    victory_picture = new QGraphicsPixmapItem();
    victory_picture->setPixmap(QPixmap(VICTORY_PICTURE));
    victory_picture->setPos(GAME_WIDTH / 2 - victory_picture->pixmap().width() / 2, GAME_HEIGHT / 2 - victory_picture->pixmap().height() / 2);
    victory_picture->setZValue(91);
    victory_picture->setVisible(false);
}

void Widget::load_pool(QGraphicsScene* scene)
{
    if (!scene) return;

    if (!playerbullet_pool){
        playerbullet_pool = new PlayerBulletPool(scene,10);
    }
    else {
        playerbullet_pool->level_scene = scene;
        for (PlayerBullet* b : *(playerbullet_pool->playerbullet_pool_list)){
            scene->addItem(b);
        }
    }

    if (!enemyplane_pool){
        enemyplane_pool = new EnemyPlanePool(scene,10);
    }
    else {
        enemyplane_pool->level_scene = scene;
        for (EnemyPlane* e : *(enemyplane_pool->enemyplane_pool_list)){
            scene->addItem(e);
        }
    }

    if (!enemybullet_pool){
        enemybullet_pool = new EnemyBulletPool(scene,10);
    }
    else {
        enemybullet_pool->level_scene = scene;
        for (EnemyBullet* b : *(enemybullet_pool->enemybullet_pool_list)){
            scene->addItem(b);
        }
    }

    if (!powerup_pool){
        powerup_pool = new PowerUpPool(scene, 5);
    }
    else {
        powerup_pool->level_scene = scene;
        for (PowerUp* p : *(powerup_pool->powerup_pool_list)){
            scene->addItem(p);
        }
    }
}

void Widget::load_playerplane1(int kind,int x,QGraphicsScene* scene)
{
    playerplane1 = new PlayerPlane();
    playerplane1->init(kind);
    scene->addItem(playerplane1);
    playerplane1->setPos(x,800);
}

void Widget::load_playerplane2(int kind,int x,QGraphicsScene* scene)
{
    playerplane2 = new PlayerPlane();
    playerplane2->init(kind);
    playerplane2->setPos(x,800);
    scene->addItem(playerplane2);

}

void Widget::endless_update()
{
    //背景移动，通过一张二方连续的地图，复制两张，两张一次向下移动，当移动到特定y时，这张图片移到上方
    level1_background1->moveBy(0,.5);
    level1_background2->moveBy(0,.5);
    if(level1_background1->pos().y() >= 1003)
        level1_background1->setPos(0, 0);
    if(level1_background2->pos().y() >= 0)
        level1_background2->setPos(0, -1003);

    //敌人生成
    static int count = 0;
    if(count == ( 150 )){//about 不知跳 个敌人/s
        EnemyPlane* enemyplane =enemyplane_pool->get_new_enemyplane();
        enemyplane->init(rand() % 4 + 1);
        double x = rand() % (GAME_WIDTH - enemyplane->pixmap().width());//避免生成在边界导致看不见
        enemyplane->setPos(x,-100);
        count = 0;
    }

    count++;

    general_update();
}

void Widget::coop_update()
{
    //背景移动，通过一张二方连续的地图，复制两张，两张一次向下移动，当移动到特定y时，这张图片移到上方
    level1_background1->moveBy(0,.5);
    level1_background2->moveBy(0,.5);
    if(level1_background1->pos().y() >= 1003)
        level1_background1->setPos(0, 0);
    if(level1_background2->pos().y() >= 0)
        level1_background2->setPos(0, -1003);

    //敌人生成
    static int count = 0;
    if(count == ( 130 )){//about0.5个敌人/s
        EnemyPlane* enemyplane =enemyplane_pool->get_new_enemyplane();
        enemyplane->init(rand() % 4 + 1);
        double x = rand() % (GAME_WIDTH - enemyplane->pixmap().width());//避免生成在边界导致看不见
        enemyplane->setPos(x,-100);
        count = 0;
    }

    count++;

    general_update();
}

void Widget::level1_update()
{
    //背景移动，通过一张二方连续的地图，复制两张，两张一次向下移动，当移动到特定y时，这张图片移到上方
    level1_background1->moveBy(0,.5);
    level1_background2->moveBy(0,.5);
    if(level1_background1->pos().y() >= 1003)
        level1_background1->setPos(0, 0);
    if(level1_background2->pos().y() >= 0)
        level1_background2->setPos(0, -1003);

    if (level_victory) {
        general_update();
        return;
    }

    if (!level_boss_spawned) {
        static int count = 0;
        if(count == ( 200 )){//about0.5个敌人/s
            EnemyPlane* enemyplane =enemyplane_pool->get_new_enemyplane();
            enemyplane->init(rand() % 4 + 1);
            double x = rand() % (GAME_WIDTH - enemyplane->pixmap().width());//避免生成在边界导致看不见
            enemyplane->setPos(x,-100);
            count = 0;
        }
        count++;
    }

    // 检查是否达到击杀目标，生成boss
    if (!level_boss_spawned && level_kill_count >= LEVEL1_KILL_TARGET) {
        level_boss_spawned = true;
        level_boss = enemyplane_pool->get_new_enemyplane();
        level_boss->init_boss(1);
        level_boss->setPos(GAME_WIDTH / 2 - level_boss->pixmap().width() / 2, -150);
    }

    general_update();
}

void Widget::level2_update()
{
    //背景移动，通过一张二方连续的地图，复制两张，两张一次向下移动，当移动到特定y时，这张图片移到上方
    level2_background1->moveBy(0,.5);
    level2_background2->moveBy(0,.5);
    if(level2_background1->pos().y() >= 1003)
        level2_background1->setPos(0, 0);
    if(level2_background2->pos().y() >= 0)
        level2_background2->setPos(0, -1003);

    if (level_victory) {
        general_update();
        return;
    }

    if (!level_boss_spawned) {
        // 还没出boss，生成普通敌人
        static int count = 0;
        if(count == ( 200 )){//about0.5个敌人/s
            EnemyPlane* enemyplane =enemyplane_pool->get_new_enemyplane();
            enemyplane->init(rand() % 4 + 1);
            double x = rand() % (GAME_WIDTH - enemyplane->pixmap().width());//避免生成在边界导致看不见
            enemyplane->setPos(x,-100);
            count = 0;
        }
        count++;
    }

    // 检查是否达到击杀目标，生成boss
    if (!level_boss_spawned && level_kill_count >= LEVEL2_KILL_TARGET) {
        level_boss_spawned = true;
        level_boss = enemyplane_pool->get_new_enemyplane();
        level_boss->init_boss(2);
        level_boss->setPos(GAME_WIDTH / 2 - level_boss->pixmap().width() / 2, -300);
        // 传递玩家指针给boss2
        level_boss->player1 = playerplane1;
        level_boss->player2 = playerplane2;

    }

    general_update();

}

void Widget::pvp_update()
{
    // 背景
    level1_background1->moveBy(0,.5);
    level1_background2->moveBy(0,.5);
    if(level1_background1->pos().y()>=1003)
        level1_background1->setPos(0,0);
    if(level1_background2->pos().y()>=0)
        level1_background2->setPos(0,-1003);


    // 玩家2操控敌机
    if(player_enemy && player_enemy->status == 2)
    {
        // 手动控制移动
        player_enemy_move();
        // 按住0键持续发射子弹
        if(player_enemy_shoot_flag && !player_enemy->weapon->weapon_timer->isActive())
        {
            player_enemy->weapon_shoot(enemybullet_pool, view->scene(), player_enemy->plane_kind);
        }
        player_enemy->is_live();
    }

    general_update();
}

void Widget::general_update()
{
    QGraphicsScene* active_scene = view ? view->scene() : nullptr;

    if (playerplane1) {
        playerplane1_move();
        if (playerplane1->weapon1 && playerplane1->weapon1->is_continuously_shooting)
            playerplane1->weapon1_shoot(playerbullet_pool, active_scene);
        if (playerplane1->weapon2 && playerplane1->weapon2->is_continuously_shooting)
            playerplane1->weapon2_shoot(playerbullet_pool, active_scene);
        if (playerplane1->weapon3 && playerplane1->weapon3->is_continuously_shooting)
            playerplane1->weapon3_shoot(playerbullet_pool, active_scene);

        if (playerplane1_health_bar)
            playerplane1_health_bar->setValue(playerplane1->get_hp_rate());
        if (playerplane1_health_text)
            playerplane1_health_text->setText(QString::number(playerplane1->health, 'f', 0));
        if (playerplane1_bomb_text)
            playerplane1_bomb_text->setText(QString("💣x%1").arg(playerplane1->bomb_count));

        if (playerplane1->shield_timer && playerplane1->shield_timer->isActive())
            playerplane1->shield->setVisible(true);
        else
            playerplane1->shield->setVisible(false);
    }

    if (playerplane2) {
        playerplane2_move();
        if (playerplane2->weapon1 && playerplane2->weapon1->is_continuously_shooting)
            playerplane2->weapon1_shoot(playerbullet_pool, active_scene);
        if (playerplane2->weapon2 && playerplane2->weapon2->is_continuously_shooting)
            playerplane2->weapon2_shoot(playerbullet_pool, active_scene);
        if (playerplane2->weapon3 && playerplane2->weapon3->is_continuously_shooting)
            playerplane2->weapon3_shoot(playerbullet_pool, active_scene);

        if(active_scene == coop_scene)
        {
            if (playerplane2_health_bar)
                playerplane2_health_bar->setValue(playerplane2->get_hp_rate());
            if (playerplane2_health_text)
                playerplane2_health_text->setText(QString::number(playerplane2->health, 'f', 0));
            if (playerplane2_bomb_text)
                playerplane2_bomb_text->setText(QString("💣x%1").arg(playerplane2->bomb_count));
        }


        if (playerplane2->shield_timer && playerplane2->shield_timer->isActive())
            playerplane2->shield->setVisible(true);
        else
            playerplane2->shield->setVisible(false);
    }
    if(active_scene == pvp_scene && player_enemy)
    {
        if (playerplane2_health_bar)
            playerplane2_health_bar->setValue(player_enemy->get_hp_rate());
        if (playerplane2_health_text)
            playerplane2_health_text->setText(QString::number(player_enemy->health, 'f', 0));
    }



    // 玩家子弹移动
    if (playerbullet_pool) {
        for (PlayerBullet* playerbullet : *(playerbullet_pool->playerbullet_pool_list)){
            if (playerbullet->status == 2)
                playerbullet->move();
            else if (playerbullet->status == 0)
                playerbullet_pool->return_playerbullet(playerbullet);
        }
    }

    // 敌机移动，发射子弹
    if (enemyplane_pool) {
        if(active_scene != pvp_scene)
        {
            for (EnemyPlane* enemyplane : *(enemyplane_pool->enemyplane_pool_list)){
                if (enemyplane->status == 2){
                    // 判断是否为boss（plane_kind >= 10）
                    if (enemyplane->plane_kind >= 10) {
                        // boss使用演出系统
                        enemyplane->boss_perform(enemybullet_pool, active_scene);
                    } else {
                        // 普通敌机使用原有逻辑
                        enemyplane->move();
                        enemyplane->weapon_shoot(enemybullet_pool, active_scene ,enemyplane->plane_kind);
                    }
                    enemyplane->is_live();
                }
                else if (enemyplane->status == 0){

                    if(active_scene == coop_scene)
                    {
                        if(enemyplane->killer == 1)
                            score1 += enemyplane->score;
                        else if(enemyplane->killer == 2)
                            score2 += enemyplane->score;

                    }
                    else
                    {
                        score += enemyplane->score;
                        // 关卡模式：记录击杀数
                        if ((active_scene == level1_scene || active_scene == level2_scene) && !level_boss_spawned) {
                            level_kill_count++;
                        }
                    }
                    // 道具掉落（非PVP模式）
                    if (active_scene != pvp_scene && enemyplane->plane_kind < 10) {
                        int drop_roll = rand() % 100;
                        if (drop_roll < POWERUP_DROP_CHANCE) {
                            PowerUp* powerup = powerup_pool->get_new_powerup();
                            int pu_type = rand() % 3 + 1; // 1:火力 2:生命 3:炸弹
                            double ex = enemyplane->pos().x();
                            double ey = enemyplane->pos().y();
                            powerup->init(ex, ey, pu_type);
                        }
                    }
                    // 检查boss是否被击败
                    if (enemyplane == level_boss && (active_scene == level1_scene || active_scene == level2_scene)) {
                        level_boss = nullptr;
                        game_victory();
                    }
                    enemyplane_pool->return_enemyplane(enemyplane);
                }
            }
        }
    }

    // 敌机子弹移动
    if (enemybullet_pool) {
        for (EnemyBullet* enemybullet : *(enemybullet_pool->enemybullet_pool_list)){
            if (enemybullet->status == 2)
                enemybullet->move(playerplane1,playerplane2,enemybullet->kind,enemybullet->bullet4_kind);
            else if (enemybullet->status == 0)
                enemybullet_pool->return_enemybullet(enemybullet);
        }
    }

    // 道具移动
    if (powerup_pool) {
        for (PowerUp* powerup : *(powerup_pool->powerup_pool_list)){
            if (powerup->status == 2) {
                powerup->move();
                powerup->is_live();
            }
            else if (powerup->status == 0) {
                powerup_pool->return_powerup(powerup);
            }
        }
    }

    collision_detection();

    // 判定死亡
    bool game_over = false;
    if (playerplane1 && playerplane1->health <= 0)
    {
        // 玩家1阵亡：PVP则玩家2获胜
        if (active_scene == pvp_scene)
            pvp_win_flag = 2;
        game_over = true;
    }
    else if (active_scene == pvp_scene && player_enemy && player_enemy->health <= 0)
    {
        // PVP操控敌机阵亡：玩家1获胜
        pvp_win_flag = 1;
        game_over = true;
    }
    else if (playerplane2 && playerplane2->health <= 0)
    {
        game_over = true;
    }

    if (game_over){
        status = 0;
        if(active_scene == coop_scene)
        {
            score = qMax(score1, score2);
        }
        save_score();
        game_end();
        score = 0;
    }

    if(active_scene == coop_scene)
    {
        if(score1_text) score1_text->setText("玩家1：" + QString::number(score1));
        if(score2_text) score2_text->setText("玩家2：" + QString::number(score2));
    }
    else
    {
        if (score_text)
            score_text->setText("分数："+QString::number(score));
    }
}

void Widget::turn_to_menu()
{
    view->setScene(menu_scene);
}

void Widget::turn_to_coop()
{

    delete_level();
    if (coop_scene) {
        delete coop_scene;
        coop_scene = nullptr;
    }

    score1 = 0;
    score2 = 0;
    score = 0;
    load_coop();
    view->setScene(coop_scene);
    load_pool(coop_scene);
    //选择飞机
    load_playerplane1(1,100,coop_scene);
    load_playerplane2(2,400,coop_scene);

    status = 2;
    pause_background->setVisible(false);
    pause_picture->setVisible(false);
    end_picture->setVisible(false);

    disconnect(game_timer, &QTimer::timeout, this, nullptr);
    connect(game_timer, &QTimer::timeout, this, &Widget::coop_update, Qt::UniqueConnection);
    game_timer->start();
}

void Widget::turn_to_pvp()
{
    delete_level();
    if (pvp_scene) {
        delete pvp_scene;
        pvp_scene = nullptr;
    }

    score = 0;
    // 清空旧玩家2飞机指针
    playerplane2 = nullptr;
    playerplane2_health_bar = nullptr;
    playerplane2_health_text = nullptr;

    load_pvp();
    view->setScene(pvp_scene);
    load_pool(pvp_scene);

    // 玩家1
    load_playerplane1(1, 100, pvp_scene);

    // 玩家2控制敌人，我是个天才
    player_enemy = enemyplane_pool->get_new_enemyplane();
    player_enemy->init(5);
    player_enemy->setPos(400, 100);
    player_enemy->status = 2;
    player_enemy->isPlayerControl = true;
    status = 2;
    pause_background->setVisible(false);
    pause_picture->setVisible(false);
    end_picture->setVisible(false);

    disconnect(game_timer, &QTimer::timeout, this, nullptr);
    connect(game_timer, &QTimer::timeout, this, &Widget::pvp_update, Qt::UniqueConnection);
    game_timer->start();
}

void Widget::turn_to_level1()
{
    delete_level();
    if (level1_scene) {
        delete level1_scene;
        level1_scene = nullptr;
    }

    score = 0;
    load_level1();
    view->setScene(level1_scene);
    load_pool(level1_scene);
    //选择飞机
    load_playerplane1(1,240,level1_scene);//单人模式放在正中间

    status = 2;
    pause_background->setVisible(false);
    pause_picture->setVisible(false);
    end_picture->setVisible(false);
    victory_picture->setVisible(false);

    disconnect(game_timer, &QTimer::timeout, this, nullptr);
    connect(game_timer, &QTimer::timeout, this, &Widget::level1_update, Qt::UniqueConnection);
    game_timer->start();
}

void Widget::turn_to_level2()
{
    delete_level();
    if (level2_scene) {
        delete level2_scene;
        level2_scene = nullptr;
    }

    score = 0;
    load_level2();
    view->setScene(level2_scene);
    load_pool(level2_scene);
    //选择飞机
    load_playerplane1(1,240,level2_scene);//单人模式放在正中间

    status = 2;
    pause_background->setVisible(false);
    pause_picture->setVisible(false);
    end_picture->setVisible(false);
    victory_picture->setVisible(false);

    disconnect(game_timer, &QTimer::timeout, this, nullptr);
    connect(game_timer, &QTimer::timeout, this, &Widget::level2_update, Qt::UniqueConnection);
    game_timer->start();
}

void Widget::turn_to_endless()
{
    delete_level();
    if (endless_scene) {
        delete endless_scene;
        endless_scene = nullptr;
    }

    score = 0;
    load_endless();
    view->setScene(endless_scene);

    load_pool(endless_scene);
    //选择飞机
    load_playerplane1(1,240,endless_scene);//单人模式放在正中间

    status = 2;
    pause_background->setVisible(false);
    pause_picture->setVisible(false);
    end_picture->setVisible(false);

    disconnect(game_timer, &QTimer::timeout, this, nullptr);
    connect(game_timer, &QTimer::timeout, this, &Widget::endless_update, Qt::UniqueConnection);
    game_timer->start();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    QGraphicsScene* active_scene = view ? view->scene() : nullptr;
    int k = event->key();
    switch(k){//优化飞机移动函数，实现斜飞，解决卡顿
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_A:
    case Qt::Key_D:
        if(!move_list_WASD.contains(k))move_list_WASD.append(k);
        break;
    case Qt::Key_J:
        if(playerplane1 && playerplane1->weapon1)
            playerplane1->weapon1->is_continuously_shooting = true;
        break;
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        if(!move_list_ARROW.contains(k))move_list_ARROW.append(k);
        break;
    case Qt::Key_0:
        if(view->scene() == pvp_scene)
            {
                player_enemy_shoot_flag = true;
            }
            else if(playerplane2 && playerplane2->weapon1)
            {
                playerplane2->weapon1->is_continuously_shooting = true;
            }
        break;
    case Qt::Key_P:
        game_pause();
        break;
    case Qt::Key_R:
        if(status == 0 || status == 1){
            //结束游戏，需要销毁对象！！！！
            save_score();
            delete_level();
            turn_to_menu();
        }
        break;
    case Qt::Key_Space:
        if (playerplane1 && playerplane1->status == 2 && active_scene != pvp_scene) {
            playerplane_release_bomb(playerplane1);
        }
        break;
    case Qt::Key_1:
        if (playerplane2 && playerplane2->status == 2 && playerplane2->bomb_count > 0) {
            playerplane_release_bomb(playerplane2);
        }
        break;
    }
}
void Widget::playerplane_release_bomb(PlayerPlane* playerplane)
{
    if (!playerplane || playerplane->bomb_count <= 0 || status != 2) {
        return;
    }

    playerplane->bomb_count--;


    bomb_damage();

    // 更新炸弹数量显示//暂定//好了，以及有了



    //播放炸弹动画
    double midX = GAME_WIDTH / 2 - bomb_picture->pixmap().width() / 2;
    double midY = GAME_HEIGHT / 2 - bomb_picture->pixmap().height() / 2;
    bomb_picture->setPos(midX, midY);
    bomb_picture->setVisible(true);
    QTimer* bomb_timer = new QTimer(this);
    bomb_timer->setSingleShot(true);
    connect(bomb_timer, &QTimer::timeout, this, [=](){
        bomb_picture->setVisible(false);
        bomb_timer->deleteLater();
    });
    bomb_timer->start(1000);
}
void Widget::bomb_damage()
{
    if (enemyplane_pool){
        for (EnemyPlane* enemyplane : *(enemyplane_pool->enemyplane_pool_list)){
            if (enemyplane->status == 2){
                enemyplane->health -= 70;
            }
        }
    }

    //清除所有敌机子弹
    if (enemybullet_pool){
        for (EnemyBullet* enemybullet : *(enemybullet_pool->enemybullet_pool_list)){
            if (enemybullet->status == 2){
                enemybullet->destroy();
            }
        }
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    int k = event->key();
    switch(k){
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_A:
    case Qt::Key_D:
        move_list_WASD.removeOne(k);
        break;
    case Qt::Key_J:
        if (playerplane1 && playerplane1->weapon1)
            playerplane1->weapon1->is_continuously_shooting = false;
        break;


    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        move_list_ARROW.removeOne(k);
        break;
    case Qt::Key_0:
        if(view->scene() == pvp_scene)
        {
            player_enemy_shoot_flag = false;
        }
        else if(playerplane2 && playerplane2->weapon1){
            playerplane2->weapon1->is_continuously_shooting = false;
        }
    break;
    }

}

void Widget::playerplane1_move()
{
    if(!playerplane1)return;
    double x = playerplane1->pos().x(), y = playerplane1->pos().y();
    double dx = 0 , dy = 0 , speed = playerplane1->speed;
    int key_count = 0;
    for(int key : move_list_WASD){
        switch(key){
        case Qt::Key_W:
            dy += -speed;
            break;
        case Qt::Key_S:
            dy += .4 * speed;
            break;
        case Qt::Key_A:
            dx += -.6 * speed;
            break;
        case Qt::Key_D:
            dx += .6 * speed;
            break;
        }
        key_count++;
    }
    if(key_count == 2){
        dx *= 0.514;//实现斜动并且平衡速度
        dy *= 0.857;
    }
    //防止超出边界
    double new_x = x + dx;
    double new_y = y + dy;
    if (new_x < 0) new_x = 0;
    if (new_x > GAME_WIDTH - playerplane1->pixmap().width()) new_x = GAME_WIDTH - playerplane1->pixmap().width();
    if (new_y < 0) new_y = 0;
    if (new_y > GAME_HEIGHT - playerplane1->pixmap().height()) new_y = GAME_HEIGHT - playerplane1->pixmap().height();
    playerplane1->setPos(new_x, new_y);
}

void Widget::playerplane2_move()
{
    if(!playerplane2)return;
    double x = playerplane2->pos().x(), y = playerplane2->pos().y();
    double dx = 0 , dy = 0 , speed = playerplane2->speed;
    int key_count = 0;
    for(int key : move_list_ARROW){
        switch(key){
        case Qt::Key_Up:
            dy += -speed;
            break;
        case Qt::Key_Down:
            dy += .4*speed;
            break;
        case Qt::Key_Left:
            dx += -.6 * speed;
            break;
        case Qt::Key_Right:
            dx += .6 * speed;
            break;
        }
        key_count++;
    }
    if(key_count == 2){
        dx *= 0.514;//实现斜动并且平衡速度
        dy *= 0.857;
    }
    //防止超出边界
    double new_x = x + dx;
    double new_y = y + dy;
    if (new_x < 0) new_x = 0;
    if (new_x > GAME_WIDTH - playerplane2->pixmap().width()) new_x = GAME_WIDTH - playerplane2->pixmap().width();
    if (new_y < 0) new_y = 0;
    if (new_y > GAME_HEIGHT - playerplane2->pixmap().height()) new_y = GAME_HEIGHT - playerplane2->pixmap().height();
    playerplane2->setPos(new_x, new_y);
}

void Widget::player_enemy_move()
{
    if(!player_enemy)return;
    double x = player_enemy->pos().x(), y = player_enemy->pos().y();
    double dx = 0 , dy = 0 , speed = player_enemy->speed;
    int key_count = 0;
    for(int key : move_list_ARROW){
        switch(key){
        case Qt::Key_Up:
            dy += -.4 * speed;
            break;
        case Qt::Key_Down:
            dy += speed;
            break;
        case Qt::Key_Left:
            dx += -.6 * speed;
            break;
        case Qt::Key_Right:
            dx += .6 * speed;
            break;
        }
        key_count++;
    }
    if(key_count == 2){
        dx *= 0.514;
        dy *= 0.857;
    }
    // 敌机边界限制
    double new_x = x + dx;
    double new_y = y + dy;
    if (new_x < 0) new_x = 0;
    if (new_x > GAME_WIDTH - player_enemy->pixmap().width()) new_x = GAME_WIDTH - player_enemy->pixmap().width();
    if (new_y < 120) new_y = 120;
    if (new_y > GAME_HEIGHT) new_y = GAME_HEIGHT;
    player_enemy->setPos(new_x, new_y);
}

void Widget::collision_detection()//由于1.大量对象在运动，2.对象数量不多，最多可能出现100个，3四叉树对内存需求大
{                                 //在我们的游戏场景里，四叉树空间碰撞检测，可能不如暴力检测，因此采用暴力检测
    collision_detection_playerbullet_with_enemyplane();
    collision_detection_enemybullet_with_playerplane();
    collision_detection_playerplane_with_enemyplane();
    collision_detection_playerplane_with_powerup();
}

void Widget::collision_detection_playerbullet_with_enemyplane()
{
    if (!playerbullet_pool || !enemyplane_pool) return;
    for (PlayerBullet* playerbullet : *(playerbullet_pool->playerbullet_pool_list)){
        if (playerbullet->status == 2){
            for (EnemyPlane* enemyplane : *(enemyplane_pool->enemyplane_pool_list)){
                if (enemyplane->status == 2){
                    if (playerbullet->collidesWithItem(enemyplane)){
                        enemyplane->killer = playerbullet->owner;
                        enemyplane->collide_with_playerbullet(playerbullet);
                        playerbullet->collide_with_enemyplane(enemyplane);
                    }
                }
            }
        }
    }
}

void Widget::collision_detection_enemybullet_with_playerplane()
{
    if (!enemybullet_pool) return;
    for (EnemyBullet* enemybullet : *(enemybullet_pool->enemybullet_pool_list)){
        if (enemybullet->status == 2){
            if (playerplane1 && playerplane1->status == 2){
                if (playerplane1->collidesWithItem(enemybullet)){
                    playerplane1->collide_with_enemybullet(enemybullet);
                    enemybullet->collide_with_playerplane();
                }
            }
            if (playerplane2 && playerplane2->status == 2){
                if (playerplane2->collidesWithItem(enemybullet)){
                    playerplane2->collide_with_enemybullet(enemybullet);
                    enemybullet->collide_with_playerplane();
                }
            }
        }
    }
}

void Widget::collision_detection_playerplane_with_powerup()
{
    if (!powerup_pool) return;
    for (PowerUp* powerup : *(powerup_pool->powerup_pool_list)){
        if (powerup->status == 2) {
            if (playerplane1 && playerplane1->status == 2) {
                if (playerplane1->collidesWithItem(powerup)) {
                    powerup->apply_effect(playerplane1);
                }
            }
            if (playerplane2 && playerplane2->status == 2) {
                if (playerplane2->collidesWithItem(powerup)) {
                    powerup->apply_effect(playerplane2);
                }
            }
        }
    }
}

void Widget::collision_detection_playerplane_with_enemyplane()
{
    if (!enemyplane_pool) return;
    for (EnemyPlane* enemyplane : *(enemyplane_pool->enemyplane_pool_list)){
        if (enemyplane->status == 2){
            if (playerplane1 && playerplane1->status == 2 && (!playerplane1->shield_timer || !playerplane1->shield_timer->isActive())){
                if (playerplane1->collidesWithItem(enemyplane)){
                    enemyplane->killer = 1;
                    playerplane1->collide_with_enemyplane(enemyplane);
                    enemyplane->collide_with_playerplane(playerplane1);
                }
            }
            if (playerplane2 && playerplane2->status == 2 && (!playerplane2->shield_timer || !playerplane2->shield_timer->isActive())){
                if (playerplane2->collidesWithItem(enemyplane)){
                    enemyplane->killer = 2;
                    playerplane2->collide_with_enemyplane(enemyplane);
                    enemyplane->collide_with_playerplane(playerplane2);
                }
            }
        }
    }

}


void Widget::game_pause()
{
    if (status == 2){
        status = 1;
        pause_background->setVisible(true);
        pause_picture->setVisible(true);
        game_timer->stop();
    }
    else if (status == 1){
        status = 2;
        pause_background->setVisible(false);
        pause_picture->setVisible(false);
        game_timer->start();
    }
}

void Widget::game_end()
{
    //显示游戏结束的界面
    pause_background->setVisible(true);
    game_timer->stop();
    end_picture->setVisible(true);
}

void Widget::game_victory()
{
    //显示胜利界面
    level_victory = true;
    status = 0;
    pause_background->setVisible(true);
    game_timer->stop();
    victory_picture->setVisible(true);
}

void Widget::save_score()
{
    QFile file("game_scores.txt");
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream in(&file);
        int highScore = 0;
        // 读取当前最高分
        if (!in.atEnd()) {
            in >> highScore;
        }
        // 如果当前分数高于最高分，则更新
        if (score > highScore) {
            highScore = score;
            // 回到文件开头，覆盖写入新的最高分
            file.seek(0);
            QTextStream out(&file);
            out << highScore;
        }
        file.close();
    }
}

int Widget::load_score()
{
    QFile file("game_scores.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        int highScore = 0;
        in >> highScore;
        file.close();
        return highScore;
    }
    // 如果文件不存在，返回0
    return 0;
}

void Widget::delete_level()
{
    //重置对象池中的对象
    score1 = 0;
    score2 = 0;
    score = 0;

    QGraphicsScene* current_scene = view ? view->scene() : nullptr;
    if (current_scene) {
        if (pause_background && pause_background->scene() == current_scene)
            current_scene->removeItem(pause_background);
        if (pause_picture && pause_picture->scene() == current_scene)
            current_scene->removeItem(pause_picture);
        if (end_picture && end_picture->scene() == current_scene)
            current_scene->removeItem(end_picture);
        if (victory_picture && victory_picture->scene() == current_scene)
            current_scene->removeItem(victory_picture);
    }

    if (enemyplane_pool){
        for (EnemyPlane* enemyplane : *(enemyplane_pool->enemyplane_pool_list)){
            enemyplane->destroy();
            if (enemyplane->scene()) {
                enemyplane->scene()->removeItem(enemyplane);
            }
            enemyplane_pool->return_enemyplane(enemyplane);
        }
    }
    if (enemybullet_pool){
        for (EnemyBullet* enemybullet : *(enemybullet_pool->enemybullet_pool_list)){
            enemybullet->destroy();
            if (enemybullet->scene()) {
                enemybullet->scene()->removeItem(enemybullet);
            }
            enemybullet_pool->return_enemybullet(enemybullet);
        }
    }
    if (playerbullet_pool){
        for (PlayerBullet* herobullet : *(playerbullet_pool->playerbullet_pool_list)){
            herobullet->destroy();
            if (herobullet->scene()) {
                herobullet->scene()->removeItem(herobullet);
            }
            playerbullet_pool->return_playerbullet(herobullet);
        }
    }
    if (powerup_pool){
        for (PowerUp* powerup : *(powerup_pool->powerup_pool_list)){
            powerup->destroy();
            if (powerup->scene()) {
                powerup->scene()->removeItem(powerup);
            }
            powerup_pool->return_powerup(powerup);
        }
    }

    //销毁玩家飞机
    if(player_enemy){
        player_enemy->isPlayerControl = false;
        if(player_enemy->scene())
                    player_enemy->scene()->removeItem(player_enemy);
        player_enemy->destroy();
        enemyplane_pool->return_enemyplane(player_enemy);
        player_enemy = nullptr;
    }
    if (playerplane1){
        if (playerplane1->scene())
            playerplane1->scene()->removeItem(playerplane1);
        delete playerplane1;
        playerplane1 = nullptr;
    }
    if (playerplane2){
        if (playerplane2->scene())
            playerplane2->scene()->removeItem(playerplane2);
        delete playerplane2;
        playerplane2 = nullptr;
    }


    playerplane1_health_bar = nullptr;
    playerplane1_health_text = nullptr;
    playerplane1_bomb_text = nullptr;
    playerplane2_health_bar = nullptr;
    playerplane2_health_text = nullptr;
    playerplane2_bomb_text = nullptr;
    score_text = nullptr;
    score1_text = nullptr;
    score2_text = nullptr;
    bomb_picture = nullptr;

    // level1_background1 = nullptr;
    // level1_background2 = nullptr;


    //不然每次打开，都会叠加一次，游戏帧都会变大一倍
    game_timer->stop();
    disconnect(game_timer, nullptr, nullptr, nullptr);


    // 重置关卡模式状态
    level_boss = nullptr;
    level_kill_count = 0;
    level_boss_spawned = false;
    level_victory = false;

    pvp_win_flag = 0;

}


