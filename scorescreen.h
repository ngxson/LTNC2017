#ifndef SCORESCREEN_H
#define SCORESCREEN_H

#include <QWidget>

namespace Ui {
class ScoreScreen;
}

class ScoreScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreScreen(QWidget *parent = 0);
    ~ScoreScreen();

public slots:
    void on_btnBack_clicked();

private:
    Ui::ScoreScreen *ui;
};

#endif // SCORESCREEN_H
