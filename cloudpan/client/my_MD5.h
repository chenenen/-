#ifndef _MD5_H_
#define _MD5_H_

#include<fstream>
#include<string>

typedef unsigned char byte;
typedef unsigned int uint32;

using std::string;
using std::ifstream;

class MD5
{
public:
	MD5();
	MD5(const void* input,size_t length);
	MD5(const string& str);
	MD5(ifstream& in);
	void uodate(const void* input,size_t length);
	void update(ifstream& in);
	const byte* digest();
	string toString();
	void reset();
private:
	void update(const byte* input,size_t length);
	void final();
	void transform(const byte block[64]);
	void encode(const uint32*inout,byte* output,size_t length);
	void decode(const byte*input,uint32* output,size_t length);
	string bytesToHexString(const byte* input,size_t length);
	MD5(const MD5&);
	MD5& operator=(const MD5&);
private:
	uint32 _state[4]; //ABCD四种状态
	uint32 _count[2]; //比特位的数
	byte _buffer[6];  //输入缓冲区
	byte _digest[16]; //信息摘要
	bool _finished;  //是否完成计算

	static const byte PADDING[64];
	static const char HEX[16];
	enum {BUFFER_SIZE=1024};
};

#endif
