#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H

#include <Row.h>
#include <QObject>
#include <QGraphicsItemGroup>
#include <QSignalMapper>
#include <QMouseEvent>

class PlayScreen: public QObject,public QGraphicsItemGroup {
    Q_OBJECT
public:
    Row *row[10];
    PlayScreen();
    void mouseMoveEvent(QMouseEvent *ev);

signals:

public slots:
    void move();

};

#endif // PLAYSCREEN_H
