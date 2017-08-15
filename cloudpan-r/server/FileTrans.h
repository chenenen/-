#ifndef _FILETRANS_H_
#define _FILETRANS_H_

FileTrans(int port,const char* addr);
~FileTrans();
void Run();
void getCmd();
void getFileInfo();
void sendFileInfo();
bool recvFile();
void sendFile();
void removeFile();
void createFile();
void showFileList();



#endif
