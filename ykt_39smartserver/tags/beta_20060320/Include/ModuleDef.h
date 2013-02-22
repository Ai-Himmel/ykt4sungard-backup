//*---------------------------------------------------------------------
//* �ļ�����:  ModuleDef.h
//* ʵ�ֹ���:  ��ҵĲ��, ҵ���, Э�����˵��
//* ��Ȩ˵��:  �����ǻ۵������޹�˾  .  2004.02 - 03 
//* ˵    ��:
//*            1. �������е�ҵ���Ľӿ�
//*            2. ����������ṩ��ҵ����API
//*            3. ���幫���Ľṹ������
//*            4. �����ն˴����Ľӿ�
//*            5. ����Э��ӿ�
//*---------------------------------------------------------------------
#ifndef __MODULE_DEF_H__
#define __MODULE_DEF_H__

#pragma once

//������Ϣ
#define RET_SUCCESS       0		//�ɹ�����
#define RET_ERROR        -1		//ʧ�ܷ���
#define RET_TIMEOUT      -2     //��ʱ����
#define RET_TERMINATE    -3     //ִ�б��жϷ���
#define RET_END_OK       -10    //����ɹ�������
#define RET_END_NG       -11    //����ʧ�ܲ�����

//����������
#define MODULE_TYPE_APPLAYER		0x01			//ҵ����
#define MODULE_TYPE_PROTOCOL        0x02            //Э�鴦��
#define MODULE_TYPE_DRIVER          0x03            //�豸����
#define MODULE_TYPE_TASK            0x04            //����������

//�������汾��Ϣ
struct TSPlusInVersion
{
	char   szCompany[128];			//��˾����
	char   szMajorVersion[16];		//���汾
	char   szMinorVersion[16];		//�ΰ汾
	char   szAuthor[32];			//����
	char   szCreateDate[24];		//��������
	char   szModifyDate[24];		//����޸�����
	char   szFunction[128];        //ʵ�ֵĹ���
};

//************************************************************************************
//*����: TSSmartFixInfo
//*����: ҵ��ģ�鴫�뵽��������ϵͳ�̶���Ϣ
//************************************************************************************
struct TSSmartFixInfo
{
	char  cHeadFlag;		//��ͷ�ַ�
	char  cEndFlag;			//��β�ַ�
	long  nPacketSize;      //���ĳ���
	long  nScanTask;		//���������������(����), Ĭ��Ϊ1000
	long  nSmartDocSize;    //�豸�����ṹ��С
	long  nTaskDocSize;     //����ṹ��С
	char  sReserved1[64];   //����1
	char  sReserved2[64];   //����2
	char  sReserved3[64];   //����3
	long  nReserved1;       //����1
	long  nReserved2;       //����2
	long  nReserved3;       //����3
};


//************************************************************************************
//*����: TSSmartDoc
//*����: 999�ն�����
//************************************************************************************
struct TSSmartDoc
{
	char	m_szMacCode[8];				//�ն˻��ͺŴ���
	char	m_szMacCard[64];			//����IC������
	char	m_szMacModle[8];			//�ն˻��ͺ�
	char	m_szMacType[24];			//��������

	long    m_nAuthID;					//��Ȩ��
	char	m_szDeviceID[16];			//�豸ID
	char	m_szRegister[16];			//ע���
	long	m_nMachineNo;				//����	
	char	m_szVersion[8];				//�豸�汾��
	char	m_szPassword[8];			//ϵͳԱ����

	char	m_szPort[32];				//ͨѶ�˿�
	long	m_nBaudRate;				//������
	long	m_nConnType;				//ͨѶ��ʽ(��/��)

	long	m_nPortCount;				//�������˿�����
	long	m_nSMTPort;					//�������˿ں�

	long	m_nCommMode;				//��·ģʽ
	long	m_nOnNet;					//�Ƿ�����
	long	m_nOnline;					//�Ƿ���������

//----------����Ϊͳ����Ϣ--------------------------//
	char	m_szStartTime[24];			//��ʱ��
	char	m_szStopTime[24];			//ֹͣʱ��
	int     m_nCurStatus;				//��ǰ״̬
	long    m_nReadBytes;				//�����ֽ�
	long    m_nWriteBytes;				//д���ֽ�
	long    m_nReadError;				//���������
	long	m_nWriteError;				//д�������
	long	m_nTimeError;				//ʱ���쳣����
	long    m_nRate;					//�ٶ��ֽ�/��, (����)
};

//�½�����ʱ����
struct TSSmartBuffer
{
	long    m_nTaskType;					//��������
	long	m_nBufferSize;					//���صĻ��������ݳ���
	char    m_lpBuffer;						//���صĻ���������
	char	m_lpCmdBuffer;					//���ص�������
	bool	m_bFirstWrite;					//�״��Ƿ�Ϊ����
	long	m_nStepLevel;					//�����Ϊ����(��ʱδ��,Ҫ������)
};

//�ص�������Ϣ
struct TSSmartCallInfo
{
	bool	bSaveToDB;				//�Ƿ񱣴浽���ݿ�
	char	szSQL[1024];			//SQL���
	bool	bMark;					//�Ƿ������
	char	pszMarkBuffer;			//����ǵ�������
	long	nMarkLength;			//��������еĳ���
	bool	bEndOperFlag;			//�����������
};

////////////////////////////////////////////////////////////////////////////////////
//����ΪSmartService�ܹ��ṩ��API
////////////////////////////////////////////////////////////////////////////////////

//*=================================================================================
//ԭ��:  long GetDBHandle(long nTimeOut)
//*����: �õ�һ�����е����ݿ���
//*����: 
//*      nTimeOut:   ��ʱʱ��(�����ָ����nTimeOut���޿��е����ݿ�,�򷵻ش���
//*����: 
//*      < 0 :    ʧ��
//*      = 0 :    ��ʱ(�޿��е�����,���Ժ�����)
//*=================================================================================
typedef long (*lpfnGetDBHandle)(long nTimeOut);

//*=================================================================================
//ԭ��:  void FreeDBHandle(long nHandle)
//*����: �ͷ�һ��ռ�õ����ݿ���
//*����: 
//*      nHandle: ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*����: 
//*      ��
//*=================================================================================
typedef void (*lpfnFreeDBHandle)(long nHandle);

//*=================================================================================
//ԭ��:  long ExecuteQuery(long nHandle, char *pszSQL);
//*����: ��ѯ���ݿ�
//*����: 
//*      nHandle:  ���ݿ���
//*      pszSQL:   SQL���
//*����: 
//*      > 0 :    ��¼�����
//*      <=0 :    ��ѯʧ��
//*=================================================================================
typedef long (*lpfnExecuteQuery)(long nHandle, char *pszSQL);

//*=================================================================================
//ԭ��:  void CloseRecHandle(long nHandle, long nRecHandle)
//*����: �ͷ�һ���򿪵ļ�¼�����
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      ��
//*=================================================================================
typedef void (*lpfnCloseRecHandle)(long nHandle, long nRecHandle);


//*=================================================================================
//ԭ��:  int IsOpen(long nHandle, long nRecHandle)
//*����: ��¼���Ƿ��
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      > 0 :  �Ѵ�
//*      <=0 :  ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnIsOpen)(long nHandle, long nRecHandle);

//*=================================================================================
//ԭ��:  int IsBOF(long nHandle, long nRecHandle)
//*����: ����Ƿ��ڼ�¼����
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      > 0 :  ��
//*      =0  :  ����
//*      < 0 :  ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnIsBOF)(long nHandle, long nRecHandle);


//*=================================================================================
//ԭ��:  int IsEOF(long nHandle, long nRecHandle)
//*����: ����Ƿ��ڼ�¼��β
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      > 0 :  ��
//*      =0  :  ����
//*      < 0 :  ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnIsEOF)(long nHandle, long nRecHandle);

//*=================================================================================
//ԭ��:  int MoveFirst(long nHandle, long nRecHandle);
//*����: ����Ƶ���¼����
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      > 0 :  �ɹ�.
//*      <= 0 : ���ɹ�. ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnMoveFirst)(long nHandle, long nRecHandle);

//*=================================================================================
//ԭ��:  int MoveLast(long nHandle, long nRecHandle);
//*����: ����Ƶ���¼��β
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      > 0 :  �ɹ�.
//*      <= 0 : ���ɹ�. ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnMoveLast)(long nHandle, long nRecHandle);

//*=================================================================================
//ԭ��:  int MoveNext(long nHandle, long nRecHandle);
//*����: �������һ����¼
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      > 0 :  �ɹ�.
//*      <= 0 : ���ɹ�. ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnMoveNext)(long nHandle, long nRecHandle);

//*=================================================================================
//ԭ��:  int MovePrev(long nHandle, long nRecHandle);
//*����: �������һ����¼
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      > 0 :  �ɹ�.
//*      <= 0 : ���ɹ�. ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnMovePrev)(long nHandle, long nRecHandle);

//*=================================================================================
//ԭ��:  int GetFieldCount(long nHandle, long nRecHandle)
//*����: �õ��ֶ���
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      > 0 :  �ֶ���
//*      <= 0 : ���ɹ�. ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnGetFieldCount)(long nHandle, long nRecHandle);

//*=================================================================================
//ԭ��:  long GetRecordCount(long nHandle, long nRecHandle)
//*����: �õ���¼��
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      >= 0 :  ��¼��
//*      < 0 : ���ɹ�. ��¼���ѹرջ��д�
//*=================================================================================
typedef long (*lpfnGetRecordCount)(long nHandle, long nRecHandle);


//*=================================================================================
//ԭ��:  int GetFieldName(long nHandle, long nRecHandle, int nIndex, char *pszRetFieldName)
//*����: �õ��ֶ���
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*      nIndex:     �ֶε�����.  
//*      pszRetFieldName:  ���ص��ֶ�����
//*����: 
//*      > 0 :  �ɹ�
//*      <= 0 : ���ɹ�. ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnGetFieldName)(long nHandle, long nRecHandle, int nIndex, char *pszRetFieldName);

//*=================================================================================
//ԭ��:  int GetFieldValue(long nHandle, long nRecHandle, int nIndex, char *pszRetFieldValue);
//*����: �õ��ַ����ֶε��ֶ�ֵ
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*      nIndex:     �ֶε�����.  
//*      pszRetFieldValue:  ���ص��ֶ�ֵ
//*����: 
//*      > 0 :  �ɹ�
//*      <= 0 : ���ɹ�. ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnGetFieldStringValue)(long nHandle, long nRecHandle, int nIndex, char *pszRetFieldValue);

//*=================================================================================
//ԭ��:  int GetFieldValue(long nHandle, long nRecHandle, char *sFieldName, char *pszRetFieldValue);
//*����: �õ��ַ����ֶε��ֶ�ֵ
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*      sFieldName:     �ֶ�����.  
//*      pszRetFieldValue:  ���ص��ֶ�ֵ
//*����: 
//*      > 0 :  �ɹ�
//*      <= 0 : ���ɹ�. ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnGetFieldStringValueEx)(long nHandle, long nRecHandle, char *sFieldName, char *pszRetFieldValue);


//*=================================================================================
//ԭ��:  int GetFieldValue(long nHandle, long nRecHandle, char *sFieldName, char *pszRetFieldValue);
//*����: �õ�����,������, �ֶε��ֶ�ֵ
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*      sFieldName:     �ֶ�����.  
//*      nRetFieldValue:  ���ص��ֶ�ֵ
//*����: 
//*      > 0 :  �ɹ�
//*      <= 0 : ���ɹ�. ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnGetFieldLongValue)(long nHandle, long nRecHandle, int nIndex, long *nRetFieldValue);
typedef int (*lpfnGetFieldLongValueEx)(long nHandle, long nRecHandle, char *sFieldName, long *nRetFieldValue);


//*=================================================================================
//ԭ��:  int GetFieldValue(long nHandle, long nRecHandle, char *sFieldName, char *pszRetFieldValue);
//*����: �õ�������, ���, �ֶε�ֵ.
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*      sFieldName:     �ֶ�����.  
//*      nRetFieldValue:  ���ص��ֶ�ֵ
//*����: 
//*      > 0 :  �ɹ�
//*      <= 0 : ���ɹ�. ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnGetFieldFloatValue)(long nHandle, long nRecHandle, int nIndex, float *nRetFieldValue);
typedef int (*lpfnGetFieldFloatValueEx)(long nHandle, long nRecHandle, char *sFieldName, float *nRetFieldValue);

//*=================================================================================
//ԭ��:  int GetFieldValue(long nHandle, long nRecHandle, char *sFieldName, char *pszRetFieldValue);
//*����: �õ��߾����ֶε�ֵ. ��С��λ�ϸߵ��ֶ�
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*      sFieldName:     �ֶ�����.  
//*      nRetFieldValue:  ���ص��ֶ�ֵ
//*����: 
//*      > 0 :  �ɹ�
//*      <= 0 : ���ɹ�. ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnGetFieldDoubleValue)(long nHandle, long nRecHandle, int nIndex, double *nRetFieldValue);
typedef int (*lpfnGetFieldDoubleValueEx)(long nHandle, long nRecHandle, char *sFieldName, double *nRetFieldValue);

//��λ����ǰ�ֶ�
typedef int (*lpfnLocate)(long nHandle, long nRecHandle, char *sFieldName, char *sValue);


//*=================================================================================
//ԭ��:  int ExecuteSQL(long nHandle, char *pszSQL);
//*����: ִ��DDL SQL���
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      pszSQL:    SQL���
//*����: 
//*      > 0 :  �ɹ�
//*      <=0 :  ʧ��
//*=================================================================================
typedef int (* lpfnExecuteSQL)(long nHandle, char *pszSQL);

//*===========================================================================================================================
//*ԭ��: long SmartExecute(long nAuthID, unsigned char *pszCmdBuffer, 
//*             long  nCmdBufferSize, unsigned char *pszRetBuffer, 
//*             long* nRetSize, long  nTimeOut);
//*����: ִ��һ���豸����,���õ����ؽ��
//*����: 
//*      nAuthID:        �豸ID��ʶ
//*      pszCmdBuffer:   ��������������
//*      nCmdBufferSize: �������������ݳ���
//*      pszRetBuffer:   ���صĽ��
//*      nRetSize:       ���ؽ���ĳ���
//*      nTimeOut:       ����ִ�еĳ�ʱʱ��
//*����: 
//*      >  0 :   ִ�гɹ�
//*      <= 0 :   ִ��ʧ��
//*=================================================================================
typedef long (*lpfnSmartExecute)(
				long nAuthID, 
				unsigned char *pszCmdBuffer, 
				long  nCmdBufferSize, 
				unsigned char *pszRetBuffer,
				long* nRetSize, 
				long  nTimeOut);


//*===========================================================================================================================
//*����: TSSmartFunction
//*����: SmartService�ṩ��ҵ��ӿڲ��API��
//*===========================================================================================================================
struct TSSmartFunction
{
	lpfnGetDBHandle				fnGetDBHandle;
	lpfnFreeDBHandle			fnFreeDBHandle;
	lpfnExecuteQuery			fnExecuteQuery;
	lpfnCloseRecHandle			fnCloseRecHandle;
	lpfnIsOpen					fnIsOpen;
	lpfnIsBOF					fnIsBOF;
	lpfnIsEOF					fnIsEOF;
	lpfnMoveFirst				fnMoveFirst;
	lpfnMoveLast				fnMoveLast;
	lpfnMoveNext				fnMoveNext;
	lpfnMovePrev				fnMovePrev;
	lpfnGetFieldCount			fnGetFieldCount;
	lpfnGetRecordCount			fnGetRecordCount;
	lpfnGetFieldName			fnGetFieldName;
	lpfnGetFieldStringValue		fnGetFieldStringValue;
	lpfnGetFieldStringValueEx	fnGetFieldStringValueEx;
	lpfnGetFieldLongValue		fnGetFieldLongValue;
	lpfnGetFieldLongValueEx		fnGetFieldLongValueEx;
	lpfnGetFieldFloatValue		fnGetFieldFloatValue;
	lpfnGetFieldFloatValueEx	fnGetFieldFloatValueEx;
	lpfnGetFieldDoubleValue		fnGetFieldDoubleValue;
	lpfnGetFieldDoubleValueEx	fnGetFieldDoubleValueEx;
	lpfnLocate					fnLocate;
	lpfnExecuteSQL				fnExecuteSQL;
	lpfnSmartExecute			fnSmartExecute;
};

////////////////////////////////////////////////////////////////////////////////////
//����Ϊҵ���ܻص�ԭ��
////////////////////////////////////////////////////////////////////////////////////

//*=================================================================================
//*ԭ��: long InitModule(TSSmartFixInfo *pSmartFixInfo, long *nFlag);
//*����: ��ʼ��ҵ����ģ��, ��װ������/��ʼ������
//*����: 
//*      pFunction, �����������API��ַ
//*      pSmartFixInfo,  ���صķ���������
//*      nFlag, ҵ���ܵı�־
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================
typedef long (* lpfnInitModule)(TSSmartFunction *pFunction, TSSmartFixInfo *pSmartFixInfo, long *nFlag);


//*=================================================================================
//*ԭ��: long ReadSmartDocInfo(void **pSmartDoc, long *nDocCount);
//*����: ��ʼ��ҵ����ģ��, ��װ������/��ʼ������
//*����: 
//*      lpKeyBuffer, ��Ȩ�ַ���(����)
//*      dwFlag, ҵ���ܵı�־
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================
typedef long (* lpfnReadSmartDocInfo)(void **pSmartDoc, long *nDocCount);

//*=================================================================================
//*����: ���ҵ����ģ��, �˳�DLLʱ����
//*����: 
//*      ��
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================
typedef LONG (* lpfnDestoryModule)();

//*=================================================================================
//*����: ������һ������ʱ����, ��ʱ����������������
//*����: 
//*       pSmartDoc:     �ն���Ϣ
//*       pDocArray:     �ն˼�������
//*       nArrayLength:  ��������
//*       pSmartBuffer:  ���ص���Ϣ
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================
typedef LONG (* lpfnCreateTaskBuffer)(TSSmartDoc *pSmartDoc, TSSmartDoc *pDocArray[], LONG nArrayLength, TSSmartBuffer  *pSmartBuffer);

//*=================================================================================
//*����: ���ն˽������ݺ�Ĵ���(ʵ�ֽ��, ����SQL��)
//*����: 
//*      �������˵��
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================
typedef LONG (*lpfnRecvProcess)(
				TSSmartDoc *pSmartDoc,	 //�ն���Ϣ
				TSSmartDoc *pDocArray[], //�ն˼�������
				LONG nArrayLength,		 //��������
				LONG nTaskType,			 //��������
				LPTSTR pszBuffer,		 //���յ���������, �践�ؽ�����������
				DWORD *dwBufferSize,	 //���յ����ݳ���, ������䳤���践��
				TSSmartCallInfo *pSmartInfo);


//*=================================================================================
//*����: Э��Ľ��,���
//*����: 
//*      �������˵��
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================





#endif //__MODULE_DEF_H__
