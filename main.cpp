#include <QApplication>
#include "const.h"
#include "BottomBar.h"
#include "PlayScreen.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QKeyEvent>

/*
Tutorial Topics:
-QGraphicsScene's sceneRect
-QGraphicView's sceneRect
-QGraphicView coordinates vs QGraphicScene coordinates vs QGraphicItem coordinates
*/


int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    // create a scene
    QGraphicsScene * scene = new QGraphicsScene();
    // make rect focusable
    BottomBar *bbar =new BottomBar();
    bbar->setFlags(QGraphicsItem::ItemIsFocusable);
    bbar->setFocus();

    PlayScreen *playscreen = new PlayScreen();

    scene->addItem(playscreen);
    scene->addItem(bbar);

    // create a view to visualize the scene
    QGraphicsView * view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // show the view
    view->show();
    view->setFixedSize(SCREEN_WIDTH+1,SCREEN_HEIGHT+1);
    scene->setSceneRect(0,0,SCREEN_WIDTH+1,SCREEN_HEIGHT+1);

    //player->setPos(view->width()/2,view->height() - player->rect().height());

    return a.exec();

}
