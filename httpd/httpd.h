#ifndef _HTTPD_H_
#define _HTTPD_H_
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/sendfile.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>

#define SIZE 1024

int start_up(char* ip,int port);
int readrow(int fd,char* buf,int len);
void error_headler(int nums);
void clear_headler(int fd);
void* headler_request(void* id);
void exe_cgi(int fd,const char* path,const char* method,const char* query_string);
void echo_www(int fd,char* path,int size);
#endif
