#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H
#include <QGraphicsView>
#include <QMouseEvent>
#include "Game.h"

class CustomView : public QGraphicsView
{
protected:
    void mouseMoveEvent(QMouseEvent *event)
    {
        //qDebug() << event->x() << " - " << event->y();
        mouse_x = event->x();
        mouse_y = event->y();
    }
};

class playwindow
{
public:
    playwindow();
    CustomView view;
};

#endif // PLAYWINDOW_H
