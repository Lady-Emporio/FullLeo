#ifndef BD_H
#define BD_H
#include "word.h"
#include "sqlite3.h"
#include <vector>

inline std::vector<Word> getWord(){
std::vector<Word> List_word;
sqlite3 *db;
sqlite3_stmt * pStmt;
if (sqlite3_open("./lingualeo.txt", &db)){
//    cout<<"Error MyERROR: \n"<< sqlite3_errmsg(db)<<endl;
    sqlite3_close(db);
    return List_word;}

if (sqlite3_prepare(db, "SELECT * FROM 'MainTable';", -1, &pStmt, NULL)){
//    cout<<"Error MyERROR: \n"<< sqlite3_errmsg(db)<<endl;
    sqlite3_finalize(pStmt);
    sqlite3_close(db);
    return List_word;}


while((sqlite3_step(pStmt)) == SQLITE_ROW){
    Word next;
    std::string id=reinterpret_cast<const char *>(sqlite3_column_text(pStmt, 0));
    next.id=stoi(id);
    next.eng=reinterpret_cast<const char *>(sqlite3_column_text(pStmt, 1));
    next.ru=reinterpret_cast<const char *>(sqlite3_column_text(pStmt, 2));
    next.audio=reinterpret_cast<const char *>(sqlite3_column_text(pStmt, 3));
    next.image=reinterpret_cast<const char *>(sqlite3_column_text(pStmt, 4));
    List_word.push_back(next);
};
sqlite3_finalize(pStmt);
sqlite3_close(db);
return List_word;
}
#endif // BD_H
