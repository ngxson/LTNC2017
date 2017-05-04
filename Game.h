#ifndef GAME_H
#define GAME_H
#include <QMediaPlayer>
#include <QString>

extern int mouse_x;
extern int mouse_y;
extern int score;
extern int lives;
extern bool isGameOver;
extern bool isPlaying;
extern QMediaPlayer *pianoNotes[3][70];
extern bool isInit;
extern QString appDir;

class Game
{
public:
    Game();
};

#endif // GAME_H
