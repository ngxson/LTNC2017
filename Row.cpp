#include "Row.h"
#include "Cell.h"
#include "const.h"
#include "BottomBar.h"
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QBrush>
#include <QGraphicsScene>
#include <QSignalMapper>

Row::Row()
{
    int x;
    for (x=0 ; x < NUM_OF_CELL_X ; x++) {
        cell[x] = new Cell();
        cell[x]->setRect(0,0,80,100);
        this->addToGroup(cell[x]);
        cell[x]->setPos(x*CELL_WIDTH,0);
        cell[x]->setBrush(* new QBrush(Qt::white));
    }

    setRightCell();
}

void Row::setRightCell() {
    cell[rightCell]->setBrush(* new QBrush(Qt::white));
    rightCell = qrand() % NUM_OF_CELL_X;
    cell[rightCell]->setBrush(* new QBrush(Qt::black));
}
