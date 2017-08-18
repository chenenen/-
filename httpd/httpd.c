#include "httpd.h"

int start_up(char* ip, int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket");
		exit(2);
	}
	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);

	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
	{
		perror("bind");
		exit(3);
	}

	if(listen(sock, 10) < 0)
	{
		perror("listen");
		exit(4);
	}
	return sock;
}

int readrow(int fd, char* buf, int len)
{
	char c= '\0';
	int i = 0;
	while(c != '\n' && i < len-1)
	{
		int s = recv(fd, &c, 1, 0);
		if(s == 0)
		{
			printf("fd is closs!\n");
			break;
		}
		else if(s < 0)
		{
			perror("recv");
			break;
		}
		if(c == '\r')
		{
			recv(fd, &c, 1,MSG_PEEK);
			if(c == '\n')
			{
				recv(fd, &c, 1, 0);
			}
			c = '\n';
		}
		buf[i++] = c;
	}
	buf[i] = '\0';
	return i;

}

void error_headler(int nums)
{}
void clear_headler(int fd)
{
	int s = 0;
	char buf[1024];
	do
	{	
		s = readrow(fd, buf, sizeof(buf));
		printf("%s",buf);
	}while(s != 1 && s > 0);
	strcpy(buf, "HTTP/1.0 200 OK\r\n\r\n<html><h1>hello HTTP!</h1></html>");
	send(fd, buf, strlen(buf), 0);
}
void* headler_request(void* id)
{
	long fd = (long)id;
#ifdef _DEBUG_
	int s = 0;
	char buf[1024];
	do
	{	
		s = readrow(fd, buf, sizeof(buf));
		printf("%s",buf);
	}while(s != 1 && s > 0);
	strcpy(buf, "HTTP/1.0 200 OK\r\n\r\n<html><h1>hello HTTP!</h1></html>");
	send(fd, buf, strlen(buf), 0);
#endif


	int s = 0;
	char buf[SIZE];
	int ret = -1;
	int nums = 0;
	int i = 0;
	int j = 0;
	int cgi = 0;
	char *ptr;
	char method[SIZE/2];
	char url[SIZE];
	char path[SIZE];
	char *query_string = NULL;
	s = readrow(fd, buf, sizeof(buf));
	if(s <= 0)
	{
		ret = -1;
		nums = 404;
		goto end;
	}

	//	clear_headler(fd);
	printf("buf:%s",buf);

	while(i < SIZE && j < SIZE/2 && !isspace(buf[i]))
		method[j++] = buf[i++];
	method[j] = 0;

	while( isspace(buf[i]) )
		i++;

	j = 0;
	while(i < SIZE && j < SIZE && !isspace(buf[i]))
		url[j++] = buf[i++];
	url[j] = 0;
	printf("%s\n", url);
	printf("%s\n", method);

	if( strlen(url) == 1 && *url == '/')
		sprintf(path, "wwwroot%s", url);
	else
		strcpy(path, url+1);
	//GET  or  POST
	if( strcasecmp(method, "GET") != 0 && strcasecmp(method, "POST") != 0)
	{
		ret = -2;
		nums = 404;
		goto end;
	}
	else if( strcasecmp(method, "GET") == 0 )
	{//GET
		//url[];
		// find '?'
		query_string = path;
		while(*query_string != '\n')
		{
			if(*query_string == '?')
			{
				*query_string = '\0';
				query_string++;
				cgi = 1;
				break;
			}
			query_string++;
		}
		printf("qqqqq  %d\n", cgi);
		//
		clear_headler(fd);

		struct stat st;
		printf("%s\n",path);
		if( stat(path, &st) < 0 )
		{

			printf(" NO dir00000\n");
			ret = -3;
			nums = 404;
			goto end;
		}
		else
		{

			printf(" NO dir\n");
			if(S_ISDIR(st.st_mode))
			{
				strcat(path, "index.html");
			}
			else if( (st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH) )
			{
				printf(" NO dir\n");
				cgi = 1;
			}
			else
			{}
		}

		printf("cgi: %d\n", cgi);
		if(cgi == 1)
		{
			exe_cgi(fd, path, method, query_string);
		}
		else
		{
			echo_www(fd, path, st.st_size);
		}
	}
	else
	{//POST
		exe_cgi(fd, path, method, query_string);
	}
end:

	error_headler(nums);
	close(fd);
	return (void*)ret;
}

void exe_cgi(int fd, const char* path, const char* method, const char* query_string)
{
	printf("DDDDDDDDDDDDDd %s DDDDDDDDDDDDDDDD\n", path);
	int s = 0;
	char buf[SIZE];
	int Content_Length = -1;
	if( strcasecmp(method, "POST") == 0 )
	{
		printf("ppost\n");
		do
		{	
			s = readrow(fd, buf, sizeof(buf));
			if(s > 0)
			{
				if( strncasecmp(buf, "Content-Length: ", 16) == 0 )
					Content_Length = atoi(buf+16);
			}

		}while(s != 1 && s > 0);


		recv(fd, buf, Content_Length, 0);
		buf[Content_Length] = 0;
		printf("ZZZZZZZ%sZZZZ\n",buf);
	}
	else{}

	char METHOD[SIZE];
	char QUERY_STRING[SIZE];
	char CONTENT_LENGTH[SIZE];

	pid_t id;


	int input[2];
	int output[2];

	if( pipe(input) < 0 )
		return ;

	if( pipe(output) < 0 )
		return ;

	id = fork();
	printf("sdsdsdsdsdsds\n");
	if(id == 0)
	{//child

		close(input[1]);
		close(output[0]);
		printf("AAAAAAAAAA\n");
		sprintf(METHOD, "METHOD=%s", method);
		putenv(METHOD);
		if(strcasecmp(method, "GET") == 0)
		{
			sprintf(QUERY_STRING, "QUERY_STRING=%s", query_string);
			putenv(QUERY_STRING);
		}
		else
		{
			sprintf(CONTENT_LENGTH, "CONTENT_LENGTH=%d", Content_Length);
			putenv(CONTENT_LENGTH);
		}
		dup2(input[0], 0);
		dup2(output[1], 1);
		execl(path, path, NULL);
		exit(1);
	}
	else if(id > 0)
	{//father
		close(input[0]);
		close(output[1]);
		if( strcasecmp(method, "POST") == 0 )
		{
			write( input[1], buf, strlen(buf) );
		}

		const char *staus_line = "HTTP/1.0 200 OK\r\n";
		const char *blank_line = "\r\n";
		const char *type = "Content-Type:text/html;charset=ISO-8859-1\r\n";
		send(fd, staus_line, strlen(staus_line), 0);
		send(fd, type, strlen(type), 0);
		send(fd, blank_line, strlen(blank_line), 0);

		int i = 0;
		while(i = read(output[0], buf, sizeof(buf)) )
		{
			printf("DDDDDDD\n");
			buf[i] = 0;
			send(fd, buf, strlen(buf), 0);
		}

		waitpid(id, NULL, 0);

		close(input[1]);
		close(output[0]);

	}else
	{
		return ;
	}


}

void echo_www(int fd, char* path, int size)
{
	int new_fd = open( path, O_RDONLY);
	if(new_fd < 0)
	{
		return ;
	}
	printf("zhe shi tu qian\n");
	printf("%s\n", path);
	const char *staus_line = "HTTP/1.0 200 OK\r\n";
	const char *blank_line = "\r\n";
	int s = send(fd, staus_line, strlen(staus_line), 0);
	printf("%d a\n", s);
	s = send(fd, blank_line, strlen(blank_line), 0);
	printf("%d b\n", s);
	s = sendfile(fd, new_fd, NULL, size);
	printf("%d c\n", s);
	close(new_fd);
}


