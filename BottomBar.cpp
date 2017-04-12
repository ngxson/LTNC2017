#include "BottomBar.h"
#include "const.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QGraphicsItemGroup>
#include <QBrush>
#include <QDebug>
#include <QSound>
#include "Row.h"
#include "Music.h"

#define NUM_OF_BOX 4
QGraphicsRectItem *box[NUM_OF_BOX];
bool canPressNote = true;
Music *music = new Music();

BottomBar::BottomBar() {
    int i;
    QGraphicsRectItem *overlay = new QGraphicsRectItem();
    overlay->setRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    this->addToGroup(overlay);
    for (i=0 ; i<NUM_OF_BOX ; i++) {
        box[i] = new QGraphicsRectItem();
        box[i]->setRect(0,0,CELL_WIDTH,BOTTOM_BAR_HEIGHT);
        this->addToGroup(box[i]);
        box[i]->setPos(i*CELL_WIDTH,SCREEN_HEIGHT-BOTTOM_BAR_HEIGHT);
        box[i]->setBrush(* new QBrush(Qt::white));
    }
    music->loadNewSong();
}

void BottomBar::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_1 && canPressNote){
        canPressNote = false;
        box[0]->setBrush(* new QBrush(Qt::blue));
        checkPressKey(0);
    } else if (event->key() == Qt::Key_2 && canPressNote){
        canPressNote = false;
        box[1]->setBrush(* new QBrush(Qt::blue));
        checkPressKey(1);
    } else if (event->key() == Qt::Key_3 && canPressNote){
        canPressNote = false;
        box[2]->setBrush(* new QBrush(Qt::blue));
        checkPressKey(2);
    } else if (event->key() == Qt::Key_4 && canPressNote){
        canPressNote = false;
        box[3]->setBrush(* new QBrush(Qt::blue));
        checkPressKey(3);
    }
}

void BottomBar::keyReleaseEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_1 ||
            event->key() == Qt::Key_2 ||
            event->key() == Qt::Key_3 ||
            event->key() == Qt::Key_4 ){
        canPressNote = true;
        box[0]->setBrush(* new QBrush(Qt::white));
        box[1]->setBrush(* new QBrush(Qt::white));
        box[2]->setBrush(* new QBrush(Qt::white));
        box[3]->setBrush(* new QBrush(Qt::white));
    }
}

void BottomBar::checkPressKey(int key) {
    music->playNextNote();
    /*if (key == rightKey) {
        qDebug() << "OK";
    } else {
        qDebug() << "ewwwwww";
    }*/
}
