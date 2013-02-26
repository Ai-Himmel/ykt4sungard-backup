/* --------------------------------------------
* 程序名称: 
* 创建日期: 2009-3-4
* 程序作者: 王彦兵
* 版本信息: 1.0.0.0
* 程序功能: 网络收费帐户转账(包含第三方对接)
* --------------------------------------------
* 修改日期:
* 修改人员:
* 修改描述:
* 版本信息:
* 备注信息:
* --------------------------------------------*/
#include "netfeetrans.h"

#ifdef __cplusplus
extern "C" {
#endif

extern CLogFile g_LogFile;

int netfee_trans(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int ret = 0;
	char szAccount[20] = "";			
	char szPassword[12]="";				
	char szTradeTime[20]="";
	char szReqCode[4]="";
	char szResMes[12]="";
	double dRemainBalance = 0;
	double dTransferBalance = 0;
	int iSerino = 0;
	Cdeposit cdeposit;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);
	SetCol(handle,0);
	SetCol(handle, F_LVOL11, 0);

	if(in_pack->damt1 <= 0)
	{
		sprintf(szMsg,"金额[%f]错误",in_pack->damt1);
		g_LogFile.WriteLogEx(1004,"金额[%f]为负",in_pack->damt1);
		out_pack->lvol11 = -16;
		goto L_RET;
	}
	iSerino = in_pack->lvol6;
	dTransferBalance = in_pack->damt1;		//转账金额	

	strncpy(szAccount,in_pack->scust_auth,sizeof(szAccount));		//账号,即学号
	
	strncpy(szPassword,in_pack->sserial1,sizeof(szPassword));		//密码

	strncpy(szReqCode,in_pack->sroom_no,sizeof(szReqCode));			//请求码 008 or 009

	strncpy(szTradeTime,in_pack->scust_auth2,sizeof(szTradeTime));	//转账时间
	
	//1.组织数据包
	cdeposit.genMessage(szReqCode,szAccount,szPassword,szTradeTime,dTransferBalance,iSerino);
	
	//2.发送接收数据包
	ret = cdeposit.send();
	if (ret < 0)
	{	
		strcpy(szMsg,"通讯错误");
		g_LogFile.WriteLogEx(1004,"发送报文错误,ret[%d]",ret);
		out_pack->lvol11 = -17;
		goto L_RET;
	}
	g_LogFile.WriteLogEx(1004,"发送报文成功,ret[%d]",ret);

	ret = cdeposit.recv();
	if(ret <= 0)
	{
		strcpy(szMsg,"通讯错误");
		if (ret == 0)
			g_LogFile.WriteLogEx(1004,"接收报文超时");
		else
			g_LogFile.WriteLogEx(1004,"接收报文错误,ret[%d]",ret);
		out_pack->lvol11 = -17;
		goto L_RET;
	}
	//3.解析数据包
	ret = cdeposit.parseMessage(dRemainBalance,szResMes);
	if (ret < 0)
	{
		if (ret == -1)
		{
			strcpy(szMsg,"数据校验结果不一致");
			g_LogFile.WriteLogEx(1004,"报文校验出错");
			out_pack->lvol11 = -17;
		}
		else if(ret == -2)
		{
			if(strncmp(szResMes,"E15",3) == 0)
				strcpy(szMsg,"账号或密码错误");
			else
				sprintf(szMsg,"其他错误[%s]",szResMes);
			g_LogFile.WriteLogEx(1004,"网络收费处理出错,响应代码[%s]",szResMes);
			out_pack->lvol11 = -18;
		}
		else
			g_LogFile.WriteLogEx(1004,"网络收费金额[%f]出错",dRemainBalance);
		
		goto L_RET;
	}
	
	//	out_pack->damt3 = dRemainBalance;		// 网络收费剩余余额
	//为了和老系统兼容
	if(strncmp(szReqCode,"008",3) == 0)
		out_pack->lvol11 = 1;
	else
		out_pack->lvol11 = 0;

L_RET:
	PutRow(handle, out_pack, pRetCode, szMsg);
	return 0;
}


#ifdef __cplusplus
}
#endif
