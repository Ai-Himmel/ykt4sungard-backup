/* ----------------------------------------------------------
 * 程序名称：bank_ccb_ahut.cpp
 * 创建日期：2009-08-10
 * 程序作者：王彦兵
 * 版本信息：1.0.0.0
 * 程序功能：安徽工大建行接口
 * ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bank_interface.h"
#include "bank_ccb_ahut.h"
#include "tcp.h"

////包头中只有交易日期，时间，流水号，终端号在变化
// termid  	: rPack->lvol6
// refno   	: rPack->sholder_ac_no
// transdate	:rPack->sdate0
// transtime	:rPack->stime0
static void GenMsgHead(char *msghead,ST_PACK *rPack)
{
	char buf[1024]="";
	AddXmlItemStr(buf,"AreaNo","");								//地区代码
	AddXmlItemStr(buf,"ChanNo","");								//渠道代码
	AddXmlItemInt(buf, "TerminalNo", rPack->lvol6);					//终端编号
	AddXmlItemStr(buf,"TransNo",rPack->sholder_ac_no);			//交易流水号
	AddXmlItemStr(buf,"TransDate",rPack->sdate0);				//交易日期
	AddXmlItemStr(buf,"TransTime",rPack->stime0);					//交易时间
	AddXmlItemStr(buf,"BankNo","");								//机构代码
	AddXmlItemStr(buf,"TellerNo","");								//柜员代码
	AddXmlItemInt(buf, "FuncTionFlag", 1);							//处理标志
	AddXmlItemStr(msghead, "MsgHead", buf);						// 全包含在MsgHead 中	
	writelog(LOG_DEBUG,"msghead[%s] ",msghead);
}

// 充值包体
static void GenMsgBodyTrans(char *msgbody,ST_PACK *rPack)	
{
	char buf[1024]="";
	AddXmlItemStr(buf, "SchoolCode", SCHOOLCODE_AHUT);			//学校代码
	AddXmlItemStr(buf, "IcCard", rPack->sphone);					//校园卡卡号(使用学工号)
	AddXmlItemStr(buf, "CusName", rPack->scust_limit);				//客户姓名
	AddXmlItemInt(buf, "SignFlag", 1);								//签约标志
	AddXmlItemStr(buf, "ActNo", rPack->scust_limit2);				// 银行卡号
	AddXmlItemDbl(buf, "Amount", rPack->damt0);					// 交易金额

	AddXmlItemStr(msgbody, "MsgBody", buf);						//全包含在MsgBody 中	
	writelog(LOG_DEBUG,"msgbody[%s] ",msgbody);
}

// 冲正包体
static void GenMsgBodyTransRev(char *msgbody,ST_PACK *rPack)
{
	char buf[1024]="";
	AddXmlItemStr(buf, "SchoolCode", SCHOOLCODE_AHUT);			//学校代码
	AddXmlItemStr(buf, "IcCard", rPack->sphone);					//校园卡卡号(使用学工号)
	AddXmlItemDbl(buf, "Amount", rPack->damt0);					// 交易金额
	AddXmlItemStr(buf, "RSeqNo", rPack->sholder_ac_no);			//交易流水号

	AddXmlItemStr(msgbody, "MsgBody", buf);						//全包含在MsgBody 中	
	writelog(LOG_DEBUG,"msgbody[%s] ",msgbody);
}

static void GenMsgBodyQuery(char *msgbody,ST_PACK *rPack)
{
	char buf[1024]="";
	AddXmlItemStr(buf, "SchoolCode", SCHOOLCODE_AHUT);			//学校代码
	AddXmlItemStr(buf, "IcCard", rPack->sphone);					//校园卡卡号(使用学工号)
	AddXmlItemInt(buf, "SignFlag", 1);								//签约标志
	AddXmlItemStr(buf, "ActNo", rPack->scust_limit2);				// 银行卡号

	AddXmlItemStr(msgbody, "MsgBody", buf);						//全包含在MsgBody 中	
	writelog(LOG_DEBUG,"msgbody[%s] ",msgbody);
}

static void GenTransReqMSG(char *msg,char *transcode,char *msghead,char *msgbody)
{
	char len_buf[16]="";
	char transcont[2048]="";
	char *trans_head="<TranRequest>";
	char *trans_tail="</TranRequest>";

	int transhead_len = strlen(trans_head);
	int msghead_len = strlen(msghead);
	int msgbody_len = strlen(msgbody);
	int transtail_len = strlen(trans_tail);
	int xmlhead_len = strlen(XML_HEAD);

	int transcont_len =   transhead_len + msghead_len + msgbody_len + transtail_len;
	
	memcpy(transcont,trans_head,transhead_len);
	memcpy(transcont+transhead_len,msghead,msghead_len);
	memcpy(transcont+transhead_len+msghead_len,msgbody,msgbody_len);
	memcpy(transcont+transhead_len+msghead_len+msgbody_len,trans_tail,transtail_len);

	sprintf(len_buf,"%08d",4 + xmlhead_len + transcont_len);
	memcpy(msg,len_buf,8);											// 8位长度
	memcpy(msg+8,transcode,4);										// 4位交易码
	memcpy(msg+12,XML_HEAD,xmlhead_len);							// xml 头
	memcpy(msg + xmlhead_len +12,transcont,transcont_len);				// 交易内容(msghead + msgbody)
	writelog(LOG_DEBUG,"msg[%s] ",msg);
}

//按照通用接口规范进行封装各自银行的接口
int Bank_Trans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int msglen=0;
	char host[16]="";		//对方机器的ip
	short port = 0;			
	int timeout = 0;

	char msg[4096]="";
	char msghead[1024] = "";							// 存储包头
	char msgbody[1024]="";								// 存储包体
	char tmp[256] = "";

	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SPHONE,0);
	
	des2src(host,rPack->scust_auth);					// 银行ip
	port=rPack->lvol0;									// 银行端口
	timeout = rPack->lvol1*1000;							// 等待银行超时时间(毫秒)

	writelog(LOG_INFO,"bank info:  ip_addr[%s],port[%d],timeout[%d] ",host,port,timeout);
	//生成包头
	GenMsgHead(msghead,rPack);

	//生成转账包体
	GenMsgBodyTrans(msgbody,rPack);

	// 生成转账报文
	GenTransReqMSG(msg,TRANS_CODE,msghead,msgbody);

	msglen = strlen(msg);
	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"连接银行错误");
		return E_TRANS_CONNECT;
	}

	writelog(LOG_INFO,"trans send[%s]",msg);
	
	ret = tcpsocket.Send(msg,msglen);
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
	      	tcpsocket.Close();
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		strcpy(szMsg,"发送数据错误");
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// 不应该出现这种情况
		tcpsocket.Close();
	      	writelog(LOG_ERR,"Send to bank，CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		return E_TRANS_REQUEST;
	}

	writelog(LOG_DEBUG,"Send ret [%d] ",ret);
	memset(msg,0,sizeof msg);
	ret = tcpsocket.Recv(tmp, 8, timeout);						// 先把长度收下来
	if(ret !=8)
	{
		out_pack->lvol1 = -1;								//接收数据错误，后台应向银行发冲正
		writelog(LOG_ERR,"充值接收银行数据包长错误ret[%d],tmp[%s]",ret,tmp);
		strcpy(szMsg,"充值接收银行数据包长错误");
		goto r_ret;  										// 接收时候出错，或超时
	}
	writelog(LOG_DEBUG,"充值接收银行数据包长ret[%d],head[%s]",ret,tmp);
	msglen = atoi(tmp);
	ret = tcpsocket.Recv(msg, msglen, timeout);					// 收报文内容
	writelog(LOG_INFO,"trans recv[%s],recvlen[%d]",msg,ret);

	if (ret<4 || ret != msglen)
	{
		out_pack->lvol1 = -1;								//超时 或 接收数据错误 ，后台应向银行发冲正
		strcpy(szMsg,"充值接收银行数据包体错误");
		goto r_ret;  
	}

	if(strncmp(msg,"1120",4) !=0)							// 前4位应该是 1120
	{
		out_pack->lvol1 = -1;								//接收数据错误，后台应向银行发冲正
		strcpy(szMsg,"充值接收银行数据交易码错误");
		goto r_ret;  
	}

	ret = GetXmlValue(tmp, 5, "ResultCode", msg);
	if(ret)
	{
		out_pack->lvol1 = -1;								//接收数据错误，后台应向银行发冲正
		strcpy(szMsg,"充值接收银行数据返回码错误");
		goto r_ret;  
	}
					
	if(strncmp(tmp,"0000",4)!=0)
	{
		GetXmlValue(tmp,40,"Err_Info",msg);
		strcpy(szMsg,tmp);									// 银行返还的错误信息
		tcpsocket.Close();
		return E_TRANS_BANK_RECVERR;
	}
	else
	{
		out_pack->lvol1 = 1;
		GetXmlValue(tmp, 21, "TransNo", msg);
		memcpy(out_pack->sphone,tmp,strlen(tmp));				// 银行流水号
		GetXmlValue(tmp, 100, "Err_Info", msg);					// 银行返还信息
	}
	writelog(LOG_INFO,"trans:bank transno[%s],retinfo[%s],lvol1[%d]",out_pack->sphone,tmp,out_pack->lvol1);

r_ret:
	tcpsocket.Close();
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

// 冲正
int Bank_Reverse(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int msglen = 0;
	char host[16]="";		//对方机器的ip
	short port = 0;			
	int timeout = 0;

	char msg[4096]="";
	char msghead[1024] = "";							// 存储包头
	char msgbody[1024]="";								// 存储包体
	char tmp[256] = "";
	
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SCERT_NO,0);

	des2src(host,rPack->scust_auth);					// 银行ip
	port=rPack->lvol0;									// 银行端口
	timeout = rPack->lvol1*1000;								// 等待银行超时时间

	//生成包头
	GenMsgHead(msghead,rPack);

	//生成冲正包体
	GenMsgBodyTrans(msgbody,rPack);

	// 生成冲正报文
	GenTransReqMSG(msg,REV_TRANS_CODE,msghead,msgbody);

	msglen = strlen(msg);
	
	writelog(LOG_INFO,"Connect to bank ip_addr[%s],port[%d] ",host,port);	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"连接银行错误");
		return E_TRANS_CONNECT;
	}
	writelog(LOG_INFO,"reverse send[%s]",msg);
	
	ret = tcpsocket.Send(msg,msglen);
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
	      	tcpsocket.Close();
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		strcpy(szMsg,"发送数据错误");
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// 不应该出现这种情况
		tcpsocket.Close();
	      	writelog(LOG_ERR,"Send to bank，CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		return E_TRANS_REQUEST;
	}

	memset(msg,0,sizeof msg);
	ret = tcpsocket.Recv(tmp, 8, timeout);						// 先把长度收下来
	if(ret !=8)
	{
		out_pack->lvol1 = -1;								//接收数据错误，后台应向银行发冲正
		writelog(LOG_ERR,"冲正接收银行数据包长错误ret[%d],tmp[%s]",ret,tmp);
		strcpy(szMsg,"冲正接收银行数据包长错误");
		goto r_ret;  										// 接收时候出错，或超时
	}

	msglen = atoi(tmp);
	ret = tcpsocket.Recv(msg, msglen, timeout);					// 收报文内容
	writelog(LOG_INFO,"transRev recv[%s],recvlen[%d]",msg,ret);

	if (ret<4 || ret != msglen)
	{
		out_pack->lvol1 = -1;								//超时 或 接收数据错误 ，后台应向银行发冲正
		strcpy(szMsg,"冲正接收银行数据包体错误");
		goto r_ret;  
	}

	if(strncmp(msg,"1130",4) !=0)							// 前4位应该是 1130
	{
		out_pack->lvol1 = -1;								//接收数据错误，后台应向银行发冲正
		strcpy(szMsg,"冲正接收银行数据交易码错误");
		goto r_ret;  
	}

	ret = GetXmlValue(tmp, 5, "ResultCode", msg);
	if(ret)
	{
		out_pack->lvol1 = -1;								//接收数据错误，后台应向银行发冲正
		strcpy(szMsg,"冲正接收银行数据返回码错误");
		goto r_ret;  
	}
					
	if(strncmp(tmp,"0000",4)!=0)
	{
		GetXmlValue(tmp,40,"Err_Info",msg);
		strcpy(szMsg,tmp);									// 银行返还的错误信息
		tcpsocket.Close();
		return E_TRANS_BANK_RECVERR;
	}
	else
	{
		out_pack->lvol1 = 1;
		GetXmlValue(tmp, 21, "TransNo", msg);
		memcpy(out_pack->sphone,tmp,strlen(tmp));				// 银行流水号
		GetXmlValue(tmp, 100, "Err_Info", msg);					// 银行返还信息
	}
	writelog(LOG_INFO,"transrev:bank transno[%s],retinfo[%s],lvol1[%d]",out_pack->sphone,tmp,out_pack->lvol1);

r_ret:
	tcpsocket.Close();
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

// 查询银行卡余额
int Bank_Querybala(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int msglen=0;
	char host[16]="";		//对方机器的ip
	short port = 0;			
	int timeout = 0;

	char msg[4096]="";
	char msghead[1024] = "";							// 存储包头
	char msgbody[1024]="";								// 存储包体
	char tmp[256] = "";

	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SALL_NAME,F_DAMT0,F_DAMT1,0);
	
	des2src(host,rPack->scust_auth);					// 银行ip
	port=rPack->lvol0;									// 银行端口
	timeout = rPack->lvol1*1000;							// 等待银行超时时间

	//生成包头
	GenMsgHead(msghead,rPack);

	//生成查询包体
	GenMsgBodyQuery(msgbody,rPack);

	// 生成查询报文
	GenTransReqMSG(msg,QUERY_BALA,msghead,msgbody);

	msglen = strlen(msg);
	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"连接银行错误");
		return E_TRANS_CONNECT;
	}

	writelog(LOG_INFO,"querybala send[%s]",msg);
	
	ret = tcpsocket.Send(msg,msglen);
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
	      	tcpsocket.Close();
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		strcpy(szMsg,"发送数据错误");
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// 不应该出现这种情况
		tcpsocket.Close();
	      	writelog(LOG_ERR,"Send to bank，CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		return E_TRANS_REQUEST;
	}

	memset(msg,0,sizeof msg);
	ret = tcpsocket.Recv(tmp, 8, timeout);						// 先把长度收下来
	if(ret !=8)
	{
		out_pack->lvol1 = -1;								//接收数据错误，后台应向银行发冲正
		strcpy(szMsg,"查询余额接收银行数据包长错误");
		goto r_ret;  										// 接收时候出错，或超时
	}

	msglen = atoi(tmp);
	ret = tcpsocket.Recv(msg, msglen, timeout);					// 收报文内容
	writelog(LOG_INFO,"querybala recv[%s],recvlen[%d]",msg,ret);

	if (ret<4 || ret != msglen)
	{
		out_pack->lvol1 = -1;								//超时 或 接收数据错误 ，后台应向银行发冲正
		strcpy(szMsg,"查询余额接收银行数据包体错误");
		goto r_ret;  
	}

	if(strncmp(msg,"1110",4) !=0)							// 前4位应该是 1110
	{
		out_pack->lvol1 = -1;								//接收数据错误，后台应向银行发冲正
		strcpy(szMsg,"查询余额接收银行数据交易码错误");
		goto r_ret;  
	}

	ret = GetXmlValue(tmp, 5, "ResultCode", msg);
	if(ret)
	{
		out_pack->lvol1 = -1;								//接收数据错误，后台应向银行发冲正
		strcpy(szMsg,"查询余额接收银行数据返回码错误");
		goto r_ret;  
	}
					
	if(strncmp(tmp,"0000",4)!=0)
	{
		GetXmlValue(tmp,40,"Err_Info",msg);
		strcpy(szMsg,tmp);									// 银行返还的错误信息
		tcpsocket.Close();
		return E_TRANS_BANK_RECVERR;
	}
	else
	{
		out_pack->lvol1 = 1;
		GetXmlValue(tmp, 40, "CusName", msg);
		memcpy(out_pack->sall_name,tmp,strlen(tmp));				// 客户名称
		GetXmlValue(tmp, 20, "ActBal", msg);						// 帐户余额
		out_pack->damt0 = D4U5(atof(tmp), 2);
		GetXmlValue(tmp, 20, "ActAvlBal", msg);					// 帐户可用余额
		out_pack->damt1= D4U5(atof(tmp), 2);	
		
	}
	writelog(LOG_INFO,"querybala:cutname[%s],actbala[%f],actavlbala[%f]",out_pack->sall_name,out_pack->damt0,out_pack->damt1);

r_ret:
	tcpsocket.Close();
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

