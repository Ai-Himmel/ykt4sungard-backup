/* ----------------------------------------------------------
 * 程序名称：F900088.sqc
 * 创建日期：2004-08-27
 * 程序作者：韩海东
 * 版本信息：1.0.0.0
 * 程序功能：与前台交互的生成报表过程(前台触发结帐)
 			 与系统定时结帐有所不同，不会进行逻辑换天，
 			 更新参数等一系列操作
 * ----------------------------------------------------------
 * 修改日期: 2004-09-08
 * 修改人员: 韩海东
 * 修改描述: 统一规范代码
 * 版本信息：1.0.0.1
 * 备注信息
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/


#define _IN_SQC_                                  
#include "fdsqc.h"                                
#include <string.h>                               
#include <stdio.h>    
#include "errdef.h"  
#include "balance.h"                                                

int F900088(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg) 
{                                                 
     

	char		hi_operator[10+1]; 
	char		szNull[] ="";              
	int 		ret=0;													  

	// 解析操作员代码
	Strncpy_t(hi_operator, in_pack->scust_no, sizeof(hi_operator)); 

	// 输入参数检查
	trim(hi_operator);
    	if (strcmp (szNull,hi_operator) == 0) 
	{
		*pRetCode=E_INPUT_NOOPERATOR;
		writelog(LOG_ERR,"hi_operator,hi_operator[%s]errcode[%d]!",hi_operator,E_INPUT_NOOPERATOR);
		goto L_RETU;
	}
  
     	//停止入帐，改数据库全局参数表中的入帐标志
	ret=StopInBalance();
	if(ret)
	{
		writelog(LOG_ERR,"修改日结标志出错!");
		return ret;
	}
	//生成运行情况报表
	ret=CreateActiveReport();
	if(ret)
	{
		writelog(LOG_ERR,"生成运行情况报表出错!");
		return ret;
	}
	//生成操作情况报表
	ret=CreateOperReport();
	if(ret)
	{
		writelog(LOG_ERR,"生成操作情况表失败!");
		return ret;
	}
	//生成普通商户结算报表
	ret=CreateShopReport();
	if(ret)
	{
		writelog(LOG_ERR,"生成商户结算报表失败!");
		return ret;
	}
	//生成资产负债报表
	ret=CreateRichDebtReport();
	if(ret)
	{
		writelog(LOG_ERR,"生成资产负债表失败!");
		return ret;
	}

	//手动结帐结束，启动服务，接收新的入帐流水
	ret=Startup();
	if(ret)
	{
		writelog(LOG_ERR,"系统启动服务失败!");
		return ret;
	}

  	writelog(LOG_ERR,"Manual balance is succeed![%d]",ret);                                        
   	//ERR_DEAL("结帐成功完成!",ret);

    return 0;   

	L_RETU:
		return *pRetCode;                                                                                                
                                          
}                                                 
                                                
