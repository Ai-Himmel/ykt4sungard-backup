 #include "stdafx.h"
#include "CardDLL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
int InitInstance();
int ifReadyOK();
//int isConnectMF = -1;    //�ж϶�д���Ƿ�ɹ���ʼ��
static int	ErrCode;
static char ErrMsg[256];


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}



HINSTANCE hDLL = NULL;
typedef INT (CALLBACK* LPSMT_ConnectMF280)(int ,int);
typedef INT (CALLBACK* LPSMT_ControlBuzzer)(void);
typedef INT (CALLBACK* LPSMT_CloseMF280)(void);	
typedef INT (CALLBACK* LPSMT_CreateGreyCard)(BOOL bPersonalFlag,BOOL bStateFlag, BOOL bBankInfo,BOOL bPacketFlag[8]);
typedef INT (CALLBACK* LPSMT_WriteCardStateInfo)(unsigned char ucShowCardNo[5],int nDealCardNo[1],unsigned char ucDeadLineDate[3],unsigned char ucCardRightType[1]);
typedef INT (CALLBACK* LPSMT_PacketAddMomey)(int ,int );
typedef INT (CALLBACK* LPSMT_PacketSetMoney)(int ,int );
typedef INT (CALLBACK* LPSMT_AutoDll)(unsigned char *);
typedef INT (CALLBACK* LPSMT_JudgeAutoFlag)();
typedef INT (CALLBACK* LPSMT_RequestCardExist)(unsigned char *,unsigned char *);
typedef INT (CALLBACK* LPSMT_ReadCardStateInfo)(unsigned char ucShowCardNo[5],int nDealCardNo[1],unsigned char ucDeadLineDate[3],unsigned char ucCardRightType[1]);
typedef INT (CALLBACK* LPSMT_WritePersonalInfo)(unsigned char ucName[8],unsigned char ucDutyNo[4],unsigned char ucCertificateNo[20],unsigned char ucDepartmentNo[10],unsigned char ucIdentifyNo[4],unsigned char ucSexNo[1], unsigned char ucCardNo[20]);
typedef INT (CALLBACK* LPSMT_ReadPersonalInfo)(unsigned char ucName[8],unsigned char ucDutyNo[4],unsigned char ucCertificateNo [20],unsigned char ucDepartmentNo[10],unsigned char ucIdentifyNo[4],unsigned char ucSexNo[1] ,unsigned char ucCardNo[20]);
typedef INT (CALLBACK* LPSMT_ChangeName)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ChangeDutyNo)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ChangeCerificateNo)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ChangeDepartmentNo)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ChangeIdentifyNo)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ChangeSexNo)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ReadPacketInfo)(int,LOOPPURSEINFO *LoopPurseInfo);
typedef INT (CALLBACK* LPSMT_ChangeDeadLineDate)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ChangeCardRightType)(unsigned char ucCardRightType[1]);
typedef INT (CALLBACK* LPSMT_WritePersonalPassword)(unsigned char PersonalPsd[3]);
typedef INT (CALLBACK* LPSMT_ReadPersonalPassword)(unsigned char PersonalPsd[3]);
typedef INT (CALLBACK* LPSMT_ClearCard)();
typedef INT (CALLBACK* LPSMT_SleepCard)();
typedef INT (CALLBACK* LPSMT_WriteLibraryNo)(unsigned char ucLibraryNo[13]);
typedef INT (CALLBACK* LPSMT_ReadLibraryNo)(unsigned char ucLibraryNo[13]);
typedef INT (CALLBACK* LPSMT_ChangeCardNo)(unsigned char ucCardNo[20]);
typedef INT (CALLBACK* LPSMT_ChangeShowCardNo)(unsigned char ucShowCardNo[5]);

//typedef INT (CALLBACK* LPSMT_SMT_ReadLibraryNo)(unsigned char ucLibraryNo[13]);
LPSMT_ConnectMF280				SMT_ConnectMF280=NULL;
LPSMT_ControlBuzzer				SMT_ControlBuzzer=NULL;
LPSMT_CloseMF280				SMT_CloseMF280=NULL;
LPSMT_CreateGreyCard			SMT_CreateGreyCard=NULL;
LPSMT_WriteCardStateInfo		SMT_WriteCardStateInfo=NULL;
LPSMT_AutoDll					SMT_AutoDll=NULL;
LPSMT_JudgeAutoFlag				SMT_JudgeAutoFlag=NULL;
LPSMT_RequestCardExist			SMT_RequestCardExist=NULL;
LPSMT_ReadCardStateInfo			SMT_ReadCardStateInfo=NULL;
LPSMT_WritePersonalInfo			SMT_WritePersonalInfo=NULL;
LPSMT_ReadPersonalInfo			SMT_ReadPersonalInfo=NULL;
LPSMT_WriteLibraryNo			SMT_WriteLibraryNo=NULL;
LPSMT_ReadLibraryNo				SMT_ReadLibraryNo=NULL;
LPSMT_ChangeName				SMT_ChangeName=NULL;
LPSMT_ChangeDutyNo				SMT_ChangeDutyNo=NULL;
LPSMT_ChangeCerificateNo		SMT_ChangeCerificateNo=NULL;
LPSMT_ChangeDepartmentNo		SMT_ChangeDepartmentNo=NULL;
LPSMT_ChangeIdentifyNo			SMT_ChangeIdentifyNo=NULL;
LPSMT_ChangeSexNo				SMT_ChangeSexNo=NULL;
LPSMT_ChangeCardNo				SMT_ChangeCardNo=NULL;
LPSMT_ChangeDeadLineDate		SMT_ChangeDeadLineDate=NULL;
LPSMT_ChangeCardRightType		SMT_ChangeCardRightType=NULL;
LPSMT_WritePersonalPassword		SMT_WritePersonalPassword=NULL;
LPSMT_ReadPersonalPassword		SMT_ReadPersonalPassword=NULL;

//Ǯ������
LPSMT_PacketSetMoney     SMT_PacketSetMoney=NULL;
LPSMT_PacketAddMomey     SMT_PacketAddMomey=NULL;
LPSMT_ReadPacketInfo	 SMT_ReadPacketInfo=NULL;
LPSMT_ClearCard		 SMT_ClearCard=NULL;
LPSMT_SleepCard		 SMT_SleepCard=NULL;
LPSMT_ChangeShowCardNo	SMT_ChangeShowCardNo=NULL;

//FreeLibrary(hDLL);
void SetErrMsg(int ecode,char *errmsg)
{
	ErrCode=ecode;;
	strcpy(ErrMsg,errmsg);
}
int __stdcall GetLastErrMsg(int ecode[1],char *errmsg)
{
	ecode[0]=ErrCode;
	strcpy(errmsg,ErrMsg);
	return 0;
}
int __stdcall dec2bcd(unsigned char *sDecStr,unsigned char *sBcdStr,int bcd_len)
{
	int i;
	unsigned char lch,hch;

	for(i=0;i<bcd_len;i++)
	{
		lch=sDecStr[2*i]-'0';
		hch=sDecStr[2*i+1]-'0';
		lch=lch<<4;
		hch=hch&0x0F;
		lch=lch&0xF0;
		sBcdStr[i]=hch|lch;
	}
	return 0;
}
int __stdcall bcd2dec(unsigned char *sBcdStr,int bcd_len,unsigned char *sDecStr)
{	
	int i;
	unsigned char lch,hch;

	for(i=0;i<bcd_len;i++)
	{
		hch=(sBcdStr[i]&0x0F);
		lch=(sBcdStr[i]&0xF0);
		lch=lch>>4;
		sDecStr[2*i]=lch+'0';
		sDecStr[2*i+1]=hch+'0';
	}
	return 0;
}

int __stdcall ConnectMF(int com,int baud)
{
	int ret = 0;
	if(hDLL==NULL)
	{
		ret=Load_Dll();
		if(ret)
			return -1;
	}
	if (com < 1)
	{
		com = 1;       //Ĭ�ϴ���1
	}
	if (baud < 1)
	{
		baud = 19200;  //Ĭ��19200
	}
	SMT_CloseMF280();
	ret = SMT_ConnectMF280(com,baud);
	if(ret!= 0)
	{
		char  sEmsg[256]="";
		sprintf(sEmsg,"���ӵ�COM%dʧ��",com);
		SetErrMsg(ret,sEmsg);
		return ret;
	}
	SMT_ControlBuzzer();

	return 0;
}

int __stdcall CloseMF(void)
{
	int ret = 0;

	ret = SMT_CloseMF280();
	if(ret)
	{
		SetErrMsg(ret,"�رմ���ʧ��");
		return ret;
	}
//	isConnectMF=-1;
	return 0;
}
//���п�
int __stdcall PublishCard(TPublishCard *pc)
{
	int ret = 0; 
	unsigned char ucBcdShowCardNo[5];
	unsigned char ucDeadLineDate[3];
	unsigned char ucCardRightType[1];
	BOOL bPersonalFlag=TRUE;
	BOOL bStateFlag=TRUE;
	BOOL bBankInfo=TRUE;
	BOOL bPacketFlag[8]={TRUE,TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE};
	int iCardNo[1];
	memset(ucBcdShowCardNo,0,sizeof(ucBcdShowCardNo));
//	if (isConnectMF) return isConnectMF;

	ret = ifReadyOK();
	if (ret !=0)
		return ret;
	/*
	if(pc->isFormat=='Y'||pc->isFormat=='y')
	{
		ret = SMT_CreateGreyCard(bPersonalFlag,bStateFlag,bBankInfo,bPacketFlag);
		if(ret != 0)
		{
			sprintf(szMsg,"��ʼ����ʧ��,ret %d",ret);
			MessageBox(NULL,szMsg,"����",0);		
			return ret;
		}
	}
	*/
	ret=SMT_ClearCard();
	if(ret)
	{
		SetErrMsg(ret,"��ʽ����ʧ��");
		return ret;
	}
	ret = strlen((char*)pc->ShowCardNo);
	if( 10==ret )	
	{
		//SetErrMsg(ret,"��ʾ���ų��Ȳ���10λ");
		//return -4;		     //��ʾ����λ������
		//ת��ΪBCD��
		dec2bcd(pc->ShowCardNo,ucBcdShowCardNo,5);
	}
	//ת��Ϊ����
	char sYear[3];
	char sMon[3];
	char sDay[3];
	
	memset(sYear,0,sizeof(sYear));
	memset(sMon,0,sizeof(sMon));
	memset(sDay,0,sizeof(sDay));

	memcpy(sYear,pc->DeadLineDate+2,2);
	memcpy(sMon,pc->DeadLineDate+4,2);
	memcpy(sDay,pc->DeadLineDate+6,2);
	
	ucDeadLineDate[0]=atoi(sYear);
	ucDeadLineDate[1]=atoi(sMon);
	ucDeadLineDate[2]=atoi(sDay);
	iCardNo[0]=atoi((char*)pc->CardNo);
	ucCardRightType[0]=pc->CardRightType;
	ret = SMT_WriteCardStateInfo(ucBcdShowCardNo,iCardNo,ucDeadLineDate,ucCardRightType);
	if(ret)
	{
		SetErrMsg(ret,"д��������Ϣʧ��");
		return ret;           //д������Ϣ����
	}
	
	//��ע,��ȱ��д���Ż�ѧ�ŵĽӿ�
	//д�ֿ���������Ϣ
	ret = SMT_WritePersonalInfo(pc->ucName,
								pc->ucDutyNo,
								pc->ucCertificateNo,
								pc->ucDepartmentNo,
								pc->ucIdentifyNo,
								pc->ucSexNo,
								pc->ucCardNo);
	if(ret)
	{
		SetErrMsg(ret,"д������Ϣʧ��");
		return ret;           //
	}
	ret=SMT_WriteLibraryNo(pc->ucLibraryNo);
	if(ret)
	{
		SetErrMsg(ret,"дͼ��֤��ʧ��");
		return ret;
	}
	ret=WriteCardPwd(pc->ucPwd);
	if(ret)
	{
		SetErrMsg(ret,"д������ʧ��");
		return ret;
	}
	//Ԥ����
	unsigned short int PacketNo = 1;
	int Money;
	Money = pc->Money;
	ret = SMT_PacketSetMoney(PacketNo,Money);
	if(ret)
	{
		SetErrMsg(ret,"����Ǯ�����ʧ��");
		return ret;		
	}
	SMT_ControlBuzzer();
	return 0;
}

int ifReadyOK()
{
//	if (isConnectMF) return isConnectMF;

	int ret = 0;

	//����д���Ƿ���Ȩ
	ret = SMT_JudgeAutoFlag();
	if(ret!=1)
	{
		SetErrMsg(ret,"������δ��Ȩ");
		return ret;
	}
	//����û����Ƿ��ڸ�Ӧ��
	char ucSerialNo[9];
	char ucType[3];

	ret = RequestCard(ucSerialNo,ucType);
	if(ret)
	{
		return ret;
	}

	return 0;
}

int __stdcall ReaderAuthor(unsigned char *ucAuthorInfo)
{
	int ret = 0;
	unsigned char ucAuthor[9];
//	if (isConnectMF) return isConnectMF;

	memset(ucAuthor,0,sizeof(ucAuthor));
	memcpy(ucAuthor,ucAuthorInfo,8);
	//����д����Ȩ
	ret = SMT_AutoDll(ucAuthor);
	if(ret)
	{
		SetErrMsg(ret,"��������Ȩʧ��");
		return ret;
	}
	SMT_ControlBuzzer();
	return 0;
}

int __stdcall RequestCard(char *ucSerialNo,char *ucType)
{

	int ret = 0;
	unsigned char SerialNo[4],Type[1];
	memset(SerialNo,0,4);
	memset(Type,0,1);

//	if (isConnectMF) return isConnectMF;
	//����û����Ƿ��ڸ�Ӧ��
	ret = SMT_RequestCardExist(SerialNo,Type);
	if(ret)
	{
		SetErrMsg(ret,"�����ڶ�������Ӧ��");
		return ret;
	}
	sprintf(ucSerialNo,"%02X%02X%02X%02X",
		SerialNo[0],
		SerialNo[1],
		SerialNo[2],
		SerialNo[3]);
	sprintf(ucType,"%02X",Type[0]);
	return 0;
}

int __stdcall RedCardInfo(TPublishCard *pc)
{
	int ret = 0; 
	unsigned char ucBcdShowCardNo[5];
	unsigned char ucDeadLineDate[3];		//�û���ʹ�ý�ֹ����
	unsigned char ucCardRightType[1];		//Ȩ��λ
	int iCardNo[1];

//	if (isConnectMF) return isConnectMF;

	ret = ifReadyOK();
	if (ret !=0)
		return ret;


	memset(pc,0,sizeof(TPublishCard));

	ret = SMT_ReadCardStateInfo(ucBcdShowCardNo,iCardNo,ucDeadLineDate,ucCardRightType);
	if (ret !=0)
	{
		SetErrMsg(ret,"����������Ϣʧ��");
		return ret;    
	}
	bcd2dec(ucBcdShowCardNo,5,pc->ShowCardNo);
	//ת��hex���ڸ�ʽ��ʮ����
	sprintf((char*)pc->DeadLineDate,"20%02d%02d%02d",ucDeadLineDate[0],ucDeadLineDate[1],ucDeadLineDate[2]);
	sprintf((char*)pc->CardNo,"%d",iCardNo[0]);
	pc->CardRightType=ucCardRightType[0];
	ret = SMT_ReadPersonalInfo(pc->ucName,pc->ucDutyNo,pc->ucCertificateNo,pc->ucDepartmentNo,pc->ucIdentifyNo,pc->ucSexNo,pc->ucCardNo);
	if (ret !=0)
	{
		SetErrMsg(ret,"����������Ϣʧ��");
		return ret;     
	}
	ret=SMT_ReadLibraryNo(pc->ucLibraryNo);
	if(ret)
	{
		SetErrMsg(ret,"дͼ��֤��ʧ��");
		return ret;
	}
	return 0;
}

//���¿���Ϣ
int __stdcall UpdateCardInfo (TPublishCard *CardInfo)
{
	int ret = 0; 
	unsigned char ucDeadLineDate[3];
	unsigned char ucCardRightType[1];
	unsigned char ucBcdShowCardNo[5];
	char sYear[3];
	char sMon[3];
	char sDay[3];
	
	ret = ifReadyOK();
	if (ret !=0)
		return ret;

	//��ע,��ȱ��д���Ż�ѧ�ŵĽӿ�
	//ת��Ϊ����
	memset(sYear,0,sizeof(sYear));
	memset(sMon,0,sizeof(sMon));
	memset(sDay,0,sizeof(sDay));
	memset(ucBcdShowCardNo,0,sizeof(ucBcdShowCardNo));

	memcpy(sYear,CardInfo->DeadLineDate+2,2);
	memcpy(sMon,CardInfo->DeadLineDate+4,2);
	memcpy(sDay,CardInfo->DeadLineDate+6,2);
	
	ucDeadLineDate[0]=atoi(sYear);
	ucDeadLineDate[1]=atoi(sMon);
	ucDeadLineDate[2]=atoi(sDay);

	ret = SMT_ChangeDeadLineDate(ucDeadLineDate);					//�޸�ʹ�ý�ֹ���ڣ�8���ֽ�����(������)��ʽΪ��"yy-mm-dd"��
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸Ľ�ֹ����ʱ����");
		return ret;
	}
	ucCardRightType[0]=CardInfo->CardRightType;
	ret = SMT_ChangeCardRightType(ucCardRightType);					//�޸�ʹ��Ȩ�����ͣ�1--254��	
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸Ŀ�Ȩ������ʱ����");
		return ret;
	}
	ret = SMT_ChangeName(CardInfo->ucName);							//�޸�����
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸�����ʱ����");
		return ret;	
	}
	ret = SMT_ChangeDutyNo(CardInfo->ucDutyNo);						//�޸�ְ�����
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸�ְ�����ʱ����");
		return ret;
	}
	ret = SMT_ChangeCerificateNo(CardInfo->ucCertificateNo);		//�޸�֤������
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸�֤������ʱ����");
		return ret;	
	}
	ret = SMT_ChangeDepartmentNo(CardInfo->ucDepartmentNo);			//�޸Ĳ��ű���
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸Ĳ��Ŵ���ʱ����");
		return ret;
	}
	ret = SMT_ChangeIdentifyNo(CardInfo->ucIdentifyNo);				//�޸���ݴ���
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸���ݴ���ʱ����");
		return ret;
	}
	ret = SMT_ChangeSexNo(CardInfo->ucSexNo);						//�޸��Ա����
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸��Ա�ʱ����");
		return ret;
	}
	ret = SMT_ChangeCardNo(CardInfo->ucCardNo);					//
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸�ѧ����ʱ����");
		return ret;
	}
	ret = SMT_WriteLibraryNo(CardInfo->ucLibraryNo);	//
	if(ret != 0)
	{
		SetErrMsg(ret,"�޸�ͼ��֤��ʱ����");
		return ret;
	}
	ret = strlen((char*)CardInfo->ShowCardNo);
	if( 10==ret )	
	{
		//ת��ΪBCD��
		dec2bcd(CardInfo->ShowCardNo,ucBcdShowCardNo,5);
		ret = SMT_ChangeShowCardNo(ucBcdShowCardNo);	//
		if(ret != 0)
		{
			SetErrMsg(ret,"�޸���ʾ����ʱ����");
			return ret;
		}
	}
	return 0;
}

int __stdcall ReadPacketInfo( LPLOOPPURSEINFO LoopPurseInfo )
{
	int ret = 0; 

//	if (isConnectMF) return isConnectMF;

	ret = ifReadyOK();
	if (ret !=0)
		return ret;

	int nPacketNo = 1;
	
	memset(LoopPurseInfo,0,sizeof(LOOPPURSEINFO));  //��ǰ�����ڴ淢�������ԭ����û��#pragma pack(1)

	ret = SMT_ReadPacketInfo(nPacketNo,LoopPurseInfo);
	if (ret !=0)
	{
		SetErrMsg(ret,"������Ϣʧ��");
		return ret;
	}
	return ret;
}

int __stdcall ReadCardNO(char *pCardNo)
{
	int ret = 0;
	int CardNo[1]={0};
	unsigned char sBcdShowCardNo[5];
	unsigned char ShowCardNo[11];			//�û�����ʾ����
	unsigned char DeadLineDate[3];			//�û���ʹ�ý�ֹ����
	unsigned char CardRightType[1];			//�û���ʹ��Ȩ�����ͣ�1--254��

	memset(ShowCardNo,0,sizeof(ShowCardNo));
	memset(CardNo,0,sizeof(CardNo));
	memset(DeadLineDate,0,sizeof(DeadLineDate));

//	if (isConnectMF) return isConnectMF;
	
	ret = ifReadyOK();
	if (ret !=0)
		return ret;

	ret = SMT_ReadCardStateInfo(sBcdShowCardNo,CardNo,DeadLineDate,CardRightType);
	if (ret !=0)
	{
		SetErrMsg(ret,"����������Ϣʧ��");
		return ret;     
	}
	sprintf(pCardNo,"%d",CardNo[0]);
	return 0;
}
int __stdcall WriteCardPwd(unsigned char pwd[6])
{
	int ret=0;
	unsigned char ucPwd[3];
	dec2bcd(pwd,ucPwd,3);
	ret=SMT_WritePersonalPassword(ucPwd);
	if(ret)
	{
		SetErrMsg(ret,"д������ʧ��");
		return ret;
	}
	return 0;
}
int __stdcall ReadCardPwd(unsigned char pwd[6])
{
	int ret=0;
	unsigned char ucPwd[3];
	ret=SMT_ReadPersonalPassword(ucPwd);
	if(ret)
	{
		SetErrMsg(ret,"��������ʧ��");
		return ret;
	}
	bcd2dec(ucPwd,3,pwd);
	return 0;
}
int __stdcall Load_Dll()
{
	if(hDLL)
		return 0;
    hDLL = LoadLibrary("SmartCom411DXQ.dll");
	if(!hDLL)
	{
		SetErrMsg(-1,"װ��SmartCom411DXQ.dll��̬��ʧ��");
		return -1;
	}

	SMT_ConnectMF280		 = (LPSMT_ConnectMF280)GetProcAddress(hDLL,"SMT_ConnectMF280");
	SMT_ControlBuzzer        = (LPSMT_ControlBuzzer)GetProcAddress(hDLL,"SMT_ControlBuzzer");
	SMT_CloseMF280           = (LPSMT_CloseMF280)GetProcAddress(hDLL,"SMT_CloseMF280");
	SMT_CreateGreyCard       = (LPSMT_CreateGreyCard)GetProcAddress(hDLL,"SMT_CreateGreyCard");
	SMT_WriteCardStateInfo   = (LPSMT_WriteCardStateInfo)GetProcAddress(hDLL,"SMT_WriteCardStateInfo");
	SMT_PacketAddMomey       = (LPSMT_PacketAddMomey)GetProcAddress(hDLL,"SMT_PacketAddMomey");
	SMT_PacketSetMoney       = (LPSMT_PacketSetMoney)GetProcAddress(hDLL,"SMT_PacketSetMoney");
	SMT_AutoDll				 = (LPSMT_AutoDll)GetProcAddress(hDLL,"SMT_AutoDll");
	SMT_JudgeAutoFlag  	     = (LPSMT_JudgeAutoFlag)GetProcAddress(hDLL,"SMT_JudgeAutoFlag");
    SMT_RequestCardExist  	 = (LPSMT_RequestCardExist)GetProcAddress(hDLL,"SMT_RequestCardExist");
	SMT_ReadCardStateInfo  	 = (LPSMT_ReadCardStateInfo)GetProcAddress(hDLL,"SMT_ReadCardStateInfo");
    SMT_WritePersonalInfo  	 = (LPSMT_WritePersonalInfo)GetProcAddress(hDLL,"SMT_WritePersonalInfo");
	SMT_ReadPersonalInfo     = (LPSMT_ReadPersonalInfo)GetProcAddress(hDLL,"SMT_ReadPersonalInfo");
	SMT_ChangeName           = (LPSMT_ChangeName)GetProcAddress(hDLL,"SMT_ChangeName");
	SMT_ChangeDutyNo         = (LPSMT_ChangeDutyNo)GetProcAddress(hDLL,"SMT_ChangeDutyNo");
	SMT_ChangeCerificateNo   = (LPSMT_ChangeCerificateNo)GetProcAddress(hDLL,"SMT_ChangeCerificateNo");
	SMT_ChangeDepartmentNo   = (LPSMT_ChangeDepartmentNo)GetProcAddress(hDLL,"SMT_ChangeDepartmentNo");
	SMT_ChangeIdentifyNo     = (LPSMT_ChangeIdentifyNo)GetProcAddress(hDLL,"SMT_ChangeIdentifyNo");
	SMT_ChangeSexNo          = (LPSMT_ChangeSexNo)GetProcAddress(hDLL,"SMT_ChangeSexNo");
    SMT_ReadPacketInfo       = (LPSMT_ReadPacketInfo)GetProcAddress(hDLL,"SMT_ReadPacketInfo");
	SMT_ChangeDeadLineDate   = (LPSMT_ChangeDeadLineDate)GetProcAddress(hDLL,"SMT_ChangeDeadLineDate");
	SMT_ChangeCardRightType  = (LPSMT_ChangeCardRightType)GetProcAddress(hDLL,"SMT_ChangeCardRightType");
	SMT_WritePersonalPassword   = (LPSMT_ChangeDeadLineDate)GetProcAddress(hDLL,"SMT_WritePersonalPassword");
	SMT_ReadPersonalPassword  = (LPSMT_ChangeCardRightType)GetProcAddress(hDLL,"SMT_ReadPersonalPassword");
	SMT_SleepCard  = (LPSMT_SleepCard)GetProcAddress(hDLL,"SMT_SleepCard");
	SMT_ClearCard			  = (LPSMT_ClearCard)GetProcAddress(hDLL,"SMT_ClearCard");
	SMT_WriteLibraryNo		  = (LPSMT_WriteLibraryNo)GetProcAddress(hDLL,"SMT_WriteLibraryNo");
	SMT_ReadLibraryNo		  = (LPSMT_ReadLibraryNo)GetProcAddress(hDLL,"SMT_ReadLibraryNo");
	SMT_ChangeCardNo		  = (LPSMT_ChangeCardNo)GetProcAddress(hDLL,"SMT_ChangeCardNo");
	SMT_ChangeShowCardNo	  = (LPSMT_ChangeShowCardNo)GetProcAddress(hDLL,"SMT_ChangeShowCardNo");
	if ((!SMT_ConnectMF280) ||
		(!SMT_ControlBuzzer) ||
		(!SMT_CloseMF280) ||
		(!SMT_CreateGreyCard) ||
		(!SMT_WriteCardStateInfo) ||
		(!SMT_PacketAddMomey) ||
		(!SMT_PacketSetMoney) ||
		(!SMT_AutoDll) ||
		(!SMT_JudgeAutoFlag) ||
		(!SMT_RequestCardExist) ||
		(!SMT_ReadCardStateInfo) ||
		(!SMT_WritePersonalInfo) ||
		(!SMT_ReadPersonalInfo) ||
		(!SMT_ChangeName) ||
		(!SMT_ChangeDutyNo) ||
		(!SMT_ChangeCerificateNo) ||
		(!SMT_ChangeDepartmentNo) ||
		(!SMT_ChangeIdentifyNo) ||
		(!SMT_ChangeSexNo) ||
		(!SMT_ReadPacketInfo) ||
		(!SMT_ChangeDeadLineDate) ||
		(!SMT_ChangeCardRightType) ||
		(!SMT_WritePersonalPassword)||
		(!SMT_ReadPersonalPassword)||
		(!SMT_SleepCard)||
		(!SMT_ClearCard)||
		(!SMT_WriteLibraryNo)||
		(!SMT_ReadLibraryNo)||
		(!SMT_ChangeCardNo)||
		(!SMT_ChangeShowCardNo)
		)
	{
		FreeLibrary(hDLL);
		hDLL = NULL;
		return -2;
	}
	return 0;
}

