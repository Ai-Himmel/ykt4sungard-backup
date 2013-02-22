/* ----------------------------------------------------------
 * 创建日期：2009-03-22
 * 程序作者：闻剑
 * 版本信息：1.0.0.0
 * 程序功能：南京工商银行银行卡绑定
 * ----------------------------------------------------------*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <signal.h>
#include "profile.h"
#include "mypub.h"  
#include "tcp.h"
#include "cpack.h"
#include "svrlink.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "bupub.h"
#include "transinfo.h"
#include "dictionary.h"
#include "shem.h"
#include "bank.h"

extern CSvrLink g_SvrLink;
#ifndef	DEBUG
	#define	DEBUG
#endif

//银行卡绑定接口
//功能号		:270001

//交易类型  :sstatus0:		'A'  增加 ,'D'  删除 ,'R' 查询
//姓名		:sall_name
//身份证号	:semail2
//学号		:spage
//银行卡号	:scard0

//返回信息
//错误码	    : lsafe_level
//错误信息:vsvarstr0
int BankCardRelation(tagBankCardRelation* BCR);

int F270001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	ST_CPACK aPack;				// 设置应答包
	ST_PACK *OutPack = &(aPack.pack);

	ResetNormalCPack(&aPack, 0, 1);

	if(Is_out_of_service())
	{
	    strcpy(szMsg,"不在银行服务时间");			
	    return 8888;
	}

	tagBankCardRelation  BCR;

	memset(&BCR,0,sizeof(BCR));
	des2src(BCR.stuempno,rPack->spager);
	des2src(BCR.custname,rPack->sall_name);
	des2src(BCR.idno,rPack->semail2);
	des2src(BCR.bankcardno,rPack->scard0);
	BCR.transtype=rPack->sstatus0[0];
	ret=BankCardRelation(&BCR);
	if(ret)
	{
		strcpy(szMsg,BCR.retmsg);
		return ret;
	}
	SetCol(handle,0);
	SetCol(handle,F_LSAFE_LEVEL,F_VSVARSTR0,F_SCARD0,0);
	OutPack->lsafe_level=BCR.retcode;
	des2src(OutPack->scard0,BCR.bankcardno);
	des2src(OutPack->vsvarstr0,BCR.retmsg);
	PutRow(handle, OutPack, pRetCode, szMsg);
	return 0;
}
