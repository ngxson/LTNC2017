#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H

#include "Row.h"
#include <QObject>
#include <QGraphicsItemGroup>
#include <QSignalMapper>
#include <QMouseEvent>
#include <QWidget>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

class PlayScreen: public QObject,public QGraphicsItemGroup {
    Q_OBJECT
public:
    Row *row[10];
    PlayScreen();
    void checkIfHitBar(int right_cell, bool isRedNote, int y);

signals:

public slots:
    void render();

};

#endif // PLAYSCREEN_H
