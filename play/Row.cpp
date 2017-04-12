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
    rightCell = 0;
    isRedNote = false;

    for (x=0 ; x < NUM_OF_CELL_X ; x++) {
        cell[x] = new Cell();
        this->addToGroup(cell[x]);
        cell[x]->setPixmap(QPixmap(":/img/images/note_none.png"));
        cell[x]->setPos(x*CELL_WIDTH,0);
        cell[x]->setScale(1);
    }

    setRightCell();
}

void Row::setRightCell() {
    // Reset old cell state
    cell[rightCell]->setPixmap(QPixmap(":/img/images/note_none.png"));
    cell[rightCell]->setPos(rightCell*CELL_WIDTH,0);
    cell[rightCell]->setScale(1);

    // Render new cell
    rightCell = qrand() % NUM_OF_CELL_X;
    isRedNote = qrand() % 100 < 4;
    if (isRedNote) {
        cell[rightCell]->setPixmap(QPixmap(":/img/images/note_red.png"));
    } else {
        cell[rightCell]->setPixmap(QPixmap(":/img/images/note_black.png"));
    }
}

int Row::getRightCell() {
    return rightCell;
}

bool Row::getIsRedNote() {
    return isRedNote;
}
