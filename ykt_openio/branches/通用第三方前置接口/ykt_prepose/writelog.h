/*=================================================================
Copyright (C) 
File name:    writelog.h
Author:       
Version:      1.0
Date:         
Description:  
Others:       
Revision history:
	1:
	Date:
	Author:
	Modifiacation:	
=================================================================*/


class CMyLog
{
public:
	CMyLog();
	~CMyLog();	
	void WriteDeviceLog( char* cpath, char* ucpID,char* str);
	bool WriteDeviceData(char* cpath, char* ucpID,char* str);
	void WriteDeviceRateLog(char* cpath, char* ucpID,char* msg,char* cfilename);
	void WriteSysLog(char* cpath, char* msg);
	void WriteDeviceSQL(char* cpath, char* ucpID,char* msg);
	void WriteDeviceMaxMoney(char* cpath, char* ucpID,char* msg);
	void CheckIsChangeYear(char* cpath);
	bool SMT_GetLastInvoiceNo(char* sID, int *nInvoiceNo );
	void Writedata(char* cpath,char*filename, char* msg);
	void readdata(char* cpath,char*filename, char* msg);
	int isDirExist( char *   path );
	void  deldata(char* cpath,char*filename);
};

