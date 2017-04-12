#include "mainwindow.h"
#include "playwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->statusBar()->setSizeGripEnabled(false);
    ui->btnPlay->setStyleSheet("border-image:url(:/img/images/ingame_bg.png);");
    //ui->graphicsView->setScene();
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
