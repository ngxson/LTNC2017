#include "Music.h"
#include <QDebug>
#include <QSound>
#include <string.h>
#include <QSoundEffect>
#include <QMediaPlayer>

QSoundEffect *keys[70];

Music::Music()
{
    int i;
    loadNewSong();
}

void Music::loadNewSong() {
    //char data[] = "35004000420042004400440040004200440042004700470047004900510051005200520054005600540052005100510052005100470047004900490047004700450045004700470040004200440045004700450044004200";
    char data[] = "470047004940474440445135420047004700493547425442524044004744470059405644524751334900573357005640524454475244";
    int i;
    noteLast = 0;
    for (i=0 ; data[i] != '\0' ; i+=4) {
        song[noteLast][0] = (data[i]-'0')*10;
        song[noteLast][0] += (data[i+1]-'0');
        song[noteLast][1] = (data[i+2]-'0')*10;
        song[noteLast][1] += (data[i+3]-'0');
        //qDebug() << song[noteLast][0] << ' ' << song[noteLast][1];
        noteLast++;
    }
}

void Music::playNextNote() {
    if (notePlaying >= noteLast)
        notePlaying = 0;
    playNoteInSong(0);
    playNoteInSong(1);
    notePlaying++;
}

void Music::playRedNote() {
    playOneNote(10);
    playOneNote(15);
    playOneNote(20);
}

void Music::playNoteInSong(int id) {
    int note = song[notePlaying][id];
    playOneNote(note);
}

void Music::playOneNote(int note) {
    if (note != 0) {
        char snum[5];
        itoa(note, snum, 10);
        char file[24] = {'\0'};
        strcat(file, "qrc:/notes/");
        strcat(file, snum);
        strcat(file, ".wav");
        QMediaPlayer *sound = new QMediaPlayer;
        sound->setMedia(QUrl(file));
        sound->play();
        //keys[note]->play();
    }
}

