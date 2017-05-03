#include "const.h"
#include "../Game.h"
#include "Music.h"
#include "Score.h"
#include "Lives.h"
#include "PlayScreen.h"
#include <QTime>
#include <QTimer>
#include <QMouseEvent>
#include <QTransform>
#include <QPoint>
#include <QString>
#include <QDebug>
#include <QWidget>

int score = 0;
int lives = 0;

#define LAST_ROW NUM_OF_CELL_Y-1

QGraphicsRectItem *mo = new QGraphicsRectItem();
QGraphicsPixmapItem *background[2];
Music *music;
int speed = SPEED_MIN;
qreal speed_real = SPEED_MIN;
int current_row;
int right_cell;
bool dontCheckBottomRow = false;
Score *scoretxt;
Lives *livestxt;

PlayScreen::PlayScreen()
{
    int y;
    current_row = 0;
    right_cell = 0;
    speed = SPEED_MIN;
    speed_real = SPEED_MIN;

    this->setAcceptHoverEvents(true);
    // Seed random function
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    //Load background
    background[0] = new QGraphicsPixmapItem();
    background[0]->setPixmap(QPixmap(":/img/images/ingame_bg.png"));
    background[0]->setPos(0, -SCREEN_HEIGHT);
    background[1] = new QGraphicsPixmapItem();
    background[1]->setPixmap(QPixmap(":/img/images/ingame_bg.png"));
    background[1]->setPos(0, 0);
    this->addToGroup(background[0]);
    this->addToGroup(background[1]);

    // Build the screen map
    for (y=0 ; y < NUM_OF_CELL_Y+1 ; y++) {
        row[y] = new Row();
        this->addToGroup(row[y]);
        row[y]->setPos(0,(y-1)*(CELL_HEIGHT)-SCREEN_HEIGHT);
    }

    // Make timer and connect it
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(render()));
    timer->start(15);

    mo->setRect(0,0,CELL_WIDTH,BOTTOM_BAR_HEIGHT);
    mo->setBrush(* new QBrush(Qt::white));
    mo->setPos(0,SCREEN_HEIGHT-BOTTOM_BAR_HEIGHT);
    this->addToGroup(mo);
    music = new Music();

    scoretxt = new Score();
    livestxt = new Lives();
    livestxt->setPos(0,24);

    this->addToGroup(scoretxt);
    this->addToGroup(livestxt);
}

void PlayScreen::render() {
    int y;

    // Increase the speed
    if (speed < SPEED_MAX) {
        speed_real = speed_real+SPEED_ACCELERATE;
        speed = (int) speed_real;
    }

    //Render background
    for (y=0 ; y < 2 ; y++) {
        if (background[y]->y() > SCREEN_HEIGHT) {
            background[y]->setPos(0,-SCREEN_HEIGHT+speed/2);
        } else {
            background[y]->setPos(0,background[y]->y()+speed/2);
        }
    }

    // Render all rows
    for (y=0 ; y < NUM_OF_CELL_Y+1 ; y++) {
        //process the cell going down to bottom
        if (row[y]->y() > SCREEN_HEIGHT-CELL_HEIGHT-BOTTOM_BAR_HEIGHT && !dontCheckBottomRow) {
            dontCheckBottomRow = true;
            right_cell = row[y]->getRightCell();
            if (current_row != y) {
                current_row = y;
                checkIfHitBar(right_cell, row[y]->getIsRedNote(), y);
            }
        }

        // Animate the cell
        qreal mScale = row[y]->cell[right_cell]->scale();
        if (mScale < 1 && mScale > 0.1) {
            row[y]->cell[right_cell]->setScale(mScale-0.1);
            row[y]->cell[right_cell]->setPos(row[y]->cell[right_cell]->x()+0.1*(CELL_WIDTH/2)
                                             ,row[y]->cell[right_cell]->y()+0.1*(CELL_HEIGHT/2));
        }

        // Move the cell
        if (row[y]->y()+speed >= SCREEN_HEIGHT) {
            dontCheckBottomRow = false;
            // Go back to top
            row[y]->setRightCell();
            row[y]->setPos(0,row[y]->y()-SCREEN_HEIGHT-CELL_HEIGHT+speed);
        } else {
            // Or continue to move down?
            row[y]->setPos(0,row[y]->y()+speed);
        }
    }

    // Move the bar according to mouse pos
    mo->setPos((qreal)mouse_x-CELL_WIDTH/2,SCREEN_HEIGHT-BOTTOM_BAR_HEIGHT);
}

void PlayScreen::checkIfHitBar(int right_cell, bool isRedNote, int y) {
    if (mo->x() > (right_cell-0.5)*CELL_WIDTH && mo->x() < (right_cell+0.5)*CELL_WIDTH) {
        if (isRedNote) {
            music->playRedNote();
            scoretxt->decrease(10);
        } else {
            music->playNextNote();
            scoretxt->increase(1);
        }
        row[y]->cell[right_cell]->setScale(0.9);
    } else {
        if (!isRedNote) {
            livestxt->decrease();
        }
    }
}
