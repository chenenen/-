#include "httpd.h"
#include<pthread.h>

static void usage(char* argv)
{
	printf("please enter # [%s] [lacol_ip] [local_port]\n", argv);
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		exit(1);
	}

	int listen_sock = start_up(argv[1], atoi(argv[2]));
//	daemon(1,0);
	while(1)
	{
		struct sockaddr_in client;
		socklen_t len = sizeof(client);

		long new_fd = accept(listen_sock, (struct sockaddr*)&client, &len);
		if(new_fd < 0)
		{
			perror("accept");
			continue;
		}
		printf("client: [%s] [%d]\n",inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		pthread_t id = 0;
		pthread_create(&id, NULL, (void*)&headler_request, (void*)new_fd);
		pthread_detach(id);
	}
	return 0;
}

