/* --------------------------------------------
 * 创建日期: 2010-8-23
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 水控费率设置
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
#include "busqc.h"
#include "acctrans.h"

static int Add846405(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	T_t_waterfeecfg tWaterFeeCfg;
	memset(&tWaterFeeCfg,0,sizeof tWaterFeeCfg);

	
    tWaterFeeCfg.feemode = rPack->lserial0;
    des2src(tWaterFeeCfg.feename,rPack->semail);
    tWaterFeeCfg.purseno = rPack->lwithdraw_flag;
    tWaterFeeCfg.feetypecnt = rPack->lvol10;

    if(tWaterFeeCfg.feetypecnt <= 0)
    {
    	ERRTIP("水控费率参数必须至少有一个类别");
    	return E_COMMON_ERR;
    }

    ret = getNewUniqNo(KEYTYPE_WATERFEECFG,&tWaterFeeCfg.feeid);	//获取最大卡号
    if (ret)
    {
    	writelog(LOG_ERR,"getNewUniqNo KEYTYPE_WATERFEECFG, ret=[%d]",ret);
        return ret;
    }
    ret = DB_t_waterfeecfg_add(&tWaterFeeCfg);
    if(ret)
    {
    	if(DB_REPEAT == ret)
    	{
    		writelog(LOG_ERR,"Add846405,ret=[%d]",ret);
    		return E_DB_WATERFEECFG_E;
    	}
    	else
    	{
    		writelog(LOG_ERR,"Add846405,ret=[%d]",ret);
    		return E_DB_WATERFEECFG_I;
    	}
    }
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);
    SetCol(handle,F_LCERT_CODE,0);
    out_pack->lcert_code = tWaterFeeCfg.feeid;
    PutRow(handle,out_pack,pRetCode,szMsg);
    return 0;
    
}

static int AllDelete(int feeid)
{
	int ret;

	ret = DB_t_waterfeetype_del_by_feeid(feeid);
	if(ret)
	{
		if(DB_NOTFOUND != ret)
		{
			writelog(LOG_ERR,"Delete846405,ret=[%d]",ret);
    		return E_DB_WATERFEETYPE_D;	
    	}
	}
	ret = DB_t_waterfeecfg_del_by_feeid(feeid);
	if(ret)
	{
		if(DB_NOTFOUND != ret)
		{
			writelog(LOG_ERR,"Delete846405,ret=[%d]",ret);
    		return E_DB_WATERFEECFG_D;	
    	}
	}
	return 0;
}


static int Delete846405(ST_PACK *rPack)
{
	int ret;

	ret = AllDelete(rPack->lcert_code);
	if(ret)
	{
		return ret;
	}
	return 0;
}


static int Import846405(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	T_t_waterfeecfg tWaterFeeCfg;
	T_t_waterfeetype tWaterFeetype;

	memset(&tWaterFeeCfg,0,sizeof tWaterFeeCfg);
	memset(&tWaterFeetype,0,sizeof tWaterFeetype);

	ret = DB_t_waterfeecfg_read_by_feeid(rPack->lcert_code,&tWaterFeeCfg);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
    	{
    		writelog(LOG_ERR,"Import846405,ret=[%d]",ret);
    		return E_DB_WATERFEECFG_N;
    	}
    	else
    	{
    		writelog(LOG_ERR,"Import846405,ret=[%d]",ret);
    		return E_DB_WATERFEECFG_R;
    	}
	}
	tWaterFeetype.feeid = tWaterFeeCfg.feeid;
	tWaterFeetype.feecnt = rPack->lvol12;
	tWaterFeetype.feetype= rPack->lvol11;

	if(tWaterFeetype.feecnt >= 1)
	{
		tWaterFeetype.starttime1=rPack->lvol0;
		tWaterFeetype.feetime1=rPack->lvol1;
		tWaterFeetype.feeamt1=rPack->lvol2;
	}
	else
	{
		AllDelete(rPack->lcert_code);
		ERRTIP("每个收费类别至少需要一组费率");
		return E_COMMON_ERR;
	}
	
	if(tWaterFeetype.feecnt >= 2)
	{
		tWaterFeetype.starttime2=rPack->lvol3;
		tWaterFeetype.feetime2=rPack->lvol4;
		tWaterFeetype.feeamt2=rPack->lvol5;
	}
	else
	{
		tWaterFeetype.starttime2=0xFF;
		tWaterFeetype.feetime2=0xFF;
		tWaterFeetype.feeamt2=0xFF;
	}
	
	if(tWaterFeetype.feecnt >= 3)
	{
		tWaterFeetype.starttime3=rPack->lvol6;
		tWaterFeetype.feetime3=rPack->lvol7;
		tWaterFeetype.feeamt3=rPack->lvol8;
	}
	else
	{
		tWaterFeetype.starttime3=0xFF;
		tWaterFeetype.feetime3=0xFF;
		tWaterFeetype.feeamt3=0xFF;
	}

	ret = DB_t_waterfeetype_add(&tWaterFeetype);
	if(ret)
	{
		AllDelete(rPack->lcert_code);
		if(DB_REPEAT == ret)
    	{
    		writelog(LOG_ERR,"Import846405,ret=[%d]",ret);
    		return E_DB_WATERFEETYPE_N;
    	}
    	else
    	{
    		writelog(LOG_ERR,"Import846405,ret=[%d]",ret);
    		return E_DB_WATERFEETYPE_R;
    	}
	}
	return 0;
	
}

static int Read846405(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret,rows;
	T_t_waterfeetype tWaterFeetype;
	T_t_waterfeecfg tWaterFeeCfg;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tWaterFeeCfg,0,sizeof tWaterFeeCfg);
	memset(&tWaterFeetype,0,sizeof tWaterFeetype);

	ResetNormalCPack(&aPack,0,sizeof aPack);
	SetCol(handle,0);
	SetCol(handle,F_LCERT_CODE,F_SEMAIL,F_LWITHDRAW_FLAG,F_LSERIAL0,F_LVOL0,
	F_LVOL1,F_LVOL2,F_LVOL3,F_LVOL4,F_LVOL5,F_LVOL6,F_LVOL7,F_LVOL8,F_LVOL10,F_LVOL11,F_LVOL12,0);

	ret = DB_t_waterfeecfg_read_by_feeid(rPack->lcert_code,&tWaterFeeCfg);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
    	{
    		writelog(LOG_ERR,"Read846405,ret=[%d]",ret);
    		return E_DB_WATERFEECFG_N;
    	}
    	else
    	{
    		writelog(LOG_ERR,"Read846405,ret=[%d]",ret);
    		return E_DB_WATERFEECFG_R;
    	}
	}

	ret = DB_t_waterfeetype_open_select_by_c0_and_feeid(tWaterFeeCfg.feeid);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
    	{
    		writelog(LOG_ERR,"Read846405,ret=[%d]",ret);
    		return E_DB_WATERFEETYPE_N;
    	}
    	else
    	{
    		writelog(LOG_ERR,"Read846405,ret=[%d]",ret);
    		return E_DB_WATERFEETYPE_R;
    	}
	}
	rows = 0;
	while(1)
	{
		memset(&tWaterFeetype,0,sizeof tWaterFeetype);
		ret = DB_t_waterfeetype_fetch_select_by_c0(&tWaterFeetype);
		if(ret)
		{
			DB_t_waterfeetype_close_select_by_c0();
			if(DB_NOTFOUND == ret)
				break;
			else
				return E_DB_WATERFEETYPE_R;
		}
		rows++;
		out_pack->lcert_code = tWaterFeetype.feeid;
		des2src(out_pack->semail,tWaterFeeCfg.feename);
		out_pack->lserial0 = tWaterFeeCfg.feemode;
		out_pack->lwithdraw_flag = tWaterFeeCfg.purseno;
		
		out_pack->lvol11 = tWaterFeetype.feetype;
		out_pack->lvol12 = tWaterFeetype.feecnt;
		
		out_pack->lvol0 = tWaterFeetype.starttime1;
		out_pack->lvol1 = tWaterFeetype.feetime1;
		out_pack->lvol2 = tWaterFeetype.feeamt1;

		out_pack->lvol3 = tWaterFeetype.starttime2;
		out_pack->lvol4 = tWaterFeetype.feetime2;
		out_pack->lvol5 = tWaterFeetype.feeamt2;

		out_pack->lvol6 = tWaterFeetype.starttime3;
		out_pack->lvol7 = tWaterFeetype.feetime3;
		out_pack->lvol8 = tWaterFeetype.feeamt3;

		PutRow(handle,out_pack,pRetCode,szMsg);
		
		if(rows % 10 == 0)
		{
			AnswerDataPart(handle,*pRetCode,szMsg);
		}
	}
	AnswerData(handle,*pRetCode,szMsg);
	return 0;
}

int F846405(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans& ats=CAccTrans::GetInst();
	des2src(ats.trans.opercode,rPack->semp);
	switch(rPack->sstation0[0])
	{
		//添加
		case 'A':
			ats.trans.transcode=MAKETRANSCODEADD(TCM_WATERFEE);
			ret=ats.InitTrans();
			if(ret)
				return ret; 		
			ret=Add846405(handle,rPack,pRetCode,szMsg);
			break;
		//删除
		case 'D':
			ats.trans.transcode=MAKETRANSCODEDEL(TCM_WATERFEE);
			ret=ats.InitTrans();
			if(ret)
				return ret; 		
			ret=Delete846405(rPack);
			break;
		//修改
		case 'U':
			ats.trans.transcode=MAKETRANSCODEUPD(TCM_WATERFEE);
			ret=ats.InitTrans();
			if(ret)
				return ret;
			break;
		case 'I':
			ats.trans.transcode=MAKETRANSCODEIMP(TCM_WATERFEE);
			ret=ats.InitTrans();
			if(ret)
				return ret; 		
			ret=Import846405(handle,rPack,pRetCode,szMsg);
			break;
		default:
			ret=Read846405(handle,iRequest,rPack,pRetCode,szMsg);
			break;
	}
	if(ret)
		return ret;
	return 0;
}


