/*=================================================================
Copyright (C) 2005 - 2006 �㶫�����ǻ۵�����Ϣ��ҵ���޹�˾
File name:    smartlog.h
Author:       DengJun
Version:      1.0
Date:         2006.5
Description:  
Others:       
Revision history:
	1:
	Date:
	Author:
	Modifiacation:	
=================================================================*/
#ifndef __SMARTLOG__H_
#define __SMARTLOG__H_

#include "smartcommunication.h"
#include "smartcommunicationdlg.h"

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
};

#endif