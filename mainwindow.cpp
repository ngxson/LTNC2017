#include "mainwindow.h"
#include "playwindow.h"
#include "scorescreen.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>

#define INTRO_WIDTH 500
#define FINE_TUNE -170

QGraphicsPixmapItem *sky[2];
QTimer * timer = new QTimer();

void setUpFileSystem();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->statusBar()->setSizeGripEnabled(false);
    ui->btnPlay->setStyleSheet("QPushButton{background: transparent;}");
    ui->btnAbout->setStyleSheet("QPushButton{background: transparent;}");
    ui->btnHighScore->setStyleSheet("QPushButton{background: transparent;}");

    //Load background
    QGraphicsPixmapItem* intro_bg = new QGraphicsPixmapItem();
    intro_bg->setPixmap(QPixmap(":/img/images/intro_bg.png"));
    intro_bg->setPos(FINE_TUNE, 0);
    sky[0] = new QGraphicsPixmapItem();
    sky[0]->setPixmap(QPixmap(":/img/images/intro_sky1.png"));
    sky[0]->setPos(-INTRO_WIDTH+FINE_TUNE, 0);
    sky[1] = new QGraphicsPixmapItem();
    sky[1]->setPixmap(QPixmap(":/img/images/intro_sky2.png"));
    sky[1]->setPos(FINE_TUNE, 0);

    QGraphicsScene * scene = new QGraphicsScene();
    scene->addItem(sky[0]);
    scene->addItem(sky[1]);
    scene->addItem(intro_bg);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene);

    connect(timer,SIGNAL(timeout()),this,SLOT(render_main()));
    timer->start(15);

    setUpFileSystem();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void setUpFileSystem() {
    QString mydir = qApp->applicationDirPath() + "/pianohero";
    mydir.replace(QString("/"), QString("\\"));
    qDebug() << mydir;
    if (!QDir(mydir).exists()) {
        QDir().mkdir(mydir);
    }
}

void MainWindow::on_btnPlay_clicked()
{
    QObject *senderObj = sender();
    QPushButton* button = qobject_cast<QPushButton*>(senderObj);

    timer->stop();
    disconnect(timer,SIGNAL(timeout()),this,SLOT(render_main()));
    this->hide();
    playwindow *p = new playwindow();
    p->view.show();
}

void MainWindow::on_btnHighScore_clicked()
{
    QObject *senderObj = sender();
    QPushButton* button = qobject_cast<QPushButton*>(senderObj);

    timer->stop();
    disconnect(timer,SIGNAL(timeout()),this,SLOT(render_main()));
    this->hide();
    ScoreScreen *p = new ScoreScreen();
    p->show();
}

void MainWindow::render_main() {
    //Render background
    for (int x=0 ; x < 2 ; x++) {
        if (sky[x]->x() > INTRO_WIDTH+FINE_TUNE) {
            sky[x]->setPos(-INTRO_WIDTH+1+FINE_TUNE,0);
        } else {
            sky[x]->setPos(sky[x]->x()+1,0);
        }

        /*if (notes[x]->x() > INTRO_WIDTH+75) {
            notes[x]->setPos(-INTRO_WIDTH+2+75,0);
        } else {
            notes[x]->setPos(notes[x]->x()+2,0);
        }*/
    }
}
