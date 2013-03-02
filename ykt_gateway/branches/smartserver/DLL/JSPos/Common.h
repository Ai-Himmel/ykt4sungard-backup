#ifndef __COMMON_H__
#define __COMMON_H__

#pragma once
//////////////////////////////////////////////////////////////////////////////////////////
//////���¶����������ķ���ֵ
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RESULT_VALUE_DEFINE_H__
#define __RESULT_VALUE_DEFINE_H__

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
#define RET_RECV_C1_TIMEOUT            -20      //-20: C1 Timeout
#define RET_RECV_C2_TIMEOUT            -21      //-20: C1 Timeout
#define RET_OK                          0       //0���ɹ�
#define RET_NG                         -1000    //ʧ��/����
#define RET_TIMEOUT                    -1001    //��ʱ
#define RET_TERMINATE                  -1002    //�жϲ���
#define RET_SYSERROR                   -2000    //ϵͳ����
#define RET_DBBUSY                     -3000    //���ݿ���Դ������
#define RET_DBQUERYERROR               -3001    //���ݿ��ѯ����
#define RET_DBEXECERROR                -3002    //���ݿ�DDL����
#define RET_NOTSUPPORT                 -3003    //��֧�ֵ�Ӳ������
#define RET_VALIDPACKET                -3004    //�Ƿ������ݰ�
#define RET_VALIDMARK                  -3005    //MARKֵ��
#define RET_VALIDMACNO                 -3006    //���Ŵ�
#define RET_TASKWHERE_ERROR	           -3007    //�豸����������
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
#define RET_ERROR_AUTH                  25      //25:��̨������ǩ��

#define RET_CONTINUE                    128     //û�е�һ�������, ����ִ��
#define RET_BROADCAST                   129     //�е�һ�������, ����Ҫ���豸�ķ�����Ϣ
#define RET_ERRORCALL                   130     //���豸����ʧ�ܺ�, �Ե���ҵ��㴦��

#define NETWORK_PAR_NONE                0       //ֱ��
#define NETWORK_PAR_STAR                1       //����
#define NETWORK_PAR_BUS                 2       //����

#define PROTOCOL_TCPIP                  3       
#define PROTOCOL_MODEM                  2
#define PROTOCOL_COM                    1

#define MAX_TASK                        1500
#define MAX_SMART_DOC					3000

//�ն��豸�ĵ�ǰ״̬
#define DOC_STATUS_STOP					0			//��ͣ��
#define DOC_STATUS_HARDWARE				1			//����δͨ, �ն��޷�Ӧ
#define DOC_STATUS_SIGNIN               2           //�豸ǩ��
#define DOC_STATUS_CLOCK                3           //ʱ�Ӵ�
#define DOC_STATUS_BLOCKVER             4           //����������
#define DOC_STATUS_OK                   5           //����ʹ��

//ǰ�òɼ����������ؽ����ͨѶ�� ���ݶ���
#define PACKET_BEGIN       '@'       //��ͷ��ʼ��
#define PACKET_END         '$'       //��ͷ��β��
#define PACKET_SPLITTER    '&'       //�ֶηָ���

#define PACKET_CMD_LOGIN             "LIN"      //��¼
#define PACKET_CMD_LOGOUT            "LOUT"     //ע��
#define PACKET_CMD_SHUTDOWN          "SSVR"     //Shutdownǰ�òɼ�������
#define PACKET_CMD_STARTRUN          "SDRI"     //ĳ�豸��ʼ����
#define PACKET_CMD_STOPRUN           "TDRI"     //ĳ�豸ֹͣ��ʼ����
#define PACKET_CMD_GETSERVERINFO     "GSVR"     //�õ���������Ϣ
#define PACKET_CMD_GETDEVICEINFO     "GDRI"     //�õ�ĳ�豸��Ϣ

#define PACKET_CMD_WARNING           "WARN"     //���ؽ��淢������Ϣ
#define PACKET_CMD_ERROR             "ERROR"    //���ؽ��淢���ش�����Ϣ
#define PACKET_CMD_DATA              "BDATA"    //���������ؽ��淢������Ϣ

#define PACKET_CMD_1001              "1001"     //
#define PACKET_CMD_1002              "1002"     //
#define PACKET_CMD_1003              "1003"     //

#define SERVER_SID                   100        //��������SID��ʶ

#define  DATABASE_TEST   0  //��������
#define  DATABASE_DEBUG  1  //����
#define  DATABASE_NORMAL 2  //����
#define  DATABASE_TASK   3  //����

#define  MSG_INFO		 0
#define  MSG_WARNING     1
#define  MSG_ERROR       2
//*------------------------------------------------------------------------------------
//*����: TSServerInfo
//*����: ��������Ϣ
//*------------------------------------------------------------------------------------
struct TSServerInfo
{
	char  szHostName[128];     //��������
	char  szVersion[16];       //�汾��

	long  nWorkMode;           //0--����ģʽ, 1--����ģʽ

	char  szDateTime[24];      //����ʱ��
	long  nTick;               //�ѳּ�ʱ��

	long  nDevLevel1;          //һ���豸����
	long  nDevLevel1Ack;       //����������һ���豸����

	long  nDevLevel2;          //�����豸����
	long  nDevLevel2Ack;       //���������Ķ����豸����
};

//*------------------------------------------------------------------------------------
//*����: TSSmartSupport
//*����: ҵ��DLL��֧�ֵ����������
//*------------------------------------------------------------------------------------
struct TSSmartSupport
{
	long   nTaskCount;
	char   TaskCode[32][8];

	long   nMacCount;
	char   MacType[32][8];
};

//*------------------------------------------------------------------------------------
//*����: TSSmartPacket
//*����: ǰ�òɼ����������ؽ����ͨѶ���ṹ
//*------------------------------------------------------------------------------------
struct TSSmartPacket
{
	char          Begin;	  //��ʼ����־
	char          Version[2]; //�汾��, ��'12'��ʾΪ1.2��
	char          SID[8];     //SID��ʶ(�ɷ��������ص�Ψһ��ʶ)
	char          Cmd[8];     //��������
	char          Length[8];  //���������峤��
	char          Result[8];  //�����صĽ��
//	char          End;        //���Ľ�����
};

//*------------------------------------------------------------------------------------
//*����: TSSmartProtocol
//*����: ͨѶЭ�������
//*------------------------------------------------------------------------------------
struct TSSmartProtocol
{
    unsigned char  PTHead[8];        //����ʼ������(ĿǰΪC2)
    unsigned short PTHeadLen;        //����ʼ������(ĿǰΪ1)
	unsigned char  PTTail[8];        //������������(ĿǰΪC3)
    unsigned short PTTailLen;        //������������(ĿǰΪ1)
	unsigned int   nLenOffset;       //���ݰ�����ƫ��(0..n)
	unsigned short nLenSize;         //�����ֽ���(ĿǰΪ1)
	unsigned int   nMinPKSize;       //����С�ĳ���(0.���޳�)
	unsigned int   nMaxPKSize;       //�����ĳ���(0.���޳�)
};

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

//����: �õ�999Smart�豸Э��Ĺ���
typedef int (__stdcall *lpfnGetSmartProtocolRule)(TSSmartProtocol *pSmartPT);
typedef int (__stdcall *lpfnVerifyBufferValid)(unsigned char *pBuffer, int nBufferSize);

#endif //__RESULT_VALUE_DEFINE_H__

struct TSChildDocInfo
{
	long    m_nAuthID;					//��Ȩ��
	long    m_nStatus;                  //״̬
	char    m_szTaskCode[8];            //����
};

struct TSDocInfo
{
	long    m_nAuthID;					//��Ȩ��
	long    m_nChild;                   //���豸��
	long    m_nStatus;                  //״̬
	char    m_szTaskCode[8];            //����
	TSChildDocInfo   Child[32];
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
	int     m_nListMark;                //��������

	long    m_nAuthID;					//��Ȩ��
	char	m_szDeviceID[16];			//�豸ID
	char	m_szRegister[16];			//ע���
	long	m_nMachineNo;				//����	
	char	m_szVersion[8];				//�豸�汾��
	char    m_szProgramver[8];          //�ֿ����汾��
	char	m_szPassword[8];			//ϵͳԱ����
	char    m_szOprPasswd[8];           //����Ա����
	int     m_nPwdswitch;               //���뿪��

	long    m_nParentID;                //�ϼ��豸��Ψһ��
	char    m_szOrgid[64];              //��������֯����
	char    m_szClass[128];				//����

	long	m_nPortCount;				//�������˿�����
	long	m_nSMTPort;					//�������˿ں�

	char	m_szPort[32];				//ͨѶ�˿�
	long	m_nBaudRate;				//������
	long	m_nConnType;				//ͨѶ��ʽ(��/��)
	long	m_nCommMode;				//��·ģʽ
	char    m_szAddr[16];               //ͨѶ��ַ
	long	m_nOnNet;					//�Ƿ�����
	long	m_nOnline;					//�Ƿ���������
	int     m_nLevel;                   //�豸����
	char    m_szLevelArray[32];         //��������

	int     m_nStatus;                  //�豸״̬, ���涨��Ϊ:
										// 0--ͣ��  0--����,  1 -- ���粻ͨ���ն��޷�Ӧ 2 -- �豸������ 
										// 3--����ǩ��  4--����������  5--ʱ�Ӵ� 

	bool    m_bEnable;                  //�Ƿ񱻶�ֹ̬ͣ

	int     m_nTerminate;               //Ҫǿ���жϱ�����(������ȫ��ʷ������жϴ�����)
	char    m_szTableName[64];          //��Ӧ�����ݿ����

	WORD    m_wFlowNo;                  //������ˮ�� modified
	WORD    m_wLastInvoiceNo;           //�ն˽�����ˮ����ĩֵ
	char    m_sLastDealTime[24];        //�ն˽���ʱ����ĩֵ
	WORD    m_wStateNo;

	WORD    m_wAfterFlowNo;             //��ǰ����ˮ��
	long    m_nFlowFlag;                //�Ƿ�ӵ�ǰ��δֵ����(����ʷ����Ч)

	long    m_nFlow;                    //���
	long    m_nCardID;					//����
	long    m_nInMoney;                 //�뿨���
	long    m_nOutMoney;                //�������
	long    m_nDealCount;				//���ױ���

	WORD    m_nBeginInvoice;            //���ʵĿ�ʼ��ˮ
	WORD    m_wSettleinvoice;           //������ˮ����ĩֵ
	char    m_sSettleTime[24];          //����ʱ����ĩֵ
	WORD    m_wEndInvoice;              //���ʵĽ�����ˮ��

	char    m_sBlackExpire[16];         //����������Ч��
	char    m_sDownBlackTime[24];       //�������´�ʱ����ĩֵ
	long    m_nStartuse;                //ǩ�����
	long    m_nLostDeal;                //�������ݶ�ʧ����
	long    m_nLostSettle;              //�������ݶ�ʧ�ı���

	char    m_sBlackListVer[16];        //�������汾��
	char    m_sLastBlackVer[16];        //���һ���´�ʧ�ܵĺ�����(CardID)
	char    m_sClockVer[16];            //ʱ�䵥�汾��
	char    m_sNumberVer[16];           //���ʽ�շѻ����ѱ�Ű汾
	char    m_sCommDateTime[24];        //���һ���ռ����ݵ�����ʱ��

	char    m_sWhiteList[8];            //Ҫɾ���İ������汾
	char    m_sWorkMode[8];             //��ʱ������ģʽ
	long    m_nSwitch;                  //��������
	char    m_sBlockVer[16];            //�㲥�ĺ�����

	TSDeviceInfo  DeviceInfo;			//���ֵͰ汾���ݵĽṹ��

	//------------------����Ϊͳ����Ϣ----------------------
	DWORD   m_dwTryCount;               //�ܵĲ�������
	DWORD   m_dwSuccess;                //�ɹ�����
	DWORD   m_dwFaild;                  //ʧ�ܴ���
	DWORD   m_dwLastTick;               //�������ʱ���
	DWORD   m_dwRecvTick;               //��������ʱ��(����)
	DWORD   m_dwMarkTick;               //�����ʱ��(����)
	DWORD   m_dwFileTick;               //�����ļ�ʱ��
	DWORD   m_dwDBTick;                 //�������ݿ�ʱ��
	DWORD   m_dwCollectTick;            //�����ռ�����ʱ��

	long	m_nSignIn;					//ǩ�����
	char	m_szSignInTime[24];			//ǩ����ʱ��
	long	m_nDealLost;				//�������ݶ�ʧ����
	long	m_nJZLost;					//�������ݶ�ʧ����
	long	m_nInSuccess;				//���ɹ�����
	long	m_nInFaild;					//���ʧ�ܱ���
	long	m_nInSuccessMoney;			//���ɹ����
	long	m_nInFaildMoney;			//���ʧ�ܽ��
	long	m_nCheckSuccess;			//����ɹ�����
	long	m_nCheckFaild;				//����ʧ�ܱ���
	long	m_nCheckSuccessMoney;		//����ɹ����
	long	m_nCheckFaildMoney;			//����ɹ����
	long	m_nBatchSuccess;			//�����ʳɹ�����
	long	m_nBatchFaild;				//������ʧ�ܱ���
	long	m_nBatchSuccessMoney;		//�����ʳɹ����
	long	m_nBatchFaildMoney;			//������ʧ�ܽ��
	long	m_nDealNumber;				//���״���
	long	m_nTransMoney;				//���׽��
};	

//************************************************************************************
//*����: TSSmartDocEx
//*����: �ܵ��ն���Ϣ
//************************************************************************************
struct TSSmartDocEx
{
	int  nNetPar;       //����ṹ: ֱ��, ����, ����
	int  nPortNo;       //��ǰĬ�϶˿�
	int  nChildDoc;     //���豸��
	TSSmartDoc *pChildDoc[32];  //���豸����, 0..31, 0--���νṹ�ķ�����
	TSDeviceInfo *pDeviceInfo;  //�豸����
};

//************************************************************************************
//*����: TSSmartTask
//*����: ��������
//************************************************************************************
struct TSSmartTask
{
	long  nTaskID;                     //����ID
	long  nTaskPlanID;                 //����ƻ�ID
	long  nAuthID;                     //��Ӧ�ն˻����������������
	char  szDeviceID[32];			   //�ն˻�ID
	int   nFunc;					   //���ܺ�
	char  szTaskCode[8];               //ͨ���������ʹ���
	char  szName[32];                  //ͨ����������
	char  szType[16];                  //ͨ����������
	long  nPriority;                   //�������ȼ�
	char  szSystemNO[16];			   //ƾ֤���
	char  szSystemRCode[8];            //�����������
	long  nResult;                     //����ִ�н����
	char  szRunTime[24];               //����ִ�����ʱ��
	long  nRepeat1;                    //����ɵĴ���
	long  nRepeat2;                    //�ѳ̵ּ�ʱ��(����)
	long  nTick;                       //����
	long  nTerminate;                  //�жϱ�־
	char  szMemo[64];                  //��ע
	char  *pData;					   //��������
};

//************************************************************************************
//*����: TSSmartTaskPlan
//*����: �ƻ�����
//************************************************************************************
struct TSSmartTaskPlan
{
	long  nTaskPlanID;                 //����ƻ�ID
    char  szTaskName[20];              //����ƻ�����
	int   nTaskCycle;                  //����ƻ�ִ������
	char  szBeginTime[24];             //��ʼ����ʱ��
	int   nRepeatTime;                 //�����೤ʱ�䣨���ӣ�
	int   nRepeatTimes;                //�ظ�����
	char  szPlan[24];                  //�ճ�����
	char  szNextRunTime[24];           //�´�ִ��ʱ��
	char  szPriorRunTime[24];          //�ϴ�ִ��ʱ��
	int   nPriorRetrun;                //�ϴ�ִ�н��
	char  szTaskTime[24];              //����ƻ���ʱ��
	char  szMemo[64];                  //��ע

	TSSmartTask  pTask[MAX_TASK];      //��ص��豸��Ϣ
	int   nTask;                       //�豸������
};


//************************************************************************************
//*����: TSSmartTimeOut
//*����: ͨѶ��ʱʱ�����
//************************************************************************************
struct TSSmartTimeOut
{
	long   nCmdID;                    //������
	char   szMacCode[16];             //���ʹ���
	char   szVersion[8];              //�汾����
	long   nTimeOut1;                 //�յ��ն˻�����C2�Ļ���ʱ��
	long   nTimeOut2;                 //�յ��ն˻��������ݰ��Ļ���ʱ��
};

typedef long (*lpfnTaskBufferProc)(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
typedef long (*lpfnTaskProc)(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

struct TaskFunction
{
	long				  nTaskID;
	char				  *pszTaskName;
	lpfnTaskBufferProc    fnTaskBufferProc;
	lpfnTaskProc          fnTaskProc;
};

//************************************************************************************
//*����: TSResultMsg
//*����: ������Ϣ�б�
//************************************************************************************
struct TSResultMsg
{
	long  nResult;
	char *pszMessage;
};

//************************************************************************************
//*����: TSResultData
//*����: ����ϵͳ���ؽ��
//************************************************************************************
struct TSResultData
{
	char  sValue1[32];
	char  sValue2[32];
	char  sValue3[32];
	char  sValue4[32];
	char  sValue5[32];
	char  sValue6[32];
	char  sValue7[32];
	char  sValue8[32];
	char  ssValue1[64];
	char  ssValue2[64];
	char  ssValue3[64];
	char  ssValue4[64];
	char  ssValue5[64];
	char  sMsg[128];
	int   nValue1;
	int   nValue2;
	int   nValue3;
	int   nValue4;
	int   nValue5;
	int   nValue6;
	int   nValue7;
	int   nValue8;
	int   nValue9;
	int   nValue10;
};

//************************************************************************************
//*����: TSSystemParam
//*����: ϵͳ����
//************************************************************************************
struct TSSystemParam
{
	char   szParameter1[64];
	char   szParameter2[64];
	char   szParameter3[64];
	char   szParameter4[64];
	char   szParameter5[64];
	char   szParameter6[128];
	int    nParameter1;
	int    nParameter2;
	int    nParameter3;
	int    nParameter4;
	int    nParameter5;
};

//************************************************************************************
//*����: TSAttachData
//*����: ���ӵ�����
//************************************************************************************
struct TSAttachData
{
	int    nCount;
	char   szValue[64];
	int    nValue;
	void   *pData;
};

//************************************************************************************
//*����: TSXFTimePara
//*����: ����ʱ��β���
//************************************************************************************
struct TSXFTimePara
{
	char szBeginTime[24];
	char szEndTime[24];
	char szClass[128];
	int  nTimes;
	int  nMoney;
};

//************************************************************************************
//*����: TSBlackCard
//*����: ������
//************************************************************************************
struct TSBlackCard
{
	int  nCardID;
	char sVersion[24];
	char sValid[24];
	int  nFlag;
};

//************************************************************************************
//*����: TSXFTimePara
//*����: ������������
//************************************************************************************
struct TSBZDataList
{
	int  nCardID;
	int  nBatch;
	int  nMoney;
};

//************************************************************************************
//*����: TSGSJRecord
//*����: ��ʧ��
//************************************************************************************
struct TSGSJRecord
{
	char   szDeviceID[32];
	int    nCardID;
	char   szShowID[32];
	int    nFlag;
	char   szPassword[16];
	char   szSerial[64];
	char   szCRC[5];
};

////////////////////////////////////////////////////////////////////////////////////
//����ΪSmartServer�ܹ��ṩ��API
////////////////////////////////////////////////////////////////////////////////////
typedef long (__stdcall *lpfnSendData)(int nDest, int nFunc, char *pszData, int nLen, int nPriority, bool bRouter);
typedef long (__stdcall *lpfnRecvData)(char *pszBuffer, int nLen, int nTimeOut);
typedef long (__stdcall *lpfnOutputRealData)(TSSmartTask *pTask, TSSmartDoc *pDoc, int nType, unsigned char *ucRawData, int nDataLen);
typedef long (__stdcall *lpfnGetParam)(int nType, TSSystemParam *pParam);
typedef long (__stdcall *lpfnReportTaskResult)(TSSmartTask *pTask, long iResult, TSResultData *pData);
typedef long (__stdcall *lpfnReadCardGSInfo)(int nflag, TSGSJRecord *pRecord);
typedef long (__stdcall *lpfnDownloadBlackCard)(TSSmartDoc *pDoc, int nFlag, char *pszFileName);
typedef long (__stdcall *lpfnOutputBlackCard)(TSSmartDoc *pDoc, long nFlag, TSBlackCard *pCard);
typedef long (__stdcall *lpfnSendDeviceTick)(TSSmartDoc *pDoc);
typedef long (__stdcall *lpfnSignIn)(TSSmartDoc *pDoc);
typedef long (__stdcall *lpfnSignOut)(TSSmartDoc *pDoc);
//*=================================================================================
//ԭ��:  long GetDBHandle(long nTimeOut)
//*����: �õ�һ�����е����ݿ���
//*����: 
//*      nFlag:   ���ݿ��־(DATABASE_TEST, DATABASE_DEBUG, DATABASE_NORMAL)
//*����: 
//*      < 0 :    ʧ��
//*      = 0 :    ��ʱ(�޿��е�����,���Ժ�����)
//*=================================================================================
typedef long (*lpfnGetDBHandle)(long nFlag);

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
//ԭ��:  void CloseRecHandle(long nRecHandle)
//*����: �ͷ�һ���򿪵ļ�¼�����
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      ��
//*=================================================================================
typedef void (*lpfnCloseRecHandle)(long nRecHandle);


//*=================================================================================
//ԭ��:  int IsOpen(long nRecHandle)
//*����: ��¼���Ƿ��
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      > 0 :  �Ѵ�
//*      <=0 :  ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnIsOpen)(long nRecHandle);

//*=================================================================================
//ԭ��:  int IsBOF(long nRecHandle)
//*����: ����Ƿ��ڼ�¼����
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      > 0 :  ��
//*      =0  :  ����
//*      < 0 :  ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnIsBOF)(long nRecHandle);


//*=================================================================================
//ԭ��:  int IsEOF(long nRecHandle)
//*����: ����Ƿ��ڼ�¼��β
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      > 0 :  ��
//*      =0  :  ����
//*      < 0 :  ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnIsEOF)(long nRecHandle);

//*=================================================================================
//ԭ��:  int MoveFirst(long nRecHandle);
//*����: ����Ƶ���¼����
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      > 0 :  �ɹ�.
//*      <= 0 : ���ɹ�. ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnMoveFirst)(long nRecHandle);

//*=================================================================================
//ԭ��:  int MoveLast(long nRecHandle);
//*����: ����Ƶ���¼��β
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      > 0 :  �ɹ�.
//*      <= 0 : ���ɹ�. ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnMoveLast)(long nRecHandle);

//*=================================================================================
//ԭ��:  int MoveNext(long nRecHandle);
//*����: �������һ����¼
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      > 0 :  �ɹ�.
//*      <= 0 : ���ɹ�. ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnMoveNext)(long nRecHandle);

//*=================================================================================
//ԭ��:  int MovePrev(long nRecHandle);
//*����: �������һ����¼
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      > 0 :  �ɹ�.
//*      <= 0 : ���ɹ�. ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnMovePrev)(long nRecHandle);

//*=================================================================================
//ԭ��:  int GetFieldCount(long nRecHandle)
//*����: �õ��ֶ���
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      > 0 :  �ֶ���
//*      <= 0 : ���ɹ�. ��¼���ѹرջ��д�
//*=================================================================================
typedef int (*lpfnGetFieldCount)(long nRecHandle);

//*=================================================================================
//ԭ��:  long GetRecordCount(long nRecHandle)
//*����: �õ���¼��
//*����: 
//*      nHandle:    ���ݿ���.  ��GetDBHandle()���ص�ֵ
//*      nRecHandle: ��¼�����.  ��ExecuteQuery()���ص�ֵ
//*����: 
//*      >= 0 :  ��¼��
//*      < 0 : ���ɹ�. ��¼���ѹرջ��д�
//*=================================================================================
typedef long (*lpfnGetRecordCount)(long nRecHandle);


//*=================================================================================
//ԭ��:  int GetFieldName(long nRecHandle, int nIndex, char *pszRetFieldName)
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
typedef int (*lpfnGetFieldName)(long nRecHandle, int nIndex, char *pszRetFieldName);

//*=================================================================================
//ԭ��:  int GetFieldValue(long nRecHandle, int nIndex, char *pszRetFieldValue);
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
typedef int (*lpfnGetFieldStringValue)(long nRecHandle, int nIndex, char *pszRetFieldValue);

//*=================================================================================
//ԭ��:  int GetFieldValue(long nRecHandle, char *sFieldName, char *pszRetFieldValue);
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
typedef int (*lpfnGetFieldStringValueEx)(long nRecHandle, char *sFieldName, char *pszRetFieldValue);


//*=================================================================================
//ԭ��:  int GetFieldValue(long nRecHandle, char *sFieldName, char *pszRetFieldValue);
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
typedef int (*lpfnGetFieldLongValue)(long nRecHandle, int nIndex, long *nRetFieldValue);
typedef int (*lpfnGetFieldLongValueEx)(long nRecHandle, char *sFieldName, long *nRetFieldValue);


//*=================================================================================
//ԭ��:  int GetFieldValue(long nRecHandle, char *sFieldName, char *pszRetFieldValue);
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
typedef int (*lpfnGetFieldFloatValue)(long nRecHandle, int nIndex, float *nRetFieldValue);
typedef int (*lpfnGetFieldFloatValueEx)(long nRecHandle, char *sFieldName, float *nRetFieldValue);

//*=================================================================================
//ԭ��:  int GetFieldValue(long nRecHandle, char *sFieldName, char *pszRetFieldValue);
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
typedef int (*lpfnGetFieldDoubleValue)(long nRecHandle, int nIndex, double *nRetFieldValue);
typedef int (*lpfnGetFieldDoubleValueEx)(long nRecHandle, char *sFieldName, double *nRetFieldValue);

//��λ����ǰ�ֶ�
typedef int (*lpfnLocate)(long nRecHandle, char *sFieldName, char *sValue);


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

//������������
typedef long (* lpfnSendRequest)(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer);

//���͹㲥����
typedef long (*lpfnBroadData)(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer);
typedef long (*lpfnBroadMessage)(char *pBuffer, long nLength);
typedef long (*lpfnBroadcastPro)(char *pszCmd, TSSmartDoc *pDoc, void *pData, long nSize);

//*=================================================================================
//*����: ����һ̨�ն�, �����»�ǩ��
//*����: 
//*      �������˵��
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================
typedef long (*lpfnAddNewSmartDoc)(long nParentID, long nPort, TSSmartDoc *pDoc);
typedef long (*lpfnDelSmartDoc)(long nAuthID);
typedef TSSmartDoc* (*lpfnGetSmartDoc)(long nAuthID);

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
	lpfnSendRequest			    fnSendRequest;
	lpfnBroadData               fnBroadData;
	lpfnBroadMessage            fnBroadMessage;
	lpfnAddNewSmartDoc          fnAddNewSmartDoc;
	lpfnDelSmartDoc             fnDelSmartDoc;
	lpfnBroadcastPro			fnBroadcastPro;
	lpfnSendData				fnSendData;
	lpfnRecvData				fnRecvData;
	lpfnOutputRealData			fnOutputRealData;
	lpfnGetParam				fnGetParam;
	lpfnReportTaskResult		fnReportTaskResult;
	lpfnReadCardGSInfo			fnReadCardGSInfo;
	lpfnDownloadBlackCard		fnDownloadBlackCard;
	lpfnOutputBlackCard			fnOutputBlackCard;
	lpfnSignIn					fnSignIn;
	lpfnSignOut					fnSignOut;
};

////////////////////////////////////////////////////////////////////////////////////
//����Ϊҵ���ܻص�ԭ��
////////////////////////////////////////////////////////////////////////////////////

//*=================================================================================
//*ԭ��: long InitModule(TSSmartFixInfo *pSmartFixInfo, long *nFlag);
//*����: ��ʼ��ҵ����ģ��, ��װ������/��ʼ������
//*����: 
//*      pFunction, �����������API��ַ
//*      pSupport,  ���ص�ҵ��DLL��֧�ֵĻ������������
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================
typedef long (__stdcall *lpfnInitModule)(TSSmartFunction *pFunction, TSSmartSupport *pSupport);

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
typedef long (__stdcall *lpfnReadSmartDocInfo)(TSSmartDoc **pSmartDoc, long *nDocCount);
typedef long (__stdcall *lpfnReleaseSmartDoc)(TSSmartDoc *pSmartDoc);

//*=================================================================================
//*����: ���ҵ����ģ��, �˳�DLLʱ����
//*����: 
//*      ��
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================
typedef long (__stdcall * lpfnDestoryModule)();

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
typedef long (__stdcall *lpfnCreateTaskBuffer)(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

//*=================================================================================
//*����: ���ն˽������ݺ�Ĵ���(ʵ�ֽ��, ����SQL��)
//*����: 
//*      �������˵��
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================
typedef long (__stdcall *lpfnSmartTaskProcess)(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

typedef long (__stdcall *lpfnDLLSupportInfo)(TSSmartSupport *pSupport);

//ʵʼ�������д��
typedef long (__stdcall *lpfnInitTaskDLL)(TSSmartFunction *pFunction);

//�ͷ������д��
typedef long (__stdcall *lpfnDestoryTaskDLL)();

//����һ������
typedef long (__stdcall *lpfnReadTask)(TSSmartTaskPlan *pTaskPlan);

//���뾭��������
typedef long (__stdcall *lpfnReadTSRTask)(TSSmartTaskPlan *pTaskPlan);

//����ִ����Ϻ�Ĵ���
typedef long (__stdcall *lpfnTaskReplace)(TSSmartTaskPlan *pTaskPlan);

//�õ���ʱ�Ĳ�����
typedef long (__stdcall *lpfnGetTimeOutMap)(TSSmartTimeOut *pBuffer, long *nCount);

//��ԭ����ı�־��״̬
typedef long (__stdcall *lpfnUpdateTask)(TSSmartTaskPlan *pTaskPlan);

#endif //__COMMON_H__
