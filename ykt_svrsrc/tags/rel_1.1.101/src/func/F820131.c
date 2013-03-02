/* ----------------------------------------------------------
 * 程序名称：F820131.c
 * 创建日期：2004-8-31 09：44
 * 程序作者：黄勋章
 * 版本信息：1.0.0.0
 * 程序功能：卡物理结构信息增加
            返回  : int 0 表示成功处理，其他作为处理失败
            参数  : TRUSERID *handle 本请求数据的通讯请求端标识
            参数  : ST_PACK *rPack 业务处理请求数据
            参数  : int *iRetCode 处理结果的返回代码，0表示成功，其他就是处理失败，在本业务处理函数调用之前，已经被初始化为0
            参数  : char *szMsg 处理结果的返回信息，在本业务处理函数调用之前，已经被初始化为空""
 * ----------------------------------------------------------
 * 修改日期: 2004-09-08 16：20
 * 修改人员: 蔡扬
 * 修改描述: 修改规范
 * 版本信息：1.0.0.1
 * 备注信息
 */


#include "fdsqc.h"
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "errdef.h"
#include "pubdb.h"
#include "dictionary.h"
#include "cardstrut_stru.h"


int F820131(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	T_t_pif_cardstrut acardstru;
	double dUniqNo=0;
	int scode=0;
	
	memset(&acardstru,0,sizeof(acardstru));
	        
	//从cpack中取得相应字符串
	acardstru. phytype  = in_pack->lvol4;
	acardstru. sectorno = in_pack->lvol5;
	acardstru. blockno  = in_pack->lvol6;
	acardstru. begin_addr = in_pack->lvol7;
	acardstru. end_addr = in_pack->lvol8;
	acardstru. bytenum  = in_pack->lvol9;
	Strncpy_t(acardstru.define,in_pack->usset0,sizeof(acardstru.define));
	Strncpy_t(acardstru.comments,in_pack->usset1,sizeof(acardstru.comments));
	//设备标志从系统键值表中取得
	scode=getNewUniqNo(KEYTYPE_CARD_STRU,&dUniqNo);
	if(0 != scode)
	{
		*pRetCode=E_DB_SYSKEY_R;
		sprintf(szMsg,"820121：取系统键值表错误，RetCode=%d\n",scode);
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ERR,szMsg);
		goto L_Ret;
	}
	//正确，赋值给结构体
	acardstru.id = (int)dUniqNo;
	
	scode=DB_t_pif_cardstrut_add(&acardstru); 
	
	if(0 != scode)
	{
		*pRetCode=E_DB_CARDSTRUT_I;
		sprintf(szMsg,"卡结构信息表插入错误，SQLLCODE=%d\n",scode);
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ERR,szMsg);
		goto L_Ret;		
	}
	return 0;
L_Ret:
	return -1;
}
