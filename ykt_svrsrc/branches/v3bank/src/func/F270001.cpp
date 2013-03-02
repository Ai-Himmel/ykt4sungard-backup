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
	
	if(Is_out_of_service())
	{
	    strcpy(szMsg,"不在银行服务时间");			
	    return 8888;
	}
	switch(rPack->sstatus0[0])
	{
	case 'Q':	                                                                        //银行卡查询
			ret=Bank_Query(handle,rPack,pRetCode,szMsg);
			break;
	default:
		ret=Bank_Query(handle,rPack,pRetCode,szMsg);
		break;
	}

	return 0;
}
