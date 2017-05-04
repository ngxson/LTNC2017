#include "scorescreen.h"
#include "mainwindow.h"
#include "playwindow.h"
#include "ui_scorescreen.h"
#include "Game.h"
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QString>
#include <algorithm>
#include <functional>

ScoreScreen::ScoreScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreScreen)
{
    ui->setupUi(this);
    QGraphicsPixmapItem* intro_bg = new QGraphicsPixmapItem();;

    ui->btnBack->setStyleSheet("QPushButton{background: transparent; color: white;border:2px solid #ffffff;}");
    ui->gameoverScore->setStyleSheet("QPushButton{background: transparent; color: white;}");
    ui->s1->setStyleSheet("QPushButton{background: transparent; color: white;}");
    ui->s2->setStyleSheet("QPushButton{background: transparent; color: white;}");
    ui->s3->setStyleSheet("QPushButton{background: transparent; color: white;}");
    ui->s4->setStyleSheet("QPushButton{background: transparent; color: white;}");
    ui->s5->setStyleSheet("QPushButton{background: transparent; color: white;}");
    ui->s1->setText("");
    ui->s2->setText("");
    ui->s3->setText("");
    ui->s4->setText("");
    ui->s5->setText("");

    if (isGameOver) {
        ui->btnPlayAgain->setStyleSheet(
                    "QPushButton{background: transparent; color: white;border:2px solid #ffffff;}");
        ui->btnPlayAgain->setText("Play Again");
        ui->gameoverScore->setText(QString::number(score));
        intro_bg->setPixmap(QPixmap(":/img/images/intro_gameover.png"));
    } else {
        //read file
        QString scorefilepath = qApp->applicationDirPath() + "/pianohero/score.nui";
        QFile scorefile1(scorefilepath);
        scorefile1.open(QIODevice::ReadOnly);
        int scores[] = {0,0,0,0,0,0};
        int pos = 0;
        foreach (QString i,QString(scorefile1.readAll()).split(QRegExp("[\n]"),QString::SkipEmptyParts)){
            if (pos == 5) break;
            scores[pos] = i.toInt(); pos++;
        }
        ui->s1->setText(QString::number(scores[0]));
        ui->s2->setText(QString::number(scores[1]));
        ui->s3->setText(QString::number(scores[2]));
        ui->s4->setText(QString::number(scores[3]));
        ui->s5->setText(QString::number(scores[4]));
        scorefile1.close();

        //setup ui
        ui->btnPlayAgain->setStyleSheet(
                    "QPushButton{background: transparent; color: white;border:none;}");
        ui->btnPlayAgain->setText("");
        intro_bg->setPixmap(QPixmap(":/img/images/intro_scoreboard.png"));
    }
    intro_bg->setPos(0, 0);
    QGraphicsScene * scene = new QGraphicsScene();
    scene->addItem(intro_bg);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene);
}

ScoreScreen::~ScoreScreen()
{
    delete ui;
}

void ScoreScreen::on_btnBack_clicked()
{
    isGameOver = false;
    this->hide();
    MainWindow *w = new MainWindow();
    w->show();
}

void ScoreScreen::on_btnPlayAgain_clicked()
{
    if (isGameOver) {
        isGameOver = false;
        this->hide();
        playwindow *p = new playwindow();
        p->view.show();
    }
}

void ScoreScreen::pushNewScore(int mScore) {
    int scores[] = {0,0,0,0,0,0};
    int pos = 0;
    QString scorefilepath1 = qApp->applicationDirPath() + "/pianohero/score.nui";

    //read file
    QFile scorefile1(scorefilepath1);
    scorefile1.open(QIODevice::ReadOnly);
    foreach (QString i,QString(scorefile1.readAll()).split(QRegExp("[\n]"),QString::SkipEmptyParts)){
        if (pos == 5) break;
        scores[pos] = i.toInt(); pos++;
    }
    scorefile1.close();

    //push new score and sort
    scores[5] = mScore;
    std::sort(scores, scores+6, std::greater<int>());

    //write to file
    QFile scorefile(scorefilepath1);
    if (scorefile.exists()) {
        scorefile.open(QFile::WriteOnly|QFile::Truncate);
        QTextStream stream( &scorefile );
        for (int i=0; i<4; i++)
            stream << QString::number(scores[i]) << '\n';
        stream << QString::number(scores[4]);
    }
    scorefile.close();
}
