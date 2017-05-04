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
    isGreenNote = false;

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
    isRedNote = false;
    isGreenNote = false;

    // Render new cell
    rightCell = qrand() % NUM_OF_CELL_X;
    if (qrand() % 100 < 15) {
        if (qrand() % 5 > 0) {
            isRedNote = true;
            cell[rightCell]->setPixmap(QPixmap(":/img/images/note_red.png"));
        } else {
            isGreenNote = true;
            cell[rightCell]->setPixmap(QPixmap(":/img/images/note_green.png"));
        }
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

bool Row::getIsGreenNote() {
    return isGreenNote;
}
