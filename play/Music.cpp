#include "Music.h"
#include "../Game.h"
#include <QDebug>
#include <QSound>
#include <QTime>
#include <string.h>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QDir>

Music::Music()
{
    int i;
    loadNewSong();
}

QString readRandomSong();

void Music::loadNewSong() {
    QString mySong = readRandomSong();
    QTime now = QTime::currentTime();
    qsrand(now.msec());
    transpose = qrand() % 4 - 3;
    noteLast = 0;
    for (int i=0 ; i < mySong.length() ; i+=4) {
        song[noteLast][0] = (mySong.at(i).toLatin1()-'0')*10;
        song[noteLast][0] += (mySong.at(i+1).toLatin1()-'0');
        song[noteLast][1] = (mySong.at(i+2).toLatin1()-'0')*10;
        song[noteLast][1] += (mySong.at(i+3).toLatin1()-'0');
        //qDebug() << song[noteLast][0] << ' ' << song[noteLast][1];
        noteLast++;
    }
}

void Music::playNextNote() {
    if (notePlaying >= noteLast) {
        notePlaying = 0;
        if (isPlaying) loadNewSong();
    }
    playNoteInSong(0);
    playNoteInSong(1);
    notePlaying++;
}

QString readRandomSong() {
    QString mydir = appDir + "/pianohero/songs";
    QDir recoredDir(mydir);
    QStringList allFiles = recoredDir.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst);

    QTime now = QTime::currentTime();
    qsrand(now.msec());
    int choosedSong = qrand() % allFiles.length();

    //Read file
    QFile songfile(QString(mydir + "/" + allFiles[choosedSong]));
    songfile.open(QIODevice::ReadOnly);
    foreach (QString i,QString(songfile.readAll()).split(QRegExp("[\n]"),QString::SkipEmptyParts)){
        return i;
    }
    //return &ret;
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
        note += transpose;
        if (!pianoNotes[0][note]->PlayingState) {
            pianoNotes[0][note]->play();
        } else if (!pianoNotes[1][note]->PlayingState) {
            pianoNotes[1][note]->play();
        } else if (!pianoNotes[2][note]->PlayingState) {
            pianoNotes[2][note]->play();
        } else {
            pianoNotes[0][note]->stop();
            pianoNotes[0][note]->play();
        }
    }
}

