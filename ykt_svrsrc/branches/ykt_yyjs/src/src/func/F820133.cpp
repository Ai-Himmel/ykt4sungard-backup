/* ----------------------------------------------------------
 * 程序名称：F820133.c
 * 创建日期：2004-8-31 09：44
 * 程序作者：黄勋章
 * 版本信息：1.0.0.0
 * 程序功能：卡物理结构信息删除
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


int F820133(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	T_t_pif_cardstrut acardstru;
	int scode=0;
	int v_id=0;
	
	memset(&acardstru,0,sizeof(acardstru));
	
	//从cpack中取值
	v_id = in_pack->lvol3;
	acardstru.id = in_pack->lvol3;
	
	//执行逻辑
	scode=DB_t_pif_cardstrut_del_by_id(v_id);
	
	if(SC_NOTFOUND==scode){
		*pRetCode=E_DB_CARDSTRUT_N;
		sprintf(szMsg,"卡物理结构信息表无相应记录，SQLLCODE=%d\n",scode);
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ERR,szMsg);
		goto L_Ret;	
	}
	if(0!=scode)
	{
		*pRetCode=E_DB_CARDSTRUT_D;
		sprintf(szMsg,"卡物理结构信息表删除错误，SQLLCODE=%d\n",scode);
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ERR,szMsg);
		goto L_Ret;		
	}
	return 0;	
	L_Ret:
		return -1;
}
