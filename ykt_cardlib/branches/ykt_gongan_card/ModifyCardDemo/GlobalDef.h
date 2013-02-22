#ifndef _GLOBAL_DEFINE_H_
#define _GLOBAL_DEFINE_H_

#include "ExceptionErr.h"

#ifdef __cplusplus
extern "C" {
#endif

extern CExceptionErr err_exce;

//////////////////////////////////////////////////////////////////////////
// DATA STRUCT
#pragma pack(1)

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
#pragma pack()

//////////////////////////////////////////////////////////////////////////
// IMPLEMENT MACRO
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

#define DCLR_DLLFUNC(r,name,arg) \
	typedef r (__stdcall * LP##name) arg; \
	extern LP##name name

#define DEF_DLLFUNC(name) \
	LP##name name = NULL

#define LOAD_DLLFUNC(handle,name) \
	name = (LP##name)GetProcAddress(handle,#name); \
	if (NULL == name) \
		return err_exce.SearchErr(KS_ERR_LOADFUNC_ADDRESS);
	
//////////////////////////////////////////////////////////////////////////
// ERROR INFOMATION
static struct Err_Def 
{
	int err_code;
	char err_info[32];
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
	{KS_ERR_EXIT, "�޴��������Ϣ"}
};

//////////////////////////////////////////////////////////////////////////
// IMPORT FUNCTION
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

#ifdef __cplusplus
}
#endif

#endif