/* ----------------------------------------------------------
 * 程序名称：F820134.c
 * 创建日期：2004-8-31 09：44
 * 程序作者：黄勋章
 * 版本信息：1.0.0.0
 * 程序功能：卡物理结构信息关键字查询
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

#include "busqc.h"
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "errdef.h"
#include "pubdb.h"
#include "dictionary.h"
#include "cardstrut_stru.h"



int F820134(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	T_t_cardstrut acardstru;
	int v_id=0;
	int nrows=0;
	int r=0;
	
	ST_CPACK aPack;                                
	ST_PACK *out_pack = &(aPack.pack);
	SetCol(handle,F_LVOL3,F_LVOL4,F_LVOL5,F_LVOL6,F_LVOL7,F_LVOL8,F_LVOL9,F_USSET0,F_USSET1,0);
	
	memset(&acardstru,0,sizeof(acardstru));
	
	v_id = in_pack->lvol3;
	
	if(0 == v_id)
	{
		DB_t_cardstrut_open_select_by_c1();
		
		while(1){
			
			memset(&acardstru,0,sizeof(acardstru));
			
			r=DB_t_cardstrut_fetch_select_by_c1(&acardstru);
			if(0 != r)
			{
				if(SC_NOTFOUND==r)
				{
					if(0 == nrows)
					{
						*pRetCode=E_DB_CARDSTRUT_N;
						sprintf(szMsg,"查询卡物理结构信息表无记录,SQLCODE=%d\n",r);
						db_chk_err(__FILE__,__LINE__,&sqlca);
   						writelog(LOG_WARNING,szMsg);
						goto L_Ret_if;
					}
				}
				else
				{
					*pRetCode=E_DB_CARDSTRUT_R;
					sprintf(szMsg,"读取卡物理结构信息表出错,SQLCODE=%d\n",r);
					db_chk_err(__FILE__,__LINE__,&sqlca);
   					writelog(LOG_WARNING,szMsg);
					goto L_Ret_if;
				}
				break;
			}
      	
      	out_pack->lvol3 =  acardstru.id;
      	out_pack->lvol4 =  acardstru.phytype;
      	out_pack->lvol5 =  acardstru.sectorno;
      	out_pack->lvol6 =  acardstru.blockno;
      	out_pack->lvol7 =  acardstru.begin_addr;
      	out_pack->lvol8 =  acardstru.end_addr;
      	out_pack->lvol9 =  acardstru.bytenum;
      	Strncpy_t((char*)out_pack->usset0,acardstru.define,sizeof(out_pack->usset0));
      	Strncpy_t((char*)out_pack->usset1,acardstru.comments,sizeof(out_pack->usset1));
      	
      	PutRow(handle,out_pack,pRetCode,szMsg); 
      	nrows++;             	
      				
      	if (15 == nrows)
      	{
      		// 这里调用AnswerDataPart是为了不让前端等待太长时间，在有15条记录的时候就给返回，至于后续数据就不用管了，BCC与前端自动会将后续数据采集回去
      		AnswerDataPart(handle,*pRetCode,szMsg);
      	}
   	};
   	
   	DB_t_cardstrut_close_select_by_c1();
   	return 0;
   	
   	L_Ret_if:
			DB_t_cardstrut_close_select_by_c1();
			return r;			
	}
	else{
		r=DB_t_cardstrut_read_by_id(v_id,&acardstru);
		if(SC_NOTFOUND==r)
		{
			*pRetCode=E_DB_CARDSTRUT_N;
			sprintf(szMsg,"卡物理结构信息表不存在相应记录,SQLCODE=%d\n",r);
			db_chk_err(__FILE__,__LINE__,&sqlca);
      			writelog(LOG_ERR,szMsg);
			goto L_Ret_else;
		}
		else if(0!=r)
		{
			*pRetCode=E_DB_CARDSTRUT_R;
			sprintf(szMsg,"卡物理信息表读取错误,SQLCODE=%d\n",r);
                     db_chk_err(__FILE__,__LINE__,&sqlca);
      			writelog(LOG_ERR,szMsg);
			goto L_Ret_else;		
		}
		out_pack->lvol3 =  acardstru.id;
      out_pack->lvol4 =  acardstru.phytype;
      out_pack->lvol5 =  acardstru.sectorno;
      out_pack->lvol6 =  acardstru.blockno;
      out_pack->lvol7 =  acardstru.begin_addr;
      out_pack->lvol8 =  acardstru.end_addr;
      out_pack->lvol9 =  acardstru.bytenum;
      Strncpy_t((char*)out_pack->usset0,acardstru.define,sizeof(out_pack->usset0));
      Strncpy_t((char*)out_pack->usset1,acardstru.comments,sizeof(out_pack->usset1));
      
      PutRow(handle,out_pack,pRetCode,szMsg);
      
      return 0; 
      
      L_Ret_else:
			return r; 		
	}
}
