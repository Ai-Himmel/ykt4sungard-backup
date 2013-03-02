/* ----------------------------------------------------------
 * 创建日期：2010-11-04
 * 程序作者：xlh
 * 版本信息：1.0.0.0
 * 程序功能：四川建设银行银行卡绑定
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
#include "CI_Datatype.h"
#include "Custom_Interface.h"
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
//int BankCardRelation(tagBankCardRelation* BCR);

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

	ret=ToRegister(handle,rPack,pRetCode,szMsg);	
	/*
	SetCol(handle,0);
	SetCol(handle,F_LSAFE_LEVEL,F_VSVARSTR0,F_SCARD0,0);
	if(ret)
	{     
		des2src(OutPack->vsvarstr0,szMsg);
	      	OutPack->lsafe_level=ret;
		return ret;
	}
	des2src(OutPack->scard0,rPack->scard0);
	if (strncmp(rPack->sstatus0,"A",1)==0)
		{
			des2src(OutPack->vsvarstr0,"签约成功!");
		}
	else
		{	
		des2src(OutPack->vsvarstr0,"取消签约成功!");
		}
	PutRow(handle, OutPack, pRetCode, szMsg);
	*/
	return 0;
	
}
