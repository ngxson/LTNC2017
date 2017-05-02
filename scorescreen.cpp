#include "scorescreen.h"
#include "mainwindow.h"
#include "ui_scorescreen.h"
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>

ScoreScreen::ScoreScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreScreen)
{
    ui->setupUi(this);
    ui->btnBack->setStyleSheet("QPushButton{background: transparent; color: white;}");
    ui->s1->setStyleSheet("QPushButton{background: transparent; color: white;}");
    ui->s2->setStyleSheet("QPushButton{background: transparent; color: white;}");
    ui->s3->setStyleSheet("QPushButton{background: transparent; color: white;}");
    ui->s4->setStyleSheet("QPushButton{background: transparent; color: white;}");
    ui->s5->setStyleSheet("QPushButton{background: transparent; color: white;}");

    //Load background
    QGraphicsPixmapItem* intro_bg = new QGraphicsPixmapItem();
    intro_bg->setPixmap(QPixmap(":/img/images/intro_sky1.png"));
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
    QObject *senderObj = sender();

    this->hide();
    MainWindow *w = new MainWindow();
    w->show();
}
