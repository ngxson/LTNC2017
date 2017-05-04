#include "playwindow.h"
#include "play/const.h"
#include "play/BottomBar.h"
#include "play/PlayScreen.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QKeyEvent>
#include "Game.h"

int mouse_x = 0;
int mouse_y = 0;

playwindow::playwindow()
{
    QGraphicsScene * scene = new QGraphicsScene();

    PlayScreen *playscreen = new PlayScreen(this);
    playscreen->setFlags(QGraphicsItem::ItemIsFocusable);
    playscreen->setFocus();

    scene->addItem(playscreen);

    view.setScene(scene);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->hide();
    //view.show();
    view.setFixedSize(SCREEN_WIDTH+1,SCREEN_HEIGHT+1);
    scene->setSceneRect(0,0,SCREEN_WIDTH+1,SCREEN_HEIGHT+1);
}
