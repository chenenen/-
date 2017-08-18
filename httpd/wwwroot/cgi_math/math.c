#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void mymath(char *buf)
{
	char *arr[3];
	int i = 0;
	int data1;
	int data2;
	while(*buf != '\0')
	{
		if(*buf == '=')
		{
			buf++;
			arr[i++] = buf;
		}
		if(*buf == '&')
		{	
			*buf = '\0';
		}
		buf++;
	}
	*arr[i] = '0';
	data1 = atoi(arr[0]);
	data2 = atoi(arr[1]);
	printf("<html><b>");
	printf("<h1>%d + %d = %d\n</h1>", data1, data2, data1+data2);
	printf("<h1>%d - %d = %d\n</h1>", data1, data2, data1-data2);
	printf("<h1>%d * %d = %d\n</h1>", data1, data2, data1*data2);
	printf("<h1>%d / %d = %d\n</h1>", data1, data2, data2==0?0:data1/data2);
	printf("<h1>%d %% %d = %d\n</h1>", data1, data2, data1%data2);
	printf("</b></html>");

}
int main()
{
	char *method = getenv("METHOD");
	char buf[1024];
	char c;
	char *query_string;
	char *content_length;
	if(method)
	{
		if( strcasecmp(method, "GET") == 0 )
		{//GET
			query_string = getenv("QUERY_STRING");
			strcpy(buf, query_string);
		}
		else
		{//POST

			content_length = getenv("CONTENT_LENGTH");
			int length = atoi(content_length);
			int i = 0;
			for(; i < length; i++)
			{
				read(0, &c, 1);
				buf[i] = c;
			}
			buf[i] = 0;
		}
		mymath(buf);
	}
	return 0;
}
