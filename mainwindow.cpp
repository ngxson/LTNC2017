#include "mainwindow.h"
#include "playwindow.h"
#include "Game.h"
#include "play/const.h"
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
#define MODE_HOME 0
#define MODE_HOWTOPLAY 1
#define MODE_ABOUTUS 2

int intro_mode = MODE_HOME;
QGraphicsPixmapItem *sky[2];
QTimer * timer = new QTimer();
QGraphicsPixmapItem* intro_aboutus;
QGraphicsPixmapItem* intro_howtoplay;
QGraphicsPixmapItem* intro_bg;
QGraphicsPixmapItem* intro_loading;
QMediaPlayer *pianoNotes[3][70];
QString appDir = qApp->applicationDirPath();
QMediaPlayer *bg_music;
bool introMusicPlaying = false;

void setUpFileSystem();
bool isGameOver = false;
bool isPlaying = false;
bool isInit = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    intro_mode = MODE_HOME;
    this->statusBar()->setSizeGripEnabled(false);
    ui->btnPlay->setStyleSheet("QPushButton{background: transparent;}");
    ui->btnAbout->setStyleSheet("QPushButton{background: transparent;}");
    ui->btnHighScore->setStyleSheet("QPushButton{background: transparent;}");
    ui->btnAction->setStyleSheet("QPushButton{background: transparent; color: white;}");
    ui->loadingpercent->setStyleSheet("QPushButton{background: transparent; color: white;}");

    //Load intro img
    intro_bg = new QGraphicsPixmapItem();
    intro_bg->setPixmap(QPixmap(":/img/images/intro_bg.png"));
    intro_bg->setPos(FINE_TUNE, 0);
    intro_bg->setVisible(false);
    intro_loading = new QGraphicsPixmapItem();
    intro_loading->setPixmap(QPixmap(":/img/images/intro_loading.png"));
    intro_loading->setPos(FINE_TUNE, 0);
    intro_loading->setVisible(true);

    //Set and hide hottoplay and aboutus
    intro_howtoplay = new QGraphicsPixmapItem();
    intro_howtoplay->setPixmap(QPixmap(":/img/images/intro_howtoplay.png"));
    intro_howtoplay->setPos(FINE_TUNE, -20);
    intro_howtoplay->setVisible(false);
    intro_aboutus = new QGraphicsPixmapItem();
    intro_aboutus->setPixmap(QPixmap(":/img/images/intro_about.png"));
    intro_aboutus->setPos(FINE_TUNE, -20);
    intro_aboutus->setVisible(false);

    //Load background
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
    scene->addItem(intro_loading);
    scene->addItem(intro_howtoplay);
    scene->addItem(intro_aboutus);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene);

    connect(timer,SIGNAL(timeout()),this,SLOT(render_main()));
    timer->start(15);

    if (!introMusicPlaying) {
        bg_music = new QMediaPlayer;
        bg_music->setMedia(QUrl(qApp->applicationDirPath()+"/intro.mp3"));
        bg_music->play();
        introMusicPlaying = true;
    }

    if (!isInit) {
        setUpFileSystem();
    } else {
        intro_loading->setVisible(false);
        intro_bg->setVisible(true);
        ui->loadingpercent->setText("");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void setUpFileSystem() {
    appDir = qApp->applicationDirPath();
    QString mydir = appDir + "/pianohero";
    mydir.replace(QString("/"), QString("\\"));
    qDebug() << mydir;
    if (!QDir(mydir).exists()) {
        QDir().mkdir(mydir);
    }

    // init scoreboard
    QString scorefilepath = appDir + "/pianohero/score.nui";
    QString arr[] = {"0","0","0","0","0"};
    QFile scorefile(scorefilepath);
    if (!scorefile.exists()) {
        scorefile.open(QIODevice::ReadWrite);
        QTextStream stream( &scorefile );
        for (int i=0; i<4; i++)
            stream << arr[i] << '\n';
        stream << arr[4];
    }
}

void MainWindow::loadPianoNotes() {
    for (int i=0 ; i<2 ; i++) {
        for (int j=1 ; j<=68 ; j++) {
            QString file;
            if (j<10) {
                file = "qrc:/notes/0" + QString::number(j) + ".wav";
            } else {
                file = "qrc:/notes/" + QString::number(j) + ".wav";
            }
            pianoNotes[i][j] = new QMediaPlayer;
            pianoNotes[i][j]->setMedia(QUrl(file));
        }
    }
}

void loadPianoNote(int voice, int note) {
    QString file;
    if (note<10) {
        file = "qrc:/notes/0" + QString::number(note) + ".wav";
    } else {
        file = "qrc:/notes/" + QString::number(note) + ".wav";
    }
    pianoNotes[voice][note] = new QMediaPlayer;
    pianoNotes[voice][note]->setMedia(QUrl(file));
}

void MainWindow::on_btnPlay_clicked()
{
    if (intro_mode == MODE_HOME && isInit) {
        intro_mode = MODE_HOWTOPLAY;
        ui->btnAction->setText("PLAY NOW");
        ui->btnAction->setStyleSheet("border:2px solid #ffffff;background: transparent; color: white;");
        intro_bg->setVisible(false);
        intro_howtoplay->setVisible(true);
    }
}

void MainWindow::on_btnAction_clicked()
{
    if (!isInit) return;
    if (intro_mode == MODE_HOWTOPLAY) {
        intro_mode = MODE_HOME;
        timer->stop();
        ui->btnAction->setText("");
        ui->btnAction->setStyleSheet("border:none;background: transparent;");
        introMusicPlaying = false;
        bg_music->stop();
        delete bg_music;
        disconnect(timer,SIGNAL(timeout()),this,SLOT(render_main()));
        this->hide();
        playwindow *p = new playwindow();
        p->view.show();
    } else if (intro_mode == MODE_ABOUTUS) {
        intro_mode = MODE_HOME;
        intro_aboutus->setVisible(false);
        intro_bg->setVisible(true);
        ui->btnAction->setText("");
        ui->btnAction->setStyleSheet("border:none;background: transparent;");
    }
}

void MainWindow::on_btnHighScore_clicked()
{
    if (!isInit) return;
    timer->stop();
    disconnect(timer,SIGNAL(timeout()),this,SLOT(render_main()));
    this->hide();
    ScoreScreen *p = new ScoreScreen();
    p->show();
}

void MainWindow::on_btnAbout_clicked()
{
    if (intro_mode == MODE_HOME && isInit) {
        intro_mode = MODE_ABOUTUS;
        ui->btnAction->setText("Go Back");
        ui->btnAction->setStyleSheet("border:2px solid #ffffff;background: transparent; color: white;");
        intro_bg->setVisible(false);
        intro_aboutus->setVisible(true);
    }
}

int loading_voice = 0;
int loading_note = 1;

void MainWindow::render_main() {
    if (!isInit) {
        if (loading_voice < MAX_VOICE) {
            if (loading_note <= MAX_NOTE) {
                loadPianoNote(loading_voice, loading_note);
                loading_note++;
            } else {
                loading_note = 1;
                loading_voice++;
            }
            int percent = (loading_voice*MAX_NOTE + loading_note)*100/(MAX_VOICE*MAX_NOTE);
            ui->loadingpercent->setText(QString::number(percent) + "%");
        } else {
            isInit = true;
            intro_bg->setVisible(true);
            intro_loading->setVisible(false);
            ui->loadingpercent->setText("");
        }
    }
    //Render background
    for (int x=0 ; x < 2 ; x++) {
        if (sky[x]->x() > INTRO_WIDTH+FINE_TUNE) {
            sky[x]->setPos(-INTRO_WIDTH+1+FINE_TUNE,0);
        } else {
            sky[x]->setPos(sky[x]->x()+1,0);
        }
    }
}
