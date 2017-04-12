#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsRectItem>
#include <QObject>

class Bullet: public QObject,public QGraphicsRectItem{
    Q_OBJECT
public:
    Bullet();
};

#endif // BULLET_H
