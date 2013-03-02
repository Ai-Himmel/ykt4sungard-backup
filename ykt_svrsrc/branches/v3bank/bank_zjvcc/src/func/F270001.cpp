/* ----------------------------------------------------------
 * 创建日期：2009-03-22
 * 程序作者：闻剑
 * 版本信息：1.0.0.0
 * 程序功能：南京工商银行银行卡绑定

 * 修改日期:	2011-01-14
 * 修改作者:	王彦兵
 * 
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
#include "bank_interface.h"

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


// 修改校验码
int Bank_ChangePin(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);

// 重置校验码
int Bank_ResetPin(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);


int F270001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	writelog(LOG_INFO,"270001 bind_process type[%s]",rPack->sstatus0);
	switch(rPack->sstatus0[0])
	{
		case 'A':				// 银行卡绑定
			return Bank_Bind(handle, rPack, pRetCode, szMsg);
		case 'D':				// 银行卡解除绑定
			return Bank_UnBind(handle, rPack, pRetCode, szMsg);
		case 'C':				// 校验码修改
			return Bank_ChangePin(handle, rPack, pRetCode, szMsg);
		case 'R':				// 校验码重置
			return Bank_ResetPin(handle, rPack, pRetCode, szMsg);			
		default:				// 银行卡绑定关系查询
			return Bank_Querybind(handle, rPack, pRetCode, szMsg);
	}
	return 0;
}

