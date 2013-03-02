#ifndef __PUBLIC_H_
#define __PUBLIC_H_

#include <vector>
#include "../export/include/bccclt.h"
using namespace std;

#define		NTASKNUM		256		//ͬʱ�����������
#define		MAX_POSNO		256
#define     MAX_INTERFACE   65		//���ĳ�ֵ������
#define		MNCONTINUETIMES	200   //����δ�յ����ݵĴ���
#define	LINE_TYPE   1	//ֱ����
#define STAR_TYPE   2	//����
#define BUS_TYPE    3	//������


#define  RECORDDATATYPE_FACE		41		//��������
#define  RECORDDATATYPE_HISTROY		42		//��ʷ����
#define  ASSISTANTDATATYPE_FACE		43		//������������
#define  TIMEDATATYPE_FACE			44		//��ʱ��������


#define QUERYWAITFORTIMEBASE	3	//��ѯ�豸״̬�ĵȴ���������
//����˴ﴴ�����ٸ����Ӿ��
#define NHANDLECOUNT   g_IniFilePara.lCreateConCount
//�Ƿ���ò�ѯ��ʽ
#define QUERYWAY		g_IniFilePara.bWaterQueryFlag
//�������еĻ���
#define    	MACHINE_TYPE_5301	"\x53\x01"  //W������
#define    	MACHINE_TYPE_5302	"\x53\x02"  //J������
#define    	MACHINE_TYPE_0201	"\x02\x01"	//��(��)ֵ��
#define    	MACHINE_TYPE_0226	"\x02\x26"	//�շѻ�
#define    	MACHINE_TYPE_0228	"\x02\x28"	//���ػ�
#define    	MACHINE_TYPE_0230	"\x02\x30"	//�����
#define    	MACHINE_TYPE_0232	"\x02\x32"	//�ϻ�������
#define    	MACHINE_TYPE_0234	"\x02\x34"	//��ԡ�����
#define    	MACHINE_TYPE_0240	"\x02\x40"	//��Ʊ��
#define    	MACHINE_TYPE_0130	"\x01\x30"	//���ʶ���
#define    	MACHINE_TYPE_0140	"\x01\x40"	//��Ʊ��
#define    	MACHINE_TYPE_0121	"\x01\x21"	//��ʱ��
#define    	MACHINE_TYPE_0224	"\x02\x24"	//��ʧ��/��һ�
#define    	MACHINE_TYPE_0236	"\x02\x36"	//����ʽ��ԡ�Ʒ���
#define    	MACHINE_TYPE_0421	"\x04\x21"	//�Ž���
#define    	MACHINE_TYPE_1055	"\x10\x55"	//�ֳֻ����Ʒѣ�
#define    	MACHINE_TYPE_5501	"\x55\x01"	//����ͨ����
#define    	MACHINE_TYPE_1056	"\x10\x56"	//�ֳֻ�(�Ʒ�+����)
#define    	MACHINE_TYPE_0243	"\x02\x43"	//ˮ��
#define    	MACHINE_TYPE_0244	"\x02\x44"	//ˮ�ؼ�ʱ
#define    	MACHINE_TYPE_0245	"\x02\x45"	//ˮ�ؼ���

#define		DRTP_FREE		0
#define		DRTP_CLOSE		1
#define		DRTP_BUSY		2

//��ȡ���˴�������
typedef struct CPackHandle
{
	XDHANDLE	handler;
	bool		bStatus; //trueռ�� false����
}CPACKHANDLE;

//����ͨѶ�����ṹ
typedef struct IP_PAR
{
	bool    bConnect;      //�Ƿ���ͨ
	char	cIPAddress[17];//IP��ַ
	int		nPortNo;       //�˿ں�	
	char	cIPToID[9];		//��IPתΪID�ŵ�	
}IP_PAR;

//�ն����Խṹ
typedef struct SMART_POS
{	
	BYTE    ucMacNo;				//����
	BYTE    ucpIDNo[5];				//ID��
	BYTE    ucRegNo[5];				//ע���	
	BYTE    ucpMachineCode[3];		//��������	
	byte	ucSendData[256];			//�ɼ����ݵ����ݰ�
	int		nSndLen;				//�ɼ����ݵĳ���	
	int		nNotCommCount;			//���Ӳ�ͨ�Ĵ���
	byte	ucDeviceVer[9];			//�豸�汾��
	byte	ucCardType[3];			//���ṹ(����)
	byte	ucCardclass[65];		//����
	int		nServerPortTotal;		//����˿�����
	byte	ucServerDeviceID[9];	//�ϼ��豸ID(����ID)
	int	    nConnectPort;			//�豸���Ӷ˿�
	int     nCommunicationStatus;	//�ն˻���ǰͨ��״̬	
	int		nLinkMode;				//��·ģʽ
	char    cIP[30];				//ͨѶIP��ַ�򴮿ں�
	int	    nPort;					//IPͨѶ�˿�
	long	nBaudRate;				//������
	int		nDataComWay;			//����ͨѶ��ʽ
	byte	ucBlackCardExp[13];		//��������Ч��
	byte	ucBlackCardVer[13];		//�������汾
	DWORD   nInvoiceNoLast;			//��ˮ����ĩֵ	
	int		nLevel;					//�Ƿ��¼��豸
	byte	sLevel_Array[2];		//���������š��ն����ӵĶ˿ں�
	int		nMessageID;				//Ψһ��ʶ��
}SMARTPOS;

//ҵ����ͨѶ�ṹ
typedef struct SMART_COMM_PACK
{	
	BYTE    ucpMachineCode[2]; //��������
	BYTE    ucMacNo;           //����	
	BYTE    ucRegNo[5];        //ע���		
	BYTE    ucpIDNo[5];        //ID��
	BYTE	ucCmd;				//������
	DWORD   nConnectPortNo;	   //�����������Ķ˿ں�
	BYTE    ucSndData[1024];    //��Ҫ���������
	DWORD   nSndDataLen;       //��Ҫ��������ݳ���
	BYTE    ucRecData[1024];    //���յ�����Ч����
	DWORD   nRecDataLen;       //���յ�����Ч���ݳ���	
	DWORD   nTaskCode;		   //�������
	DWORD	nAcction;			//ҵ�����
	int		nFlag;
	bool	bExecute;			//true��ʾ����δִ�� false��ִ��
	int		nMessageID;			//���˴���ϢID��
	byte	sMemo[64];			//������ʱ����
	DWORD   nMemo;				//������ʱ����
}SMARTCOMMPACK;

//����ִ�н����
typedef struct SMART_TASK_RESULT
{
	SMARTCOMMPACK Pos;
	DWORD	nAcction;			//ҵ�����
	BYTE	ucIP[20];			//���ӷ����IP��ַ
	bool	ResultStatus;		//����ִ�еĽ��״̬(�ɹ�\ʧ��)
	char    ucErrMsg[128];		//�����񲻳ɹ�,�򷵻���ش�����Ϣ
	int		nTaskResultStatus;	//��������״̬��
}SMARTTASKRESULT;

//�������ݽṹ
typedef struct Str_SaleRecord
{
	char	sRegNo[9];			//ע���
	long	lVer;				//�汾
	long	lWalletcode;		//Ǯ����
	long	lStartReason;		//����ԭ��
	long	lCardID;			//���׿���
	long	lInvoiceNo;			//������ˮ��
	char	sDealTime[21];		//����ʱ��
	char	sDate[12];			//��������
	char	sTime[12];			//����ʱ��
	long	lTimes;				//��Ƭ���״���
	long	lInMoney;			//�뿨ֵ
	long	lOutMoney;			//����ֵ
	long    lTransMoney;		//���׽��
	long	lRateMoney;			//����
	long	lDealCode;			//���ױ�ʶ
	char	sCrc[5];			//CRC��־	
	long	nFunctionID;		//���ܺ�
	char	sSaleType[30];
	byte    sAssitFlag;			//������־	
	long	lOperatorID;		//����Ա����
	long	lBatchNo;			//���κ�
	long	nICCardCode;		//���ʹ���
	long	nWorkMode;			//����ģʽ
	char	sShowCardNo[16];	//��ʾ����
	long	nTimerType;			//��������
	long	nInductorNo;		//��Ӧͷ���
	long	nDutyFlag;			//���°��־
	long	nEatNum;			//�ʹ���
	char	sShopID[8];			//�̻���
}STRSALERECORD;

typedef struct SMART_COMM_PACK_STR
{
	SMARTCOMMPACK CommPack[NTASKNUM];
	bool		  bHaveFlag;	//false��ʾû������ ture��ʾ������
}SMARTCOMMPACKSTR;

typedef struct SMART_INI_FILE_PARA
{
	DWORD		lSleepTime1;		//���ն�ͨѶ�ȴ�ʱ��1
	DWORD		lSleepTime2;		//���ն�ͨѶ��ʱʱ��2
	DWORD		lSleepTime3;		//���ն�ͨѶ��ʱʱ��3
	DWORD		lGetTaskWaitTime;	//����˴�ȡ����ʱ����
	DWORD		lUpRecordWaitTime;	//��ѯ��¼�ļ�ʱ����
	DWORD		lCreateConCount;	//�������˴�������
	bool		bWaterQueryFlag;	//ˮ�ز�ѯ��־ true ��ʾ���ò�ѯ false��ʾ����ѯ
	int			lMainFunc;			//ǰ�ö�Ӧ���˴﹦�ܺ�
	char		sHostIP[20];		//������IP��ַ,ָ���˴���������ķ���IP
	int			lHostPort;			//����˿ں�,ָ���˴���������ķ���˿�
	int			lFrontRegNo;		//ǰ��ע���
	char		sKey[32];			//��̬��Կ
	int			lRegFlag;			//ע���־  1��ʾǰ���Ѿ�ע�� 0��ʾδע��	
	bool		bWriteDebugLog;	    //������־����
	int         DownBlacktime1;     //ʱ��1����ȫ�������� 
	int         DownBlacktime2;     //ʱ��1����ȫ�������� 
}SMARTINIFILEPARA;

//�������궨��
#define		SMT_COLLECTDATA				930999			//�ռ�����
#define		SMT_SETFEERATE				931101			//�´�����
#define		SMT_GETFEERATE				931102			//�ϴ�����
#define		SMT_SETWORKSECRET			931103			//���ù�����Կ
#define		SMT_GETHISTORYDATA			931104			//ȡ��ʷ��ˮ
#define		SMT_SETCLOCK				931105			//�����ն�ʱ��
#define		SMT_GETCLOCK				931106			//��ȡ�ն�ʱ��
#define		SMT_GETBLACKVERSION			931107			//�ϴ��������汾
#define		SMT_SETBLACKVERSION			931108			//�´��������汾
#define		SMT_SETBLACKVALIDDATE		931109			//�´���������Ч��
#define		SMT_GETBLACKVALIDDATE		931110			//�ϴ���������Ч��
#define		SMT_BROADCASTBLACK			931111			//�㲥������
#define		SMT_DELBLACK				931112			//ɾ��һ��������
#define		SMT_DELALLBLACK				931113			//ɾ�����к�����
#define		SMT_GETBLACKNUM				931114			//ȡ�ն˺���������
#define		SMT_OPENCTRL				931117			//��ˮ
#define		SMT_CLOSECTRL				931118			//��ˮ
#define		SMT_SETCARDTYPE				931119			//���ÿ���
#define		SMT_GETCARDTYPE				931120			//�ϴ�����
#define		SMT_SETWHITECARD			931121			//����һ��������
#define		SMT_DELWHITECARD			931122			//ɾ��һ��������
#define		SMT_DELALLWHITECARD			931123			//ɾ�����а�����
#define		SMT_CONFIRMWHITECARD		931324			//�ж�һ��������
#define		SMT_SETPOSPLACE				931125			//���üƷ����ص�
#define		SMT_GETPOSPLACE				931126			//�ϴ��Ʒ����ص�
#define		SMT_SETWARMMONEY			931127			//���ñ������
#define		SMT_GETWARMMONEY			931128			//�ϴ��������
//����˴�����
#define		SMT_SETADDTOTALMONEY		930124			//���ó�ֵ�ܶ�
#define		SMT_SMARTFRONTSETCLOCK		930001			//�´�ʱ��
#define		SMT_SMARTFRONTGETCLOCK		930002			//�ϴ�ʱ��
#define		SMT_SMARTFRONTREGISTER		930051			//ǰ��ע��
#define		SMT_SMARTFRONTLOGIN			930052			//ǰ��ǩ��
#define		SMT_SMARTFRONTALLDEVICE		930037			//ǰ��һ�����´������豸
#define		SMT_SMARTFRONTDOWNALLBLACK	930066			//ǰ��һ���´����к�����
#define		SMT_SMARTFRONTDOWNALLBLACK_EVERYDAY	930068	//ǰ��ÿ���´����к����� xiao

#define		SMT_SMARTFRONTBROADBLACK	930005			//ǰ�ý��չ㲥������
#define		SMT_SMARTFRONTOPENORCLOSE	930067			//ǰ�û�ȡ����/����
#define		SMT_SMARTFRONTSENDTICK		930071			//ǰ�÷��������ϴ�״̬
#define		SMT_SMARTFRONTGETRATE		930068			//ǰ�û�ȡ�豸�ķ���
#define		SMT_SMARTFRONTWARNMONEY		930070			//ǰ�û�ȡ�������
#define		SMT_SMARTFRONTGETTASK		930099			//ǰ�û�ȡ����
#define		SMT_SMARTFRONTGETMAINPARA	930007			//ǰ�û�ȡ���˴��豸������
#define		SMT_SMARTFRONTUPMAINPARA	930008			//ǰ���ϴ��豸������
#define		SMT_SMARTFRONTADDBLACKLIST	930003			//ǰ�û�ȡ���˴����Ӻ�����
#define		SMT_SMARTFRONTDELBLACKLIST	930004			//ǰ�û�ȡ���˴�ɾ��������
#define		SMT_SMARTFRONTADDMONEY		930034			//��ֵ��ˮ�ϴ����ܺ�
#define		SMT_SMARTFRONTMAGMONEY		930036			//�������ˮ�ϴ����ܺ�
#define		SMT_SMARTFRONTSALEHISTROY	930016			//�ɼ�������ʷ����
#define		SMT_SMARTFRONTADDHISTROY	930018			//�ɼ���ֵ��ʷ����
#define		SMT_SMARTFRONTUPDEALDATA	930031			//���ѱ����ϴ����˴�
#define		SMT_SMARTFRONTUPASSISDATA	930033			//�����ϴ����˴�
#define		SMT_SMARTFRONTMANAGERATE	930006			//�´�����ѱ���
#define		SMT_SMARTFRONTPWDMONEY		930010			//�´��������ý��
#define		SMT_SMARTFRONTDAYMONEY		930061			//�´����ۼ������޶�
#define		SMT_SMARTFRONTMANAGEPWD     930063			//�����ն˹���Ա����
#define		SMT_SMARTFRONTCARDTYPE		950040			//�����ն���չ����
#define		SMT_SMARTFRONTCHANGEMONEY	950029			//�ϴ���ϴ�»���ֵ
#define		SMT_SMARTFRONTGETBLACKCARD  950007			//��ȡ������
#define		SMT_SMARTFRONTSETBLACKCARD  930046			//���������
#define		SMT_SMARTFRONTDOWNALLASSIT	849007			//��ȡ��������
#define		SMT_SMARTFRONTDOWNGETASSIT	930077			//��ȡ��������
#define		SMT_SMARTFRONTWHETHERASSIT	849006			//�Ƿ���첹��
#define		SMT_SMARTFRONTUPTIMEDATA			930101	//�ϴ���ʱ��¼
#define		SMT_SMARTFRONTTIMEHISTROY			930102	//�ɼ���ʱ��ʷ��¼
#define		SMT_SMARTFRONTGETTIMEMAINPARA		930103	//ǰ�û�ȡ���˴��ʱ�豸������
#define		SMT_SMARTFRONTGETTIMESEGMENT		930105	//ǰ�û�ȡ���˴��ʱ�豸ʱ���
#define		SMT_SMARTFRONTGETTIMEHOLIDAY		930109	//ǰ�û�ȡ���˴��ʱ�豸�ڼ�����
#define		SMT_SMARTFRONTGETTIMEWHITEVER		930113	//ǰ�û�ȡ���˴��ʱ�豸�������汾
#define		SMT_SMARTFRONTGETTIMEWHITELIST		930117	//ǰ�û�ȡ���˴��ʱ�豸������
#define		SMT_SMARTFRONTGETTIMESWITCH			930120	//ǰ�û�ȡ���˴��ʱ�豸���ؿ���
#define		SMT_SMARTFRONTGETTIMEWHITELISTVER	930121	//ǰ�û�ȡ���˴��ʱ�豸���������汾
#define		SMT_SMARTFRONTGETEATNUM				950042	//ǰ�û�ȡ�ʹ���
#define		SMT_SMARTFRONTADDAUTHTRUE			849005	//������ֵ��Ȩ��ȷ��
#define		SMT_SMARTFRONTADDREQUEST			849003	//������ֵ����
#define		SMT_SMARTFRONTADDREQUESTCANCEL		849004	//������ֵ����
#define		SMT_SMARTFRONTASSISTANTLISTLOAD		930020	//WLPORT���������´�
#define		SMT_SMARTFRONTSETTASKRESULT	930098			//ǰ�ý�����ִ�н�����͸����˴�
#endif