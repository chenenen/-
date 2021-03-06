#include"mycached.h"

Mycached::Mycached(const char* ip,int port)
{
	memc = memcached_create(NULL);
	servers = memcached_server_list_append(NULL,ip,port,&rc);
	rc = memcached_server_free(servers);
}
bool Mycached::InsertValue(const char* key,const char* value,int timeout)
{
	rc = memcached_set(memc,key,strlen(key),value,strlen(value),(time_t)timeout,(uint32_t)0);
	if(rc == MYMCACHED_SUCCESS)
	{
		cout<<"Insert success!"<<endl;
		cout<<"Insert key:"<<key<<"value:"<<value<<endl;
	}
	else
	{
		return false;
	}
	return true;
}

char* Mycached::GetValue(const char* key)
{
	if(key == NULL)
		return NULL;
	char* value = NULL;

	value = memcached_get(memc,ky,strlen(key),&valuesize,&flags,&rc);
	if(rc == MEMCACHED_SUCCESS)
	{
		cout<<"Get key:"<<key<<"value:"<<value<<endl;
		return value;
	}
	return NULL;
}

bool Mycached::DeleteKey(const char* key)
{
	rc = memcached_delete(memc,key,strlen(key),time_t(0));
	if(rc == MEMCACHED_SUCCESS)
	{
		cout<<"Delete key:"<<key<<endl;
	}
	return false;
}

Mycached::~Mycached()
{
	memcached_free(memc);
}









