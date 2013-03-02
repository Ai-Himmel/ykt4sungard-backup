#ifndef __SMARTTERMINAL_H__
#define __SMARTTERMINAL_H__

#pragma once

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////////////////////
//////���¶����������ķ���ֵ
//////////////////////////////////////////////////////////////////////////////////////////

#define RET_DATAVALUE_ERROR            -1       //-1:���ݳ��Ȳ���ֵ̫�����ڸ�ֵ,
#define RET_RECV_ERROR                 -2       //-2:�������ݴ�����û�д򿪼�ͨѶ��
#define RET_SEND_ERROR                 -3       //-3:�������ݴ�����û�д򿪼�ͨѶ��
#define RET_RECV_TIMEOUT               -4       //-4:�������ݳ�ʱ;
#define RET_ADDR_ERROR                 -5       //-5:���ص�ַ��ƥ��
#define RET_TERME_NOANSWER             -6       //-6:�ն��޷�Ӧ
#define RET_COMMONU_ERROR              -7       //-7:���ڴ�/�رմ�
#define RET_DATALENGTH_ERROR           -8       //-8�������ݳ��ȴ���
#define RET_DATACRC_ERROR              -9       //-9:����У���
#define RET_PARAMETER_ERROR1           -10      //-10:���������
#define RET_OK                          0       //0���ɹ�
#define RET_CARD_INVALID                1       //1:�Ƿ���
#define RET_CLOCK_ERROR                 2       //2:ʱ�Ӵ�
#define RET_MONEY_FORMAT_ERROR          3       //3:Ǯ����ʽ��
#define RET_DATA_FULL                   4       //4:������
#define RET_SEQNUM_ERROR                5       //5:��ˮ�Ŵ�
#define RET_PARAMETER_ERROR2            7       //7:���������
#define RET_COMMAND_ERROR               8       //8:�޴�����������޷���ʱʹ��
#define RET_REMARK_ERROR                9       //9:�ظ�����
#define RET_NO_RECORD                   10      //10:�޼�¼������
#define RET_AUTHNO_ERROR                11      //11:��Ȩ�Ų���
#define RET_REQU_SIGNIN                 13      //13:����ǩ��
#define RET_BLACKLIST_ERROR             14      //14:��������Ч�ڹ���
#define RET_CARD_MONEY_ENOUGH           15      //15:���ڽ���
#define RET_RECORD_NO_COLLECT           17      //17:���м�¼δ�ռ�
#define RET_CARD_DEGREE_ERROR           18      //18:��ʹ�ô�������
#define RET_CARD_EXPECT_ERROR           19      //19:��Ƭ�ѹ���Ч��
#define RET_CARD_MONEY_LARGE            20      //20:��Ƭ���̫��
#define RET_CARD_SEQOVER                22      //22:�ѽ��ʵĽ�����ˮ�ѱ�����(�޷�����)
#define RET_ACCREC_NOTUP                23      //23:���н��˼�¼δ�ϴ�
#define RET_NOT_AUTH                    24      //24:�豸δ��Ȩ�޷�ǩ��

#define NETWORK_PAR_NONE                0       //ֱ��
#define NETWORK_PAR_STAR                1       //����
#define NETWORK_PAR_BUS                 2       //����




#define   RET_OK		0
#define   RET_ERROR		-1
#define   TCPIP         0
#define   SERIAL        1
#define   MODEM         2

#define   STX1          0xC0
#define   STX2          0xC1
#define   ETX1          0xC2
#define   ETX2          0xC3

//*------------------------------------------------------------------------------------
//*����: TSDeviceInfo
//*����: �豸��Ϣ(��������ʱ��)
//*------------------------------------------------------------------------------------
struct TSDeviceInfo
{
	long nAuthID;                   //������Ȩ��
	char sRegNo[16];					//����ע���
	int  nHardware;                 //Ӳ������
	char sVersion[24];              //Ӳ���汾��
	int  nAddr;                     //��������(0-255) 0��ʾ�㲥ͨѶ
	int  nNetPar;                   //����ṹ: ֱ��, ����, ����
	int  nLevel;					//�ն��豸�����ӵ����ݷ������ļ�����
	unsigned char sLevelArray[32];	//��������
	int  nTotalNo;                  //�ն˻�������
	int  nPort;                     //���͵�ǰͨѶ�˿� ���ߵ�ǰͨѶ��������
	int  nNoReponseTime;            //�ն��޷�Ӧ����
};

//*------------------------------------------------------------------------------------
//*����: TSCmdBuffer
//*����: ���ص����������
//*------------------------------------------------------------------------------------
struct TSCmdBuffer
{
	int nBufferSize;					//����Ļ������ĳ���
	unsigned char *pBuffer;             //����Ļ�����
	int nCmdSize;                       //���ص����������
	long  nTimeOut1;                    //���صĳ�ʱʱ��1
	long  nTimeOut2;                    //���صĳ�ʱʱ��2
};

#ifdef __OLD_COMMON_DEF_H__
//*------------------------------------------------------------------------------------
//*����: TSDeviceInfo
//*����: �豸��Ϣ(��������ʱ��)
//*------------------------------------------------------------------------------------
struct TSDeviceInfo
{
	long nAuthID;                   //������Ȩ��
	char sRegNo[16];					//����ע���
	int  nHardware;                 //Ӳ������
	char sVersion[24];              //Ӳ���汾��
	int  nAddr;                     //��������(0-255) 0��ʾ�㲥ͨѶ
	int  nNetPar;                   //����ṹ: ֱ��, ����, ����
	int  nLevel;					//�ն��豸�����ӵ����ݷ������ļ�����
	unsigned char sLevelArray[32];	//��������
	int  nTotalNo;                  //�ն˻�������
	int  nPort;                     //���͵�ǰͨѶ�˿� ���ߵ�ǰͨѶ��������
	int  nNoReponseTime;            //�ն��޷�Ӧ����
};

//*------------------------------------------------------------------------------------
//*����: TSCmdBuffer
//*����: ���ص����������
//*------------------------------------------------------------------------------------
struct TSCmdBuffer
{
	int nBufferSize;					//����Ļ������ĳ���
	unsigned char *pBuffer;             //����Ļ�����
	int nCmdSize;                       //���ص����������
	long  nTimeOut1;                    //���صĳ�ʱʱ��1
	long  nTimeOut2;                    //���صĳ�ʱʱ��2
};

#endif //#ifdef __OLD_COMMON_DEF_H__

//--------------------
//*����: TSSmartProtocol
//*����: ͨѶЭ�������
//--------------------
struct TSSmartProtocol
{
    unsigned char  PTHead[8];        //����ʼ������(ĿǰΪC2)
    unsigned short PTHeadLen;        //����ʼ������(ĿǰΪ1)
	unsigned char  PTTail[8];        //������������(ĿǰΪC3)
    unsigned short PTTailLen;        //������������(ĿǰΪ1)
	unsigned int   nLenOffset;       //���ݰ�����ƫ��(0..n)
	unsigned short nLenSize;         //�����ֽ���(ĿǰΪ1)
	unsigned int   nMinPKSize;       //����̵ĳ���
	unsigned int   nMaxPKSize;       //�����ĳ���(0.���޳�)
};

/***************************************************************
 *˵����ҵ��̬������ĵ�*
 *���ߣ�����
 *����ʱ�䣺2004��1��6��
 *�޸�����: 2004��1��8��
 *�޸����ݣ��ն��豸������������Ӧ��������
/***********************1***********************************/
//������ṹ����ϸ�� �����ݽṹ������ ���͡�����������ṹ 

// �ն��豸���� 
typedef struct TerminalProperty
{
	DWORD	dwLength;	//���ݽṹ����
	DWORD   dwMainKey;	// ��Ӧ����
	BYTE    ucState;	//�ն��豸״̬ 0 --- ������ 1---����̬ 2---����̬ 3---����̬
	
	BYTE    ucIDNo[4];	//�ն��豸ID��
	BYTE    ucMacNo;	//�ն��豸����
	BYTE    ucRegNo[4];	//�ն��豸ע���
	BYTE    ucType[2];	//�ն��豸������
	BYTE    ucProgVer[4];//����汾��
	
	WORD	wEDFlowNo;	//����������ˮ��
	WORD    wECFlowNo;	//����������ˮ��
	WORD    wNoReponseTime; //����Ӧ����
}TerminalProperty;


//ͨѶ������������
typedef struct CommunicationProperty
{
	DWORD	dwLength;	//���ݽṹ����
	BYTE    ucMode;		//��·ģʽ 0---tcp/ip 1---serialport 2---modem 3---udp
	bool    bStyle;		//ͨ��ģʽ true---����   false---����
	bool    bNetFlag;	//������� true---����   false---����
	
	WORD    wSerialNo;	//���ں�
	WORD    wBaudRate;	//������
	
	bool    bServerOrClient;//�ն�Ϊ��������ͻ��� true---������ false---�ͻ���
	
	char    cServerIpAddr[16];//�����IP��ַ
	WORD    wServerPortNo;	  //����˶˿ں�
	
	char    cClientIpAddr[16];//�ͻ���IP��ַ
	WORD    wClientPortNo;	  //�ͻ��˶˿ں�
	
	char    cPhoneNo[256];	  //�绰����
}CommunicationProperty;

//���������
typedef struct TaskProperty
{
	DWORD 	dwLength;	//���ݽṹ����
	WORD    wIDNo;		//����ID��
	BYTE    ucMode;		//����ģʽ 0---Ĭ������ 1---�ƴ����� 2---��ʱ����
	
	//�ƴ����������
	DWORD   wTaskTotalNo;	//���������ܴ���
	DWORD   wTaskCurrentNo; //�������е�ǰ����
	
	//��ʱ���������
	DWORD   wTaskTotalTime; //����������ʱ��
	DWORD   wTaskCurrentTime;//��������ʱ��
	
	//�����ֲ�����
	BYTE	ucCommandTotalNo;  //����������
	BYTE    ucCommandCurrentNo;//�����ֵ�ǰ��
	BYTE    ucCommandArray[256];//�������б�
	BYTE    ucERetryNo;	   //�������������Դ���
	BYTE    ucRetryNo;	   //���������Դ���
}TaskProperty;

//���ͺ�������ҵ���ӿڲ���
typedef struct TSSmartDoc
{
	DWORD 	m_dwLength;	//���ݽṹ����
	bool    m_bNetPar;	//true---����   false---������
	BYTE    m_ucTotalNo;	//�ն˻�������
	BYTE    m_ucNo;		//���͵�ǰͨѶ�˿� ���ߵ�ǰͨѶ��������
	WORD    m_wNoReponseTime;//�ն��޷�Ӧ����
	
	CommunicationProperty m_CommunicationInfo;//ͨ�Ų���
	TaskProperty	      m_TaskInfo;	  //�������
	TerminalProperty      m_TerminalInfo[256];//
}TSSmartDoc;


//ͨѶ������Ϣ����
typedef struct TSSmartBuffer
{
	BYTE	ucMode;    //0---���ͣ���Ҫ���أ�1---���ͣ�����Ҫ���أ�2---�����ݷ��� 3---�����ݷ���
	WORD    wLength;   //���ݳ���
	BYTE    ucBuffer[512];//������
	WORD    wWaitTime1;//�ȴ�ʱ��1
	WORD    wWaitTime2;//�ȴ�ʱ��2
	
}TSSmartBuffer;	


extern int nAllocateMemoryFlag;
extern char chDir[512];

extern int _stdcall calc_crc16(unsigned char len,unsigned char *in,unsigned char *out);
extern void SVC_DSP_2_HEX(unsigned char *dsp,unsigned char *hex,int count);
extern void SVC_HEX_2_DSP(unsigned char *hex,unsigned char *dsp,int count);
extern int PubCommands(int Machine,unsigned char Commandbyte,int len,unsigned char *Buffer,int level,unsigned char *level_Array);
extern int _stdcall BuildTaskBuffer(TSSmartDoc *pDoc,TSSmartBuffer *pBuf,unsigned char *Data,int nLen);
extern void CollectRawDataProcess(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer);
extern void ConfirmRawDataProcess(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer);

extern void CollectHistoryDealData_Process(TSSmartDoc *pDoc,   TSSmartBuffer *pBuffer);
extern void CollectHistoryCheckInData_Process(TSSmartDoc *pDoc,TSSmartBuffer *pBuffer);

#endif
