/* --------------------------------------------
 * 程序名称: F849014.c
 * 创建日期: 2006-8-7
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 电控宿舍信息查询
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
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
#include "fdsqc.h"
#include "gwpack.h"
#include "tcp.h"
#include "dbfunc_foo.h"

#define QUERY_DORM_NAME 847205

#ifdef __cplusplus
extern "C"
#endif
int F849014(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int card_id = 0;
	T_t_pif_card tCard;
	char buf[64] = "";
	char comments[256] = "";
	char reqdata[1024] = "";
	char temp[1024] = "";
	ST_CPACK aPack;
	ST_PACK* out_pack = &(aPack.pack);
	char svr_ip[21 ] = "";
	int svr_port = 0;

	CTcpSocket sock;
	KSG_GW_PACK_t * resp = NULL;

	if(strlen(in_pack->sname) < 1)
	{
		*pRetCode = E_INPUT_DORM_NO;
		goto L_RETU;
	}
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSMESS,0);

	ret = GetPowerServerInfo(svr_ip,&svr_port);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	gw_server_info_t svrinfo;
	des2src(svrinfo.server_ip,svr_ip);
	svrinfo.server_port = svr_port;
	svrinfo.sock = &sock;
	AddXmlItemStr(temp,XML_KEY_DORM_NO,in_pack->sname);
	writelog(LOG_DEBUG,"xml[%s]",temp);
	sprintf(reqdata,"<YKT_DATA>%s</YKT_DATA>",temp);
	writelog(LOG_DEBUG,"xml[%s]",reqdata);
	ret = SendToServer(&svrinfo,QUERY_DORM_NAME,reqdata);
	if(ret)
	{
		writelog(LOG_DEBUG,"电控返回数据[%d]",ret);
		*pRetCode =ret;
		goto L_RETU;
	}

	ret = RecvFromServer(&svrinfo,&resp);
	if(ret)
	{
		writelog(LOG_DEBUG,"电控返回数据[%d]",ret);
		*pRetCode = ret;
		goto L_RETU;
	}
	else
	{
		if(resp->func_no != QUERY_DORM_NAME || resp->retcode != 0)
		{
			writelog(LOG_DEBUG,"funcno [%d] ret[%d]",resp->func_no,resp->retcode);
			*pRetCode = E_POWER_RECV_ERR;
			goto L_RETU;
		}
		des2src(reqdata,resp->data);
		ret = GetXmlValue(comments,sizeof comments,XML_KEY_DORM_NAME,reqdata);
		if(ret)
		{
			writelog(LOG_DEBUG,"无数据[%s][%d]",reqdata,ret);
			*pRetCode = ret;
			goto L_RETU;
		}
		des2src(out_pack->vsmess,comments);
		PutRow(handle,out_pack,pRetCode,szMsg);
	}
	if(resp)
		free(resp);
	return 0;
L_RETU:
	if(resp)
		free(resp);
	return -1;
}

