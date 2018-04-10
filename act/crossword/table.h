#ifndef TABLE_H
#define TABLE_H
#include <ctime>	//time
#include <cstdlib>	//rand srand
#include <QString>
#include "backend/word.h"
#include <vector>
#include "backend/leo_const.h"
using namespace Leo;
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
    bool run(std::string*,algTable);
    std::vector<Word> Using_Word;
private:
    bool FindIndexCollaps(int *row,int *col,std::string word,pos *pos,int *indexCollaps);
    bool CanISetWord(int row,int col,std::string word,pos pos,int indexCollaps);
    void SetInTable(int row,int col,std::string word,pos pos,int indexCollaps,Word ClassWord);
    void IfNeedBlock();
    int maxRowInThisTableNow;
    int maxColInThisTableNow;
    bool runFast(std::string *);
    bool runFull(std::string *);
};


inline bool NotInTableIndexError(int x,pos position){
    if(position==vertical){
        if(x>=LeoConst::CONST()->All_INT_PARAMS["TABLE_ROW"]){return true;}
    }
    else if(position==horizontal){
        if(x>=LeoConst::CONST()->All_INT_PARAMS["TABLE_COL"]){return true;}
    }
    if(x<0){return true;}
    else 		{return false;}
}


inline Cell getBlock(){
    Cell blockCell;
    blockCell.setStatus(block);
    blockCell.setValue('#');
    return blockCell;
}
#endif // TABLE_H
