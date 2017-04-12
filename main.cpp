#include "mainwindow.h"
#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <string>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    /*QPushButton *button[10][10];
    QGridLayout *gridLayout = w.findChild<QGridLayout*>("gridLayout");
    Q_ASSERT(gridLayout);*/
    //gridLayout->addWidget(new QLabel("hello, the second"));

    w.show();
    return a.exec();
}
