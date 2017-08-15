#ifndef _SQLCONNPOLL_H__
#define _SQLCONNPOLL_H_

CSqlConnPool();
~CSqlConnPool();
void Init(const SqlConnInfo& sqlConnInfo);
void SetDBName(const char* DBName);
void Destroy();
Connection* CreateConnection();
void TerminateConnection(Connection* conn);
void Connection* GetConnection();
void ReleaseConnection(Connection* conn);
bool IsValidConnection(Connection*conn);


#endif
