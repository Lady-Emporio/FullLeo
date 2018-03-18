#ifndef WORD_H
#define WORD_H
#include <string>
struct Word{
    int id;
    std::string eng;
    std::string ru;
    std::string audio;
    std::string image;
};

inline Word getEmptyWord(){
    Word empty;
    empty.id=-1;
    empty.eng="-1";
    empty.ru="-1";
    empty.audio="-1";
    empty.image="-1";
    return empty;
}

#endif // WORD_H
