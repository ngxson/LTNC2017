#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include "../Game.h"

class Score: public QGraphicsTextItem{
public:
    Score(QGraphicsItem * parent=0);
    void increase(int many);
    void decrease(int many);
};

#endif // SCORE_H
