/* ----------------------------------------------------------
 * 程序名称：bank_nyyh.cpp
 * 创建日期：2007-07-27 14:58
 * 程序作者：韩海东
 * 版本信息：1.0.0.0
 * 程序功能：通用接口规范的封装
 * ----------------------------------------------------------
 * 修改日期: 2008-03-26
 * 修改人员: 李翔
 * 修改描述: 新增云南信用合作社接口函数
 * 版本信息: 
 * 备注信息: 
 * ----------------------------------------------------------
 * 修改日期: 2008-04-26
 * 修改人员: 李翔
 * 修改描述: 新增云南农业银行接口函数
 * 版本信息: 
 * 备注信息: 
 * ----------------------------------------------------------
 * 修改日期: 2008-07-26
 * 修改人员: 李翔
 * 修改描述: 新增哈尔滨中行接口函数
 * 版本信息: 
 * 备注信息: 
 * ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
//#include "bank.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bank_gd.h"
#include "mac.h"
#include "Third_Mac.h"
#include "iso8583.h"
#include "bank_pub.h"

//按照通用接口规范进行封装各自银行的接口
int Bank_QueryBalance(INNER_TRANS_REQUEST * pNode,double *balance)
{
	int ret=0;
	char temp[6]="";
	int i=0;
	int flag=0;
	int send_length = 0;
	int recv_length = 0;
	
	// 云南信用合作社
	char packet_send_buf[4096] = "";		// 信合发送报文buf
	char packet_recv_buf[4096] = "";		// 信合接受报文buf
	BANK_YNXH_TRADE_STRUCT_PACKET 	ynxh_req;	// 信合请求报文
	BANK_YNXH_TRADE_STRUCT_PACKET 	ynxh_ans;	// 信合应答报文
	memset(&ynxh_req, 0, sizeof(ynxh_req));
	memset(&ynxh_ans, 0, sizeof(ynxh_ans));

	// 云南农行
	BANK_YNNH_TRADE_STRUCT_PACKET ynnh_req;
	BANK_YNNH_TRADE_STRUCT_PACKET ynnh_ans;
	memset(&ynnh_req, 0x20, sizeof(ynnh_req));
	memset(&ynnh_ans, 0x20, sizeof(ynnh_ans));
	
	BANK_ZGYH_TRADE_STRUCT_TRANS_REQ 	zgyh_req;
	BANK_ZGYH_TRADE_STRUCT_TRANS_ANS 	zgyh_ans;

	BANK_GSYH_TRADE_STRUCT 			gsyh_req;
	BANK_GSYH_TRADE_STRUCT 			gsyh_ans;

	memset(&zgyh_req,0x20,sizeof zgyh_req);
	memset(&zgyh_ans,0x20,sizeof zgyh_ans);

	memset(&gsyh_ans,0x20,sizeof gsyh_ans);
	memset(&gsyh_req,0x20,sizeof gsyh_req);

	// 哈尔滨工行
	BANK_HRBZH_TRADE_STRUCT_PACKET send_hrbzh;
	BANK_HRBZH_TRADE_STRUCT_PACKET recv_hrbzh;
	memset(&send_hrbzh, 0x00, sizeof(send_hrbzh));
	memset(&recv_hrbzh, 0x00, sizeof(recv_hrbzh));
	
	//分析上传银行卡号属于哪个银行，根据银行标志，发送给不同的银行
	for(i=0;i<=g_Bank.BankCount;i++)
	{
		if(i==g_Bank.BankCount)	return E_TRANS_BANK_CARD_NONSUPPORT;
		for(int j=0;j<MAX_RANGE;j++)
		{
			printf("i=[%d],j=[%d],bankcard=[%s],range=[%s],len=[%d]]\n",i,j,pNode->BankCardNo,g_Bank.BankUnit[i].szBankCardRange[j],strlen(g_Bank.BankUnit[i].szBankCardRange[j]));
			if(0==strlen(g_Bank.BankUnit[i].szBankCardRange[j]))	break;
			if(0==memcmp(pNode->BankCardNo,g_Bank.BankUnit[i].szBankCardRange[j]
				,strlen(g_Bank.BankUnit[i].szBankCardRange[j])))
			{
				flag=1;
				g_Bank.cur_bankid=i;
				break;
			}
		}
		if(flag==1)	
			break;
	}
	printf("Bank_Transfer start!i=[%d],g_Bank.BankUnit[i].iBankID=[%d]\n",i,g_Bank.BankUnit[i].iBankID);
	//中国银行，中国银行目前不支持查询银行余额的接口
	if(g_Bank.BankUnit[i].iBankID==BANK_ZGYH)
	{
		return E_TRANS_BANK_FUNC_NONSUPPORT;
	}
	//工商银行，按照工商银行接口进行发送数据包并解析返回包
	else if(g_Bank.BankUnit[i].iBankID==BANK_GSYH)
	{
		memset(&gsyh_req.ZoneNo,0x20,sizeof(gsyh_req));
		memcpy(gsyh_req.ZoneNo,BANK_GSYH_ZONE_NO_GZ,4); //地区编号;广州:3602,珠海:2002;
		memcpy(gsyh_req.BusiType,BANK_GSYH_TYPE_SCHOOL,2);//交易类型，固定11
		memcpy(gsyh_req.TranCode,BANK_GSYH_TRADE_CODE_QUERYBALANCE,2);////交易类型;1:转帐,2:取消,3:余额查询
		gsyh_req.TranFlag[0]='0';						//交易标志;0:正交易,1:反交易
		memcpy(gsyh_req.BankCardNo,pNode->BankCardNo,strlen(pNode->BankCardNo));//银行卡号;借方帐号，清算时为学校帐号
		//memcpy(gsyh_req.TranMoney,pNode->TransMoney,strlen(pNode->TransMoney));//交易金额;
		memcpy(gsyh_req.MoneyType,"001",3);//货币种类;001:人民币
		memcpy(gsyh_req.TranDate,pNode->TradeDate,8); //交易日期;YYYYMMDD
		memcpy(gsyh_req.TranTime,pNode->TradeTime,6);//交易时间;HHMMSS
		gsyh_req.PwdFlag[0]='0';
		gsyh_req.PwdType[0]='0';
		memcpy(gsyh_req.LocalSn,"999999",6);
		memcpy(gsyh_req.LocalDetranSn,"000000",6);		//冲正时填入的原转帐交易流水号
		memcpy(gsyh_req.BankSn,"000000",6);			//银行流水号
		memcpy(gsyh_req.MercAccount,BANK_GSYH_MERCH_NO,5);	//圈存时为中山大学商户号,清算时为商户的商户号
		memcpy(gsyh_req.MercAccountCode,"01",2);		//户代号，指商户当有多个银行帐号时，该字段指示是哪一个帐号；先固定为01;
		memcpy(gsyh_req.GDCAccount,pNode->CardNo,strlen(pNode->CardNo));	//校园卡号;
		memcpy(gsyh_req.PosNo,pNode->TerminalId,5);				//圈存机号;
		memcpy(gsyh_req.AgentPercent,"000000000",9);		//清算时的代理提成百分比
		memcpy(gsyh_req.AgentType,"01",2);			//业务种类,01:圈存,02:消费;
		//memset(gsyh_req.Filter,0x20,sizeof(gsyh_req.Filter));				//空格补位
		Trace_Bank_Package_GSYH(&gsyh_req,"send query bank package");
		ret=send_to_and_recv_from_bank(BANK_GSYH,(char*)&gsyh_req,sizeof(gsyh_req),(char*)&gsyh_ans,sizeof(gsyh_ans),&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		Trace_Bank_Package_GSYH(&gsyh_ans,"receivce query bank package");
		if(0!=strncmp(gsyh_ans.RetCode,"00",2))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s] ",gsyh_ans.RetCode);
			memcpy(temp,gsyh_ans.RetCode,2);
			temp[2]=0;
			switch(atoi(temp))
			{
				case 1:		//银行卡挂失
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
					return	E_TRANS_BANKCARD_LOST;
				case 2:		//银行卡状态错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
					return	E_TRANS_BANKACC_STATERR;
				case 3:		//银行卡金额不足
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
					return	E_TRANS_BANKACC_NOMONEY;
				case 4:		//银行密码错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_BANKCARD_PWDERR;
				case 98:		//银行处理超时
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
					return	E_TRANS_BANK_NOANSWER;
				case 99:		//其他错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_UNKNOW_ERROR;
				default:		//其他未知错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_UNKNOW_ERROR;
			}
		}

		//填充应答包
		//sprintf(pNode->RetCode,"%d",SUCCEED);
		memcpy(pNode->Balance,gsyh_ans.TranMoney,sizeof(pNode->Balance));
		writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%9s]",gsyh_ans.TranMoney);
	}
	// 云南信用合作社
	else if (g_Bank.BankUnit[i].iBankID==BANK_YNXH)
	{	
		// 4. 组合发送数据报文
		ret = Packet_Buf_Transform(packet_send_buf, &ynxh_req, PACKET_TO_BUF, BANK_YNXH, BANK_TRADE_CODE_QUERYBALANCE, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}		

		Trace_Bank_Package_YNXH(&ynxh_req, "send query bank package");

		// 5. 发送数据报文和接受应答数据报文
		ret = send_to_and_recv_from_bank(BANK_YNXH, packet_send_buf, atoi(ynxh_req.head.packet_length) + 4, packet_recv_buf, sizeof(packet_recv_buf), &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_YNXH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		
		// 6. 组合应答数据报文
		ret = Packet_Buf_Transform(packet_recv_buf + 4, &ynxh_ans, BUF_TO_PACKET, BANK_YNXH, BANK_TRADE_CODE_QUERYBALANCE, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		
		// 7. 输出应答数据报文
		Trace_Bank_Package_YNXH(&ynxh_ans,"receivce query bank package");

		// 8. 判断错误码
		ret = Get_Bank_Error_Code(&ynxh_ans, BANK_YNXH);
		if (ret)
		{
			writelog(LOG_ERR, "bank_no=[%s]--errcode=[%d]", g_Bank.BankUnit[i].szBankAccountNO, ret);
			return ret;
		}

		// 9, 输出查询的余额
		memcpy(pNode->Balance, ynxh_ans.cur_balance + 34, sizeof(pNode->Balance));
		writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%9s]",pNode->Balance);
	}
	// 云南农行
	else if (BANK_YNNH== g_Bank.BankUnit[i].iBankID)
	{
		ret = Packet_Buf_Transform(packet_send_buf, &ynnh_req, PACKET_TO_BUF, BANK_YNNH, BANK_TRADE_CODE_QUERYBALANCE, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}		

		Trace_Bank_Package_YNNH(&ynnh_req, "send query bank package");

		recv_length = sizeof(ynnh_ans.ynnh_head) + sizeof(ynnh_ans.remain_money) + sizeof(ynnh_ans.account_money);
		
		ret = send_to_and_recv_from_bank(BANK_YNNH, packet_send_buf, atoi(ynnh_req.ynnh_head.packet_length), packet_recv_buf, recv_length, &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_YNNH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		
		ret = Packet_Buf_Transform(packet_recv_buf, &ynnh_ans, BUF_TO_PACKET, BANK_YNNH, BANK_TRADE_CODE_QUERYBALANCE, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		
		Trace_Bank_Package_YNNH(&ynnh_ans,"receivce query bank package");

		ret = Get_Bank_Error_Code(&ynnh_ans, BANK_YNNH);
		if (ret)
		{
			writelog(LOG_ERR, "bank_no=[%s]--errcode=[%d]", g_Bank.BankUnit[i].szBankAccountNO, ret);
			return ret;
		}
		
		memcpy(pNode->Balance, ynnh_ans.remain_money, sizeof(pNode->Balance));			// 可用金额右补空格
		writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%9s]",pNode->Balance);
	}
	// 哈尔滨中行
	else if (g_Bank.BankUnit[i].iBankID==BANK_HRBZH)
	{	
		// 注意: (1) 哈尔滨中行发送查询和转帐交易的时候需要进行交易签到
		//		 (2) 将交易签到交易放到查询和转帐交易中
		//		 (3) 每次在查询和转帐之前发送一次交易签到, 交易成功以后执行查询和转帐
		//Add by hhd at 2010-8-27
		//		(1)中行修改业务流程，根据学生输入电话银行密码还是卡号，来选择是否做签到交易
		//		(2)因为银行的原因，10年暑期无法做到批量生成电话银行密码，因此修改以上流程
		//		(3)修改后，判断电话银行密码上送是否为空，为空不做签到直接交易，如果
		if(strlen(pNode->BankCardPwd)==0)	//判断是否输入电话银行密码，不输入判断卡号，输入原流程
		{
			if(0==strncmp(pNode->BankCardNo,pNode->Reserve1,strlen(pNode->BankCardNo)))
			{
				goto QUERY;
			}
			else 
			{
				writelog(LOG_ERR,"pNode.BankCardNo=[%s],pNode.Reserve1=[%s]",pNode->BankCardNo,pNode->Reserve1);
				return E_TRANS_RELATION_NOEXIT;
			}
		}
SIGNIN:
		// 1. 组合签到报文
		memset(packet_send_buf, 0x00, sizeof(packet_send_buf));
		memset(packet_recv_buf, 0x00, sizeof(packet_send_buf));
		ret = Packet_Buf_Transform(packet_send_buf, &send_hrbzh, PACKET_TO_BUF, BANK_HRBZH, BANK_TRADE_CODE_SIGN_IN, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}		

		// 2. 输出签到报文
		Trace_Bank_Package_HRBZH(&send_hrbzh, "send sign in bank package");

		// 3. 发送数据报文和接受应答数据报文(签到交易)
		ret = send_to_and_recv_from_bank(BANK_HRBZH, packet_send_buf, atoi(send_hrbzh.hrbzh_head.MsgLen) + sizeof(send_hrbzh.hrbzh_head), packet_recv_buf, sizeof(packet_recv_buf), &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_HRBZH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		
		// 4. 组合应答数据报文(签到交易)
		ret = Packet_Buf_Transform(packet_recv_buf, &recv_hrbzh, BUF_TO_PACKET, BANK_HRBZH, BANK_TRADE_CODE_SIGN_IN, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		
		// 7. 输出签到交易应答
		Trace_Bank_Package_HRBZH(&recv_hrbzh, "receivce sign in bank package");

		// 8. 判断错误码
		ret = Get_Bank_Error_Code(&recv_hrbzh, BANK_HRBZH);
		if (ret)
		{
			writelog(LOG_ERR, "bank_no=[%s]--errcode=[%d]", g_Bank.BankUnit[i].szBankAccountNO, ret);
			return ret;
		}
QUERY:	
		memset(packet_send_buf, 0x00, sizeof(packet_send_buf));
		memset(packet_recv_buf, 0x00, sizeof(packet_recv_buf));
		memset(&send_hrbzh, 0x00, sizeof(send_hrbzh));
		memset(&recv_hrbzh, 0x00, sizeof(recv_hrbzh));
		// 9. 组合查询报文
		ret = Packet_Buf_Transform(packet_send_buf, &send_hrbzh, PACKET_TO_BUF, BANK_HRBZH, BANK_TRADE_CODE_QUERYBALANCE, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}

		// 10. 输出查询报文
		Trace_Bank_Package_HRBZH(&send_hrbzh, "send query bank package");

		// 11. 发送数据报文和接受应答数据报文(查询交易)
		ret = send_to_and_recv_from_bank(BANK_HRBZH, packet_send_buf, atoi(send_hrbzh.hrbzh_head.MsgLen) + sizeof(send_hrbzh.hrbzh_head), packet_recv_buf, sizeof(packet_recv_buf), &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_HRBZH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		
		// 12. 组合应答数据报文(查询交易)
		ret = Packet_Buf_Transform(packet_recv_buf, &recv_hrbzh, BUF_TO_PACKET, BANK_HRBZH, BANK_TRADE_CODE_QUERYBALANCE, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		
		// 13. 输出查询交易应答
		Trace_Bank_Package_HRBZH(&recv_hrbzh, "receivce query bank package");

		// 14. 判断错误码
		ret = Get_Bank_Error_Code(&recv_hrbzh, BANK_HRBZH);
		if (ret)
		{
			writelog(LOG_ERR, "bank_no=[%s]--errcode=[%d]", g_Bank.BankUnit[i].szBankAccountNO, ret);
			return ret;
		}
		
		// 15. 输出查询的余额
//		memcpy(pNode->Balance, ynxh_ans.cur_balance + 34, sizeof(pNode->Balance));
		memcpy(pNode->Balance, recv_hrbzh.hrbzh_trade_packet.trans_amount + sizeof(recv_hrbzh.hrbzh_trade_packet.trans_amount) - sizeof(pNode->Balance), sizeof(pNode->Balance));
		writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%9.9s]",pNode->Balance);
	}
	else
	{
		return E_TRANS_BANK_CARD_NONSUPPORT;
	}
	
	return 0;
}

int Bank_Transfer(INNER_TRANS_REQUEST * pNode,int serial_no)
{
	int ret=0;
	char temp[6]="";
	int flag=0;
	int i=0;
	int len=0;
	char sMoney[32]="";
	char sSerialno[32]="";
	int recv_length = 0;
	
	// 云南信用合作社
	int req_packet_length = 0;				// 信合请求报文总长度
	int ans_packet_length = 0;				// 信合应答报文总长度
	char prs_next[516] = "";				// 信合加密后的密钥
	char mac[9] = "";						// 信合计算后的mac密钥
	char packet_str[516] = "";				// 信合报文组合 
	char packet_send_buf[1892] = "";		// 发送报文buf
	char packet_recv_buf[1892] = "";		// 接受报文buf
	BANK_YNXH_TRADE_STRUCT_PACKET 	ynxh_req;	// 请求报文
	BANK_YNXH_TRADE_STRUCT_PACKET 	ynxh_ans;	// 应答报文
	memset(&ynxh_req, 0, sizeof(ynxh_req));
	memset(&ynxh_ans, 0, sizeof(ynxh_ans));

	// 云南农行
	BANK_YNNH_TRADE_STRUCT_PACKET ynnh_req;
	BANK_YNNH_TRADE_STRUCT_PACKET ynnh_ans;
	memset(&ynnh_req, 0x20, sizeof(ynnh_req));
	memset(&ynnh_ans, 0x20, sizeof(ynnh_ans));
	
	BANK_ZGYH_TRADE_STRUCT_TRANS_REQ 	zgyh_req;
	BANK_ZGYH_TRADE_STRUCT_TRANS_ANS 	zgyh_ans;

	BANK_GSYH_TRADE_STRUCT 			gsyh_req;
	BANK_GSYH_TRADE_STRUCT 			gsyh_ans;

	memset(&zgyh_req,0x20,sizeof zgyh_req);
	memset(&zgyh_ans,0x20,sizeof zgyh_ans);

	memset(&gsyh_ans,0x20,sizeof gsyh_ans);
	memset(&gsyh_req,0x20,sizeof gsyh_req);

	// 哈尔滨工行
	BANK_HRBZH_TRADE_STRUCT_PACKET send_hrbzh;
	BANK_HRBZH_TRADE_STRUCT_PACKET recv_hrbzh;
	memset(&send_hrbzh, 0x00, sizeof(send_hrbzh));
	memset(&recv_hrbzh, 0x00, sizeof(recv_hrbzh));
	
	//分析上传银行卡号属于哪个银行，根据银行标志，发送给不同的银行
	//转到transinfo外层去处理
	for(i=0;i<=g_Bank.BankCount;i++)
	{
		if(i==g_Bank.BankCount)	
		{
				writelog(LOG_ERR,"E_TRANS_BANK_CARD_NONSUPPORT,i=[%d]!g_Bank.BankCount=[%d]",i,g_Bank.BankCount);
				return E_TRANS_BANK_CARD_NONSUPPORT;
		}
		for(int j=0;j<MAX_RANGE;j++)
		{
			//printf("i=[%d],j=[%d],bankcard=[%s],range=[%s],len=[%d]]\n",i,j,pNode->BankCardNo,g_Bank.BankUnit[i].szBankCardRange[j],strlen(g_Bank.BankUnit[i].szBankCardRange[j]));
			if(0==strlen(g_Bank.BankUnit[i].szBankCardRange[j]))	break;
			if(0==memcmp(pNode->BankCardNo,g_Bank.BankUnit[i].szBankCardRange[j]
				,strlen(g_Bank.BankUnit[i].szBankCardRange[j])))
			{
				flag=1;
				g_Bank.cur_bankid=i;
				break;
			}
		}
		if(flag==1)	
			break;
	}
	printf("Bank_Transfer start!i=[%d],g_Bank.BankUnit[i].iBankID=[%d]\n",i,g_Bank.BankUnit[i].iBankID);
	
	//中国银行
	if(g_Bank.BankUnit[i].iBankID==BANK_ZGYH)
	{
		//memset(&zgyh_req,0x20,sizeof(zgyh_req));
		//memset(zgyh_req.head.Ret,0x20,sizeof(zgyh_req.head.Ret));					//返回码; 非0000为不成功
		memcpy(zgyh_req.head.TranCode,BANK_ZGYH_TRADE_CODE_TRANS,4);			//交易码; DXRB:转账,DXRV:冲正
		//memset(zgyh_req.head.BrnId,0x20,sizeof(zgyh_req.head.BrnId));				//网点号; 空格
		//memset(zgyh_req.head.TmlId,0x20,sizeof(zgyh_req.head.TmlId));				//终端号; 空格
		//memset(zgyh_req.head.TelId,0x20,sizeof(zgyh_req.head.TelId));				//柜员号; 空格
		//memset(zgyh_req.head.Filer1,0x20,sizeof(zgyh_req.head.Filer1));				//预留项;
		zgyh_req.head.Mchno_len=0x08;				//固定值; 0x08
		memcpy(zgyh_req.head.Merch_no,BANK_ZGYH_MERCH_NO,8);			//单位编码;  必填
		//memset(zgyh_req.head.Mch_name,0x20,sizeof(zgyh_req.head.Mch_name));			//单位名称;空格
		//memset(zgyh_req.head.Errcd,0x20,sizeof(zgyh_req.head.Errcd));				//错误代码;
		//memset(zgyh_req.head.ErrMsg,0x20,sizeof(zgyh_req.head.ErrMsg));				//错误信息;
		sprintf(sSerialno,"%d",serial_no);
		memcpy(zgyh_req.head.LocalNo,sSerialno,strlen(sSerialno));			//本地流水号
		//memcpy(zgyh_req.head.LocalNo,sSerialno,strlen(sSerialno));					//本地流水号;
		//memset(zgyh_req.head.BankNo,0x20,sizeof(zgyh_req.head.BankNo));//银行流水号;
		//memset(zgyh_req.head.Filer2,0x20,sizeof(zgyh_req.head.Filer2));				//预留;

		memcpy(zgyh_req.GDCAccount,pNode->CardNo,strlen(pNode->CardNo));			//校园卡帐号
		memcpy(zgyh_req.BankCard,pNode->BankCardNo,strlen(pNode->BankCardNo));	//银行卡号
		zgyh_req.CardType='D';				//卡类型；C信用卡,D借记卡

//		memcpy(zgyh_req.TranMoney,pNode->TransMoney,9);		//交易金额
//wenjian add
		sprintf(sMoney,"%013d",atoi(pNode->TransMoney));
		memcpy(zgyh_req.TranMoney,sMoney,sizeof(zgyh_req.TranMoney));	//交易金额
		//memset(zgyh_req.PinBlock,0x20,sizeof(zgyh_req.PinBlock));			//预留
		//memset(zgyh_req.TpkUdlmk,0x20,sizeof(zgyh_req.TpkUdlmk));			//预留
		Trace_Bank_Package_ZGYH_R(&zgyh_req,"Send query bank package:中国银行");
		ret=send_to_and_recv_from_bank(BANK_ZGYH,(char*)&zgyh_req,sizeof(zgyh_req),(char*)&zgyh_ans,sizeof(zgyh_ans),&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		Trace_Bank_Package_ZGYH_A(&zgyh_ans,"Receivce query bank package:中国银行");
		if(0!=strncmp(zgyh_ans.head.Ret,"0000",4))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%4.4s],msg=[%s] ",
						zgyh_ans.head.Ret,zgyh_ans.head.ErrMsg);
			memcpy(temp,zgyh_ans.head.Ret,4);
			temp[4]=0;
			switch(atoi(temp))
			{
				case 1:		//银行卡挂失
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
					return	E_TRANS_BANK_RECVERR;
				default:		//其他未知错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_BANK_RECVERR;
			}
		}
	}
	//工商银行
	else if(g_Bank.BankUnit[i].iBankID==BANK_GSYH)
	{
//		memset(&gsyh_req,0x20,sizeof(gsyh_req));
		memcpy(gsyh_req.ZoneNo,BANK_GSYH_ZONE_NO_GZ,4); //地区编号;广州:3602,珠海:2002;
		memcpy(gsyh_req.BusiType,BANK_GSYH_TYPE_SCHOOL,2);//交易类型，固定11
		memcpy(gsyh_req.TranCode,BANK_GSYH_TRADE_CODE_TRANS,2);////交易类型;1:转帐,2:取消,3:余额查询
		gsyh_req.TranFlag[0]='0';						//交易标志;0:正交易,1:反交易
		memcpy(gsyh_req.BankCardNo,pNode->BankCardNo,strlen(pNode->BankCardNo));//银行卡号;借方帐号，清算时为学校帐号			
		//memcpy(gsyh_req.TranMoney,pNode->TransMoney,9);//交易金额;
		sprintf(sMoney,"%010d",atoi(pNode->TransMoney));
		memcpy(gsyh_req.TranMoney,sMoney,sizeof(gsyh_req.TranMoney));	//交易金额
		memcpy(gsyh_req.MoneyType,"001",3);//货币种类;001:人民币
		memcpy(gsyh_req.TranDate,pNode->TradeDate,8); //交易日期;YYYYMMDD
		memcpy(gsyh_req.TranTime,pNode->TradeTime,6);//交易时间;HHMMSS
		gsyh_req.PwdFlag[0]='0';
		gsyh_req.PwdType[0]='0';							
		sprintf(sSerialno,"%d",serial_no);
		memcpy(gsyh_req.LocalSn,sSerialno,strlen(sSerialno));			//本地流水号
		//memcpy(gsyh_req.LocalDetranSn,"000000",6);		//冲正时填入的原转帐交易流水号
		//memcpy(gsyh_req.BankSn,"000000",6);			//银行流水号
		memcpy(gsyh_req.MercAccount,BANK_GSYH_MERCH_NO,5);	//圈存时为中山大学商户号,清算时为商户的商户号
		memcpy(gsyh_req.MercAccountCode,"01",2);		//户代号，指商户当有多个银行帐号时，该字段指示是哪一个帐号；先固定为01;
		memcpy(gsyh_req.GDCAccount,pNode->CardNo,strlen(pNode->CardNo));	//校园卡号;
		memcpy(gsyh_req.PosNo,pNode->TerminalId,strlen(pNode->TerminalId));	//圈存机号;
		memcpy(gsyh_req.AgentPercent,"000000000",9);		//清算时的代理提成百分比
		memcpy(gsyh_req.AgentType,"01",2);			//业务种类,01:圈存,02:消费;
		memset(gsyh_req.Filter,0x20,sizeof(gsyh_req.Filter));				//空格补位
		Trace_Bank_Package_GSYH(&gsyh_req,"Send query bank package:工商银行");
		ret=send_to_and_recv_from_bank(BANK_GSYH,(char*)&gsyh_req,sizeof(gsyh_req),(char*)&gsyh_ans,sizeof(gsyh_ans),&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		Trace_Bank_Package_GSYH(&gsyh_ans,"Receivce query bank package:工商银行");
		if(0!=strncmp(gsyh_ans.RetCode,"00",2))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s] ",gsyh_ans.RetCode);
			memcpy(temp,gsyh_ans.RetCode,2);
			temp[2]=0;
			switch(atoi(temp))
			{
				case 1:		//银行卡挂失
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
					return	E_TRANS_BANKCARD_LOST;
				case 2:		//银行卡状态错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
					return	E_TRANS_BANKACC_STATERR;
				case 3:		//银行卡金额不足
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
					return	E_TRANS_BANKACC_NOMONEY;
				case 4:		//银行密码错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_BANKCARD_PWDERR;
				case 98:		//银行处理超时
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
					return	E_TRANS_BANK_NOANSWER;
				case 99:		//其他错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_UNKNOW_ERROR;
				default:		//其他未知错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_UNKNOW_ERROR;
			}
		}

		//填充应答包
		//sprintf(pNode->RetCode,"%d",SUCCEED);
		//memcpy(pNode->Balance,gsyh_ans.TranMoney,sizeof(pNode->Balance));
		//writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%9s]",gsyh_ans.TranMoney);
	}
	else if (BANK_YNXH == g_Bank.BankUnit[i].iBankID)
	{
		// 3. 组合发送数据报文
		ret = Packet_Buf_Transform(packet_send_buf, &ynxh_req, PACKET_TO_BUF, 
								   BANK_YNXH, BANK_TRADE_CODE_TRANS, pNode, serial_no);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_BANK_NOANSWER;
		}

		// 4. 输出发送数据报文
		Trace_Bank_Package_YNXH(&ynxh_req, "send bank transfer package");
			
		// 5. 发送数据报文和接受应答数据报文
		ret = send_to_and_recv_from_bank(BANK_YNXH, packet_send_buf, atoi(ynxh_req.head.packet_length) + 4, packet_recv_buf, sizeof(packet_recv_buf), &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_YNXH,ret);
			return E_TRANS_BANK_NOANSWER;
		}

		// 6. 组合应答数据报文
		ret = Packet_Buf_Transform(packet_recv_buf + 4, &ynxh_ans, BUF_TO_PACKET, BANK_YNXH, BANK_TRADE_CODE_TRANS, pNode, serial_no);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_BANK_NOANSWER;
		}

		// 7. 输出应答数据报文
		Trace_Bank_Package_YNXH(&ynxh_ans,"receivce bank transfer package");

		// 8. 判断错误码
		ret = Get_Bank_Error_Code(&ynxh_ans, BANK_YNXH);
		if (ret)
		{
			writelog(LOG_ERR, "bank_no=[%s]--errcode=[%d]", g_Bank.BankUnit[i].szBankAccountNO, ret);
			return ret;
		}		
	}
	// 云南农行
	else if (BANK_YNNH == g_Bank.BankUnit[i].iBankID)
	{
		ret = Packet_Buf_Transform(packet_send_buf, &ynnh_req, PACKET_TO_BUF, BANK_YNNH, 
			BANK_TRADE_CODE_TRANS, pNode, serial_no);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}		

		Trace_Bank_Package_YNNH(&ynnh_req, "send bank transfer package");

		recv_length = sizeof(ynnh_req.ynnh_head) + sizeof(ynnh_req.bank_account) + 
			sizeof(ynnh_req.bank_pin) + sizeof(ynnh_req.card_id);
		
		ret = send_to_and_recv_from_bank(BANK_YNNH, packet_send_buf, strlen(packet_send_buf), packet_recv_buf, recv_length, &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]", BANK_YNNH, ret);
			return E_TRANS_BANK_NOANSWER;
		}
		
		ret = Packet_Buf_Transform(packet_recv_buf, &ynnh_ans, BUF_TO_PACKET, BANK_YNNH,
			BANK_TRADE_CODE_TRANS, pNode, serial_no);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		
		Trace_Bank_Package_YNNH(&ynnh_ans,"receivce bank transfer package");

		ret = Get_Bank_Error_Code(&ynnh_ans, BANK_YNNH);
		if (ret)
		{
			writelog(LOG_ERR, "bank_no=[%s]--errcode=[%d]", g_Bank.BankUnit[i].szBankAccountNO, ret);
			return ret;
		}
	}
	else if (BANK_HRBZH == g_Bank.BankUnit[i].iBankID)
	{
		//Add by hhd at 2010-8-27
		//		(1)中行修改业务流程，根据学生输入电话银行密码还是卡号，来选择是否做签到交易
		//		(2)因为银行的原因，10年暑期无法做到批量生成电话银行密码，因此修改以上流程
		//		(3)修改后，判断电话银行密码上送是否为空，为空不做签到直接交易，如果
		if(strlen(pNode->BankCardPwd)==0)	//判断是否输入电话银行密码，不输入判断卡号，输入原流程
		{
			des2src(pNode->BankCardPwd,"000000",6);
			writelog(LOG_ERR,"密码为空:pNode.BankCardNo=[%s],pNode.Reserve1=[%s]",pNode->BankCardNo,pNode->Reserve1);
			if(0==strncmp(pNode->BankCardNo,pNode->Reserve1,strlen(pNode->BankCardNo)))
			{
				goto TRANS;
			}
			else 
			{
				writelog(LOG_ERR,"pNode.BankCardNo=[%s],pNode.Reserve1=[%s]",pNode->BankCardNo,pNode->Reserve1);
				return E_TRANS_RELATION_NOEXIT;
			}
		}
SIGNIN:
		// 1. 组合签到报文
		ret = Packet_Buf_Transform(packet_send_buf, &send_hrbzh, PACKET_TO_BUF, BANK_HRBZH, BANK_TRADE_CODE_SIGN_IN, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}		

		// 2. 输出签到报文
		Trace_Bank_Package_HRBZH(&send_hrbzh, "send sign in bank package");

		// 3. 发送数据报文和接受应答数据报文(签到交易)
		ret = send_to_and_recv_from_bank(BANK_HRBZH, packet_send_buf, atoi(send_hrbzh.hrbzh_head.MsgLen) + sizeof(send_hrbzh.hrbzh_head), packet_recv_buf, sizeof(packet_recv_buf), &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_HRBZH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		
		// 4. 组合应答数据报文(签到交易)
		ret = Packet_Buf_Transform(packet_recv_buf, &recv_hrbzh, BUF_TO_PACKET, BANK_HRBZH, BANK_TRADE_CODE_SIGN_IN, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		
		// 7. 输出签到交易应答
		Trace_Bank_Package_HRBZH(&recv_hrbzh, "receivce sign in bank package");

		// 8. 判断错误码
		ret = Get_Bank_Error_Code(&recv_hrbzh, BANK_HRBZH);
		if (ret)
		{
			writelog(LOG_ERR, "bank_no=[%s]--errcode=[%d]", g_Bank.BankUnit[i].szBankAccountNO, ret);
			return ret;
		}
TRANS:	
		memset(packet_send_buf, 0x00, sizeof(packet_send_buf));
		memset(packet_recv_buf, 0x00, sizeof(packet_recv_buf));
		memset(&send_hrbzh, 0x00, sizeof(send_hrbzh));
		memset(&recv_hrbzh, 0x00, sizeof(recv_hrbzh));
		// 9. 组合转账报文
		ret = Packet_Buf_Transform(packet_send_buf, &send_hrbzh, PACKET_TO_BUF, BANK_HRBZH, BANK_TRADE_CODE_TRANS, pNode, serial_no);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}

		// 10. 输出转帐报文
		Trace_Bank_Package_HRBZH(&send_hrbzh, "TTTTTTTTTT send bank transfer package");

		// 11. 发送数据报文和接受应答数据报文(转帐交易)
		ret = send_to_and_recv_from_bank(BANK_HRBZH, packet_send_buf, atoi(send_hrbzh.hrbzh_head.MsgLen) + sizeof(send_hrbzh.hrbzh_head), packet_recv_buf, sizeof(packet_recv_buf), &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_HRBZH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		
		// 12. 组合应答数据报文(转帐交易)
		ret = Packet_Buf_Transform(packet_recv_buf, &recv_hrbzh, BUF_TO_PACKET, BANK_HRBZH, BANK_TRADE_CODE_TRANS, pNode, serial_no);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		
		// 13. 输出转帐交易应答
		Trace_Bank_Package_HRBZH(&recv_hrbzh, "receivce bank transfer package");

		// 14. 判断错误码
		ret = Get_Bank_Error_Code(&recv_hrbzh, BANK_HRBZH);
		if (ret)
		{
			writelog(LOG_ERR, "bank_no=[%s]--errcode=[%d]", g_Bank.BankUnit[i].szBankAccountNO, ret);
			return ret;
		}
	}
	else
	{
		return E_TRANS_BANK_CARD_NONSUPPORT;
	}
	
	return 0;
}

int Bank_Undo(INNER_TRANS_REQUEST * pNode)
{

	int ret=0;
	char temp[6]="";
	int flag=0;
	int i=0;
	int recv_length = 0;
	
	// 云南信用合作社
	int req_packet_length = 0;				// 信合请求报文总长度
	int ans_packet_length = 0;				// 信合应答报文总长度
	char prs_next[516] = "";				// 信合加密后的密钥
	char mac[9] = "";						// 信合计算后的mac密钥
	char packet_str[516] = "";				// 信合报文组合 
	char packet_send_buf[1892] = "";		// 发送报文buf
	char packet_recv_buf[1892] = "";		// 接受报文buf
	BANK_YNXH_TRADE_STRUCT_PACKET 	ynxh_req;	// 请求报文
	BANK_YNXH_TRADE_STRUCT_PACKET 	ynxh_ans;	// 应答报文
	memset(&ynxh_req, 0, sizeof(ynxh_req));
	memset(&ynxh_ans, 0, sizeof(ynxh_ans));

	// 云南农行
	BANK_YNNH_TRADE_STRUCT_PACKET ynnh_req;
	BANK_YNNH_TRADE_STRUCT_PACKET ynnh_ans;
	memset(&ynnh_req, 0x20, sizeof(ynnh_req));
	memset(&ynnh_ans, 0x20, sizeof(ynnh_ans));
	
	BANK_ZGYH_TRADE_STRUCT_DETRANS_REQ 	zgyh_req;
	BANK_ZGYH_TRADE_STRUCT_DETRANS_ANS 	zgyh_ans;

	BANK_GSYH_TRADE_STRUCT 			gsyh_req;
	BANK_GSYH_TRADE_STRUCT 			gsyh_ans;

	memset(&zgyh_req,0x20,sizeof zgyh_req);
	memset(&zgyh_ans,0x20,sizeof zgyh_ans);

	memset(&gsyh_ans,0x20,sizeof gsyh_ans);
	memset(&gsyh_req,0x20,sizeof gsyh_req);

	// 哈尔滨中行
	BANK_HRBZH_TRADE_STRUCT_PACKET send_hrbzh;
	BANK_HRBZH_TRADE_STRUCT_PACKET recv_hrbzh;
	memset(&send_hrbzh, 0x00, sizeof(send_hrbzh));
	memset(&recv_hrbzh, 0x00, sizeof(recv_hrbzh));

	//分析上传银行卡号属于哪个银行，根据银行标志，发送给不同的银行
	for(i=0;i<=g_Bank.BankCount;i++)
	{
		if(i==g_Bank.BankCount)	
		{
				writelog(LOG_ERR,"E_TRANS_BANK_CARD_NONSUPPORT,i=[%d]!g_Bank.BankCount=[%d]",i,g_Bank.BankCount);
				return E_TRANS_BANK_CARD_NONSUPPORT;
		}
		for(int j=0;j<MAX_RANGE;j++)
		{
			writelog(LOG_INFO,"BANKID=[%d], BANKCARDRAGNT=[%s], i=[%d], j=[%d]", g_Bank.BankUnit[i].iBankID, g_Bank.BankUnit[i].szBankCardRange[j], i, j);
			if(0==strlen(g_Bank.BankUnit[i].szBankCardRange[j]))	break;
			if(0==memcmp(pNode->BankCardNo,g_Bank.BankUnit[i].szBankCardRange[j]
				,strlen(g_Bank.BankUnit[i].szBankCardRange[j])))
			{
				flag=1;
				g_Bank.cur_bankid=i;
				break;
			}
		}
		if(flag==1)	
			break;
	}
	//中国银行
	if(g_Bank.BankUnit[i].iBankID==BANK_ZGYH)
	{
		memset(zgyh_req.head.Ret,0x20,sizeof(zgyh_req.head.Ret));					//返回码; 非0000为不成功
		memcpy(zgyh_req.head.TranCode,BANK_ZGYH_TRADE_CODE_DETRANS,4);			//交易码; DXRB:转账,DXRV:冲正
		memset(zgyh_req.head.BrnId,0x20,sizeof(zgyh_req.head.BrnId));				//网点号; 空格
		memset(zgyh_req.head.TmlId,0x20,sizeof(zgyh_req.head.TmlId));				//终端号; 空格
		memset(zgyh_req.head.TelId,0x20,sizeof(zgyh_req.head.TelId));				//柜员号; 空格
		memset(zgyh_req.head.Filer1,0x20,sizeof(zgyh_req.head.Filer1));				//预留项;
		zgyh_req.head.Mchno_len=0x08;				//固定值; 0x08
		memcpy(zgyh_req.head.Merch_no,BANK_ZGYH_MERCH_NO,8);			//单位编码;  必填
		memset(zgyh_req.head.Mch_name,0x20,sizeof(zgyh_req.head.Mch_name));			//单位名称;空格
		memset(zgyh_req.head.Errcd,0x20,sizeof(zgyh_req.head.Errcd));				//错误代码;
		memset(zgyh_req.head.ErrMsg,0x20,sizeof(zgyh_req.head.ErrMsg));				//错误信息;
		sprintf(zgyh_req.head.LocalNo,"%d",pNode->SendNo);			//本地流水号;
		memset(zgyh_req.head.BankNo,0x20,sizeof(zgyh_req.head.BankNo));				//银行流水号;
		memset(zgyh_req.head.Filer2,0x20,sizeof(zgyh_req.head.Filer2));				//预留;

		memcpy(zgyh_req.GDCAccount,pNode->CardNo,12);			//校园卡帐号
		memcpy(zgyh_req.BankCard,pNode->BankCardNo,20);			//银行卡号
		zgyh_req.CardType='D';				//卡类型；C信用卡,D借记卡
		memcpy(zgyh_req.TranMoney,pNode->TransMoney,9);			//交易金额
		memset(zgyh_req.PinBlock,0x20,sizeof(zgyh_req.PinBlock));			//预留
		memset(zgyh_req.TpkUdlmk,0x20,sizeof(zgyh_req.TpkUdlmk));			//预留
		memset(zgyh_req.XykSqh,0x20,sizeof(zgyh_req.XykSqh));		//信用卡授权号
		sprintf(zgyh_req.OldLocalNo,"%d",pNode->RecvNo);		//原本地流水号
		
		//Trace_Bank_Package_ZGYH_R(&zgyh_req,"Send query bank package:中国银行");
		ret=send_to_and_recv_from_bank(BANK_ZGYH,(char*)&zgyh_req,sizeof(zgyh_req),(char*)&zgyh_ans,sizeof(zgyh_ans),&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		//Trace_Bank_Package_ZGYH_A(&zgyh_ans,"Receivce query bank package:中国银行");
		if(0!=strncmp(zgyh_ans.head.Ret,"0000",4))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%4.4s] ",zgyh_ans.head.Ret);
			memcpy(temp,zgyh_ans.head.Ret,4);
			temp[4]=0;
			switch(atoi(temp))
			{
				case 1:		//银行卡挂失
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
					return	E_TRANS_BANKCARD_LOST;
				case 2:		//银行卡状态错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
					return	E_TRANS_BANKACC_STATERR;
				case 3:		//银行卡金额不足
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
					return	E_TRANS_BANKACC_NOMONEY;
				case 4:		//银行密码错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_BANKCARD_PWDERR;
				case 98:		//银行处理超时
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
					return	E_TRANS_BANK_NOANSWER;
				case 99:		//其他错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_UNKNOW_ERROR;
				default:		//其他未知错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_UNKNOW_ERROR;
			}
		}
	}
	//工商银行
	else if(g_Bank.BankUnit[i].iBankID==BANK_GSYH)
	{
		memcpy(gsyh_req.ZoneNo,BANK_GSYH_ZONE_NO_GZ,4); //地区编号;广州:3602,珠海:2002;
		memcpy(gsyh_req.BusiType,BANK_GSYH_TYPE_SCHOOL,2);//交易类型，固定11
		memcpy(gsyh_req.TranCode,BANK_GSYH_TRADE_CODE_DETRANS,2);////交易类型;1:转帐,2:取消,3:余额查询
		gsyh_req.TranFlag[0]='0';						//交易标志;0:正交易,1:反交易
		memcpy(gsyh_req.BankCardNo,pNode->BankCardNo,sizeof(pNode->BankCardNo));//银行卡号;借方帐号，清算时为学校帐号
		memcpy(gsyh_req.TranMoney,pNode->TransMoney,9);//交易金额;
		memcpy(gsyh_req.MoneyType,"001",3);//货币种类;001:人民币
		memcpy(gsyh_req.TranDate,pNode->TradeDate,8); //交易日期;YYYY-MM-DD
		memcpy(gsyh_req.TranTime,pNode->TradeTime,6);//交易时间;HHMMSS
		gsyh_req.PwdFlag[0]='0';
		gsyh_req.PwdType[0]='0';							
		sprintf(gsyh_req.LocalSn,"%d",pNode->SendNo);			//本地流水号
		sprintf(gsyh_req.LocalDetranSn,"%d",pNode->RecvNo);		//冲正时填入的原转帐交易流水号
		memcpy(gsyh_req.BankSn,"000000",6);			//银行流水号
		memcpy(gsyh_req.MercAccount,BANK_GSYH_MERCH_NO,5);	//圈存时为中山大学商户号,清算时为商户的商户号
		memcpy(gsyh_req.MercAccountCode,"01",2);		//户代号，指商户当有多个银行帐号时，该字段指示是哪一个帐号；先固定为01;
		memcpy(gsyh_req.GDCAccount,pNode->CardNo,10);			//校园卡号;
		memcpy(gsyh_req.PosNo,pNode->TerminalId,5);				//圈存机号;
		memcpy(gsyh_req.AgentPercent,"000000000",9);		//清算时的代理提成百分比
		memcpy(gsyh_req.AgentType,"01",2);			//业务种类,01:圈存,02:消费;
		memset(gsyh_req.Filter,0x20,sizeof(gsyh_req.Filter));				//空格补位
		Trace_Bank_Package_GSYH(&gsyh_req,"Send query bank package:工商银行");
		ret=send_to_and_recv_from_bank(BANK_GSYH,(char*)&gsyh_req,sizeof(gsyh_req),(char*)&gsyh_ans,sizeof(gsyh_ans),&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		Trace_Bank_Package_GSYH(&gsyh_ans,"Send query bank package:工商银行");
		if(0!=strncmp(gsyh_ans.RetCode,"00",2))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s] ",gsyh_ans.RetCode);
			memcpy(temp,gsyh_ans.RetCode,2);
			temp[2]=0;
			switch(atoi(temp))
			{
				case 1:		//银行卡挂失
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
					return	E_TRANS_BANKCARD_LOST;
				case 2:		//银行卡状态错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
					return	E_TRANS_BANKACC_STATERR;
				case 3:		//银行卡金额不足
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
					return	E_TRANS_BANKACC_NOMONEY;
				case 4:		//银行密码错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_BANKCARD_PWDERR;
				case 98:		//银行处理超时
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
					return	E_TRANS_BANK_NOANSWER;
				case 99:		//其他错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_UNKNOW_ERROR;
				default:		//其他未知错误
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_UNKNOW_ERROR;
			}
		}

		//填充应答包
		//sprintf(pNode->RetCode,"%d",SUCCEED);
		//memcpy(pNode->Balance,gsyh_ans.TranMoney,sizeof(pNode->Balance));
		//writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%9s]",gsyh_ans.TranMoney);
	}
	else if ((BANK_YNXH == g_Bank.BankUnit[i].iBankID))
	{
		// 3. 组合发送数据报文
		ret = Packet_Buf_Transform(packet_send_buf, &ynxh_req, PACKET_TO_BUF, 
								   BANK_YNXH, BANK_TRADE_CODE_DETRANS, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_BANK_NOANSWER;
		}

		// 4. 输出发送数据报文
		Trace_Bank_Package_YNXH(&ynxh_req, "send detrans bank package");
			
		// 5. 发送数据报文和接受应答数据报文
		ret = send_to_and_recv_from_bank(BANK_YNXH, packet_send_buf, atoi(ynxh_req.head.packet_length) + 4, packet_recv_buf, ans_packet_length, &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_YNXH,ret);
			return E_TRANS_BANK_NOANSWER;
		}

		// 6. 组合应答数据报文
		ret = Packet_Buf_Transform(packet_recv_buf + 4, &ynxh_ans, BUF_TO_PACKET, BANK_YNXH, BANK_TRADE_CODE_DETRANS, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_BANK_NOANSWER;
		}

		// 7. 输出应答数据报文
		Trace_Bank_Package_YNXH(&ynxh_ans,"receivce detrans bank package");

		// 8. 判断错误码
		ret = Get_Bank_Error_Code(&ynxh_ans, BANK_YNXH);
		if (ret)
		{
			writelog(LOG_ERR, "bank_no=[%s]--errcode=[%d]--card_id=[%s]", g_Bank.BankUnit[i].szBankAccountNO, ret, pNode->CardNo);
			return ret;
		}
	}
	// 云南农行
	else if (BANK_YNNH == g_Bank.BankUnit[i].iBankID)
	{
		ret = Packet_Buf_Transform(packet_send_buf, &ynnh_req, PACKET_TO_BUF, BANK_YNNH, 
			BANK_TRADE_CODE_DETRANS, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}		

		Trace_Bank_Package_YNNH(&ynnh_req, "send detrans bank package");

		recv_length = sizeof(ynnh_req.ynnh_head) + sizeof(ynnh_req.bank_account) + sizeof(ynnh_req.trans_serail);
		
		ret = send_to_and_recv_from_bank(BANK_YNNH, packet_send_buf, strlen(packet_send_buf), packet_recv_buf, recv_length, &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]", BANK_YNNH, ret);
			return E_TRANS_BANK_NOANSWER;
		}
		
		ret = Packet_Buf_Transform(packet_recv_buf, &ynnh_ans, BUF_TO_PACKET, BANK_YNNH,
			BANK_TRADE_CODE_DETRANS, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		
		Trace_Bank_Package_YNNH(&ynnh_ans,"receivce detrans bank package");

		ret = Get_Bank_Error_Code(&ynnh_ans, BANK_YNNH);
		if (ret)
		{
			writelog(LOG_ERR, "bank_no=[%s]--errcode=[%d]", g_Bank.BankUnit[i].szBankAccountNO, ret);
			return ret;
		}
	}
	else if (BANK_HRBZH == g_Bank.BankUnit[i].iBankID)
	{	
		ret = Packet_Buf_Transform(packet_send_buf, &send_hrbzh, PACKET_TO_BUF, BANK_HRBZH, BANK_TRADE_CODE_DETRANS, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}

		Trace_Bank_Package_HRBZH(&send_hrbzh, "send detrans bank package");

		ret = send_to_and_recv_from_bank(BANK_HRBZH, packet_send_buf, atoi(send_hrbzh.hrbzh_head.MsgLen) + sizeof(send_hrbzh.hrbzh_head), packet_recv_buf, sizeof(packet_recv_buf), &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_HRBZH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		
		ret = Packet_Buf_Transform(packet_recv_buf, &recv_hrbzh, BUF_TO_PACKET, BANK_HRBZH, BANK_TRADE_CODE_DETRANS, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		
		Trace_Bank_Package_HRBZH(&recv_hrbzh, "receivce detrans bank package");

		ret = Get_Bank_Error_Code(&recv_hrbzh, BANK_HRBZH);
		if (ret)
		{
			writelog(LOG_ERR, "bank_no=[%s]--errcode=[%d]", g_Bank.BankUnit[i].szBankAccountNO, ret);
			return ret;
		}
	}
	else
	{
		return E_TRANS_BANK_CARD_NONSUPPORT;
	}
	return 0;
}
int Bank_CheckLine()
{
	return 0;
}

int Bank_SignIn(INNER_TRANS_REQUEST *pNode)
{
	return 0;
}
int Bank_SignOut()
{
	return 0;
}
int send_to_and_recv_from_bank(int const bank_id,char* pSend, int send_len,char* pRecv,int recv_len,ST_BANK_CONFIG *pBank)
{
	struct SockNode  SockNode;
	char bank_ip[20]="";
	int bank_port=0;
	int ret=0;
	int delay_time=10000;
	// 云南信合使用
	int packet_length = 0;
	int packet_head_length = 0;
	char str_packet_length[5] = "";

	des2src(bank_ip,pBank->BankUnit[pBank->cur_bankid].szBankIP);
	bank_port=pBank->BankUnit[pBank->cur_bankid].iBankPort;
	delay_time=pBank->BankUnit[pBank->cur_bankid].iBankTimeout;
	//启用signal，防止阻塞模式的socket

	alarm(delay_time/1000);
	//连接银行
	ret=SockNode.hSock.ConnectTcp(bank_ip,bank_port);
	if(!ret)
	{	
		alarm(0);
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],bank_ip[%s],port[%d] ",ret,bank_ip,bank_port);
		return E_TRANS_BANK_NETERR;
	}
	alarm(0);
	//发送数据到银行
	writelog(LOG_ERR,"Send to Bank--Buf[%s]--Length[%d]", pSend, send_len);
	if (BANK_YNXH == bank_id || BANK_HRBZH == bank_id) 
	{
		// 报文数据 = 报文长度(4字节) + 报文总长度
		Trace_8583_Package(pSend, send_len, 0, "send msg");
	}
	
	ret = SockNode.hSock.Send(pSend, send_len);
	if (ret < 0)
	{
	      	// 发送时，端口有问题，包括被关闭
		writelog(LOG_ERR,"Send to bank error,ret = [%d] ",ret);
		return E_TRANS_BANK_NETERR;
	}
	else if (0==ret)
	{
		// 不应该出现这种情况
	    writelog(LOG_ERR,"Send to bank error,CTcpSocket.Send should not return this error,error code is[%d]!\n",errno);
	    return	E_TRANS_BANK_NETERR;
	}
	
	writelog(LOG_ERR,"Send to Bank Ret=[%d]", ret);
	system("sleep 1");

	// 接收信合返回信息
	if (BANK_YNXH == bank_id)
	{
		// 如果是信合圈存设备, 收包长度不确定, 先解头部的46个字节, 获取整个报文长度
		packet_head_length = 50;
		ret = SockNode.hSock.Recv(pRecv, packet_head_length, delay_time);
		if (ret != packet_head_length)
		{
			writelog(LOG_ERR,"Receive packet head from bank error,ret= [%d]--packet_head_length=[%d]", ret, packet_head_length);
			return	E_TRANS_BANK_NOANSWER;  // 接收时候出错，或超时
		}

		memcpy(str_packet_length, pRecv, 4);
		packet_length = atoi(str_packet_length);
		
		// 获取报文体长度
		printf("报文体长度	=[%4.4s]\n", str_packet_length);
		ret = SockNode.hSock.Recv(pRecv + packet_head_length, packet_length + 4 - packet_head_length , delay_time);
		if (ret != packet_length + 4 - packet_head_length)
		{
			writelog(LOG_ERR,"Receive packet from bank error,ret= [%d]--packet_length=[%d]", ret, packet_length - 46);
			return	E_TRANS_BANK_NOANSWER;  // 接收时候出错，或超时
		}

		Trace_8583_Package(pRecv, packet_length + 4, 0, "recv msg");
	}
	else if (BANK_HRBZH == bank_id)
	{
		//sleep(1);
		usleep(TIME_OUT1);
		// 如果是中行圈存设备, 收包长度不确定, 先解头部的88个字节, 获取整个报文长度
		packet_head_length = 88;
		ret = SockNode.hSock.Recv(pRecv, packet_head_length, delay_time);
		if (ret != packet_head_length)
		{
			writelog(LOG_ERR,"Receive packet head from bank error,ret= [%d]--packet_head_length=[%d]", ret, packet_head_length);
			return	E_TRANS_BANK_NOANSWER;  // 接收时候出错，或超时
		}

		memcpy(str_packet_length, pRecv + packet_head_length - 4, 4);	// from 85 to 88, 4 byte packet length
		packet_length = atoi(str_packet_length);
		
		ret = SockNode.hSock.Recv(pRecv + packet_head_length, packet_length, delay_time);
		if (ret != packet_length)
		{
			writelog(LOG_ERR,"Receive packet from bank error,ret= [%d]--packet_length=[%d]", ret, packet_length - 46);
			return	E_TRANS_BANK_NOANSWER;  // 接收时候出错，或超时
		}

		Trace_8583_Package(pRecv, packet_length + packet_head_length, 0, "recv msg");
	}
	else
	{		
		ret = SockNode.hSock.Recv(pRecv,recv_len,delay_time);
		if (ret != recv_len)
		{
			writelog(LOG_ERR,"Receive from bank error,ret= [%d] ",ret);
			return	E_TRANS_BANK_NOANSWER;  // 接收时候出错，或超时
		}
		Trace_8583_Package(pRecv, recv_len, 10, "recv msg");
	}
	
	SockNode.hSock.Close();
	return 0;
}

