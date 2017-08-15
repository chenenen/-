.PHONY:clean all
exec:
	g++ -o ser Myserver.cpp MyDB.cpp -I /usr/include/libmemcached/include -L/usr/include/libmemcached/lib -L/usr/lib/mysql -lmemcached -lpthread --std=gnu+0x;
	g++ -o FTS FileTrans.cpp md5.cpp MyDB.cpp -I/usr/include/libmemcached/include -L/usr/include/libmemcached/lib -L/usr/lib/mysql -lmysqlclient -lmemcached -lpthread --std=gnu++0x;

clean:
	rm -f *.o
	rm -f *-;
	rm *.a;
