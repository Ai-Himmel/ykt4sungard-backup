/* ----------------------------------------------------------
 * �������ƣ�transinfo.cpp
 * �������ڣ�2004-09-09 14:58
 * �������ߣ�������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ�����ת�ʸ��ֽ��׺���ʵ��
 * ----------------------------------------------------------
 * �޸�����: 2005-03-10
 * �޸���Ա: ����
 * �޸�����: ��������ͨ�Ų����Ƶ�bank.h������bu������룬��bankguard����
 *           �˴�ֻ����pos�������������нӿڵ��ã�
 * �汾��Ϣ��1.0.1.1
 * ----------------------------------------------------------*/
#include <stdlib.h>
//#include "fdsqc.h"
#include <string.h>
#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <signal.h>
#include "profile.h"
//#include "errdef.h"
#include "mypub.h"  
#include "tcp.h"
#include "cpack.h"
#include "svrlink.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "bupub.h"
//#include "dbfunc.h"
#include "transinfo.h"
#include "dictionary.h"
#include "shem.h"
//#include "account.h"
#include "bank.h"

int 	DRTP_BRANCH=7000;
int 	BCC_BASEFUNCNO=9000;
int 	TIMEOUT=4;
char COMPACC_TIME[2+1]="06";
int	LOGIN_MODE=1;
int	AUTH_MODE=1;
char	DRTP_IP[20]="10.49.188.243";
int	DRTP_PORT=4000;	

extern CSvrLink g_SvrLink;
#ifndef	DEBUG
	#define	DEBUG
#endif


//��ѯת����ˮ
int Pos_QuerySerial(INNER_TRANS_REQUEST * pNode,TRUSERID * handle,int *pRetCode,char *szMsg);
int DelTrans(INNER_TRANS_REQUEST * pNode,int other_serial_no)
{
	int ret=0;
	//ret=call_240003();
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));

	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 240003;
	SetHeadCol(&sPack, F_SORDER2, 0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	//memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));
	des2src(sPack.pack.sorder2,pNode->TerminalId);

	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
		return E_TRANS_SCHOOL_NETERR;
	}	

	//���Ӧ���������pNode,���ض�����Կ������ͨѶ��Կ
	if(BANK_LOGIN)
	{
		memcpy(pNode->BankCardPwd,shm+2+8,sizeof(pNode->BankCardPwd));
	}
	memcpy(pNode->BankCardNewPwd,aPack.pack.scard0,sizeof(pNode->BankCardNewPwd));
	if(ret)
	{
		return ret;
	}
	return 0;
}

//POS��½	240101
int Pos_Login(INNER_TRANS_REQUEST * pNode)
{
	//double unique=0;
	int ret=0;
//	INNER_TRANS_REQUEST  from_pos;

	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
//	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));

	//����δǩ���ɹ���POS���ܵ�½������Կ
	//�������е�½���ɹ�Ҳ���Խ���У԰��ҵ��
	//���Դ˴������ж������Ƿ��½�ɹ�
	/*
	if(!BANK_LOGIN)
	{
		writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
		return	E_TRANS_BANK_NETERR;
	}
	*/
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 240008;
	SetHeadCol(&sPack, F_SORDER2, 0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	//memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));
	des2src(sPack.pack.sorder2,pNode->TerminalId);

	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
		return E_TRANS_SCHOOL_NETERR;
	}	

	//���Ӧ���������pNode,���ض�����Կ������ͨѶ��Կ
	if(BANK_LOGIN)
	{
		memcpy(pNode->BankCardPwd,shm+2+8,sizeof(pNode->BankCardPwd));
	}
	memcpy(pNode->BankCardNewPwd,aPack.pack.scard0,sizeof(pNode->BankCardNewPwd));
//	writelog(LOG_ERR,"key=[%s]",aPack.pack.scard0);
	return 0;
}


//��ѯ���п����
int Pos_QueryBank(INNER_TRANS_REQUEST * pNode)
{

	int ret=0;
	double bank_balance=0;
	char device_id[10+1]="";
	char card_id[12+1]="";
	char bankcard_no[30+1]="";
	char card_pwd[6+1]="";

	//�ж��豸�Ƿ��¼
	des2src(card_id,pNode->CardNo);
	des2src(device_id,pNode->TerminalId);
	des2src(bankcard_no,pNode->BankCardNo);
	des2src(card_pwd,pNode->AccountPwd);
	//ret=device_login_yes_or_no(atoi(device_id));
	if(ret)
	{	
		if(ret<0)
		{
			writelog(LOG_ERR,"device_login_yes_or_no faild,=[%s]",device_id);
			return E_TRANS_SCHOOL_NETERR;
		}
		else
		{
			writelog(LOG_INFO,"Device has not signed in!device_id=[%s],background ret=[%d]",device_id,ret);
			return E_TRANS_TERM_NOLOGIN;
		}
	}
	//�жϲ�����ʽ(AUTH_MODE)������󶨹�ϵ���ж�У԰�������Ƿ���ȷ
	if(AUTH_MODE_SCHOOLPWD==g_Bank.AUTH_MODE)
	{
		//�жϰ󶨶�Ӧ��ϵ�Ƿ����

//		ret=verify_sch_bank_relationship(0,atoi(card_id),"",0,bankcard_no);
//		if(ret)
//		{
//			writelog(LOG_INFO,"verify_sch_bank_relationship error!card_id=[%s],bankcard_id=[%s]",card_id,bankcard_no);
//			return E_TRANS_RELATION_ERR;
//		}
		ret=verify_card_password(atoi(card_id),"", 0,card_pwd);
		if(ret)
		{
			writelog(LOG_INFO,"Verify card password faild!card_id=[%s]",card_id);
			return ret;
		}
	}
	//ʹ�����������ֶ�ȡ�Ͼ���������ĳֿ������������֤���ֶ�
	ret=Get_cut_name_and_id(atoi(pNode->CardNo),pNode->Reserve2,pNode->Reserve3,pNode->Reserve1);
	if(ret)
	{
		writelog(LOG_ERR,"Get_cut_name_and_id err,errcode=[%d],name=[%20s]",ret,pNode->Reserve2);
	}
	
	//�������в�ѯ��������
	ret=Bank_QueryBalance(pNode,&bank_balance);
	if(ret)
	{
		writelog(LOG_INFO,"Bank_QueryBalance error!card_id=[%s],bankcard_id=[%s]",card_id,bankcard_no);
		return ret;
	}
	sprintf(pNode->Balance,"%.2lf",bank_balance);
	writelog(LOG_INFO,"Query bank card balance succeed!Balance=[%s]",pNode->Balance);
	return 0;

}

//�޸�У԰������
int Pos_ChangePwd(INNER_TRANS_REQUEST * pNode)
{
	int ret=0;
	char device_id[10+1]="";
	char card_id[12+1]="";
	char card_pwd[6+1]="";
	char card_pwd_new[6+1]="";

	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
	//ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�
	memset(&sPack,0,sizeof sPack);

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));

	des2src(card_pwd,pNode->AccountPwd);
	des2src(card_pwd_new,pNode->AccountNewPwd);
	des2src(device_id,pNode->TerminalId);
	des2src(card_id, pNode->CardNo);
	//�ж��豸�Ƿ��¼
	writelog(LOG_ERR,"pwd1=[%6s],pwd2=[%6s]",card_pwd,card_pwd_new);

	ret=device_login_yes_or_no(atoi(device_id));
	if(ret)
	{	
		if(ret<0)
		{
			writelog(LOG_ERR,"device_login_yes_or_no faild,=[%s]",device_id);
			return E_TRANS_SCHOOL_NETERR;
		}
		else
		{
			writelog(LOG_INFO,"Device has not signed in!device_id=[%s],background ret=[%d]",device_id,ret);
			return E_TRANS_TERM_NOLOGIN;
		}
	}
	//�ж����������Ƿ���ȷ
	ret=verify_card_password(atoi(card_id),"",0, pNode->AccountPwd);
	if(ret)
	{
		writelog(LOG_INFO,"Verify card password faild!card_id=[%s]",card_id);
		return ret;
	}
	//���̨�����޸����������
	
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.firstflag=1;
	sPack.head.nextflag = 0;
	sPack.head.RequestType = 847111;
	SetHeadCol(&sPack, F_LVOL0,F_SCUST_NO,F_LWITHDRAW_FLAG, 0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	//memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));
	sPack.pack.lvol0=atoi(card_id);
	sPack.pack.lwithdraw_flag=atol(pNode->TerminalId);
	des2src(sPack.pack.scust_no,card_pwd_new);

	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
		return E_TRANS_UNKNOW_ERROR;
	}	
	return 0;
}

//��ʧУ԰��

int Pos_LostCard(INNER_TRANS_REQUEST * pNode)
{

	int ret=0;
	char device_id[10+1]="";
	char card_id[12+1]="";
	
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
//	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));

	des2src(device_id,pNode->TerminalId);
	des2src(card_id, pNode->CardNo);
	//�ж��豸�Ƿ��¼
	ret=device_login_yes_or_no(atoi(device_id));
	if(ret)
	{	
		if(ret<0)
		{
			writelog(LOG_ERR,"device_login_yes_or_no faild,=[%s]",device_id);
			return E_TRANS_SCHOOL_NETERR;
		}
		else
		{
			writelog(LOG_INFO,"Device has not signed in!device_id=[%s],background ret=[%d]",device_id,ret);
			return E_TRANS_TERM_NOLOGIN;
		}
	}
	//�ж����������Ƿ���ȷ
	if(g_Bank.LOGIN_MODE==LOGIN_MODE_CUT_NO)
		ret=verify_card_password(0,"",atoi(card_id), pNode->AccountPwd);
	else
		ret=verify_card_password(0,card_id,0, pNode->AccountPwd);
	if(ret)
	{
		writelog(LOG_INFO,"Verify card password faild!card_id=[%s]",card_id);
		return ret;
	}
	//���̨�����ʧ����
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 846307;
	SetHeadCol(&sPack, F_LVOL0,F_LVOL1,F_SPAGER,F_LVOL6,F_LVOL7,F_LVOL8,F_SCUST_AUTH,F_LVOL2, F_LWITHDRAW_FLAG,F_SSTATUS1,0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	//memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));
	//�жϵ�½ģʽ��ʹ�ÿͻ��ŵ�½����ѧ���ŵ�½
/*
	if(g_Bank.LOGIN_MODE==LOGIN_MODE_CUT_NO)
	{
		des2src(sPack.pack.scust_auth,"");
		sPack.pack.lvol1=atoi(card_id);
	}
	else
	{
		des2src(sPack.pack.spager,card_id);
		sPack.pack.lvol8=0;
	}
*/
	sPack.pack.lvol0=atol(pNode->AccountPwd);
	sPack.pack.lvol1=0;
	sPack.pack.lwithdraw_flag=atol(pNode->TerminalId);
///	des2src(sPack.pack.scust_limit,OPER_SYSTEM_KEY);
	sPack.pack.sstatus1[0]='1';
	sPack.pack.lvol6=0;
	sPack.pack.lvol7=atoi(device_id);
	sPack.pack.lvol2=0;

	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		if(ret<0)
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return E_TRANS_UNKNOW_ERROR;
		}
		else
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return aPack.head.retCode;
		}
	}	
	return 0;
}

int Pos_UnlostCard(INNER_TRANS_REQUEST * pNode)
{
	int ret=0;
	char device_id[10+1]="";
	char card_id[12+1]="";
	
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
//	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));

	des2src(device_id,pNode->TerminalId);
	des2src(card_id, pNode->CardNo);
	//�ж��豸�Ƿ��¼
	ret=device_login_yes_or_no(atoi(device_id));
	if(ret)
	{	
		if(ret<0)
		{
			writelog(LOG_ERR,"device_login_yes_or_no faild,=[%s]",device_id);
			return E_TRANS_SCHOOL_NETERR;
		}
		else
		{
			writelog(LOG_INFO,"Device has not signed in!device_id=[%s],background ret=[%d]",device_id,ret);
			return E_TRANS_TERM_NOLOGIN;
		}
	}
	//�ж����������Ƿ���ȷ
	ret=verify_card_password(atoi(card_id),"",0, pNode->AccountPwd);
	if(ret)
	{
		writelog(LOG_ERR,"Verify card password faild!card_id=[%s]",card_id);
		return ret;
	}
	//���̨����������
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 846307;
	SetHeadCol(&sPack, F_LVOL0,F_SCUST_LIMIT,F_LVOL6,F_LVOL7, F_LWITHDRAW_FLAG,F_SSTATUS1,0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	//memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));

	//�жϵ�½ģʽ��ʹ�ÿͻ��ŵ�½����ѧ���ŵ�½
	sPack.pack.lvol0=atoi(card_id);
	sPack.pack.lvol2=0;
	sPack.pack.lwithdraw_flag=atol(pNode->TerminalId);
/// des2src(sPack.pack.scust_limit,OPER_SYSTEM_KEY);
	sPack.pack.sstatus1[0]='2';
	sPack.pack.lvol6=0;
	sPack.pack.lvol7=atoi(device_id);

	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		if(ret<0)
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return E_TRANS_UNKNOW_ERROR;
		}
		else
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return aPack.head.retCode;
		}
	}	
	des2src(pNode->Reserve1,aPack.pack.sserial0);
	sprintf(pNode->CardNo,"%d",aPack.pack.lvol0);
	sprintf(pNode->TerminalId,"%d",aPack.pack.lwithdraw_flag);
	return 0;

}

int Pos_Bank_Reverse(INNER_TRANS_REQUEST *pNode)
{
	int ret=0;
//	double bank_balance=0;
	char device_id[10+1]="";
	des2src(device_id,pNode->TerminalId);

	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));

	//�ж��豸�Ƿ��¼
	ret=device_login_yes_or_no(atoi(device_id));
	if(ret)
	{	
		if(ret<0)
		{
			writelog(LOG_ERR,"device_login_yes_or_no faild,=[%s]",device_id);
			return E_TRANS_SCHOOL_NETERR;
		}
		else
		{
			writelog(LOG_INFO,"Device has not signed in!device_id=[%s],background ret=[%d]",device_id,ret);
			return E_TRANS_TERM_NOLOGIN;
		}
	}

	//�������
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 240015;
	SetHeadCol(&sPack, F_SORDER2,F_SCUST_AUTH,F_SEMP_PWD,F_SSERIAL0,F_SSTATION0,F_LVOL5,F_LVOL0,
			   F_LVOL6,F_LVOL1,F_LVOL2,F_LVOL3,F_SDATE0,F_LVOL4, 0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	des2src(sPack.pack.sorder2,pNode->TerminalId);
	sPack.pack.lvol0=pNode->RecvNo;
	des2src(sPack.pack.sdate0,pNode->TradeDate);

	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0)
	{
		writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
	    	if (-2 == ret)			
	        	return E_TRANS_INNER_TIMEOUT;
	    	else
	        	return E_TRANS_INNER_TIMEOUT;
	}	
	//�����̨ʧ��,��˴����غ�̨���صĴ�����
	if(aPack.head.retCode)
	{
		return aPack.head.retCode;
	}

	return 0;
}
//POSת��
// ����ʱ��Ҫ��������
int Pos_Transfer(INNER_TRANS_REQUEST * pNode,int txcode,int checkpwd)
{
	int ret=0;
//	double bank_balance=0;
	char device_id[10+1]="";
	char card_id[12+1]="";
	char bankcard_no[30+1]="";
	char card_pwd[6+1]="";
	int	cur_serial_no=0;
	des2src(card_id,pNode->CardNo);
	des2src(device_id,pNode->TerminalId);
	des2src(bankcard_no,pNode->BankCardNo);
	des2src(card_pwd,pNode->AccountPwd);


	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
//	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));

	//�ж��豸�Ƿ��¼
	//ret=device_login_yes_or_no(atoi(device_id));
	if(ret)
	{	
		if(ret<0)
		{
			writelog(LOG_ERR,"device_login_yes_or_no faild,=[%s]",device_id);
			return E_TRANS_SCHOOL_NETERR;
		}
		else
		{
			writelog(LOG_INFO,"Device has not signed in!device_id=[%s],background ret=[%d]",device_id,ret);
			return E_TRANS_TERM_NOLOGIN;
		}
	}
	if(checkpwd)
	{
		//�жϲ�����ʽ(AUTH_MODE)������󶨹�ϵ���ж�У԰�������Ƿ���ȷ
		if(AUTH_MODE_SCHOOLPWD==g_Bank.AUTH_MODE)
		{
			//�жϰ󶨶�Ӧ��ϵ�Ƿ����

//			ret=verify_sch_bank_relationship(0,atoi(card_id),"",0,bankcard_no);
//			if(ret)
//			{
//				writelog(LOG_INFO,"verify_sch_bank_relationship error!card_id=[%s],bankcard_id=[%s]",card_id,bankcard_no);
//				return E_TRANS_RELATION_ERR;
//			}
			ret=verify_card_password(atoi(card_id),"", 0,card_pwd);
			if(ret)
			{
				writelog(LOG_ERR,"Verify card password faild!card_id=[%s]",card_id);
				return ret;
			}

		}
	}
	//ѭ���������������ļ����ж��ϴ����п��Ŷ�Ӧ�������Լ���Ӧ�����п�Ŀ�ʺ�
	int flag=0;
	for(int i=0;i<=g_Bank.BankCount;i++)
	{

		if(i==g_Bank.BankCount)	
		{
				writelog(LOG_ERR,"E_TRANS_BANK_CARD_NONSUPPORT,i=[%d]!g_Bank.BankCount=[%d]",i,g_Bank.BankCount);
				return E_TRANS_BANK_CARD_NONSUPPORT;
		}
		for(int j=0;j<MAX_RANGE;j++)
		{
			//printf("i=[%d],j=[%d],bankcard=[%s],range=[%s],len=[%d]]\n",i,j,pNode->BankCardNo,g_Bank.BankUnit[i].szBankCardRange[j],strlen(g_Bank.BankUnit[i].szBankCardRange[j]));
			if(0==strlen(g_Bank.BankUnit[i].szBankCardRange[j]))	break;
			if(0==memcmp(pNode->BankCardNo,g_Bank.BankUnit[i].szBankCardRange[j]
				,strlen(g_Bank.BankUnit[i].szBankCardRange[j])))
			{
				flag=1;
				g_Bank.cur_bankid=i;
				break;
			}
		}
		if(flag==1)	
			break;
	}

	
	//����ģ����������
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 240002;
	SetHeadCol(&sPack, F_SORDER2,F_SCUST_AUTH,F_SEMP_PWD,F_SSERIAL0,F_SSTATION0,F_LVOL5,F_LVOL0,
			   F_LVOL6,F_LVOL1,F_LVOL2,F_LVOL3,F_LVOL4, 0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	//memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));
	des2src(sPack.pack.sorder2,pNode->TerminalId);
	des2src(sPack.pack.scust_auth,pNode->BankCardNo);
	des2src(sPack.pack.semp_pwd,pNode->AccountPwd);
	des2src(sPack.pack.sserial0,pNode->CardNo);
	sPack.pack.lvol5=atoi(pNode->TransMoney);
	sPack.pack.lvol0=pNode->SendNo;
	sPack.pack.lvol6=atoi(pNode->AccountMoney);
	sPack.pack.lvol1=pNode->RecvNo;
	// modify by ���� 2008-08-30 
	// �޸Ľ��ױ�־,ת�˽��׿�������ͬ�Ľ���
	sPack.pack.lvol4 = txcode;

	sPack.pack.lvol2=g_Bank.BankUnit[g_Bank.cur_bankid].iBankID;
	des2src(sPack.pack.sstation0,g_Bank.BankUnit[g_Bank.cur_bankid].szBankAccountNO);	// ��дһ��ͨ�������˻�
	if (BANK_YNXH == g_Bank.BankUnit[g_Bank.cur_bankid].iBankID) 
		sPack.pack.lvol3 = 4;		// ����һ��ͨ�˻�, ��ͬ�˻��벻ͬ����
	else if (BANK_YNNH == g_Bank.BankUnit[g_Bank.cur_bankid].iBankID) 
		sPack.pack.lvol3 = 5; 
	else sPack.pack.lvol3 = 0; 

	writelog(LOG_ERR,"g_Bank.BankUnit[g_Bank.cur_bankid].szBankAccountNO=[%s]",
			 g_Bank.BankUnit[g_Bank.cur_bankid].szBankAccountNO);
	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0)
	{
		writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
		strcpy(pNode->Reserve3,aPack.pack.vsmess);
	   	 if (-2 == ret)
	        	return E_TRANS_INNER_TIMEOUT;
	    	else
	        	return E_TRANS_INNER_TIMEOUT;
	}	
	//�����̨ʧ��,��˴����غ�̨���صĴ�����
	if(aPack.head.retCode)
	{
		strcpy(pNode->Reserve3,aPack.pack.vsmess);
		return aPack.head.retCode;
	}
	//�������нӿں���,���ղ�ͬ������ת�ʽӿڷ��ͱ��Ĳ�����Ӧ��
	//�ú���Ϊͨ�ýṹ,��ͬ���нӿڰ��ոú��������з�װת�ʱ���
	//
	ret=Get_cut_name_and_id(atoi(pNode->CardNo),pNode->Reserve2,pNode->Reserve3,pNode->Reserve1);
	if(ret)
	{
		writelog(LOG_ERR,"Get_cut_name_and_id err,errcode=[%d],name=[%20s]",ret,pNode->Reserve2);
	}
	cur_serial_no=aPack.pack.lvol1;
	int SendBankSeqno=atoi(aPack.pack.sname2+8);
	ret=Bank_Transfer(pNode,SendBankSeqno);
	if(ret)
	{
		writelog(LOG_ERR,"Bank_Transfer error,errcode=[%d]",ret);
		if(E_TRANS_BANK_NOANSWER==ret)			//�������û�з��ذ������г�������
		{
			ResetNormalCPack(&sPack, 0, 1);
			sPack.head.RequestType = 240003;
			SetHeadCol(&sPack, F_SORDER2,F_SCUST_AUTH,F_SEMP_PWD,F_SSERIAL0,F_LVOL5,F_LVOL0,
					   F_LVOL6,F_LVOL1,F_LVOL2,F_LVOL3, 0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
			//memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));
			des2src(sPack.pack.sorder2,pNode->TerminalId);
			des2src(sPack.pack.scust_auth,pNode->BankCardNo);
			des2src(sPack.pack.semp_pwd,pNode->AccountPwd);
			des2src(sPack.pack.sserial0,pNode->CardNo);
			sPack.pack.lvol5=atoi(pNode->TransMoney);
			sPack.pack.lvol0=SendBankSeqno;
			sPack.pack.lvol6=atoi(pNode->AccountMoney);
			sPack.pack.lvol1=pNode->RecvNo;
			sPack.pack.lvol2=g_Bank.BankUnit[g_Bank.cur_bankid].iBankID;
			if (BANK_YNXH == g_Bank.BankUnit[g_Bank.cur_bankid].iBankID) 
				sPack.pack.lvol3 = 4; 		// ����һ��ͨ�˻�, ��ͬ�˻��벻ͬ����
			else if (BANK_YNNH == g_Bank.BankUnit[g_Bank.cur_bankid].iBankID) 
				sPack.pack.lvol3 = 5; 
			else 
				sPack.pack.lvol3 = 0;
			
			ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, 
						  &sPack, &aPack, &ArrayPack);
			if (ret < 0||aPack.head.retCode!=0)
			{
				writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
				strcpy(pNode->Reserve3,aPack.pack.vsmess);
			}	
			return E_TRANS_BANK_NOANSWER;
		}
		else		
			return ret;
	}

	//���ú�̨��ʽ���˽ӿ�
	ResetNormalCPack(&aPack, 0, 1);
	sPack.head.RequestType = 240001;
	SetHeadCol(&sPack, F_SORDER2,F_SCUST_AUTH,F_SEMP_PWD,F_SSERIAL0,F_SSTATION0,F_LVOL5,
			   F_LVOL0,F_LVOL6,F_LVOL1,F_LVOL2,F_LVOL7,F_LVOL3,F_LVOL4,0);       // ���÷���windows BU��ͷ����ͼ��Ϣ

	//�ⲿϵͳ��ʶ����ʶ�ĸ�����
	sPack.pack.lvol2=g_Bank.BankUnit[g_Bank.cur_bankid].iBankID;
	des2src(sPack.pack.sstation0,g_Bank.BankUnit[g_Bank.cur_bankid].szBankAccountNO);
	sPack.pack.lvol7=cur_serial_no;	//ģ�����˷��ص���ˮ�ţ��ô���ˮ����ʽ����
	sPack.pack.lvol4 = txcode;
	if (BANK_YNXH == g_Bank.BankUnit[g_Bank.cur_bankid].iBankID) 
		sPack.pack.lvol3 = 4; 		// ����һ��ͨ�˻�, ��ͬ�˻��벻ͬ����
	else if (BANK_YNNH == g_Bank.BankUnit[g_Bank.cur_bankid].iBankID) 
		sPack.pack.lvol3 = 5; 
	else 
		sPack.pack.lvol3 = 0;

	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0)
	{
		writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
		strcpy(pNode->Reserve3,aPack.pack.vsmess);
	   	 if (-2 == ret)
	        	return E_TRANS_INNER_TIMEOUT;
	    	else
	        	return E_TRANS_INNER_TIMEOUT;
	}	
	if(aPack.head.retCode)
	{
		strcpy(pNode->Reserve3,aPack.pack.vsmess);
		return aPack.head.retCode;
	}
	
	sprintf(pNode->TransMoney,"%f",aPack.pack.damt1);
	sprintf(pNode->ExtraMoney,"%f",aPack.pack.damt2);
	sprintf(pNode->AccountMoney,"%d",aPack.pack.lvol2);
	strncpy(pNode->TradeDate,aPack.pack.sdate0,8);
	pNode->RecvNo=aPack.pack.lvol1;
	pNode->MngFeeFlag='1';
	//writelog(LOG_INFO,"transfer succeed!");
	return 0;
}
//POS�ɷ�
int Pos_Fee(INNER_TRANS_REQUEST * pNode)
{
	//sprintf(pNode->RetCode,"%d",E_TRANS_FUNC_NONSUPPORT);
	writelog(LOG_INFO,"Pay fee function is not support for a while!");

	return E_TRANS_FUNC_NONSUPPORT;
}

//���Ӷ�Ӧ��ϵ
int Pos_AddRelation(INNER_TRANS_REQUEST * pNode)
{
	//sprintf(pNode->RetCode,"%d",E_TRANS_FUNC_NONSUPPORT);
	writelog(LOG_INFO,"Add relation function is not support for a while!");

	return E_TRANS_FUNC_NONSUPPORT;
}

//ɾ����Ӧ��ϵ
int Pos_DelRelation(INNER_TRANS_REQUEST * pNode)
{
	//sprintf(pNode->RetCode,"%d",E_TRANS_FUNC_NONSUPPORT);
	writelog(LOG_INFO,"Delete relation function is not support for a while!");
	return E_TRANS_FUNC_NONSUPPORT;
}
//��ѯУ԰��ת����ˮ
int Pos_QuerySerial(INNER_TRANS_REQUEST * pNode,TRUSERID *handle,int *pRetCode,char *szMsg)
{
	writelog(LOG_INFO,"Query transfer serial function is not support for a while!");
	return E_TRANS_FUNC_NONSUPPORT;
}
//Ȧ���д��ʧ�ܳ���(ʵ�ʲ���������ֻ�Ǹ�д��״̬)
int Pos_WriteErrCard(INNER_TRANS_REQUEST * pNode)
{
	int ret=0;
	char card_id[12+1]="";
	
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
//	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));

	des2src(card_id, pNode->CardNo);

	//���̨����������
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 847108;
	SetHeadCol(&sPack, F_LVOL0,F_LSERIAL1,F_LVOL2,0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	//memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));

	//�жϵ�½ģʽ��ʹ�ÿͻ��ŵ�½����ѧ���ŵ�½
	sPack.pack.lvol0=atoi(card_id);
	sPack.pack.lserial1=pNode->RecvNo;
	sPack.pack.lvol2=TXCODE_BANK_SCHOOL;

	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
		return E_TRANS_UNKNOW_ERROR;
	}	
	return 0;

}


/*
int Do_Compare( BANK_TRANS_REQUEST *pBankTrans )
{
	
	char mac_key[32]="";
	char mac[16]="";
	int ret;

	BANK_TRANS_REQUEST BankTransPak;

	memcpy(mac_key,STATIC_KEY,sizeof(mac_key));
	memset(&BankTransPak,0,BANK_TRANS_PACKLEN);

	//д���״���
	memcpy( BankTransPak.TradeCode,TRADE_BANK_COMP, sizeof(BankTransPak.TradeCode));
	//д�������ںͽ���ʱ��
	getsysdate(BankTransPak.TradeDate);
	getsystime(BankTransPak.TradeTime);
	//дԺУ����
	sprintf(BankTransPak.CustNo,"%-16s",SCHOOL_CODE);
	//дУ��mac��

	//дУ��mac��----���մ˴�Ӧ�������лش������Ķ�̬��Կ��mac��Կ���˴��Ĺ�����
	generate_mac((char*)(&BankTransPak),sizeof(BankTransPak),BankTransPak.MAC);
	//ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,BankTransPak.MAC);

	TRACE_BANK_TRANS(&BankTransPak,"send compare package");

	//�������ݵ����в�ͬʱ�����������ݣ��˴����жϷ��ص�macУ��
	ret=send_to_and_recv_from_bank((char*)(&BankTransPak),BANK_TRANS_PACKLEN, (char*)&BankTransPak,BANK_TRANS_PACKLEN,0);

	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return E_TRANS_BANK_NOANSWER;
	}

	TRACE_BANK_TRANS(&BankTransPak,"recv compare package");


	ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,mac);
	ret=memcmp(mac,BankTransPak.MAC,8);
	if(ret)
	{
		writelog(LOG_INFO,"Mac vertify fail,source_mac=[%s],true_mac[%s]",BankTransPak.MAC,mac);
		return	E_TRANS_BANK_RECVERR;
	}

	memcpy(pBankTrans, &BankTransPak, BANK_TRANS_PACKLEN);

	writelog(LOG_INFO,"Congratulation, compare succeed!");

	return 0;


}*/
int Do_Compare_file()
{
/*
	FILE *fp;
	TIniFile tf;
	char path_name[256]="";
	char file_name[256]="";
	int ret=0;
	int cnt=0;
	int i=0;

	BANK_COMPARE_RECODE compare,compare1;
	T_t_tif_bank_comp	bank_comp;
	T_t_tif_report_trans_comp trans_comp;
	T_t_tif_tradeserial	tradeserial;
	T_t_tif_tradeserial_his his_tradeserial;
	T_t_tif_diff_transfer  diff_transfer;

	char logicdate[10]="";
	char tmp_date[10]="";
	char forward_date[10]="";

	double trans_count=0;
	double bank_count=0;
	double trans_amt=0;
	double bank_amt=0;
	double second=0;

	double temp=0;
	char *p=getenv("BIN_PATH");

	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return ret;
	}

	ret=datetime2second(logicdate, "YYYYMMDD", &second);
	if(ret)
	{
		writelog(LOG_ERR,"datetime2second error,errcode=[%d]",ret);
		return 	ret;
	}
	 //trans_count=0;
	 //bank_count=0;
	 //trans_amt=0;
	// bank_amt=0;

	second=second-24*60*60;
	ret=second2datetime(second, forward_date, "YYYYMMDD");
	if(ret)
	{
		writelog(LOG_ERR,"second2datetime error,errcode=[%d]",ret);
		return 	ret;
	}

	memset(&bank_comp,0,sizeof(bank_comp));
	memset(&compare,0,sizeof(compare));
	memset(&trans_comp,0,sizeof(trans_comp));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&his_tradeserial,0,sizeof(his_tradeserial));

	memset(&compare1,0x30,sizeof(compare1));

	ret=DB_t_tif_report_trans_comp_read_by_cmp_date(forward_date,&trans_comp);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_t_tif_report_trans_comp_read_by_cmp_date error,errcode=[%d]",ret);
		goto LRet;
	}
	if(1==trans_comp.cmp_flag)
	{
		writelog(LOG_ERR,"trans_comp.cmp_flag =1,already compare!");
		goto LRet;
	}
	//���û�������
	if(p==NULL)
	{
	   	writelog(LOG_ERR,"Cann't get env HOME PATH\n");
	   	return -1;
	}
	//sprintf(path_name,"%s/ftp",p);
	sprintf(path_name,"%s",p);
	//strcpy(path_name,"/bank/ykt/src/bank/ftp");
	sprintf(file_name,"%s/XYK00002.%8.8s",path_name,forward_date);
	writelog(LOG_ERR,"Open indirect file=[%s]",file_name);
	if((fp = fopen(file_name,"rb"))==NULL)
	{
		writelog(LOG_ERR,"Open indirect file error,file=[%s]",file_name);
		return	-1;
	}

	while(!feof(fp))
	{
		memset(&bank_comp,0,sizeof(bank_comp));
		memset(&compare,0,sizeof(compare));
		cnt++;
		if(NULL==fgets((char *)(&compare),sizeof(compare),fp))
		{
			writelog(LOG_ERR,"fgets error,");
			continue;
		}
		//��֪��Ϊʲô������Ҫ��һ�����ܶ�?
		if((cnt+2)%2==0)	continue;
		//��ʼ���и�ֵ
		if(memcmp(&compare,&compare1,10)==0)	break;
		else
		{
			strncpy(bank_comp.op_date,forward_date,sizeof(bank_comp.op_date)-1);
			memcpy(bank_comp.tx_code,compare.TradeCode,2);
			bank_comp.card_id=atoi(compare.GDCAccount);
			memcpy(bank_comp.bankcard,compare.BankCard,20);
			bank_comp.local_sn=atoi(compare.LocalSn);
			//printf("--------local_sn[%d]=[%d]\n",cnt,bank_comp.local_sn);
			memcpy(bank_comp.bank_sn,compare.BankSn,20);
			strncpy(bank_comp.trans_money,compare.TransMomoy,9);

			ret=DB_t_tif_bank_comp_add(&bank_comp);
			if(ret)
			{
				writelog(LOG_ERR,"DB_t_tif_bank_comp_add rows[%d] error,errcode=[%d]",cnt,ret);
				goto LRet;
			}
		}
	}
	//��ȡ�����ļ��������رն����ļ����ύ����
	//printf("Line=[%d]\n",__LINE__);
	if(fclose(fp))
	{
		writelog(LOG_ERR,"Close file error,file=[%s]",file_name);
		goto LRet;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		goto LRet;
	}

	//��ʼ���ж���
	cnt=0;

	//������
	ret=DB_his_t_tif_tradeserial_get_count_by_serial_type(&temp,240001,forward_date);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_get_count_by_serial_type err,errcode=[%d]",ret);
		goto LRet;
	}
	trans_count=trans_count+temp;
	trans_comp.localself_num=trans_count;

	ret=DB_his_t_tif_tradeserial_get_sum_by_serial_type(&temp, 240001, forward_date);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_his_t_tif_tradeserial_get_sum_by_serial_type err,errcode=[%d]",ret);
		goto LRet;
	}
	trans_amt=trans_amt+temp;
	trans_comp.localself_amt=trans_amt;

	ret=DB_t_tif_bank_comp_open_select_by_cur1_and_op_date(forward_date);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_bank_comp_open_select_by_cur1_and_op_date err,errcode=[%d]",ret);
		goto LRet;
	}
	while(1)
	{
		ret=DB_t_tif_bank_comp_fetch_select_by_cur1(&bank_comp);
		if(ret)
		{
			DB_t_tif_bank_comp_close_select_by_cur1();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"There havn't record from t_tif_bankcomp table!");
						break;
					}
				else		break;
			}
			else
				goto LRet;
		}
		//���Ӷ��ڷ�01������Ľ��׵��ų�(����:����)
		if(1!=atoi(bank_comp.tx_code)) 	{continue;}
		cnt++;
		bank_count=bank_count+1;
		bank_amt=bank_amt+atof(bank_comp.trans_money)/100.00;
		memset(&diff_transfer,0,sizeof(diff_transfer));
		//printf("Line=[%d],cnt=[%d]\n",__LINE__,cnt);

		ret=DB_t_tif_tradeserial_his_read_by_bak_date_and_serial_no(forward_date,bank_comp.local_sn,&his_tradeserial);
		if(ret)
		{
			if(100==ret)
			{
				strncpy(diff_transfer.op_date,forward_date,sizeof(diff_transfer.op_date)-1);
				strncpy(diff_transfer.bankcard,bank_comp.bankcard,sizeof(diff_transfer.bankcard)-1);
				diff_transfer.bank_amt=atoi(bank_comp.trans_money)/100.00;
				strncpy(diff_transfer.bank_sn,bank_comp.bank_sn,sizeof(diff_transfer.bank_sn)-1);
				diff_transfer.card_id=bank_comp.card_id;
				diff_transfer.local_sn=bank_comp.local_sn;
				diff_transfer.diff_amt=diff_transfer.bank_amt-diff_transfer.local_amt;
				diff_transfer.status=1;
				ret=DB_t_tif_diff_transfer_add(&diff_transfer);
				if(ret)
				{
					writelog(LOG_ERR,"DB_t_tif_diff_transfer_add error,errcode=[%d]!",ret);
					break;
				}
				continue;
			}
			else
			{
				writelog(LOG_ERR,"DB_t_tif_tradeserial_his_read_lock_by_c0_and_enteract_date_and_serial_no error,errcode=[%d]!",ret);
				break;
			}
		}
		if(his_tradeserial.serial_state!=2)
		{
				strncpy(diff_transfer.op_date,forward_date,sizeof(diff_transfer.op_date)-1);
				strncpy(diff_transfer.bankcard,bank_comp.bankcard,sizeof(diff_transfer.bankcard)-1);
				diff_transfer.bank_amt=atoi(bank_comp.trans_money)/100.00;
				strncpy(diff_transfer.bank_sn,bank_comp.bank_sn,sizeof(diff_transfer.bank_sn)-1);
				diff_transfer.card_id=bank_comp.card_id;
				diff_transfer.local_amt=0;
				diff_transfer.local_sn=bank_comp.local_sn;
				diff_transfer.diff_amt=diff_transfer.bank_amt-diff_transfer.local_amt;
				diff_transfer.status=1;
				ret=DB_t_tif_diff_transfer_add(&diff_transfer);
				if(ret)
				{
					writelog(LOG_ERR,"DB_t_tif_diff_transfer_add error,errcode=[%d]!",ret);
					break;
				}
		}
	}

	trans_comp.bankself_amt=bank_amt;
	trans_comp.bankself_num=bank_count;
	trans_comp.localself_amt=trans_amt;
	trans_comp.localself_num=trans_count;
	trans_comp.cmp_flag=1;
	strncpy(trans_comp.cmp_date,forward_date,sizeof(trans_comp.cmp_date)-1);
	ret=DB_t_tif_report_trans_comp_add(&trans_comp);
	if(ret)
	{
		writelog(LOG_DEBUG,"DB_t_tif_report_trans_comp_add error,errcode=[%d]",ret);
		goto LRet;

	}

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		goto LRet;
	}
	return 0;

LRet:
	db_rollback();
	return ret;

	*/
	return 0;
}
int Do_Compare_file_shoudong()
{
/*
	FILE *fp;
	TIniFile tf;
	char path_name[256]="";
	char file_name[256]="";
	int ret=0;
	int cnt=0;
	int i=0;

	BANK_COMPARE_RECODE compare,compare1;
	T_t_tif_bank_comp	bank_comp;
	T_t_tif_report_trans_comp trans_comp;
	T_t_tif_tradeserial	tradeserial;
	T_t_tif_tradeserial_his his_tradeserial;
	T_t_tif_diff_transfer  diff_transfer;

	char logicdate[10]="";
	char tmp_date[10]="";
	char forward_date[10]="";

	double trans_count=0;
	double bank_count=0;
	double trans_amt=0;
	double bank_amt=0;
	double second=0;

	double temp=0;
	char *p=getenv("BIN_PATH");

	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return ret;
	}

	ret=datetime2second(logicdate, "YYYYMMDD", &second);
	if(ret)
	{
		writelog(LOG_ERR,"datetime2second error,errcode=[%d]",ret);
		return 	ret;
	}
	 //trans_count=0;
	 //bank_count=0;
	 //trans_amt=0;
	// bank_amt=0;

	second=second-24*60*60;
	ret=second2datetime(second, forward_date, "YYYYMMDD");
	if(ret)
	{
		writelog(LOG_ERR,"second2datetime error,errcode=[%d]",ret);
		return 	ret;
	}

	memset(&bank_comp,0,sizeof(bank_comp));
	memset(&compare,0,sizeof(compare));
	memset(&trans_comp,0,sizeof(trans_comp));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&his_tradeserial,0,sizeof(his_tradeserial));

	memset(&compare1,0x30,sizeof(compare1));

	ret=DB_t_tif_report_trans_comp_read_by_cmp_date(forward_date,&trans_comp);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_t_tif_report_trans_comp_read_by_cmp_date error,errcode=[%d]",ret);
		goto LRet;
	}
	if(1==trans_comp.cmp_flag)
	{
		writelog(LOG_ERR,"trans_comp.cmp_flag =1,already compare!");
		goto LRet;
	}
	//���û�������
	if(p==NULL)
	{
	   	writelog(LOG_ERR,"Cann't get env HOME PATH\n");
	   	return -1;
	}
	//sprintf(path_name,"%s/ftp",p);
	sprintf(path_name,"%s",p);
	//strcpy(path_name,"/bank/ykt/src/bank/ftp");
	sprintf(file_name,"%s/XYK00002.%8.8s",path_name,forward_date);
	writelog(LOG_ERR,"Open indirect file=[%s]",file_name);
	if((fp = fopen(file_name,"rb"))==NULL)
	{
		writelog(LOG_ERR,"Open indirect file error,file=[%s]",file_name);
		return	-1;
	}

	while(!feof(fp))
	{
		memset(&bank_comp,0,sizeof(bank_comp));
		memset(&compare,0,sizeof(compare));
		cnt++;
		if(NULL==fgets((char *)(&compare),sizeof(compare),fp))
		{
			writelog(LOG_ERR,"fgets error,");
			continue;
		}
		//��֪��Ϊʲô������Ҫ��һ�����ܶ�?
		if((cnt+2)%2==0)	continue;
		//��ʼ���и�ֵ
		if(memcmp(&compare,&compare1,10)==0)	break;
		else
		{
			strncpy(bank_comp.op_date,forward_date,sizeof(bank_comp.op_date)-1);
			memcpy(bank_comp.tx_code,compare.TradeCode,2);
			bank_comp.card_id=atoi(compare.GDCAccount);
			memcpy(bank_comp.bankcard,compare.BankCard,20);
			bank_comp.local_sn=atoi(compare.LocalSn);
			//printf("--------local_sn[%d]=[%d]\n",cnt,bank_comp.local_sn);
			memcpy(bank_comp.bank_sn,compare.BankSn,20);
			strncpy(bank_comp.trans_money,compare.TransMomoy,9);

			ret=DB_t_tif_bank_comp_add(&bank_comp);
			if(ret)
			{
				writelog(LOG_ERR,"DB_t_tif_bank_comp_add rows[%d] error,errcode=[%d]",cnt,ret);
				goto LRet;
			}
		}
	}
	//��ȡ�����ļ��������رն����ļ����ύ����
	//printf("Line=[%d]\n",__LINE__);
	if(fclose(fp))
	{
		writelog(LOG_ERR,"Close file error,file=[%s]",file_name);
		goto LRet;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		goto LRet;
	}

	//��ʼ���ж���
	cnt=0;

	//������
	ret=DB_his_t_tif_tradeserial_get_count_by_serial_type(&temp,240001,forward_date);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_get_count_by_serial_type err,errcode=[%d]",ret);
		goto LRet;
	}
	trans_count=trans_count+temp;
	trans_comp.localself_num=trans_count;

	ret=DB_his_t_tif_tradeserial_get_sum_by_serial_type(&temp, 240001, forward_date);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_his_t_tif_tradeserial_get_sum_by_serial_type err,errcode=[%d]",ret);
		goto LRet;
	}
	trans_amt=trans_amt+temp;
	trans_comp.localself_amt=trans_amt;

	ret=DB_t_tif_bank_comp_open_select_by_cur1_and_op_date(forward_date);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_bank_comp_open_select_by_cur1_and_op_date err,errcode=[%d]",ret);
		goto LRet;
	}
	while(1)
	{
		ret=DB_t_tif_bank_comp_fetch_select_by_cur1(&bank_comp);
		if(ret)
		{
			DB_t_tif_bank_comp_close_select_by_cur1();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"There havn't record from t_tif_bankcomp table!");
						break;
					}
				else		break;
			}
			else
				goto LRet;
		}
		cnt++;
		bank_count=bank_count+1;
		bank_amt=bank_amt+atof(bank_comp.trans_money)/100.00;
		memset(&diff_transfer,0,sizeof(diff_transfer));
		//printf("Line=[%d],cnt=[%d]\n",__LINE__,cnt);

		ret=DB_t_tif_tradeserial_his_read_by_bak_date_and_serial_no(forward_date,bank_comp.local_sn,&his_tradeserial);
		//��ˮ����û�м�¼�����
		if(ret)
		{
			if(100==ret)
			{
				strncpy(diff_transfer.op_date,forward_date,sizeof(diff_transfer.op_date)-1);
				strncpy(diff_transfer.bankcard,bank_comp.bankcard,sizeof(diff_transfer.bankcard)-1);
				diff_transfer.bank_amt=atoi(bank_comp.trans_money)/100.00;
				strncpy(diff_transfer.bank_sn,bank_comp.bank_sn,sizeof(diff_transfer.bank_sn)-1);
				diff_transfer.card_id=bank_comp.card_id;
				diff_transfer.local_sn=bank_comp.local_sn;
				diff_transfer.diff_amt=diff_transfer.bank_amt-diff_transfer.local_amt;
				diff_transfer.status=1;
				ret=DB_t_tif_diff_transfer_add(&diff_transfer);
				if(ret)
				{
					writelog(LOG_ERR,"DB_t_tif_diff_transfer_add error,errcode=[%d]!",ret);
					break;
				}
				continue;
			}
			else
			{
				writelog(LOG_ERR,"DB_t_tif_tradeserial_his_read_lock_by_c0_and_enteract_date_and_serial_no error,errcode=[%d]!",ret);
				break;
			}
		}
		//��ˮ���д��ڣ�����û�����˵����
		if(his_tradeserial.serial_state!=2)
		{
				strncpy(diff_transfer.op_date,forward_date,sizeof(diff_transfer.op_date)-1);
				strncpy(diff_transfer.bankcard,bank_comp.bankcard,sizeof(diff_transfer.bankcard)-1);
				diff_transfer.bank_amt=atoi(bank_comp.trans_money)/100.00;
				strncpy(diff_transfer.bank_sn,bank_comp.bank_sn,sizeof(diff_transfer.bank_sn)-1);
				diff_transfer.card_id=bank_comp.card_id;
				diff_transfer.local_amt=0;
				diff_transfer.local_sn=bank_comp.local_sn;
				diff_transfer.diff_amt=diff_transfer.bank_amt-diff_transfer.local_amt;
				diff_transfer.status=1;
				ret=DB_t_tif_diff_transfer_add(&diff_transfer);
				if(ret)
				{
					writelog(LOG_ERR,"DB_t_tif_diff_transfer_add error,errcode=[%d]!",ret);
					break;
				}
		}
	}

	trans_comp.bankself_amt=bank_amt;
	trans_comp.bankself_num=bank_count;
	trans_comp.localself_amt=trans_amt;
	trans_comp.localself_num=trans_count;
	trans_comp.cmp_flag=1;
	strncpy(trans_comp.cmp_date,forward_date,sizeof(trans_comp.cmp_date)-1);
	ret=DB_t_tif_report_trans_comp_add(&trans_comp);
	if(ret)
	{
		writelog(LOG_DEBUG,"DB_t_tif_report_trans_comp_add error,errcode=[%d]",ret);
		goto LRet;

	}

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		goto LRet;
	}
	return 0;

LRet:
	db_rollback();
	return ret;

	*/
	return 0;
}

/*int Do_Transfer(BANK_TRANS_REQUEST *pBankTrans)
{

	//char buffer[20]="";
	char temp[128]="";
	int ho_OpCount=0;
	int delay_time=0;
	double ho_Fee_Change=0;
	int ret=0;
	FILE *fp;
	TIniFile tf;
	int nrows=0;
	char path_name[128]="";
	char file_name[128]="";
	BANK_TRANSFER_HEAD		trans_head;
	BANK_TRANSFER_RECORD	trans_record;
	T_v_tif_shopdeptfee	v_shopdeptfee;
	T_t_cif_shop		t_shop;

	//ϵͳ���ڽ��㣬�������ɻ����ļ�
	//sleep(1);
	//ret=DB_v_tif_shopdeptfee_read_sum_fee(&ho_OpCount,&ho_Fee_Change);
	if(ret)
	{
		writelog(LOG_ERR,"DB_v_tif_shopdeptfee_read_sum_fee err [%d]",ret);
		return ret;
	}
	ho_OpCount=4;
	ho_Fee_Change=12345.98;
	strcpy(path_name,"/ykt/ykt/src/bank/ftp");
	sprintf(file_name,"%s/fd_%8.8s",path_name,getsysdate(NULL));

	#ifdef DEBUG
	//	strcpy(path_name,"./ftp/fd_20041009");
		writelog(LOG_ALERT,"file_name2=[%s]",file_name);
	#endif

	fp = fopen(file_name,"wb");
	if (fp==NULL)
	{
		writelog(LOG_ALERT,"Open indicate file fail");
		return -1;
	}
	memcpy(trans_head.rmb_batch_no,BATCH_NO,sizeof(trans_head.rmb_batch_no));
	fprintf(fp,"%-14.14s",trans_head.rmb_batch_no);		//�������

	memcpy(trans_head.rmb_start_seq,"000000",6);
	fprintf(fp,"%-6.6s",trans_head.rmb_start_seq);			//��000000

	trans_head.rmb_acc_status='0';
	fprintf(fp,"%c",trans_head.rmb_acc_status);			//����״̬����0��

	trans_head.rmb_chk_status='2';
	fprintf(fp,"%c",trans_head.rmb_chk_status);			//���״̬����2��

	sprintf(trans_head.rmb_total_amount,"%-13d",int(ho_Fee_Change*100));
	fprintf(fp,"%-13.13s",trans_head.rmb_total_amount);		//�ܽ��(11λ����2λС������С����)

	sprintf(trans_head.rmb_total_num,"%-6d",ho_OpCount);
	fprintf(fp,"%-6.6s",trans_head.rmb_total_num);			//�ܱ���

	fprintf(fp,"%-13.13s",trans_head.rmb_enter_amount);	//���ʽ��

	fprintf(fp,"%-6.6s",trans_head.rmb_enter_num);			//���ʱ���

	sprintf(trans_head.rmb_unit_name,"%-40s",UNIT_NAME);
	fprintf(fp,"%-40.40s",trans_head.rmb_unit_name);		//��λ����
#ifdef DEBUG
	writelog(LOG_ALERT,"trans_head.rmb_unit_name=[%s]",trans_head.rmb_unit_name);
#endif

	strcpy(trans_head.rmb_unit_account,UNIT_ACCOUNT);
	//sprintf(trans_head.rmb_unit_account,"%-20s"UNIT_ACCOUNT);
	fprintf(fp,"%-20.20s",trans_head.rmb_unit_account);		//��λ�ʺ�
#ifdef DEBUG
	writelog(LOG_ALERT,"trans_head.rmb_unit_account=[%s]",trans_head.rmb_unit_account);
#endif

	memcpy(trans_head.rmb_apply_date,getsysdate(NULL),sizeof(trans_head.rmb_apply_date));
	fprintf(fp,"%-8.8s",trans_head.rmb_apply_date);			//�����������ڣ��������ڣ�

	//memcpy(trans_head.rmb_send_date,trans_head.rmb_apply_date,sizeof(trans_head.rmb_apply_date));
	memcpy(trans_head.rmb_send_date,getsystime(NULL),sizeof(trans_head.rmb_send_date));
	fprintf(fp,"%-8.8s",trans_head.rmb_send_date);			//�ϴ����ڣ��������ڣ�

#ifdef DEBUG
	printf("[%14.14s]\n",trans_head.rmb_batch_no      ); 	//�������
	printf("[%6.6s]\n",trans_head.rmb_start_seq      ); 		//��000000
	printf("[%c]\n",trans_head.rmb_acc_status        ); 		//����״̬����0��
	printf("[%c]\n",trans_head.rmb_chk_status        ); 		//���״̬����2��
	printf("[%13.13s]\n",trans_head.rmb_total_amount  ); 	//�ܽ��(11λ����2λС������С����)
	printf("[%6.6s]\n",trans_head.rmb_total_num      ); 	//�ܱ���
	printf("[%13.13s]\n",trans_head.rmb_enter_amount ); 	//���ʽ��(11λ����2λС������С����)
	printf("[%6.6s]\n",trans_head.rmb_enter_num     ); 	//���ʱ���
	printf("[%40.40s]\n",trans_head.rmb_unit_name    ); 	//��λ����
	printf("[%20.20s]\n",trans_head.rmb_unit_account  ); 	//��λ�ʺ�
	printf("[%8.8s]\n",trans_head.rmb_apply_date     ); 	//�����������ڣ��������ڣ�
	printf("[%8.8s]\n",trans_head.rmb_send_date     );  	//�ϴ����ڣ��������ڣ�
#endif

	//д�뻮���ļ�
	// fprintf(fp,(char*)(&trans_head));
	strcpy(temp,"1");
	ret=DB_v_tif_shopdeptfee_open_select_by_c6_and_is_indep(temp);
	if(ret)
	{
		//db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ALERT,"DB_v_tif_shopdeptfee_open_select_by_c6_and_is_indep[%d]",ret);
		return ret;
	}

	while(1)
	{
		//��ʼ����������
		ho_Fee_Change=0;
		memset(&v_shopdeptfee,0,sizeof(v_shopdeptfee));
		memset(&t_shop,0,sizeof(t_shop));
		ret=DB_v_tif_shopdeptfee_fetch_select_by_c6(&v_shopdeptfee);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				if(0==nrows)
				{
					writelog(LOG_ERR,"DB_v_tif_shopdeptfee_fetch_select_by_c6[%d]",ret);
					break;
				}
				else		break;	//ѭ����¼����
			}
			else
			{
				//db_chk_err(__FILE__,__LINE__,&sqlca);
				writelog(LOG_ERR,"DB_v_tif_shopdeptfee_fetch_select_by_c6[%d]",ret);
				return ret;
			}
		}
		ret=DB_t_cif_shop_read_by_shop_id(v_shopdeptfee.shop_id,&t_shop);
		if(ret)
		{
			//db_chk_err(__FILE__,__LINE__,&sqlca);
			writelog(LOG_ALERT,"DB_t_cif_shop_read_by_shop_id[%d]",ret);
			return ret;
		}
		strcpy(trans_record.rmb_batch_no1,BATCH_NO);
		sprintf(trans_record.rmb_seq_no,"%d",nrows);
		trans_record.rmb_acc_status1='0';
		trans_record.rmb_tran_kind='2';
		strncpy(trans_record.rmb_cust_name,t_shop.b_act_name,sizeof(trans_record.rmb_cust_name));
		strncpy(trans_record.rmb_acc_no,t_shop.b_act_id,sizeof(trans_record.rmb_acc_no));
		trans_record.rmb_cb_cr='0';
		sprintf(trans_record.rmb_tran_amt,"%f",ho_Fee_Change);
		strcpy(trans_record.rmb_cur_code,"001");
		strcpy(trans_record.rmb_host_no,"00000000");
		memcpy(trans_record.rmb_ret_code,"    ",sizeof(trans_record.rmb_ret_code));
		strcpy(trans_record.rmb_acc_date,"00000000");
		strcpy(trans_record.rmb_host_no1,"000000000");
		strcpy(trans_record.rmb_open_branch,"0000000");
		memcpy(trans_record.rmb_vcho_kind,"  ",sizeof(trans_record.rmb_vcho_kind));
		strcpy(trans_record.rmb_vcho_bat_no,"00");
		strcpy(trans_record.rmb_vcho_no,"000000000");
		strcpy(trans_record.rmb_memo,"  ");
		strcpy(trans_record.rmb_tran_info,"  ");

		fprintf(fp,(char*)(&trans_record));

		nrows++;
	}
	fclose(fp);
	memset(pBankTrans,0,BANK_TRANS_PACKLEN);
	//��ʼ���з������㱨��
	memcpy( pBankTrans->TradeCode,TRADE_BANK_BALANCE, sizeof(pBankTrans->TradeCode));	//д���״���
	//д�������ںͽ���ʱ��
	getsysdate(pBankTrans->TradeDate);
	getsystime(pBankTrans->TradeTime);
	//дԺУ����
	sprintf(pBankTrans->CustNo,"%-16s",SCHOOL_CODE);
	//д���п���-�˴�Լ��Ϊ�����ļ���
	sprintf(pBankTrans->BankCardNo,"%8.8s",getsysdate(NULL));
	//дУ��mac��
	//дУ��mac��----���մ˴�Ӧ�������лش������Ķ�̬��Կ��mac��Կ���˴��Ĺ�����
	generate_mac((char*)pBankTrans,sizeof(pBankTrans),pBankTrans->MAC);
	//ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,BankTransPak.MAC);

	TRACE_BANK_TRANS(pBankTrans,"send transfer package");

	//�������ݵ����в�ͬʱ�����������ݣ��˴����жϷ��ص�macУ��
	ret=send_to_and_recv_from_bank((char*)pBankTrans,BANK_TRANS_PACKLEN, (char*)pBankTrans,BANK_TRANS_PACKLEN,delay_time);
	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return E_TRANS_BANK_NOANSWER;
	}
	TRACE_BANK_TRANS(pBankTrans,"recv transfer package");

	//ũ����ʱδУ���mac,������ʱ���ε�

	ret=check_mac((char*)pBankTrans,BANK_TRANS_PACKLEN);
	if(ret)
	{
		writelog(LOG_ERR,"Receive data mac verify error,error code is [%d] ",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_RECVERR);
		return	E_TRANS_BANK_RECVERR;
	}
	writelog(LOG_INFO,"Congratulation, transer succeed!");
	return 0;
}
*/

//�жϸ��豸�Ƿ�ǩ����
int device_login_yes_or_no(int device_id)
{
	int ret=0;
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
//	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));


	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 240009;
	SetHeadCol(&sPack, F_SORDER2, 0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	//memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));

	sprintf(sPack.pack.sorder2,"%d",device_id);
	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		if(ret<0)
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return E_TRANS_UNKNOW_ERROR;
		}
		else
		{		
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return aPack.head.retCode;
		}
	}	
	return 0;
}

int device_login_yes_or_noEx(int device_id, char *szMsg)
{
	int ret = 0;
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
//	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));


	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 240009;
	SetHeadCol(&sPack, F_SORDER2, 0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	//memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));

	sprintf(sPack.pack.sorder2,"%d",device_id);
	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0 || aPack.head.retCode != 0)
	{
		memcpy(szMsg, aPack.pack.vsmess, sizeof(aPack.pack.vsmess) -1);
		
		if (ret < 0)
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return E_TRANS_UNKNOW_ERROR;
		}
		else
		{		
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return aPack.head.retCode;
		}
	}	
	return 0;
}

//�ж������У԰�������Ƿ���ȷ
int verify_card_password(int card_id,char *stuemp_no,int cut_id,char *password)
{
	int ret=0;
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
//	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));


	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 240010;
	SetHeadCol(&sPack, F_SSERIAL0,F_SCUST_AUTH,F_LVOL8,F_SEMP_PWD,0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	//memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));

	sprintf(sPack.pack.sserial0,"%d",card_id);
	des2src(sPack.pack.scust_auth, stuemp_no);
	sPack.pack.lvol8=cut_id;
	des2src(sPack.pack.semp_pwd,password);
	
	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		if(ret<0)
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return E_TRANS_UNKNOW_ERROR;
		}
		else
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return aPack.head.retCode;
		}
	}	
	writelog(LOG_INFO,"verify_card_password get cardno[%d]",aPack.pack.lvol0);
	sprintf(password,"%d",aPack.pack.lvol0);
	return 0;

}
int VerifyCardPwd(int cardno,char *cardpwd, char *szMsg)
{
	int ret=0;
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
//	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));


	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 240000;
	SetHeadCol(&sPack, F_LVOL0,F_SCUST_LIMIT,0);       // ���÷���windows BU��ͷ����ͼ��Ϣ

	sPack.pack.lvol0 = cardno;
	des2src(sPack.pack.scust_limit,cardpwd);
	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);

	if (ret < 0 || aPack.head.retCode!=0)
	{
		memcpy(szMsg, aPack.pack.vsmess, sizeof(aPack.pack.vsmess) -1);
		if (ret < 0)
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return E_TRANS_UNKNOW_ERROR;
		}
		else
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return aPack.head.retCode;
		}
	}	
	return 0;
}



int verify_card_passwordEx(int card_id,char *stuemp_no,int cut_id,char *password, char *szMsg)
{
	int ret=0;
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
//	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));


	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 240010;
	SetHeadCol(&sPack, F_SSERIAL0,F_SCUST_AUTH,F_LVOL8,F_SEMP_PWD,0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	//memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));

	sprintf(sPack.pack.sserial0,"%d",card_id);
	des2src(sPack.pack.scust_auth, stuemp_no);
	sPack.pack.lvol8 = cut_id;
	des2src(sPack.pack.semp_pwd,password);
	
	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);

	if (ret < 0 || aPack.head.retCode!=0)
	{
		memcpy(szMsg, aPack.pack.vsmess, sizeof(aPack.pack.vsmess) -1);

		if (ret < 0)
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return E_TRANS_UNKNOW_ERROR;
		}
		else
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return aPack.head.retCode;
		}
	}	
	return 0;
}
int QryBankCardNo(int cardno,char *bankcardno,char *szMsg)
{
	int ret=0;
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
//	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));

	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 841602;
	SetHeadCol(&sPack, F_LVOL0,F_SSTATUS0,0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	sPack.pack.lvol0=cardno;
	sPack.pack.sstatus0[0]='Q';
	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		memcpy(szMsg, aPack.pack.vsmess, sizeof(aPack.pack.vsmess) -1);
		if(ret<0)
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return E_TRANS_UNKNOW_ERROR;
		}
		else
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return aPack.head.retCode;
		}
	}	
	strcpy(bankcardno,aPack.pack.scard0);
	return 0;
}

int verify_sch_bank_relationship(int cut_id,int card_id,char *stuemp_no,int area_id,char *bankcard_no)
{
	int ret=0;
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
//	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));

	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 240011;
	SetHeadCol(&sPack, F_LVOL8,F_SCUST_AUTH,F_LVOL0,F_SPHONE,F_LVOL1,0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	//memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));
	sPack.pack.lvol0=card_id;
	sPack.pack.lvol8=cut_id;
	sPack.pack.lvol1=area_id;
	des2src(sPack.pack.scust_auth,stuemp_no);
	des2src(sPack.pack.sphone,bankcard_no);

	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		if(ret<0)
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return E_TRANS_UNKNOW_ERROR;
		}
		else
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return aPack.head.retCode;
		}
	}	
	return 0;
}
int SetHeadCol(ST_CPACK *in_cpack, ...)
{
	va_list ap;
	int arg;
	va_start(ap, in_cpack);
	while ((arg = va_arg(ap, int)) >= 0)
	{
		SetParmBit(&(in_cpack->head), arg);
	}
	va_end(ap);
    return(g_SvrLink.SetCol(0, in_cpack->head.ParmBits));
}
int Is_out_of_service()
{
	char b_time[6+1]="";
	char e_time[6+1]="";
	char cur_time[6+1]="";
	
	memcpy(b_time,g_Bank.SERV_TIME,6);
	memcpy(e_time,g_Bank.SERV_TIME+7,6);

	getsystime(cur_time);
//	writelog(LOG_INFO,"B_TIME=[%s],E_TIME=[%s],CUR_TIME=[%s]",b_time,e_time,cur_time);

	if((strncmp(cur_time,b_time,6)<=0)||(strncmp(cur_time,e_time,6)>=0))
	{
		return -1;
	}
	return 0;
}

int do_update_device_state(INNER_TRANS_REQUEST * pNode)
{
	int ret=0;
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
//	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));

	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 930057;
	SetHeadCol(&sPack, F_SORDER2,0);       // ���÷���windows BU��ͷ����ͼ��Ϣ

	des2src(sPack.pack.sorder2,pNode->TerminalId);

	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		if(ret<0)
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return E_TRANS_UNKNOW_ERROR;
		}
		else
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return aPack.head.retCode;
		}
	}	
	return 0;


}
int do_updateconsumelimit(ST_PACK *in_pack)
{
	int ret=0;
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
//	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));

	ResetNormalCPack(&sPack, 0, 1);
	SetHeadCol(&sPack, F_SSTATUS1,F_LWITHDRAW_FLAG,F_LVOL0,F_LVOL6,F_LVOL7,F_SSTATION1,F_DAMT11,F_DAMT12,0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	sPack.head.RequestType = 846320;
	sPack.pack.lwithdraw_flag=atoi(in_pack->sorder2);
	sPack.pack.sstatus1[0]='1';
	sPack.pack.lvol0 = atoi(in_pack->sserial0);
	sPack.pack.damt11 =atof(in_pack->sserial1);
	sPack.pack.damt12 =atof(in_pack->sorder1);

//	writelog(LOG_INFO,"singlelimit[%.2lf]",in_pack->sserial1);
//	writelog(LOG_INFO,"daylimit[%.2lf]",in_pack->sorder1);
//	writelog(LOG_INFO,"drtp branchno[%d]bccbasefuncno[%d]timeout[%d]",g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT);
	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		if(ret<0)
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return E_TRANS_UNKNOW_ERROR;
		}
		else
		{
			writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
			return aPack.head.retCode;
		}
	}	
	return 0;
}

int Get_cut_name_and_id(int card_id,char *cut_name,char *id,char *stuempno)
{
	int ret=0;
	ST_PACK ArrayPack[50];			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
//	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(ArrayPack, 0, sizeof(ST_PACK )*50);
	
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 846602;
	SetHeadCol(&sPack,F_LVOL0,F_SALL_NAME,F_SEMAIL2, 0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	//memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));
	sPack.pack.lvol0=card_id;
	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, ArrayPack);
	if (ret < 0)
	{
		writelog(LOG_ERR,"Call[%d] ret[%d],errcode[%d],msg[%s]",sPack.head.RequestType,ret,aPack.head.retCode,aPack.pack.vsmess);
	    	if (-2 == ret)
	       	 return E_TRANS_INNER_TIMEOUT;
	    	else
	        	return E_TRANS_INNER_TIMEOUT;
	}	
	//�����̨ʧ��,��˴����غ�̨���صĴ�����
	if(aPack.head.retCode)
	{
		return aPack.head.retCode;
	}
	strcpy(cut_name,aPack.pack.sall_name);
	strcpy(id,aPack.pack.semail2);
	strcpy(stuempno,aPack.pack.spager);
	return 0;
}
