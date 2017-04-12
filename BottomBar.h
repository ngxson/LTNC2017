#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QObject>
#include <QGraphicsRectItem>
#include "Row.h"

class BottomBar: public QGraphicsItemGroup {
public:
    BottomBar();
public:
    void keyPressEvent(QKeyEvent * event);
    void checkPressKey(int key);
public:
    void keyReleaseEvent(QKeyEvent * event);
};

#endif // BUTTOMBAR_H
