#ifndef _COMM_H_
#define _COMM_H_

#include<iostream>
#include<string.h>
#include<list>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<sys/epoll.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<sys/sendfile.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<cstring>
#include<sstream>
#include<signal.h>
#include<errno.h>
using namespace std;

#define CPT  6790 //管理端口
#define TPT  6791 //传输端口
#define MPT  6792 //聊天端口
#define MCA  11111 //memcached端口

#define SERADDR "127.0.0.1"
#define DBUSER "root"
#define DBPSSW "root"
#define DBNAME "cloudpan"

#define SER_HOME_PATH "/home/cherlene/cloudpan/ser"
#define CLI_HOME_PATH "/home/cherlene/cloudpan/cli"

#define BUFFSIZE 128

#define EPOLL_SIZE 50

//用户都有哪些操作类型
enum OP_TYPE{ERR=-1,ENTER=1,REGISTER=2,UPLOAD=3,DOWNLOAD=4,CHART=5,RM=6,LS=7};

//用户信息
typedef struct Msg
{
	OP_TYPE type;
	string user_id;
	string passwd;
}msginfo;

//文件头部信息
struct fileinfo
{
	string filename;     //文件名
	string fileMD5;      //文件MD5值
	string filepath;     //文件存储路径
	int file_chunk_size; //文件分块个数
	int filesize;        //文件大小
	int chunk_size;      //分块标准
	bool trans_status;   //文件传输状态
};

//文件信息
struct filedata
{ 
	string filename;    //文件名
	int id;             //分块id 
	int offset;         //该块在文件的偏移量
	bool trans_status;  //传输状态
};

#endif

