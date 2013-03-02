/* ----------------------------------------------------------
 * 程序名称：F900290.sqc
 * 创建日期：2006-08-31
 * 程序作者：韩海东
 * 版本信息：1.0.0.0
 * 程序功能：查询普通商户结算表--当天情况
 * ----------------------------------------------------------*/
 

#define _IN_SQC_                                  
#include <string.h>                               
#include <stdio.h>    
#include "errdef.h"  
#include "pubdb.h"  
#include "pubfunc.h"      
#include "fdsqc.h"                                
#include "dbfunc.h"
#include "dbfunc_foo.h"


int Select_By_ShopBalance_Bet_Where_1(TRUSERID *handle,int *pRetCode,char *szMsg,int shop_id);
                                                  
// {900170 ,F900170,"查询普通商户结算表" ,"Dean"       ,1,     false,0,0,0,0,0}, 
                                                  
int F900290(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg) 
{                                                 
	char hi_operator[10+1]="";
	char	hi_idNo[255+1]="";

	int i=0;
	int ret=0;
   	char * pch;


	// 准备处理结果中在ST_PACK中使用的字段                     
	Strncpy_t(hi_operator, in_pack->scust_no, sizeof(hi_operator)); 
	Strncpy_t(hi_idNo, in_pack->vsmess, sizeof(hi_idNo)); 

	// 输入参数检查
	trim(hi_operator);
	trim(hi_idNo);

	if (!strlen (hi_operator)) 
	{
		*pRetCode=E_INPUT_NOOPERATOR;
		writelog(LOG_ERR,"Operator is null,hi_operator[%s]errcode[%d]!",hi_operator,E_INPUT_NOOPERATOR);
		goto L_RETU;
	}
   	if (!strlen(hi_idNo)) 
	{
		*pRetCode=E_INPUT_NOFUNCNO;
		writelog(LOG_ERR,"Shopid is null,hi_idNo[%s]errcode[%d]!",hi_operator,E_INPUT_NOFUNCNO);
		goto L_RETU;
   	}
   	pch = strtok (hi_idNo," ");
   	while (pch != NULL)
   	{
	 	i = atoi(pch);
		ret=Select_By_ShopBalance_Bet_Where_1(handle,pRetCode,szMsg,i);
		if(ret)
		{
			*pRetCode=ret;
			writelog(LOG_ALERT,"Select_By_ShopBalance_Bet_Where err,errcode[%d]",ret);
			goto L_RETU;
		}
	     	pch = strtok (NULL, " ");
	}
                                                  
	return 0;

	L_RETU:
		return *pRetCode;                                                                                                
                                                  
}         

int Select_By_ShopBalance_Bet_Where_1(TRUSERID *handle,int *pRetCode,char *szMsg,int shop_id)
{
		int ret=0;
		int nrows = 0;
		int i=0;

		ST_CPACK aPack;                                 
		ST_PACK *out_pack = &(aPack.pack);  
		T_t_tif_report_shop_balance pv_tif_shopdeptfee;
		memset(&pv_tif_shopdeptfee,0,sizeof(pv_tif_shopdeptfee));
		
		i=shop_id;

		ret= DB_v_tif_shopdeptfee_open_select_by_c5();
		if(ret)
		{
			*pRetCode=ret;
			db_chk_err(__FILE__,__LINE__,&sqlca);
			writelog(LOG_ALERT,"DB_v_tif_shopdeptfee_open_select_by_c5 err sqlcode[%d]",SQLCODE);
			goto L_RETU;
		}

		SetCol(handle,0);                           
		//SetCol(handle,F_LVOL0,F_SALL_NAME,F_LVOL1,F_LVOL2,F_DAMT0,F_DAMT1,F_DAMT2,F_SORDER0,F_STX_PWD,0); 
		SetCol(handle,F_SCUST_NO,F_SCUST_NO2,F_SALL_NAME,F_LVOL0,F_LVOL1,F_LVOL2,F_LVOL7,F_DAMT0,F_DAMT1,F_DAMT2,F_SROOM_NO2,F_STX_PWD,F_SORDER0,0); 
									  
	   	while(1)                                             
	   	{                               
			memset(out_pack,0,sizeof(ST_PACK));
		      // 初始化宿主变量                           
	       	ret=DB_v_tif_shopdeptfee_fetch_select_by_c5(&pv_tif_shopdeptfee);
			if(ret)
			{

				db_chk_err(__FILE__,__LINE__,&sqlca);
				if(ret==DB_NOTFOUND)
				{
					if(0==nrows)
					{
						*pRetCode=E_DB_T_REPORT_SHOP_BALANCE_N;
						writelog(LOG_DEBUG,"fetch t_tif_report_shop_balance no data [%d]",ret);
						goto L_RETU;
					}
					else
						break;
				}
				else 	*pRetCode=E_DB_T_REPORT_SHOP_BALANCE_R;
				writelog(LOG_ALERT,"DB_v_tif_shopdeptfee_fetch_select_by_c5 err sqlcode[%d]",SQLCODE);
				goto L_RETU;
			}
			if(i==pv_tif_shopdeptfee.shop_id||i==pv_tif_shopdeptfee.dept_id)
			{
				out_pack->lvol0 = pv_tif_shopdeptfee.shop_id;    
				memset(out_pack->sall_name,0,sizeof out_pack->sall_name);
				Strncpy_t(out_pack->sall_name, pv_tif_shopdeptfee.shop_name, sizeof(out_pack->sall_name)); 
				out_pack->lvol1 = pv_tif_shopdeptfee.dept_id;                     
				out_pack->lvol2 = pv_tif_shopdeptfee.trade_num;                   
				out_pack->damt0 = pv_tif_shopdeptfee.trade_amt;                   
				out_pack->damt1 = pv_tif_shopdeptfee.mng_amt;                     
				out_pack->damt2 = pv_tif_shopdeptfee.trade_amt+pv_tif_shopdeptfee.mng_amt;                   
		      	PutRow(handle,out_pack,pRetCode,szMsg);      
		      	nrows++;     
			}

	   	}                                   
	       DB_v_tif_shopdeptfee_close_select_by_c5();
//	   	EXEC SQL CLOSE C1;      

		return 0;
		L_RETU:
			return *pRetCode;                                                                                                

	}
                                                  

