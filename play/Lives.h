#ifndef LIVES_H
#define LIVES_H

#include <QGraphicsTextItem>
#include "../Game.h"

class Lives: public QGraphicsTextItem{
public:
    Lives(QGraphicsItem * parent=0);
    void increase();
    void decrease();
};

#endif // LIVES_H
