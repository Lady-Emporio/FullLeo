#ifndef TABLE_H
#define TABLE_H
#include "const.h"
#include "word.h"
#include "bd.h"
#include <ctime>	//time
#include <cstdlib>	//rand srand
#include <QString>
class Cell{
public:
    Cell();
    status Status();
    void setStatus(status);
    char Value();
    void setValue(char);
    pos Pos();
    void setPos(pos);
    Word FirstWord();
    void setFirstWord(Word);
    Word SecondWord();
    void setSecondWord(Word);
private:
    Word firstWord_;
    Word secondWord_;
    char value_;
    status status_;
    pos pos_;

};


class Table
{
public:
    Table();
    ~Table();
    Cell **table;
    bool run(std::string*);
    std::vector<Word> Using_Word;
private:
    bool FindIndexCollaps(int *row,int *col,std::string word,pos *pos,int *indexCollaps);
    bool CanISetWord(int row,int col,std::string word,pos pos,int indexCollaps);
    void SetInTable(int row,int col,std::string word,pos pos,int indexCollaps,Word ClassWord);
    void IfNeedBlock();
};


inline bool NotInTableIndexError(int x){
    if(x>=TABLE_ROW){return true;}//всего 40х40, он не может быть больше или равен 40.
    else if(x<0){return true;}
    else 		{return false;}
}


inline Cell getBlock(){
    Cell blockCell;
    blockCell.setStatus(block);
    blockCell.setValue('#');
    return blockCell;
}

#endif // TABLE_H
