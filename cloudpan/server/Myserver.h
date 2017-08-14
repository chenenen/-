#ifndef _MYSERVER_H_
#define _MYSERVER_H_

Myserver(int port,const char* addr);
~Myserver();
void Socket();
void Bind();
void Listen();
void epoll_work();
void Run();
void do_service(int conn);
void 
void selectFTServer();
void get_cmd();

#endif
