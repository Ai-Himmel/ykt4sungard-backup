#ifndef _KS_SERIALPORT_H_
#define _KS_SERIALPORT_H_

#include <Windows.h>

class KS_SerialPort
{
private:
	int portno_;
	int baud_;
	HANDLE com_handle_;
	int do_read(unsigned char *buf,size_t maxlen,size_t timeout,OVERLAPPED &m_ov);
public:
	KS_SerialPort(int portno,int baud);
	~KS_SerialPort();
	int open();
	void close();
	int read(unsigned char *buf,size_t maxlen,size_t timeout);
	int write(const unsigned char *buf,size_t buflen,size_t timeout);

};

#endif // _KS_SERIALPORT_H_

