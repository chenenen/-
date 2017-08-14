#include"myclient.h"
#include"md5.h"

Mycached(int port,const char* addr)
{
	if(sock = socket(AF_INET,SOCK_STREAM,0)<0)
	{
		perror("sock failed!");
		return -1;
	}
	memset(&seraddr,0,sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(port);
	seraddr.sin_addr.s_addr = inet_addr(addr);
}

~Mycached(){}

void Run()
{
	if(connect(sock,(struct sockaddr*)&seraddr,sizeof(seraddr)<0))
	{
		perror("connect filed!");
		return -2;
	}
	while(1)
	{
		DoSomthing();
	}
}
//登录口
void Entry_Menu()
{
	cout<<"#########################"<<endl;
	cout<<"Welcome!"<<endl;
	cout<<"#########################"<<endl;
	cout<<"                         "<<endl;
	cout<<"   1、登录 2、注册       "<endl;
	cout<<"                         "<<endl;
	cout<<"#########################"<<endl;
	cout<<"choose>: ";
}
//关于登录进去信息查看
void Look_Menu()
{
	system("clear");
	cout<<"#########################"<<endl;
	cout<<"Welcome"<<endl;
	cout<<"#########################"<<endl;
	cout<<"                         "<<endl;
	cout<<"  1、查看好友 2、个人信息"<<endl;
	cout<<"#########################"<<endl;
	cout<<"choose>: ";
}
//用户进行请求发送，相当于验证用户
void SenMsg()
{
	while(1)
	{
		int ret = send(sock,(msg.c_str()),msg.size()+1,0);
		recv(sock,(void*)msg.c_str(),msg.size(),0);
		if(strcmp("1",msg.c_str(),1)==0||
			strncmp("register success",msg.c_str(),10)==0)
		{
			Look_Menu();
		}
		else if(strncmp("user exited",msg.c_str(),17)==0)
		{
			cout<<msg.c_str()<<endl;
			DoSomthing();
		}
		else
		{
			cout<<"用户名或密码错误"<<endl;
			Dosomthing();
		}
		while(1)
		{}
}
//获取用户的信息
void GetInfo()
{
	string user,passwd;
	cout<<"用户名";
	cin>>user;
	msg+=user;
	cout<<"密码";
	cin>>passwd;
	msg = msg+" "+MD5(passwd).toString();
	SendMsg();
}

//客户端执行的事
void DoSomthing()
{
	int choice;
	Entry_Menu();
	cin>>choice;
	switch(choice)
	{
		//登录
		case ENTER:
			msg = "1";
			GetInfo();
			break;
		//注册
		case REGISTER:
			msg = "2";
			GetInfo();
			break;
		//文件上传
		case UPLODE():
			msg = "3";
			break;
		//文件下载
		case DOWNLOAD:
			msg = "4";
			break;
		//聊天
		case CHART:
			msg = "5";
			break;
		default:
			msg = "-1";
			break;
	}
}

//int main()
//{
//	Myclient.cl(CPT,"127.0.0.1");
//	cl.Run();
//	return 0;
}
