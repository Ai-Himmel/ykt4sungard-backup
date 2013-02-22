#ifndef _CARDDLL_DEF_H_
#define _CARDDLL_DEF_H_

#ifndef NOUSE_MFC
#include "..\include\LogFile.h"
#endif // NOUSE_MFC

#ifdef __cplusplus
extern "C" {
#endif 
#pragma pack(1)

#ifndef WIN32
#ifndef DWORD
#define DWORD int
#endif

#ifndef WORD
#define WORD short
#endif

#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef BOOL
#define BOOL int
#define TRUE 1
#define FALSE 0
#endif
	
#ifndef ULONG
#define ULONG unsigned long
#endif
#else
#include <windows.h>
#endif

typedef struct               
{
	unsigned char ShowCardNo[11];			//�û�����ʾ����
	unsigned char CardNo[8];				//�û������׿���
	unsigned char DeadLineDate[9];			//�û���ʹ�ý�ֹ����
	int CardRightType;						//�û���ʹ��Ȩ�����ͣ�1--254��
	unsigned char ucName[9];				//����
	unsigned char ucDutyNo[9];				//ְ�����
	unsigned char ucCertificateNo[21];		//֤������
	unsigned char ucDepartmentNo[11];		//���ű��
	unsigned char ucIdentifyNo[5];			//��ݴ���
	unsigned char ucSexNo[2];				//�Ա����
	unsigned char ucCardNo[21];				//���ţ����Ż�ѧ�ţ�
	unsigned char ucPwd[6];					//������
	unsigned char ucLibraryNo[21];			//ͼ��֤��
	int Money;								//���֣�
	unsigned char isFormat;					//�Ƿ��ʽ����һ����
}TPublishCard;


typedef struct
{
		DWORD RemainMoney;			// ����Ǯ�����
		WORD DealTimes;				// �û���������ˮ��
		BYTE DealYear;				// ��������
		BYTE DealMonth; 
		BYTE DealDay;
		BYTE DealHour;
		BYTE DealMin;
		BYTE DealTimes_CurTime;		// �ۼƽ��״���(��ǰʱ�����)
		BYTE DealTimes_CurDay;		// �ۼƽ��״���(������)
} LOOPPURSEINFO ,*LPLOOPPURSEINFO;

typedef struct 
{
	int bala;
	int daybala;
	int total_cnt;
	int day_cnt;
	int time_cnt;
	int date;	//yyyymmdd
	int time;	//hhmmss
}MONEY_PACK_INFO;

typedef struct
{
	char cardtype;
	int termid;
	int remain;
	BYTE oldSerialNo[4];
}WATER_PACK_INFO;

/******************************************************/
// ���ʽṹ
/******************************************************/
typedef struct  
{
	BYTE time_ladder[1];				// ʱ�����
	BYTE deduct_time[1];				// �۷ѵĵ�λʱ�䣬����Ϊ��λ
	BYTE deduct_fee[1];					// �۷ѵĵ�λ���Է�Ϊ��λ
}FEE_RATE;

/******************************************************/
// ��ǰȨ�޵ķ��ʸ���
/******************************************************/
typedef struct
{
	short right_flag;					// Ȩ�ޱ�־, 1��, 0�ر�
	short right_num;					// ���뵱ǰȨ���µķ��ʸ���
	FEE_RATE fee_rate[5];				// �������Ϊ5��, ��ʵ��һЩû���õ�
}FEE_RIGHT_NO;

/*******************************************************/
// ���ʿ��ṹ˵��
/*******************************************************/
typedef struct  
{
	BYTE water_card_flag[5];			// ˮ�ؿ���־
	char packet_num;					// ˮ��Ǯ����
	BYTE main_work_key[9];				// ��������Կ(����)
	BYTE packet_work_key[9];			// СǮ��������Կ(����)
	BYTE work_mode;						// ����ģʽ
	int water_packet_limit;				// ˮ��Ǯ���޶�
	int transfer_limit;					// ˮ��ת���޶�
	BYTE data_length[3];				// ���ݳ���
	BYTE check_crc[2];					// Ч���ֽ�
	FEE_RIGHT_NO fee_right_num[256];	// ���÷��ʵĸ���
}FEE_RATE_CARD_INFO;

typedef struct  
{
	char   devphy999_id[9];
	double sum_balance;
}COLLECT_BALANCE;

/*******************************************************/
// �������ÿ��ṹ˵��
/*******************************************************/
typedef struct  
{
	int card_id;					// ���׿���
	int sum_elec_volume;			// �ܵ���
	int local_elec_volume;			// ���ε���
	int limit_elec_power;			// ������ݹ���
	int alarm_elec_volume;			// ������ʾ����
	int brake_elec_volume;			// ��բ����
}ELEC_VOLUME_CARD_INFO;

/*******************************************************/
// У԰���ṹ˵��
/*******************************************************/
typedef struct _CardInfo 
{
	int 	 card_id;			//���׿���
	int 	 customer_id;		//�ͻ���
	char     physical_no[9];	//������
	char     state_id[5];		//��״̬
	char     password[33];		//������
} CardInfo;

/*******************************************************/
// �ͻ���Ϣ�ṹ˵��
/*******************************************************/
typedef struct _CutInfo 
{
	int 	 customer_id;				//�ͻ���
	char 	 cut_name[21];				//�ͻ�����
	char     classdept_no[11];			//���ű��
	char     class_no[11];				//�༶
	char     classdept_name[151];		//��ϵ�˲��Ż��߰༶����
} CutInfo;

/*******************************************************/
// ��ȡ���Լ��ͻ���Ҫ��Ϣ����
/*******************************************************/
typedef struct _DataInfo              
{
	int      cut_id;                //�ͻ�ID��      
	char	 cut_name[21];			//�ͻ�����
	char     class_no[11];			//�༶
	char     classdept_no[11];		//���ű��
	char 	 classdept_name[151];	//��ϵ�˲��Ż��߰༶����
	char     password[33];			//������, ��ʱ��Ϊ�����ֶ�
	char     state_id[5];			//��״̬, �����ֶ�
} DataInfo;

/*******************************************************/
// ��ȡ���Լ��ͻ���Ҫ��Ϣ����(��չ)
/*******************************************************/
typedef struct _DataInfoEx              
{
	int      cut_id;                //�ͻ�ID��
	int		 card_id;				//���׿���
	int		 cut_type;				//�ͻ�������
	char     cut_type_name[21];		//�ͻ��������
	char	 cut_name[21];			//�ͻ�����
	char     sex[2];				//�Ա�
	char     class_no[11];			//�༶
	char     classdept_no[11];		//���ű��
	char 	 classdept_name[151];	//��ϵ�˲��Ż��߰༶����
	char     password[33];			//������, ��ʱ��Ϊ�����ֶ�
	char     state_id[5];			//��״̬, �����ֶ�
	char     stuemp_no[21];			//ѧ����
	char     physical_no[9];		//������
} DataInfoEx;

typedef struct
{
	int nInfoID;               	 //���׿���
	int nMoneyCent;           	 //���׽��(��)
	int nBalance;               //�����, �����Ժ�����(��)
	int nTotalTimes;  		     //�ۼ����Ѵ���
	int nOperatorNum;         	 //����Ա��, ���1��254��ʾ��ͬ�Ĳ���Ա
	int nYear; 				 //������ 2007����
	int nMonth;
	int nDay;                	 //����
	int nHour;
	int nMinute;
	int nSecond;                //ʱ��
	int bNormal;				 //�Ҽ�¼��־����Ϊ"false"����Ϊ"true"
	int bCancel;                //���ʽ����Ƿ���������, �Ƿ�ȡ��, ���ʽ���δȡ��"false"�����ʽ��ױ�����Աȡ��"true"
	int bReload;             	 //���ɱ�־��0�������ɼ���1�����ɼ�
	int nDMAdr;               	 //���ߵ�ַ 0~255
} POSRECORD;

#pragma pack()

#ifndef NOUSE_MFC
// ����������־, ֻ���ں������ó����ʱ��д��־, ���ڵ��ԺͶԽӹ����в鿴������Ϣ
CLogFile g_log_file("cardlog", 10);
#define DEBUG_CARD_MSGOUT(ret, msg) { g_log_file.WriteLogEx(1000, "FILE:%s--LINE:%d--FunName:%s--Ret:%d--Msg:%s", __FILE__, __LINE__, __FUNCTION__, ret, msg); }
#else 
#define DEBUG_CARD_MSGOUT(ret,msg)
#endif // NOUSE_MFC

//////////////////////////////////////////////////////////////////////////
// IMPLEMENT MACRO
#define CHARGE_TERMINAL			0x01			// �շ��ն�
#define MANAGE_CENTER			(0x01 << 1)		// ��������
#define SAVING_POS				(0x01 << 2)		// ��ֵ�ն�
#define DOOR_DEVICE				(0x01 << 3)		// �Ž�
#define AUTHENTICATION_TERMINAL (0x01 << 4)		// ��֤�ն�
#define AREA_CONTROL			(0x01 << 5)		// �������
#define REMAIN_BIT_SEVEN		0				// ����
#define REMAIN_BIT_EIGHT		0				// ����

#define KS_ERR_EXIT						-1
#define KS_ERR_LOADLIBRARY				1001			
#define KS_ERR_LOADFUNC_ADDRESS			1002			
#define KS_ERR_GETVERSION				1003			
#define KS_ERR_NOINITFILE				1004
#define KS_ERR_NOLOCALEXE				1005
#define KS_ERR_PORTNOEXIST				1006
#define KS_ERR_OPENCOM					1007
#define KS_ERR_NOTOPENCOM				1008
#define KS_ERR_CLOSECOM					1009
#define KS_ERR_READAUTHCARD				1010
#define KS_ERR_CHANGECARDID				1011
#define KS_ERR_CHANGESHOWCARDID			1012
#define KS_ERR_READCARDINFO				1013
#define KS_ERR_CHANGESEPNO				1014
#define KS_ERR_INPUTWORKKEYLENGTH	    1015
#define KS_ERR_INITAUTHCARD				1016
#define KS_ERR_RESETAUTHCARD			1017
#define KS_ERR_INPUTSHOWIDLENGTH		1018
#define KS_ERR_NOMANAGEAUTHCARDFLAG		1019
#define KS_ERR_INPUTNULLFAILED			1020			
#define KS_ERR_INPUTZEROFAILED			1021			
#define KS_ERR_REFINECARDSECTOR			1022
#define KS_ERR_WRITECARDMONEY			1023
#define KS_ERR_CONNECTDEVICE			1024
#define KS_ERR_READCARDID				1025
#define KS_ERR_READCARDMONEY			1026
#define KS_ERR_READSTUEMPNO				1027
#define KS_ERR_READPOSSERIAL			1028
#define KS_ERR_INPUTMONEY				1029
#define KS_ERR_READSERIAL				1030
#define KS_ERR_READSTUEMPNULL			1031


#define DCLR_DLLFUNC(r,name,arg) \
	typedef r (__stdcall * LP##name) arg; \
	extern LP##name name

#define DEF_DLLFUNC(name) \
	LP##name name = NULL

#ifdef NOUSE_MFC
#define LOAD_DLLFUNC(handle,name) do { \
	name = (LP##name)GetProcAddress(handle,#name); \
	if (NULL == name) \
		return -1; } while(0)
#else
#define LOAD_DLLFUNC(handle,name) do { \
	name = (LP##name)GetProcAddress(handle,#name); \
	if (NULL == name) \
		return err_exce.SearchErr(KS_ERR_LOADFUNC_ADDRESS); }while(0)
#endif

#define RET_ERR_FUNC(name, msg, l_ret) do{ if (!name) { strcat(msg, #name); goto l_ret; } }while(0);
#define LOAD_DLLFUNC2(handle, des_name, src_name, msg, l_ret)  do { des_name = (LP##src_name)GetProcAddress(handle,#src_name); \
	RET_ERR_FUNC(des_name, msg, l_ret) }while(0);

#define KS_READER	0
#define KS_POS		1

#define RET_ERROR(ret, msg) if (ret != 0) { DEBUG_CARD_MSGOUT(ret, msg) return ret; }

#define FUNC0(name_reader, name_pos, dll_flag, ret) if (KS_READER == dll_flag) { ret = name_reader(); }else { ret = name_pos(); }
#define FUNC1(name_reader, name_pos, dll_flag, arg1, ret) if (KS_READER == dll_flag) { ret = name_reader(arg1); }else { ret = name_pos(arg1); }
#define FUNC2(name_reader, name_pos, dll_flag, arg1, arg2, ret) if (KS_READER == dll_flag) { ret = name_reader(arg1, arg2); }else { ret = name_pos(arg1, arg2); }
#define FUNC3(name_reader, name_pos, dll_flag, arg1, arg2, arg3, ret) if (KS_READER == dll_flag) { ret = name_reader(arg1, arg2, arg3); }else { ret = name_pos(arg1, arg2, arg3); }
#define FUNC4(name_reader, name_pos, dll_flag, arg1, arg2, arg3, arg4, ret) if (KS_READER == dll_flag) { ret = name_reader(arg1, arg2, arg3, arg4); }else { ret = name_pos(arg1, arg2, arg3, arg4); }

//////////////////////////////////////////////////////////////////////////
// ERROR INFOMATION
static struct Err_Def 
{
	int err_code;
	char err_info[128];
}g_Err_Def[] = 
{
	{KS_ERR_LOADLIBRARY, "��ȡ��̬�����"},
	{KS_ERR_LOADFUNC_ADDRESS, "��ȡ������ַ����"},
	{KS_ERR_GETVERSION, "��ȡ��̬��汾����"},
	{KS_ERR_NOINITFILE, "û��ini�����ļ�"},
	{KS_ERR_NOLOCALEXE, "û�б���exe����"},
	{KS_ERR_PORTNOEXIST, "�˿ڲ�����"},
	{KS_ERR_OPENCOM, "�򿪴��ڴ���"},
	{KS_ERR_NOTOPENCOM, "û�д򿪴���"},
	{KS_ERR_CLOSECOM, "�رմ��ڴ���"},
	{KS_ERR_READAUTHCARD, "��ȡ��Ȩ������"},
	{KS_ERR_CHANGECARDID, "�޸Ľ��׿��Ŵ���"},
	{KS_ERR_CHANGESHOWCARDID, "�޸���ʾ���Ŵ���"},
	{KS_ERR_READCARDINFO, "��ȡ����Ϣ����"},
	{KS_ERR_CHANGESEPNO, "�޸�ѧ���Ŵ���"},
	{KS_ERR_INPUTWORKKEYLENGTH, "������Ȩ������Կ���ȳ���"},
	{KS_ERR_INITAUTHCARD, "��ʼ����Ȩ��ʧ��"},
	{KS_ERR_RESETAUTHCARD, "������Ȩ��ʧ��"},
	{KS_ERR_INPUTSHOWIDLENGTH, "������ʾ���ų��ȳ���"},
	{KS_ERR_REFINECARDSECTOR, "���տ�����ʧ��"},
	{KS_ERR_WRITECARDMONEY, "д�����ʧ��"},
	{KS_ERR_CONNECTDEVICE, "�����豸����"},
	{KS_ERR_READCARDID, "��ȡ���׿���ʧ��"},
	{KS_ERR_READCARDMONEY, "��ȡ�����ʧ��"},
	{KS_ERR_READSTUEMPNO, "��ȡѧ����ʧ��"},
	{KS_ERR_READPOSSERIAL, "��ȡPOS����ˮʧ��"},
	{KS_ERR_INPUTMONEY, "���뿨���ʧ��"},
	{KS_ERR_READSERIAL, "��ȡ������ʧ��"},
	{KS_ERR_READSTUEMPNULL, "��ȡѧ����Ϊ��"},
	{KS_ERR_EXIT, "�޴��������Ϣ"}
};

//////////////////////////////////////////////////////////////////////////
// IMPORT FUNCTION
#ifndef CARDDLL_EXPORTS
typedef void (*LPGetBlockData)(int sect,int block,BYTE *buf
							   ,BYTE *key,long flag);

DCLR_DLLFUNC(int,ConnectMF,(int nPortNo, int nBaudRate));
DCLR_DLLFUNC(int,CloseMF,());
DCLR_DLLFUNC(int,SMT_ChangeShowCardNo,(unsigned char ucShowCardNo[5]));
DCLR_DLLFUNC(int,SMT_ChangeDealCardNo,(int nDealCardNo));
DCLR_DLLFUNC(int,SMT_ReadCardStateInfo,(unsigned char ucShowCardNo[5],
										int nDealCardNo[1],
										unsigned char ucDeadLineDate[3],
										unsigned char ucCardRightType[1]));
DCLR_DLLFUNC(int,ReadCardMainKey,(BYTE * main_key, short wantFlag, short * readFlag));
DCLR_DLLFUNC(int,SMT_AutoDll,(unsigned char *ucWorkingKey));
DCLR_DLLFUNC(int,ControlBuzzer,(void));
DCLR_DLLFUNC(int,ReadCardInfo,(TPublishCard *pc));
DCLR_DLLFUNC(int,SMT_ChangeCardNo,(unsigned char ucCardNo[20]));
DCLR_DLLFUNC(int,ProcessCallBack,(int step));
DCLR_DLLFUNC(int,InitNewAuthCard,(BYTE main_key[8], BYTE flag, LPProcessCallBack lpCallBack));
DCLR_DLLFUNC(int,ResetNewAuthCard,(int * err_code, LPProcessCallBack lpCallBack));
DCLR_DLLFUNC(int,SMT_ReadAuthorWorkKeyAndFlag,(BYTE auth_work_key[8], BYTE *flag));
DCLR_DLLFUNC(int,Load_WorkKey,(char *ascWorkKey));
DCLR_DLLFUNC(int,ReadSerial,(unsigned char *serial));
DCLR_DLLFUNC(int,ReadPacketInfo,( LPLOOPPURSEINFO LoopPurseInfo ));
DCLR_DLLFUNC(int,SMT_ReadPacketInfo,(int nPacketNo, LOOPPURSEINFO *LoopPurseInfo)); 
DCLR_DLLFUNC(int,ReadCardNO,(int CardNo[1]));
DCLR_DLLFUNC(int,SMT_PacketSetMoney,(int nPacketNo,int nMoney));
DCLR_DLLFUNC(int,SMT_GetPacketInfo,(int nPacketNo, MONEY_PACK_INFO *pPackInfo));
DCLR_DLLFUNC(int,SMT_ChangeDeadLineDate,(unsigned char ucDeadLineDate[3]));
DCLR_DLLFUNC(int,ReadCardMainKey,(BYTE * main_key, short wantFlag, short * readFlag));
DCLR_DLLFUNC(int,RefineCardSector,(int sector, unsigned char login_key[7]));
DCLR_DLLFUNC(int,SMT_PacketSetMoney2,(int nPacketNo, int nMoney, int nCnt));
DCLR_DLLFUNC(int,ReadAuthCardBlock,(int startSect, int endSect, short block, LPGetBlockData lpFunc));
DCLR_DLLFUNC(int,ReadWaterCardBlock,(int startSect,int endSect,short block,LPGetBlockData lpFunc));

#endif 

#ifdef __cplusplus
}
#endif

#endif