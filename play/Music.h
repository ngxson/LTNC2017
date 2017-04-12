#ifndef MUSIC_H
#define MUSIC_H

#include <QObject>
#include <QMediaPlayer>

class Music
{
public:
    int song[100][2];
    QMediaPlayer *notes[88];
    int notePlaying = 0;
    int noteLast = 0;
    Music();
    void loadNewSong();
    void playNextNote();
    void playRedNote();
private:
    void playOneNote(int id);
    void playNoteInSong(int id);
};

#endif // MUSIC_H
