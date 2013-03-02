/* ----------------------------------------------------------
 * 程序名称：F820123.sqc
 * 创建日期：2004-8-3
 * 程序作者：黄勋章 
 * 版本信息：1.0.0.0
 * 程序功能：设备物理信息删除
 * ----------------------------------------------------------
 
 * 修改日期: 2004-09-08
 * 修改人员: 张汉杰
 * 修改描述: 修改规范
 * 版本信息: 1.0.0.1
 * 备注信息
 * ----------------------------------------------------------*/

#include "fdsqc.h"
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "errdef.h"
#include "pubdb.h"
#include "dictionary.h"
#include "phydevice_stru.h"

// 函数名: F820123.sqc
// 编程  : 黄勋章 2004-8-30 09：44
// 描述  : 设备物理信息删除
// 返回  : int 0 表示成功处理，其他作为处理失败
// 参数  : TRUSERID *handle 本请求数据的通讯请求端标识
// 参数  : ST_PACK *rPack 业务处理请求数据
// 参数  : int *iRetCode 处理结果的返回代码，0表示成功，其他就是处理失败，在本业务处理函数调用之前，已经被初始化为0
// 参数  : char *szMsg 处理结果的返回信息，在本业务处理函数调用之前，已经被初始化为空""

int F820123(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	T_t_pif_phydevice aphydev;
	int scode=0;
	int v_phytype=0;
	
	memset(&aphydev,0,sizeof(aphydev));
	
	v_phytype = in_pack->lvol6;
	aphydev.phytype = in_pack->lvol6;
	
	
	scode=DB_t_pif_phydevice_del_by_phytype(v_phytype);
	
	if(scode==SC_NOTFOUND){
		*pRetCode=E_DB_PHYDEVICE_N;
		sprintf(szMsg,"设备物理结构信息表无相应记录，SQLLCODE=%d\n",scode);
		writelog(LOG_ERR,szMsg);
		db_chk_err(__FILE__,__LINE__,&sqlca);
		goto L_Ret;	
	}
	if(scode!=0)
	{
		*pRetCode=E_DB_PHYDEVICE_D;
		sprintf(szMsg,"设备物理结构信息表删除错误，SQLLCODE=%d\n",scode);
		writelog(LOG_ERR,szMsg);
		db_chk_err(__FILE__,__LINE__,&sqlca);
		goto L_Ret;		
	}
	return 0;
	
	L_Ret:
		return -1;
}
