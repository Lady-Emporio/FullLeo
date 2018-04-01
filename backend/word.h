#ifndef WORD_H
#define WORD_H
#include <QString>
struct Word{
    int id;
    QString eng;
    QString ru;
    QString audio;
    QString image;
};

inline Word getEmptyWord(){
    Word empty;
    empty.eng="-1";
    empty.ru="-1";
    return empty;
}
#endif // WORD_H
