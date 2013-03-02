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
#include "account.h"
#include "fdsqc.h"



int F240010(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	char key[32+1]="";
	char pwd[32+1]="";
	char account_pwd[6+1]="";
	int ret=0;
	T_t_pif_card card;
	int cut_id=0;
	char stuemp_no[20+1]="";
	int card_id=0;
	T_t_pif_card	tCard1;

	memset(&tCard1,0,sizeof(tCard1));
	memset(&card,0,sizeof(card));
	cut_id=rPack->lvol8;
	des2src(stuemp_no,rPack->scust_auth);
	card_id=atoi(rPack->sserial0);
	//writelog(LOG_ERR," stuemp_no=[%s],cut_id=[%d],card_id=[%s]",rPack->scust_auth,rPack->lvol8,rPack->sserial0);
	if(0==card_id)
	{
		if(0==cut_id)
		{
			ret=get_tradecard_no_by_stupid(stuemp_no,&card_id);			//卡标识
			if(ret)
			{
				if(100==ret)
				{
					writelog(LOG_ERR,"get_tradecard_no_by_stupid have no recode,errcode=[%d],stuemp_no=[%s]",ret,stuemp_no);
					*pRetCode=E_TRANS_SCHACC_NOEXIT;
					goto L_RETU;
				}
				if(-811==ret)
				{
					writelog(LOG_ERR,"This customer have more than one card,errcode=[%d],stuemp_no=[%s]",ret,stuemp_no);
					*pRetCode=E_TRANS_SCHCARD_TWICE;
					goto L_RETU;
				}
				writelog(LOG_ERR,"get_tradecard_no_by_stupid error,errcode=[%d]",ret);
				*pRetCode=E_DB_CARD_R;
				goto L_RETU;
			}
		}
		else
		{
			ret=get_curr_card_by_custid(cut_id, &tCard1);
			if(ret)
			{
				if(E_DB_CARD_N==ret)
				{
					writelog(LOG_ERR,"get_curr_card_by_custid have no recode,errcode=[%d]",ret);
					*pRetCode=E_TRANS_SCHACC_NOEXIT;
					goto L_RETU;
				}
				if(E_CUSTOMER_HASNO_NORM_CARD==ret)
				{
					writelog(LOG_ERR,"This customer have more than one card,errcode=[%d]",ret);
					*pRetCode=E_TRANS_SCHACC_DESTORY;
					goto L_RETU;
				}
				writelog(LOG_ERR,"get_curr_card_by_custid error,errcode=[%d]",ret);
				*pRetCode=E_DB_CARD_R;
				goto L_RETU;
			}
			card_id=tCard1.card_id;

		}
	}
	
	ret=DB_t_pif_card_read_by_card_id(card_id,&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_read_by_card_id error,errcode=[%d],card_id=[%d]",ret,card_id);
		*pRetCode=E_DB_CARD_R;
		goto L_RETU;
	}

	strcpy(key,STATIC_SEED_KEY);
	des2src(account_pwd, rPack->semp_pwd);
	EncodePwd(key,account_pwd,pwd, 0);

	//判断卡密码是否正确
	if(0!=memcmp(pwd,card.password,sizeof(pwd)))
	{
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,card.password);
		*pRetCode=E_TRANS_SCHCARD_PWDERR;
		goto L_RETU;
	}
	
	return 0;
L_RETU:
	return -1;
}


