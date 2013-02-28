/* --------------------------------------------
 * 程序名称: F847232
 * 创建日期: 2007-05-15
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 通用前置机参数设置
 * --------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "acctrans.h"
#include "busqc.h"
#include "dbfunc_foo.h"

static int Read847232(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	/*
	EXEC SQL BEGIN DECLARE SECTION;
	sqlint32 ho_sysid;
	char ho_sysname[61] = "";
	char ho_
	sqlint16 ho_indr = 1;
	char sqlcmd[1024] = "";
	EXEC SQL END DECLARE SECTION;
	char sqltmp[128];
	*/
	int rows;
	int ret;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	T_t_subsyspara subsyspara;
	T_t_subsystem subsystem;
	ret = DB_t_subsyspara_open_select_by_c1();
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_SUBSYSPARAMS_N;
		return E_DB_SUBSYSPARAMS_R;
	}
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LCERT_CODE,F_LVOL0,F_LVOL1,F_LVOL2,F_LVOL3,F_LVOL4,F_LVOL5,F_LVOL6
		,F_LVOL7,F_LVOL8,F_LVOL9,F_SDATE0,F_SEMAIL,F_SSTATUS1,F_SNAME2,F_LVOL10,F_LVOL12,F_SCUST_AUTH,F_LSAFE_LEVEL,F_LSAFE_LEVEL2,0);
	rows = 0;
	while(1)
	{
		memset(&subsyspara,0,sizeof subsyspara);
		ret = DB_t_subsyspara_fetch_select_by_c1(&subsyspara);
		if(ret)
		{	
			DB_t_subsyspara_close_select_by_c1();
			if(ret == DB_NOTFOUND)
			{
				if(rows > 0)
					return 0;
				return E_DB_SUBSYSPARAMS_N;
			}
			return E_DB_SUBSYSPARAMS_R;
		}
		memset(&subsystem,0,sizeof subsystem);
		ret = DB_t_subsystem_read_by_sysid(subsyspara.sysid,&subsystem);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
				continue;
			DB_t_subsyspara_close_select_by_c1();
			return E_DB_SUBSYSTEM_R;
		}
		if(subsystem.status[0]!=STATUS_NORMAL)
			continue;
		rows++;
		des2src(out_pack->semail,subsystem.sysname);
		out_pack->lcert_code = subsystem.sysid;
		out_pack->lvol0 = subsyspara.beatinterval; // 10s
		out_pack->lvol1 = subsyspara.beatcntlimit;
		out_pack->lvol2 = subsyspara.reqbeatfuncno;
		// 保留
		out_pack->lvol3 = subsyspara.reqtaskfuncno;
		out_pack->lvol4 = subsyspara.exectimeout; // 1s
		
//		des2src(out_pack->sdate0,subsyspara.devtype); // 测试设备
//		out_pack->sstatus1[0] = subsyspara.workmode[0]; // 设备联机模式

		out_pack->lvol5 = subsyspara.colinterval; // 流水采集频率 5s
		out_pack->lvol6 = subsyspara.reqdevfuncno;
		out_pack->lvol7 = subsyspara.taskmaxlimit; 
		out_pack->lvol8 = subsyspara.qryinterval;
		out_pack->lvol9 = subsyspara.respfuncno;
		out_pack->lvol10 = subsyspara.bccdrtpno;
		des2src(out_pack->scust_auth,subsyspara.bccdrtpip);
		out_pack->lvol12=subsyspara.bccdrtpport;
		out_pack->lsafe_level=subsyspara.bccmainfuncno;
		out_pack->lsafe_level2=subsyspara.bccinterval;
		
		PutRow(handle,out_pack,pRetCode,szMsg);
		if(rows%10 == 0)
			AnswerDataPart(handle,*pRetCode,szMsg);
	}
	AnswerData(handle,*pRetCode,szMsg);
	return 0;
}

static int Add847232(ST_PACK *rPack,char *szMsg)
{
	int ret;
	T_t_subsystem subsystem;
	T_t_subsyspara subsyspara;

	memset(&subsystem,0,sizeof subsystem);
	memset(&subsyspara,0,sizeof subsyspara);

	ret = DB_t_subsystem_read_by_sysid(rPack->lcert_code,&subsystem);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_SUBSYSTEM_N;
		return E_DB_SUBSYSTEM_R;
	}
	if(subsystem.status[0]!=STATUS_NORMAL)
	{
		strcpy(szMsg,"子系统已注销");
		return E_SUBSYSTEM_LOGOUT;
	}
	/*
	ret = DB_t_subsysparams_read_by_sysid(subsystem.system_id,&subsyspara);
	if(ret)
	{
		if(DB_NOTFOUND != ret)
			return E_DB_SUBSYSPARAMS_R;
	}
	else
	{
		
	}
	*/
	subsyspara.sysid = subsystem.sysid;
	subsyspara.beatinterval = rPack->lvol0 ; // 10s
	subsyspara.beatcntlimit = rPack->lvol1;
	subsyspara.reqbeatfuncno = rPack->lvol2;
	// 保留
	 subsyspara.reqtaskfuncno= rPack->lvol3;
	subsyspara.exectimeout = rPack->lvol4; // 1s
	
//	des2src(subsyspara.devtype,rPack->sdate0); // 测试设备
//	subsyspara.workmode[0] = rPack->sstatus1[0]; // 设备联机模式

	subsyspara.colinterval = rPack->lvol5 ; // 流水采集频率 5s
	subsyspara.reqdevfuncno= rPack->lvol6;
	subsyspara.taskmaxlimit = rPack->lvol7; 
	subsyspara.qryinterval = rPack->lvol8;
	subsyspara.respfuncno = rPack->lvol9 ;
	subsyspara.bccdrtpno=rPack->lvol10;
	des2src(subsyspara.bccdrtpip,rPack->scust_auth);
	subsyspara.bccdrtpport=rPack->lvol12;
	subsyspara.bccmainfuncno=rPack->lsafe_level;
	subsyspara.bccinterval=rPack->lsafe_level2;
	ret = DB_t_subsyspara_add(&subsyspara);
	if(ret)
	{
		if(DB_REPEAT == ret)
			return E_DB_SUBSYSPARAMS_E;
		return E_DB_SUBSYSPARAMS_I;
	}
	return 0;
}

static int Update847232(ST_PACK *rPack,char *szMsg)
{
	int ret;
	T_t_subsystem subsystem;
	T_t_subsyspara subsyspara;

	memset(&subsystem,0,sizeof subsystem);
	memset(&subsyspara,0,sizeof subsyspara);

	ret = DB_t_subsystem_read_by_sysid(rPack->lcert_code,&subsystem);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_SUBSYSTEM_N;
		return E_DB_SUBSYSTEM_R;
	}
	if(subsystem.status[0]!=STATUS_NORMAL)
	{
		strcpy(szMsg,"子系统已注销");
		return E_SUBSYSTEM_LOGOUT;
	}
	
	ret = DB_t_subsyspara_read_by_sysid(subsystem.sysid,&subsyspara);
	if(ret)
	{
		if(DB_NOTFOUND != ret)
			return E_DB_SUBSYSPARAMS_R;
		return E_DB_SUBSYSPARAMS_N;
	}
	subsyspara.sysid = subsystem.sysid;
	subsyspara.beatinterval = rPack->lvol0 ; // 10s
	subsyspara.beatcntlimit = rPack->lvol1;
	subsyspara.reqbeatfuncno = rPack->lvol2;
	subsyspara.reqtaskfuncno= rPack->lvol3;
	subsyspara.exectimeout = rPack->lvol4; // 1s
	subsyspara.colinterval = rPack->lvol5 ; // 流水采集频率 5s
	subsyspara.reqdevfuncno= rPack->lvol6;
	subsyspara.taskmaxlimit = rPack->lvol7; 
	subsyspara.qryinterval = rPack->lvol8;
	subsyspara.respfuncno = rPack->lvol9 ;
	subsyspara.bccdrtpno = rPack->lvol10;
	
//	des2src(subsyspara.devtype,rPack->sdate0); // 测试设备
//	subsyspara.workmode[0] = rPack->sstatus1[0]; // 设备联机模式
//	subsyspara.work_mode[1] = '\0';

	des2src(subsyspara.bccdrtpip,rPack->scust_auth);
	subsyspara.bccdrtpport=rPack->lvol12;
	subsyspara.bccmainfuncno=rPack->lsafe_level;
	subsyspara.bccinterval=rPack->lsafe_level2;
	ret = DB_t_subsyspara_update_by_sysid(subsystem.sysid,&subsyspara);
	if(ret)
	{
		if(DB_NOTFOUND== ret)
			return E_DB_SUBSYSPARAMS_N;
		return E_DB_SUBSYSPARAMS_I;
	}
	return 0;
}

int F847232(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	switch(rPack->sstatus0[0])
	{
		//添加
		case 'I':
			ret=Add847232(rPack,szMsg);
			break;
		//删除
		/*
		case 'D':
			ret=Delete848258(rPack);
			break;
		*/
		//查询
		case 'R':
			ret=Read847232(handle,iRequest,rPack,pRetCode,szMsg);
			break;
		//修改
		case 'U':
			ret=Update847232(rPack,szMsg);
			break;
		default:
			ret=E_INPUT_DATA_INVAILD;
			break;
	}
	if(ret)
	{
		*pRetCode=ret;
		return -1;
	}
	return 0;
}

