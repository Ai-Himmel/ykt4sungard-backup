#pragma once

#include "logfile.h"
#include "Kdbc.h"

#define STX 0x02		//开头
#define ETX 0x03		//结尾
#define TIMEOUT 5		//秒

typedef struct 
{
	char reqno[3];
	char deviceid[4];
	char cardid[12];
	char tradeamt[7];
	char serialno[7];
	char cardbala[11];
	char tradecount[6];
	char bankno[20];
}COMM_REQ;

typedef struct  
{
	char reqno[3];
	char deviceid[4];
	char key[33];
	char cardbala[11];
	char respno[3];
}COMM_RES;


class DataParse
{
private:
	char m_RecvData[1024];
	int  m_RecvLen;
	char m_SendData[1024];
	int  m_SendLen;
//	int s_PreRecvLen;
	
	COMM_REQ comm_req;
	COMM_RES comm_res;

	FIELDMAP *m_deviceIDMap;
	FIELDMAP accMap;

	CKdbc kdbc;

public:
	DataParse(void);
	~DataParse(void);
	KSYkt_Log_Writer m_logWriter;					//日志类
	void SetDeviceIDMap(FIELDMAP *deviceIDMap);
	int Recv(char *buf,int bufLen);
	int GetResponse();
	int Send(char *buf,int &bufLen);
	void Flush();
};
