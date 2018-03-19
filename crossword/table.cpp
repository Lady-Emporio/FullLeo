#include "table.h"
#include <algorithm>

using namespace std;
//############Cell##################
Cell::Cell(){
    firstWord_=getEmptyWord();
    secondWord_=getEmptyWord();
    value_='@';
    status_=freely;
    pos_=zero;
}

status Cell::Status(){return this->status_;}
void Cell::setStatus(status x){this->status_=x;}
char Cell::Value(){return this->value_;}
void Cell::setValue(char x){this->value_=x;}
pos Cell::Pos(){return this->pos_;}
void Cell::setPos(pos x){this->pos_=x;}
Word Cell::FirstWord(){return this->firstWord_;}
void Cell::setFirstWord(Word x){this->firstWord_=x;}
Word Cell::SecondWord(){return this->secondWord_;}
void Cell::setSecondWord(Word x){this->secondWord_=x;}

//#############################table#########
Table::Table()
{
    table=new Cell*[TABLE_ROW];
    for(int i=0;i!=TABLE_ROW;++i){
        table[i]=new Cell[TABLE_COL];
    };
    qDebug("bad");
}

Table::~Table(){
    for(int i=0;i!=TABLE_ROW;++i){
        delete [] table[i];
    };
    delete [] table;
    qDebug("happy");
}

bool Table::run(string *Error){
    vector<Word> ListWord=getWord();
    if (ListWord.size()<=15){
            *Error="Small size: "+to_string(ListWord.size());
            return false;
    };
    sort(ListWord.begin(),ListWord.end(),[](Word x1,Word x2) {return (x1.eng<x2.eng);}); //убираю дубли
    auto last=unique(ListWord.begin(),ListWord.end(),[](Word x1,Word x2) {return (x1.eng==x2.eng);});
    ListWord.erase(last, ListWord.end());
    //сортирую по возрастанию размера строки
    sort(ListWord.begin(),ListWord.end(),[](Word x1,Word x2) {return (x1.eng.size()<x2.eng.size());});
    //Десять последних самых больших слов рандомно сортируем.
    std::srand ( (int)time(0));
    random_shuffle ( ListWord.end()-11, ListWord.end(),[](int i) {return std::rand()%i;});
    //############Region вставляю первое слово
    Word fword=ListWord.back();
    string FirstWord=fword.eng;
    ListWord.pop_back();
    if(CanISetWord(TABLE_ROW/2,(TABLE_COL/2)-(FirstWord.size()/2),FirstWord,horizontal,-1)){
        Using_Word.push_back(fword);
        SetInTable(TABLE_ROW/2,(TABLE_COL/2)-(FirstWord.size()/2),FirstWord,horizontal,-1,fword);
    }else{
            *Error="First word error can`t set in table";
            return false;
    }
    //############EndRegion вставляю первое слово
    int row,col,indexCollaps;
    pos WordPos;
//    for(int i=ListWord.size()-1;i!=ListWord.size()-4;--i){
    for(int i=ListWord.size()-1;i!=-1;--i){
        string next=ListWord[i].eng;
        if(FindIndexCollaps(&row,&col,next,&WordPos,&indexCollaps)){
            Using_Word.push_back(ListWord[i]);
            SetInTable(row,col,next,WordPos,indexCollaps,ListWord[i]);
            IfNeedBlock();
        }
    }

    return true;
}

bool Table::FindIndexCollaps(int *row,int *col,std::string word,pos *WordPos,int *indexCollaps){
    for(int i_row=0;i_row!=TABLE_ROW;++i_row){
        for(int i_col=0;i_col!=TABLE_COL;++i_col){
            for(int i=0;i!=word.size();++i){
                if(table[i_row][i_col].Value()==word[i]){
                    if(table[i_row][i_col].Pos()==vertical){
                        //Если нашли символ в слове, которое написано по вертикале, то по горизонтале вставляем.
                        int r,c;
                        r=i_row;//отправляем первый символ слова (word[0]s)
                        c=i_col-i;
                        if(NotInTableIndexError(c)){continue;}
                        if(CanISetWord(r,c,word,horizontal,i)){
                            *row=r;
                            *col=c;
                            *WordPos=horizontal;
                            //*indexCollaps=i;
                            return true;
                        }
                    }
                    else if(table[i_row][i_col].Pos()==horizontal){
                        int r,c;
                        r=i_row-i;
                        c=i_col;
                        if(NotInTableIndexError(r)){continue;}
                        if(CanISetWord(r,c,word,vertical,i)){
                            *row=r;
                            *col=c;
                            *WordPos=vertical;
                            //*indexCollaps=i;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Table::CanISetWord(int row,int col,std::string word,pos WordPos,int indexCollaps){
    if(WordPos==vertical){
        for(int i=-1;i!=word.size()+1;++i){
            if(i==-1){
                if(NotInTableIndexError(row+i)){ continue;} //перед словом блок не поставить-за границу выходит.
                if(table[row+i][col].Status()==wordHere){return false;}//если перед словом блок, то порядок,а если слово то плохо.
                continue;
            }
            else if(i==word.size()){//индекс за словом. За последним символом слова.
                if(NotInTableIndexError(row+i)){ continue;} //за словом блок не поставить-за границу выходит.
                if(table[row+i][col].Status()==wordHere){return false;}//если за словом блок, то порядок,а если слово то плохо.
                 continue;
            }
            if(NotInTableIndexError(row+i)){ return false;}
            Cell cell=table[row+i][col];
            if (cell.Status()==block){return false;}//Если наткнуть на блок, то точно слово не поставить.
            if (cell.Status()==wordHere){
                if(i==indexCollaps){continue;}  //насткнулся на слово, с которым и пересекаюсь.
                if(cell.Value()!=word[i]){return false;}
            }
        };
    }
    if(WordPos==horizontal){
        for(int i=-1;i!=word.size()+1;++i){
            if(i==-1){
                if(NotInTableIndexError(col+i)){ continue;} //перед словом блок не поставить-за границу выходит.
                if(table[row][col+i].Status()==wordHere){return false;}//если перед словом блок, то порядок,а если слово то плохо.
                continue;
            }
            else if(i==word.size()){//индекс за словом. За последним символом слова.
                if(NotInTableIndexError(col+i)){ continue;} //за словом блок не поставить-за границу выходит.
                if(table[row][col+i].Status()==wordHere){return false;}//если за словом блок, то порядок,а если слово то плохо.
                 continue;
            }
            if(NotInTableIndexError(col+i)){ return false;}
            Cell cell=table[row][col+i];
            if (cell.Status()==block){return false;}//Если наткнуть на блок, то точно слово не поставить.
            if (cell.Status()==wordHere){
                if(i==indexCollaps){continue;}  //насткнулся на слово, с которым и пересекаюсь.
                if(cell.Value()!=word[i]){return false;}
            }
        };
    }
    return true;
 }

void Table::SetInTable(int row,int col,std::string word,pos WordPos,int indexCollaps,Word ClassWord){
    if(WordPos==vertical){
        for(int i=-1;i!=word.size()+1;++i){
            int now_row=row+i;
            if(i==-1){
                if(NotInTableIndexError(now_row)){ continue;} //перед словом блок не поставить-за границу выходит.
                else{
                    table[now_row][col]=getBlock();
                    continue;
                }
            }
            else if(i==word.size()){
                if(NotInTableIndexError(now_row)){ continue;}
                else{
                    table[now_row][col]=getBlock();
                    break;
                }
            }
            Cell *cell=&table[now_row][col];
            if(cell->Status()!=wordHere){
                cell->setStatus(wordHere);
                cell->setValue(word[i]);
                cell->setFirstWord(ClassWord);
                cell->setPos(WordPos);
            }
            else if(cell->Status()==wordHere){
                cell->setSecondWord(ClassWord);
            }
        };
    }
    if(WordPos==horizontal){
        for(int i=-1;i!=word.size()+1;++i){
            if(i==-1){
                if(NotInTableIndexError(col-1)){ continue;} //перед словом блок не поставить-за границу выходит.
                else{
                    table[row][col-1]=getBlock();
                    continue;
                }
            }
            else if(i==word.size()){
                if(NotInTableIndexError(col+word.size())){ continue;}
                else{
                    table[row][col+word.size()]=getBlock();
                    break;
                }
            }
            Cell *cell=&table[row][col+i];
            if(cell->Status()!=wordHere){
                cell->setStatus(wordHere);
                cell->setValue(word[i]);
                cell->setFirstWord(ClassWord);
                cell->setPos(WordPos);
            }
            else if(cell->Status()==wordHere){
                cell->setSecondWord(ClassWord);
            }
        };
    }
}

void Table::IfNeedBlock(){
    for(int row=0;row!=TABLE_ROW;++row){
        for(int col=0;col!=TABLE_COL;++col){
            Cell *cell=&table[row][col];
            if(cell->Status()!=block && cell->Status()!=wordHere){
                int sum=0;
                if(!NotInTableIndexError(col+1)){if(table[row][col+1].Status()==wordHere){sum+=1;}}
                if(!NotInTableIndexError(col-1)){if(table[row][col-1].Status()==wordHere){sum+=1;}}
                if(!NotInTableIndexError((row+1))){if(table[row+1][col].Status()==wordHere){sum+=1;}}
                if(!NotInTableIndexError(row-1)){if(table[row-1][col].Status()==wordHere){sum+=1;}}
                if(sum>1){
                    *cell=getBlock();
                }
            }
        }
    }
}











