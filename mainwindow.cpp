#include "mainwindow.h"
#include "playwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <QDebug>

#define INTRO_WIDTH 451

QGraphicsPixmapItem *intro_bg[2];
QGraphicsPixmapItem *notes[2];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->statusBar()->setSizeGripEnabled(false);
    //ui->btnPlay->setStyleSheet("border-image:url(:/img/images/ingame_bg.png);");

    //Load background
    intro_bg[0] = new QGraphicsPixmapItem();
    intro_bg[0]->setPixmap(QPixmap(":/img/images/intro_bg.png"));
    intro_bg[0]->setPos(-INTRO_WIDTH, 0);
    intro_bg[1] = new QGraphicsPixmapItem();
    intro_bg[1]->setPixmap(QPixmap(":/img/images/intro_bg.png"));
    intro_bg[1]->setPos(0, 0);
    notes[0] = new QGraphicsPixmapItem();
    notes[0]->setPixmap(QPixmap(":/img/images/intro_notes.png"));
    notes[0]->setPos(-INTRO_WIDTH, 0);
    notes[1] = new QGraphicsPixmapItem();
    notes[1]->setPixmap(QPixmap(":/img/images/intro_notes.png"));
    notes[1]->setPos(0, 0);
    QGraphicsPixmapItem *logo = new QGraphicsPixmapItem();
    logo->setPixmap(QPixmap(":/img/images/intro_logo.png"));
    logo->setPos(130, 0);

    QGraphicsScene * scene = new QGraphicsScene();
    scene->addItem(intro_bg[0]);
    scene->addItem(intro_bg[1]);
    scene->addItem(notes[0]);
    scene->addItem(notes[1]);
    scene->addItem(logo);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene);

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(render_main()));
    timer->start(15);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnPlay_clicked()
{
    QObject *senderObj = sender();
    QPushButton* button = qobject_cast<QPushButton*>(senderObj);

    this->hide();
    playwindow *p = new playwindow();
    p->view.show();
}

void MainWindow::render_main() {
    //Render background
    for (int x=0 ; x < 2 ; x++) {
        if (intro_bg[x]->x() > INTRO_WIDTH) {
            intro_bg[x]->setPos(-INTRO_WIDTH+1,0);
        } else {
            intro_bg[x]->setPos(intro_bg[x]->x()+1,0);
        }

        if (notes[x]->x() > INTRO_WIDTH) {
            notes[x]->setPos(-INTRO_WIDTH+2,0);
        } else {
            notes[x]->setPos(notes[x]->x()+2,0);
        }
    }
}
