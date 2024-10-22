#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnPlay_clicked();
    void on_btnHighScore_clicked();
    void on_btnAction_clicked();
    void on_btnAbout_clicked();
    void render_main();
    void loadPianoNotes();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
