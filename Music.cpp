#include "Music.h"
#include <QDebug>
#include <QSound>
#include <string.h>
#include <QSoundEffect>

QSoundEffect *keys[70];

Music::Music()
{
    int i;
    for (i=1 ; i<68 ; i++) {
        char snum[5];
        itoa(i, snum, 10);
        char file[24] = {'\0'};
        strcat(file, ":/notes/");
        strcat(file, snum);
        strcat(file, ".wav");
        //QSound key(file);
        //keys[i] = new QSoundEffect();
        //keys[i]->setSource(QUrl::fromLocalFile(file));
        //keys[i]->setVolume(0.8f);
    }
    loadNewSong();
}

void Music::loadNewSong() {
    char data[] = "35004000420042004400440040004200440042004700470047004900510051005200520054005600540052005100510052005100470047004900490047004700450045004700470040004200440045004700450044004200";
    //"470047004940474440445135420047004700493547425442524044004744470059405644524751334900573357005640524454475244";
    int i;
    noteLast = 0;
    for (i=0 ; data[i] != '\0' ; i+=4) {
        song[noteLast][0] = (data[i]-'0')*10;
        song[noteLast][0] += (data[i+1]-'0');
        song[noteLast][1] = (data[i+2]-'0')*10;
        song[noteLast][1] += (data[i+3]-'0');
        qDebug() << song[noteLast][0] << ' ' << song[noteLast][1];
        noteLast++;
    }
}

void Music::playNextNote() {
    if (notePlaying > noteLast)
        notePlaying = 0;
    playNote(0);
    playNote(1);
    notePlaying++;
}

void Music::playNote(int id) {
    int note = song[notePlaying][id];
    if (note != 0) {
        char snum[5];
        itoa(note, snum, 10);
        char file[24] = {'\0'};
        strcat(file, ":/notes/");
        strcat(file, snum);
        strcat(file, ".wav");
        QSound::play(file);
        //keys[note]->play();
    }
}
