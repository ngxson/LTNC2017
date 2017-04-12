#ifndef CELL_H
#define CELL_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>

class Cell: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Cell();
};

#endif // CELL_H
