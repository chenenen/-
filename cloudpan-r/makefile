.PHONY:clean all
exec:
	g++ -o client myclient.cpp my_MD5.cpp
	g++ -o server myserver.cpp MyDB.cpp -I /usr/include/libmemcached/include -L/usr/include/libmemcached/lib -L/usr/lib/mysql -lmysqlclient -lmemcached -lpthread --std=gnu++0x;
	g++ -o FTS fileTrans.cpp my_MD5.cpp MyDB.cpp -I /usr/include/libmemcached/include -L/usr/include/libmemcached/lib -L/usr/lib/mysql -lmysqlclient -lmemcached -lpthread --std=gnu++0x;
clean:
	rm -f *.o;
	rm -f *~;
	rm .a;
