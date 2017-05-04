#include "Lives.h"
#include "../Game.h"
#include <QFont>
#include "const.h"

Lives::Lives(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the score to 0
    lives = 3;

    // draw the text
    setPlainText(QString("♥♥♥"));
    setDefaultTextColor(QColor(255, 50, 50));
    setFont(QFont("times",20));
}

void Lives::increase(){
    lives++;

    if (lives > LIVES_MAX) return;

    QString txt = "";
    for (int i=0 ; i<lives ; i++)
        txt = txt + "♥";
    setPlainText(txt);
}

void Lives::decrease(){
    lives--;

    if (lives > LIVES_MAX) return;

    QString txt = "";
    for (int i=0 ; i<lives ; i++)
        txt = txt + "♥";
    setPlainText(txt);
}
