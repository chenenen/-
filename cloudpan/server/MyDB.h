#ifndef _MYDB_H_
#define _MYDB_H_

MyDB();
~MyDB();
bool InitDB(string host,string,user,string passwd,string BDname);
bool execSQL(string sql);


#endif

