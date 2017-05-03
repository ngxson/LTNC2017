#include "Score.h"
#include "../Game.h"
#include <QFont>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the score to 0
    score = 0;

    // draw the text
    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times",16));
}

void Score::increase(int many){
    score += many;
    setPlainText(QString("Score: ") + QString::number(score));
}

void Score::decrease(int many){
    score -= many;
    setPlainText(QString("Score: ") + QString::number(score));
}
