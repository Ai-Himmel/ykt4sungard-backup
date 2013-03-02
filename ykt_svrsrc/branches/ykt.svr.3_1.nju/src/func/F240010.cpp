/* --------------------------------------------
 * 程序名称: F240010.sqc
 * 创建日期: 2007-07-21
 * 程序作者: 韩海东
 * 版本信息: 1.0.0.0
 * 程序功能: 判断输入的卡密码是否正确
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "acctrans.h"
#include "busqc.h"

int F240010(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	char key[32+1]="";
	char pwd[32+1]="";
	char account_pwd[6+1]="";
	int ret=0;
	T_t_card card;
	int custid=0;
	char stuempno[20+1]="";
	int cardno=0;
	T_t_card	tCard1;

	memset(&card,0,sizeof(card));
	custid=rPack->lvol8;
	des2src(stuempno,rPack->scust_auth);
	cardno=atoi(rPack->sserial0);
	//writelog(LOG_ERR," stuempno=[%s],custid=[%d],cardno=[%s]",rPack->scust_auth,rPack->lvol8,rPack->sserial0);
	if(cardno<1)
	{
		if(custid<1)//学号,无卡使用
		{
			//挂失时使用，其他不使用
			if(strlen(stuempno)<1)
			{
				return E_TRANS_SCHACC_NOEXIT;
			}
			ret=get_custid_by_stuempno(stuempno,&custid);
			if(ret)
			{
				return ret;
			}
		}
		//客户号
		memset(&tCard1,0,sizeof(tCard1));
		ret=get_cardno_by_custid(custid, &cardno);
		if(ret)
		{
			return ret;
		}
	}
	ret=DB_t_card_read_by_cardno(cardno,&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_card_read_by_cardno error,errcode=[%d],cardno=[%d]",ret,cardno);
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDNO,cardno);
		else
			return E_DB_CARD_R;
	}
	if(card.status[0]!=STATUS_NORMAL)
	{
		return ERRINFO(E_CARD_LOGOUT,card.cardno);
	}	
	strcpy(key,STATIC_SEED_KEY);
	des2src(account_pwd, rPack->semp_pwd);
	EncodePwd(key,account_pwd,pwd, 0);

	//判断卡密码是否正确
	if(0!=strncmp(pwd,card.cardpwd,sizeof(pwd)))
	{
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,card.cardpwd);
		return E_TRANS_SCHCARD_PWDERR;
	}
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);		
	
	SetCol(handle,F_LVOL0,0);	
	outPack->lvol0=card.cardno;
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}


