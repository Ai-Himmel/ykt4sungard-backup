#pragma once
#include <stdio.h>
#include "tcp.h"
#include "pubfunc.h"

class Cdeposit
{
public:
	Cdeposit(void);
	virtual ~Cdeposit(void);
	int genMessage(char *reqcode,char *account,char *psword,char* tradetime,double amount,int serino);
	int parseMessage(double &bala,char *pRescode);
	int send();
	int recv();
	bool isConnected();
private:
	CTcpSocket tcpSocket;
	char message[512];
	bool genMac(char *buf,char *maccheck);
	int checkMac();
};
