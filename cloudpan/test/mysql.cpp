#include"mysql.h"
#include<iostrem>
using namespace std;
MyDB()
{
	connection = mysql_init(NULL);
	if(connection == NULL)
	{
		cout<<"mysql connect filed!"<<endl;
		exit(1);
	}
}

~MyDB()
{
	if(connection != NULL)
	{
		mysql_close(connection);
	}
}

bool InitDB(string host,string user,string passwd,string DBname)
{
	connection = mysql_real_connect(connection,host.c_str(),user.c_str(),password.c_str(),DBname.c_str(),0,NULL);

	if(connection == NULL)
	{
		cout<<"Error"<<mysql_error(connection)<<endl;
		exit(1);
	}
	return true;
}

bool MyDB::execSQL(string sql)
{
	int i,j;
	if(mysql_query(connection,sql.c_str()))
	{
		cout<<"Query Error"<<mysql_error(connection)<<endl;
		exit(1);
	}else
	{
		result = mysql_use_result(connection);//获取结果集
		for(i=0;i<mysql_field_count(connection);++i)
		{
			//获取下一行
			row = mysql_fetch_row(result);
			if(row <= 0)
				break;
			for(j=0;j<mysql_num_fields(result);++j)
			{
				cout<<row[j]<<" ";
			}
			cout<<endl;
		}
		//释放结果集的内存
		mysql_free_result(result);
	}
	return true;
}

int main()
{
	MyDB db;
	db.InitDB("localhost","root","cherlene","FTP");
	cout<<"查询表user的信息"<<endl;
	db.execSQL("select * from user;");
	cout<<"查找用户‘cherlene’的文件列表"<<endl;
	db.execSQL("select user_id,filename,size,type from user,files where user.user_id='cherlene' and user.file_id=files.id;");
	cout<<"查找用户‘cherlene’的好友列表"<<endl;
	db.execSQL("select user.user_id,friends.user_id from user,friends where user.user_id='cherlene' and user.friends_id=friends.id;");
	return 0;
}
