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
    void pushNewScore(int mScore);

public slots:
    void on_btnBack_clicked();
    void on_btnPlayAgain_clicked();

private:
    Ui::ScoreScreen *ui;
};

#endif // SCORESCREEN_H
