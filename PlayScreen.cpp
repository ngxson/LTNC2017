#include "const.h"
#include "PlayScreen.h"
#include <QTime>
#include <QTimer>
#include <QMouseEvent>
#include <QTransform>
#include <QPoint>
#include <QString>

#define LAST_ROW NUM_OF_CELL_Y-1

PlayScreen::PlayScreen()
{
    int y;

    // Seed random function
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    // Build the screen map
    for (y=0 ; y < NUM_OF_CELL_Y+1 ; y++) {
        row[y] = new Row();
        this->addToGroup(row[y]);
        row[y]->setPos(0,(y-1)*(CELL_HEIGHT));
    }

    // Make timer and connect it
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(15);
}

void PlayScreen::move() {
    int y;

    // Move all except the last row
    for (y=0 ; y < NUM_OF_CELL_Y+1 ; y++) {
        if (row[y]->y() >= SCREEN_HEIGHT) {
            row[y]->setRightCell();
            row[y]->setPos(0,-CELL_HEIGHT+10);
        } else {
            row[y]->setPos(0,row[y]->y()+10);
        }
    }
}

void PlayScreen::mouseMoveEvent(QMouseEvent *ev) {
        // vvv That's where the magic happens
        QTransform t;
        t.scale(1, -1);
        t.translate(0, -SCREEN_HEIGHT+1);
        QPoint pos = ev->pos() * t;
        // ^^^
        //qDebug() << "z";
}
