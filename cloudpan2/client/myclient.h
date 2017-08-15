#ifndef _MYCLIENT_H
#define _MYCLIENT_H

class Myclient
{
public:
	Myclient(int port,const char* addr);
	~Myclient();
	void Run();
	void Entry_Menu();
	void Look_Menu();
	void SendMsg();
	void GetInfo();
	void DoSomthing();
private:
};

#endif
