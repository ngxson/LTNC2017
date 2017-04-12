#ifndef MUSIC_H
#define MUSIC_H

#include <QObject>

class Music
{
public:
    int song[100][2];
    int notePlaying = 0;
    int noteLast = 0;
    Music();
    void loadNewSong();
    void playNextNote();
private:
    void playNote(int id);
};

#endif // MUSIC_H
