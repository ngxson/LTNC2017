#ifndef ROW_H
#define ROW_H

#include <QObject>
#include <QGraphicsItemGroup>
#include <QSignalMapper>
#include "Cell.h"

class Row: public QObject,public QGraphicsItemGroup {
    Q_OBJECT
public:
    Cell *cell[10];
    int rightCell;
    bool isRedNote;
    Row();
    void setRightCell();
    int getRightCell();
    bool getIsRedNote();
};

#endif // ROW_H
