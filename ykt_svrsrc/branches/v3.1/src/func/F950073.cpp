/* --------------------------------------------
 * 创建日期: 2010-10-22 
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 汇多充值机充值请求
 * --------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "acctrans.h"
#include "busqc.h"
#include "interfacefunc.h"
#include "interface.h"
#include "transfunc.h"

extern int addPOSCheckPOS(int deviceid,T_t_device &tDevice);


int F950073(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	char packid[30]={0};
	char reqid[20]={0};
	T_t_device tDevice;
	T_t_transpack transpack;
	CAccTrans *pAccTrans = CAccTrans::getInstance();
	TRANS &trans = pAccTrans->trans;
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);

	memset(&tDevice,0,sizeof tDevice);
	memset(&transpack,0,sizeof transpack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LCERT_CODE,F_SPHONE3,F_LSERIAL0,F_LWITHDRAW_FLAG,0);

	GetCpackDataString(rPack,transpack.reqdata);
	des2src(tDevice.devphyid,rPack->sphone3);
	ret = addPOSCheckPOS(rPack->lwithdraw_flag,tDevice);
	if(ret)
	{
		outPack->lcert_code = ret;
	}
	else
	{
		des2src(transpack.transdate,rPack->sdate0);
		des2src(transpack.transtime,rPack->stime0);
		transpack.reqsno = rPack->lserial0;
		
		sprintf(transpack.packetid,"%s%s%03d",transpack.transdate,transpack.transtime,transpack.reqsno%1000);
		sprintf(transpack.reqid,"%d",tDevice.deviceid);
		transpack.funcno = iRequest;
		transpack.status[0]=TRANSPACKSTATE_NODEAL;
		des2src(transpack.lastupdtime,trans.sysdatetime);
		transpack.datalen = strlen(transpack.reqdata);
		if(rPack->lvol10 == 2) // 中途拔卡,发送交易取消
		{
			transpack.status[0] = TRANSPACKSTATE_WRITEFAILD;
			transpack.revflag = 0;
		}
		else if(rPack->lvol10 == 1)//交易冲正
		{
			transpack.revflag = 1;
		}
		else 
		{
			transpack.errcode = ERRIF_DATA;
			transpack.status[0] = TRANSPACKSTATE_DENY;
		}
		ret = DB_t_transpack_add(&transpack);
		if(ret)
		{
			if(DB_REPEAT == ret)
			{
				//
				des2src(packid,transpack.packetid);
				des2src(reqid,transpack.reqid);
				memset(&transpack,0,sizeof transpack);
				ret = DB_t_transpack_read_lock_by_c0_and_packetid_and_reqid(packid,reqid,&transpack);
				if(ret)
				{
					outPack->lcert_code = ERRIF_SYSTEM;
				}
				else
				{
					
					des2src(transpack.lastupdtime,trans.sysdatetime);
					if(rPack->lvol10 == 2) // 中途拔卡,发送交易取消
					{
						transpack.status[0] = TRANSPACKSTATE_WRITEFAILD;
						transpack.revflag = 0;
					}
					else if(rPack->lvol10 == 1)//交易冲正
					{
						transpack.revflag = 1;
						transpack.retrycnt++;
					}
					else 
					{
						transpack.errcode = ERRIF_DATA;
					}
					ret = DB_t_transpack_update_lock_by_c0(&transpack);
					if(ret)
					{
						outPack->lcert_code = ERRIF_SYSTEM;
					}
					else
					{
						outPack->lcert_code = 0;
					}
				}
				
			}
			else
			{
				outPack->lcert_code = ERRIF_SYSTEM;
			}
		}
		else
		{
			// 没有对应的充值记录
			outPack->lcert_code = 0;
		}
	}
	des2src(outPack->sphone3,tDevice.devphyid);
	outPack->lwithdraw_flag = tDevice.deviceid;
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
	
}

