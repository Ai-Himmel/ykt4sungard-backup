#ifndef _DRTPHELPER_H_
#define _DRTPHELPER_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "ksglobal.h"
#include <string>
#include <exception>
#include "mytypes.h"
#include "CPack.h"
#include "drtplib.h"
#include <ace/Log_Msg.h>

class CDRTPHelper
{
private:
	//<! DRTP ������Ip
	char m_serverIP[32];
	//<! DRTP �������˿ں�
	int m_serverPort;
	//<! DRTP �����ܺ�
	int m_funcNo;
	int m_drtpNo;
	//<! �����ܺ�
	int m_requestType;
	//<! ������Ϣ
	char m_errmsg[512];
	//<! DRTP Handle
	int m_drtpHandle;
	//<! DRTP ����� CPACK ��
	ST_CPACK m_requestPack;
	//<! DRTP Ӧ��� CPACK ��
	ST_CPACK m_responsePack;
	//<! DRTP ���� buffer
	BYTE m_drtpBuf[8192];
	//<! DRTP ����ʱ����� CPACK ����
	ST_PACK	m_dataArray[100];
	//<! �α�ָ��
	ST_PACK* m_currRecord;
	//<! ��ǰ���α�� index
	int m_currIndex;
	//<! DRTP ���ؼ�¼��
	int m_currRecordCount;
	//<! DRTP �����ĳ�ʱʱ��
	int m_timeout;
	//<! �������
	int m_errcode;
	//! ��ʼ��ȡ������ݰ������CPACK��
	void SetNextRequest();
	//<! ��־��� DRTP ������Ϣ
	void logDrtpErrMsg()
	{
		ACE_DEBUG((LM_ERROR,"DRTP����ʧ�ܣ�������[%d]��Ϣ[%s]",m_errcode
			,m_errmsg));
	}
	int testDrtpHandle();
public:
	//! constructor
	/*
	 \param ip DRTP ������IP
	 \param prot DRTP �������˿�
	 \param funcno DRTP ���������ܺ�
	 */
	CDRTPHelper(const char* ip,int port,int funcno,int drtp_no);
	//! destructor
	~CDRTPHelper(void);
	//! ����Drtp����
	int Connect(void);
	//! ����
	void Reset(void);
	//! ���������ͷ��Ϣ
	void SetRequestHeader(int funcno, int first = 1);
	//! ���� CPACK �ֶ�ֵ
	void AddField(int field,const char * value,int len = -1);
	void AddField(int field,int value);
	void AddField(int field,long value);
	void AddField(int field,unsigned long value);
	void AddField(int field,float value);
	void AddField(int field,double value);
	//! �������󣬲����շ�����Ϣ
	/*!
	 \param timeout ��ʱʱ�䣬��λΪ����, Ĭ��Ϊ 100
	 */
	int SendRequest(int timeout = 100);
	//! DRTP ���õĴ�����Ϣ
	std::string GetErrMsg();
	//! DRTP ���ú���Ӧ�÷��������صĴ�����
	int GetReturnCode();
	//! DRTP ���ú���Ӧ�÷��������ص���Ϣ
	std::string GetReturnMsg();
	//! �ж��Ƿ��и��� CPACK ��
	bool HasMoreRecord();
	//! ȡ�õ�ǰ�α�ָ��� CPACK ��Ȼ��ָ����һ��CPACK
	ST_PACK* GetNextRecord();
	//! �ر� DRTP ����
	void Close();
	//////////////////////////////////////////////////////////////////////////
	//! ��ʼ�� DRTP ��Դ
	static int InitDrtp();
	//! �ͷ�DRTP ��Դ
	static void UninitDrtp(); 
};

class DrtpConnectException : public std::exception
{

};
#endif // _DRTPHELPER_H_

