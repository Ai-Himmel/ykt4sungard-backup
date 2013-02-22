/* ----------------------------------------------------------
 * �������ƣ�bank_nyyh.cpp
 * �������ڣ�2007-07-27 14:58
 * �������ߣ�������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ�ͨ�ýӿڹ淶�ķ�װ
 * ----------------------------------------------------------
 * �޸�����: 2008-03-26
 * �޸���Ա: ����
 * �޸�����: �����������ú�����ӿں���
 * �汾��Ϣ: 
 * ��ע��Ϣ: 
 * ----------------------------------------------------------
 * �޸�����: 2008-04-26
 * �޸���Ա: ����
 * �޸�����: ��������ũҵ���нӿں���
 * �汾��Ϣ: 
 * ��ע��Ϣ: 
 * ----------------------------------------------------------
 * �޸�����: 2008-07-26
 * �޸���Ա: ����
 * �޸�����: �������������нӿں���
 * �汾��Ϣ: 
 * ��ע��Ϣ: 
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

//����ͨ�ýӿڹ淶���з�װ�������еĽӿ�
int Bank_QueryBalance(INNER_TRANS_REQUEST * pNode,double *balance)
{
	int ret=0;
	char temp[6]="";
	int i=0;
	int flag=0;
	int send_length = 0;
	int recv_length = 0;
	
	// �������ú�����
	char packet_send_buf[4096] = "";		// �źϷ��ͱ���buf
	char packet_recv_buf[4096] = "";		// �źϽ��ܱ���buf
	BANK_YNXH_TRADE_STRUCT_PACKET 	ynxh_req;	// �ź�������
	BANK_YNXH_TRADE_STRUCT_PACKET 	ynxh_ans;	// �ź�Ӧ����
	memset(&ynxh_req, 0, sizeof(ynxh_req));
	memset(&ynxh_ans, 0, sizeof(ynxh_ans));

	// ����ũ��
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

	// ����������
	BANK_HRBZH_TRADE_STRUCT_PACKET send_hrbzh;
	BANK_HRBZH_TRADE_STRUCT_PACKET recv_hrbzh;
	memset(&send_hrbzh, 0x00, sizeof(send_hrbzh));
	memset(&recv_hrbzh, 0x00, sizeof(recv_hrbzh));
	
	//�����ϴ����п��������ĸ����У��������б�־�����͸���ͬ������
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
	//�й����У��й�����Ŀǰ��֧�ֲ�ѯ�������Ľӿ�
	if(g_Bank.BankUnit[i].iBankID==BANK_ZGYH)
	{
		return E_TRANS_BANK_FUNC_NONSUPPORT;
	}
	//�������У����չ������нӿڽ��з������ݰ����������ذ�
	else if(g_Bank.BankUnit[i].iBankID==BANK_GSYH)
	{
		memset(&gsyh_req.ZoneNo,0x20,sizeof(gsyh_req));
		memcpy(gsyh_req.ZoneNo,BANK_GSYH_ZONE_NO_GZ,4); //�������;����:3602,�麣:2002;
		memcpy(gsyh_req.BusiType,BANK_GSYH_TYPE_SCHOOL,2);//�������ͣ��̶�11
		memcpy(gsyh_req.TranCode,BANK_GSYH_TRADE_CODE_QUERYBALANCE,2);////��������;1:ת��,2:ȡ��,3:����ѯ
		gsyh_req.TranFlag[0]='0';						//���ױ�־;0:������,1:������
		memcpy(gsyh_req.BankCardNo,pNode->BankCardNo,strlen(pNode->BankCardNo));//���п���;�跽�ʺţ�����ʱΪѧУ�ʺ�
		//memcpy(gsyh_req.TranMoney,pNode->TransMoney,strlen(pNode->TransMoney));//���׽��;
		memcpy(gsyh_req.MoneyType,"001",3);//��������;001:�����
		memcpy(gsyh_req.TranDate,pNode->TradeDate,8); //��������;YYYYMMDD
		memcpy(gsyh_req.TranTime,pNode->TradeTime,6);//����ʱ��;HHMMSS
		gsyh_req.PwdFlag[0]='0';
		gsyh_req.PwdType[0]='0';
		memcpy(gsyh_req.LocalSn,"999999",6);
		memcpy(gsyh_req.LocalDetranSn,"000000",6);		//����ʱ�����ԭת�ʽ�����ˮ��
		memcpy(gsyh_req.BankSn,"000000",6);			//������ˮ��
		memcpy(gsyh_req.MercAccount,BANK_GSYH_MERCH_NO,5);	//Ȧ��ʱΪ��ɽ��ѧ�̻���,����ʱΪ�̻����̻���
		memcpy(gsyh_req.MercAccountCode,"01",2);		//�����ţ�ָ�̻����ж�������ʺ�ʱ�����ֶ�ָʾ����һ���ʺţ��ȹ̶�Ϊ01;
		memcpy(gsyh_req.GDCAccount,pNode->CardNo,strlen(pNode->CardNo));	//У԰����;
		memcpy(gsyh_req.PosNo,pNode->TerminalId,5);				//Ȧ�����;
		memcpy(gsyh_req.AgentPercent,"000000000",9);		//����ʱ�Ĵ�����ɰٷֱ�
		memcpy(gsyh_req.AgentType,"01",2);			//ҵ������,01:Ȧ��,02:����;
		//memset(gsyh_req.Filter,0x20,sizeof(gsyh_req.Filter));				//�ո�λ
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
				case 1:		//���п���ʧ
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
					return	E_TRANS_BANKCARD_LOST;
				case 2:		//���п�״̬����
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
					return	E_TRANS_BANKACC_STATERR;
				case 3:		//���п�����
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
					return	E_TRANS_BANKACC_NOMONEY;
				case 4:		//�����������
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_BANKCARD_PWDERR;
				case 98:		//���д���ʱ
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
					return	E_TRANS_BANK_NOANSWER;
				case 99:		//��������
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_UNKNOW_ERROR;
				default:		//����δ֪����
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_UNKNOW_ERROR;
			}
		}

		//���Ӧ���
		//sprintf(pNode->RetCode,"%d",SUCCEED);
		memcpy(pNode->Balance,gsyh_ans.TranMoney,sizeof(pNode->Balance));
		writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%9s]",gsyh_ans.TranMoney);
	}
	// �������ú�����
	else if (g_Bank.BankUnit[i].iBankID==BANK_YNXH)
	{	
		// 4. ��Ϸ������ݱ���
		ret = Packet_Buf_Transform(packet_send_buf, &ynxh_req, PACKET_TO_BUF, BANK_YNXH, BANK_TRADE_CODE_QUERYBALANCE, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}		

		Trace_Bank_Package_YNXH(&ynxh_req, "send query bank package");

		// 5. �������ݱ��ĺͽ���Ӧ�����ݱ���
		ret = send_to_and_recv_from_bank(BANK_YNXH, packet_send_buf, atoi(ynxh_req.head.packet_length) + 4, packet_recv_buf, sizeof(packet_recv_buf), &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_YNXH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		
		// 6. ���Ӧ�����ݱ���
		ret = Packet_Buf_Transform(packet_recv_buf + 4, &ynxh_ans, BUF_TO_PACKET, BANK_YNXH, BANK_TRADE_CODE_QUERYBALANCE, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		
		// 7. ���Ӧ�����ݱ���
		Trace_Bank_Package_YNXH(&ynxh_ans,"receivce query bank package");

		// 8. �жϴ�����
		ret = Get_Bank_Error_Code(&ynxh_ans, BANK_YNXH);
		if (ret)
		{
			writelog(LOG_ERR, "bank_no=[%s]--errcode=[%d]", g_Bank.BankUnit[i].szBankAccountNO, ret);
			return ret;
		}

		// 9, �����ѯ�����
		memcpy(pNode->Balance, ynxh_ans.cur_balance + 34, sizeof(pNode->Balance));
		writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%9s]",pNode->Balance);
	}
	// ����ũ��
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
		
		memcpy(pNode->Balance, ynnh_ans.remain_money, sizeof(pNode->Balance));			// ���ý���Ҳ��ո�
		writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%9s]",pNode->Balance);
	}
	// ����������
	else if (g_Bank.BankUnit[i].iBankID==BANK_HRBZH)
	{	
		// ע��: (1) ���������з��Ͳ�ѯ��ת�ʽ��׵�ʱ����Ҫ���н���ǩ��
		//		 (2) ������ǩ�����׷ŵ���ѯ��ת�ʽ�����
		//		 (3) ÿ���ڲ�ѯ��ת��֮ǰ����һ�ν���ǩ��, ���׳ɹ��Ժ�ִ�в�ѯ��ת��
		//Add by hhd at 2010-8-27
		//		(1)�����޸�ҵ�����̣�����ѧ������绰�������뻹�ǿ��ţ���ѡ���Ƿ���ǩ������
		//		(2)��Ϊ���е�ԭ��10�������޷������������ɵ绰�������룬����޸���������
		//		(3)�޸ĺ��жϵ绰�������������Ƿ�Ϊ�գ�Ϊ�ղ���ǩ��ֱ�ӽ��ף����
		if(strlen(pNode->BankCardPwd)==0)	//�ж��Ƿ�����绰�������룬�������жϿ��ţ�����ԭ����
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
		// 1. ���ǩ������
		memset(packet_send_buf, 0x00, sizeof(packet_send_buf));
		memset(packet_recv_buf, 0x00, sizeof(packet_send_buf));
		ret = Packet_Buf_Transform(packet_send_buf, &send_hrbzh, PACKET_TO_BUF, BANK_HRBZH, BANK_TRADE_CODE_SIGN_IN, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}		

		// 2. ���ǩ������
		Trace_Bank_Package_HRBZH(&send_hrbzh, "send sign in bank package");

		// 3. �������ݱ��ĺͽ���Ӧ�����ݱ���(ǩ������)
		ret = send_to_and_recv_from_bank(BANK_HRBZH, packet_send_buf, atoi(send_hrbzh.hrbzh_head.MsgLen) + sizeof(send_hrbzh.hrbzh_head), packet_recv_buf, sizeof(packet_recv_buf), &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_HRBZH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		
		// 4. ���Ӧ�����ݱ���(ǩ������)
		ret = Packet_Buf_Transform(packet_recv_buf, &recv_hrbzh, BUF_TO_PACKET, BANK_HRBZH, BANK_TRADE_CODE_SIGN_IN, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		
		// 7. ���ǩ������Ӧ��
		Trace_Bank_Package_HRBZH(&recv_hrbzh, "receivce sign in bank package");

		// 8. �жϴ�����
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
		// 9. ��ϲ�ѯ����
		ret = Packet_Buf_Transform(packet_send_buf, &send_hrbzh, PACKET_TO_BUF, BANK_HRBZH, BANK_TRADE_CODE_QUERYBALANCE, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}

		// 10. �����ѯ����
		Trace_Bank_Package_HRBZH(&send_hrbzh, "send query bank package");

		// 11. �������ݱ��ĺͽ���Ӧ�����ݱ���(��ѯ����)
		ret = send_to_and_recv_from_bank(BANK_HRBZH, packet_send_buf, atoi(send_hrbzh.hrbzh_head.MsgLen) + sizeof(send_hrbzh.hrbzh_head), packet_recv_buf, sizeof(packet_recv_buf), &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_HRBZH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		
		// 12. ���Ӧ�����ݱ���(��ѯ����)
		ret = Packet_Buf_Transform(packet_recv_buf, &recv_hrbzh, BUF_TO_PACKET, BANK_HRBZH, BANK_TRADE_CODE_QUERYBALANCE, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		
		// 13. �����ѯ����Ӧ��
		Trace_Bank_Package_HRBZH(&recv_hrbzh, "receivce query bank package");

		// 14. �жϴ�����
		ret = Get_Bank_Error_Code(&recv_hrbzh, BANK_HRBZH);
		if (ret)
		{
			writelog(LOG_ERR, "bank_no=[%s]--errcode=[%d]", g_Bank.BankUnit[i].szBankAccountNO, ret);
			return ret;
		}
		
		// 15. �����ѯ�����
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
	
	// �������ú�����
	int req_packet_length = 0;				// �ź��������ܳ���
	int ans_packet_length = 0;				// �ź�Ӧ�����ܳ���
	char prs_next[516] = "";				// �źϼ��ܺ����Կ
	char mac[9] = "";						// �źϼ�����mac��Կ
	char packet_str[516] = "";				// �źϱ������ 
	char packet_send_buf[1892] = "";		// ���ͱ���buf
	char packet_recv_buf[1892] = "";		// ���ܱ���buf
	BANK_YNXH_TRADE_STRUCT_PACKET 	ynxh_req;	// ������
	BANK_YNXH_TRADE_STRUCT_PACKET 	ynxh_ans;	// Ӧ����
	memset(&ynxh_req, 0, sizeof(ynxh_req));
	memset(&ynxh_ans, 0, sizeof(ynxh_ans));

	// ����ũ��
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

	// ����������
	BANK_HRBZH_TRADE_STRUCT_PACKET send_hrbzh;
	BANK_HRBZH_TRADE_STRUCT_PACKET recv_hrbzh;
	memset(&send_hrbzh, 0x00, sizeof(send_hrbzh));
	memset(&recv_hrbzh, 0x00, sizeof(recv_hrbzh));
	
	//�����ϴ����п��������ĸ����У��������б�־�����͸���ͬ������
	//ת��transinfo���ȥ����
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
	
	//�й�����
	if(g_Bank.BankUnit[i].iBankID==BANK_ZGYH)
	{
		//memset(&zgyh_req,0x20,sizeof(zgyh_req));
		//memset(zgyh_req.head.Ret,0x20,sizeof(zgyh_req.head.Ret));					//������; ��0000Ϊ���ɹ�
		memcpy(zgyh_req.head.TranCode,BANK_ZGYH_TRADE_CODE_TRANS,4);			//������; DXRB:ת��,DXRV:����
		//memset(zgyh_req.head.BrnId,0x20,sizeof(zgyh_req.head.BrnId));				//�����; �ո�
		//memset(zgyh_req.head.TmlId,0x20,sizeof(zgyh_req.head.TmlId));				//�ն˺�; �ո�
		//memset(zgyh_req.head.TelId,0x20,sizeof(zgyh_req.head.TelId));				//��Ա��; �ո�
		//memset(zgyh_req.head.Filer1,0x20,sizeof(zgyh_req.head.Filer1));				//Ԥ����;
		zgyh_req.head.Mchno_len=0x08;				//�̶�ֵ; 0x08
		memcpy(zgyh_req.head.Merch_no,BANK_ZGYH_MERCH_NO,8);			//��λ����;  ����
		//memset(zgyh_req.head.Mch_name,0x20,sizeof(zgyh_req.head.Mch_name));			//��λ����;�ո�
		//memset(zgyh_req.head.Errcd,0x20,sizeof(zgyh_req.head.Errcd));				//�������;
		//memset(zgyh_req.head.ErrMsg,0x20,sizeof(zgyh_req.head.ErrMsg));				//������Ϣ;
		sprintf(sSerialno,"%d",serial_no);
		memcpy(zgyh_req.head.LocalNo,sSerialno,strlen(sSerialno));			//������ˮ��
		//memcpy(zgyh_req.head.LocalNo,sSerialno,strlen(sSerialno));					//������ˮ��;
		//memset(zgyh_req.head.BankNo,0x20,sizeof(zgyh_req.head.BankNo));//������ˮ��;
		//memset(zgyh_req.head.Filer2,0x20,sizeof(zgyh_req.head.Filer2));				//Ԥ��;

		memcpy(zgyh_req.GDCAccount,pNode->CardNo,strlen(pNode->CardNo));			//У԰���ʺ�
		memcpy(zgyh_req.BankCard,pNode->BankCardNo,strlen(pNode->BankCardNo));	//���п���
		zgyh_req.CardType='D';				//�����ͣ�C���ÿ�,D��ǿ�

//		memcpy(zgyh_req.TranMoney,pNode->TransMoney,9);		//���׽��
//wenjian add
		sprintf(sMoney,"%013d",atoi(pNode->TransMoney));
		memcpy(zgyh_req.TranMoney,sMoney,sizeof(zgyh_req.TranMoney));	//���׽��
		//memset(zgyh_req.PinBlock,0x20,sizeof(zgyh_req.PinBlock));			//Ԥ��
		//memset(zgyh_req.TpkUdlmk,0x20,sizeof(zgyh_req.TpkUdlmk));			//Ԥ��
		Trace_Bank_Package_ZGYH_R(&zgyh_req,"Send query bank package:�й�����");
		ret=send_to_and_recv_from_bank(BANK_ZGYH,(char*)&zgyh_req,sizeof(zgyh_req),(char*)&zgyh_ans,sizeof(zgyh_ans),&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		Trace_Bank_Package_ZGYH_A(&zgyh_ans,"Receivce query bank package:�й�����");
		if(0!=strncmp(zgyh_ans.head.Ret,"0000",4))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%4.4s],msg=[%s] ",
						zgyh_ans.head.Ret,zgyh_ans.head.ErrMsg);
			memcpy(temp,zgyh_ans.head.Ret,4);
			temp[4]=0;
			switch(atoi(temp))
			{
				case 1:		//���п���ʧ
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
					return	E_TRANS_BANK_RECVERR;
				default:		//����δ֪����
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_BANK_RECVERR;
			}
		}
	}
	//��������
	else if(g_Bank.BankUnit[i].iBankID==BANK_GSYH)
	{
//		memset(&gsyh_req,0x20,sizeof(gsyh_req));
		memcpy(gsyh_req.ZoneNo,BANK_GSYH_ZONE_NO_GZ,4); //�������;����:3602,�麣:2002;
		memcpy(gsyh_req.BusiType,BANK_GSYH_TYPE_SCHOOL,2);//�������ͣ��̶�11
		memcpy(gsyh_req.TranCode,BANK_GSYH_TRADE_CODE_TRANS,2);////��������;1:ת��,2:ȡ��,3:����ѯ
		gsyh_req.TranFlag[0]='0';						//���ױ�־;0:������,1:������
		memcpy(gsyh_req.BankCardNo,pNode->BankCardNo,strlen(pNode->BankCardNo));//���п���;�跽�ʺţ�����ʱΪѧУ�ʺ�			
		//memcpy(gsyh_req.TranMoney,pNode->TransMoney,9);//���׽��;
		sprintf(sMoney,"%010d",atoi(pNode->TransMoney));
		memcpy(gsyh_req.TranMoney,sMoney,sizeof(gsyh_req.TranMoney));	//���׽��
		memcpy(gsyh_req.MoneyType,"001",3);//��������;001:�����
		memcpy(gsyh_req.TranDate,pNode->TradeDate,8); //��������;YYYYMMDD
		memcpy(gsyh_req.TranTime,pNode->TradeTime,6);//����ʱ��;HHMMSS
		gsyh_req.PwdFlag[0]='0';
		gsyh_req.PwdType[0]='0';							
		sprintf(sSerialno,"%d",serial_no);
		memcpy(gsyh_req.LocalSn,sSerialno,strlen(sSerialno));			//������ˮ��
		//memcpy(gsyh_req.LocalDetranSn,"000000",6);		//����ʱ�����ԭת�ʽ�����ˮ��
		//memcpy(gsyh_req.BankSn,"000000",6);			//������ˮ��
		memcpy(gsyh_req.MercAccount,BANK_GSYH_MERCH_NO,5);	//Ȧ��ʱΪ��ɽ��ѧ�̻���,����ʱΪ�̻����̻���
		memcpy(gsyh_req.MercAccountCode,"01",2);		//�����ţ�ָ�̻����ж�������ʺ�ʱ�����ֶ�ָʾ����һ���ʺţ��ȹ̶�Ϊ01;
		memcpy(gsyh_req.GDCAccount,pNode->CardNo,strlen(pNode->CardNo));	//У԰����;
		memcpy(gsyh_req.PosNo,pNode->TerminalId,strlen(pNode->TerminalId));	//Ȧ�����;
		memcpy(gsyh_req.AgentPercent,"000000000",9);		//����ʱ�Ĵ�����ɰٷֱ�
		memcpy(gsyh_req.AgentType,"01",2);			//ҵ������,01:Ȧ��,02:����;
		memset(gsyh_req.Filter,0x20,sizeof(gsyh_req.Filter));				//�ո�λ
		Trace_Bank_Package_GSYH(&gsyh_req,"Send query bank package:��������");
		ret=send_to_and_recv_from_bank(BANK_GSYH,(char*)&gsyh_req,sizeof(gsyh_req),(char*)&gsyh_ans,sizeof(gsyh_ans),&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		Trace_Bank_Package_GSYH(&gsyh_ans,"Receivce query bank package:��������");
		if(0!=strncmp(gsyh_ans.RetCode,"00",2))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s] ",gsyh_ans.RetCode);
			memcpy(temp,gsyh_ans.RetCode,2);
			temp[2]=0;
			switch(atoi(temp))
			{
				case 1:		//���п���ʧ
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
					return	E_TRANS_BANKCARD_LOST;
				case 2:		//���п�״̬����
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
					return	E_TRANS_BANKACC_STATERR;
				case 3:		//���п�����
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
					return	E_TRANS_BANKACC_NOMONEY;
				case 4:		//�����������
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_BANKCARD_PWDERR;
				case 98:		//���д���ʱ
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
					return	E_TRANS_BANK_NOANSWER;
				case 99:		//��������
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_UNKNOW_ERROR;
				default:		//����δ֪����
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_UNKNOW_ERROR;
			}
		}

		//���Ӧ���
		//sprintf(pNode->RetCode,"%d",SUCCEED);
		//memcpy(pNode->Balance,gsyh_ans.TranMoney,sizeof(pNode->Balance));
		//writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%9s]",gsyh_ans.TranMoney);
	}
	else if (BANK_YNXH == g_Bank.BankUnit[i].iBankID)
	{
		// 3. ��Ϸ������ݱ���
		ret = Packet_Buf_Transform(packet_send_buf, &ynxh_req, PACKET_TO_BUF, 
								   BANK_YNXH, BANK_TRADE_CODE_TRANS, pNode, serial_no);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_BANK_NOANSWER;
		}

		// 4. ����������ݱ���
		Trace_Bank_Package_YNXH(&ynxh_req, "send bank transfer package");
			
		// 5. �������ݱ��ĺͽ���Ӧ�����ݱ���
		ret = send_to_and_recv_from_bank(BANK_YNXH, packet_send_buf, atoi(ynxh_req.head.packet_length) + 4, packet_recv_buf, sizeof(packet_recv_buf), &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_YNXH,ret);
			return E_TRANS_BANK_NOANSWER;
		}

		// 6. ���Ӧ�����ݱ���
		ret = Packet_Buf_Transform(packet_recv_buf + 4, &ynxh_ans, BUF_TO_PACKET, BANK_YNXH, BANK_TRADE_CODE_TRANS, pNode, serial_no);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_BANK_NOANSWER;
		}

		// 7. ���Ӧ�����ݱ���
		Trace_Bank_Package_YNXH(&ynxh_ans,"receivce bank transfer package");

		// 8. �жϴ�����
		ret = Get_Bank_Error_Code(&ynxh_ans, BANK_YNXH);
		if (ret)
		{
			writelog(LOG_ERR, "bank_no=[%s]--errcode=[%d]", g_Bank.BankUnit[i].szBankAccountNO, ret);
			return ret;
		}		
	}
	// ����ũ��
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
		//		(1)�����޸�ҵ�����̣�����ѧ������绰�������뻹�ǿ��ţ���ѡ���Ƿ���ǩ������
		//		(2)��Ϊ���е�ԭ��10�������޷������������ɵ绰�������룬����޸���������
		//		(3)�޸ĺ��жϵ绰�������������Ƿ�Ϊ�գ�Ϊ�ղ���ǩ��ֱ�ӽ��ף����
		if(strlen(pNode->BankCardPwd)==0)	//�ж��Ƿ�����绰�������룬�������жϿ��ţ�����ԭ����
		{
			des2src(pNode->BankCardPwd,"000000",6);
			writelog(LOG_ERR,"����Ϊ��:pNode.BankCardNo=[%s],pNode.Reserve1=[%s]",pNode->BankCardNo,pNode->Reserve1);
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
		// 1. ���ǩ������
		ret = Packet_Buf_Transform(packet_send_buf, &send_hrbzh, PACKET_TO_BUF, BANK_HRBZH, BANK_TRADE_CODE_SIGN_IN, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}		

		// 2. ���ǩ������
		Trace_Bank_Package_HRBZH(&send_hrbzh, "send sign in bank package");

		// 3. �������ݱ��ĺͽ���Ӧ�����ݱ���(ǩ������)
		ret = send_to_and_recv_from_bank(BANK_HRBZH, packet_send_buf, atoi(send_hrbzh.hrbzh_head.MsgLen) + sizeof(send_hrbzh.hrbzh_head), packet_recv_buf, sizeof(packet_recv_buf), &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_HRBZH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		
		// 4. ���Ӧ�����ݱ���(ǩ������)
		ret = Packet_Buf_Transform(packet_recv_buf, &recv_hrbzh, BUF_TO_PACKET, BANK_HRBZH, BANK_TRADE_CODE_SIGN_IN, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		
		// 7. ���ǩ������Ӧ��
		Trace_Bank_Package_HRBZH(&recv_hrbzh, "receivce sign in bank package");

		// 8. �жϴ�����
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
		// 9. ���ת�˱���
		ret = Packet_Buf_Transform(packet_send_buf, &send_hrbzh, PACKET_TO_BUF, BANK_HRBZH, BANK_TRADE_CODE_TRANS, pNode, serial_no);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}

		// 10. ���ת�ʱ���
		Trace_Bank_Package_HRBZH(&send_hrbzh, "TTTTTTTTTT send bank transfer package");

		// 11. �������ݱ��ĺͽ���Ӧ�����ݱ���(ת�ʽ���)
		ret = send_to_and_recv_from_bank(BANK_HRBZH, packet_send_buf, atoi(send_hrbzh.hrbzh_head.MsgLen) + sizeof(send_hrbzh.hrbzh_head), packet_recv_buf, sizeof(packet_recv_buf), &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_HRBZH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		
		// 12. ���Ӧ�����ݱ���(ת�ʽ���)
		ret = Packet_Buf_Transform(packet_recv_buf, &recv_hrbzh, BUF_TO_PACKET, BANK_HRBZH, BANK_TRADE_CODE_TRANS, pNode, serial_no);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		
		// 13. ���ת�ʽ���Ӧ��
		Trace_Bank_Package_HRBZH(&recv_hrbzh, "receivce bank transfer package");

		// 14. �жϴ�����
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
	
	// �������ú�����
	int req_packet_length = 0;				// �ź��������ܳ���
	int ans_packet_length = 0;				// �ź�Ӧ�����ܳ���
	char prs_next[516] = "";				// �źϼ��ܺ����Կ
	char mac[9] = "";						// �źϼ�����mac��Կ
	char packet_str[516] = "";				// �źϱ������ 
	char packet_send_buf[1892] = "";		// ���ͱ���buf
	char packet_recv_buf[1892] = "";		// ���ܱ���buf
	BANK_YNXH_TRADE_STRUCT_PACKET 	ynxh_req;	// ������
	BANK_YNXH_TRADE_STRUCT_PACKET 	ynxh_ans;	// Ӧ����
	memset(&ynxh_req, 0, sizeof(ynxh_req));
	memset(&ynxh_ans, 0, sizeof(ynxh_ans));

	// ����ũ��
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

	// ����������
	BANK_HRBZH_TRADE_STRUCT_PACKET send_hrbzh;
	BANK_HRBZH_TRADE_STRUCT_PACKET recv_hrbzh;
	memset(&send_hrbzh, 0x00, sizeof(send_hrbzh));
	memset(&recv_hrbzh, 0x00, sizeof(recv_hrbzh));

	//�����ϴ����п��������ĸ����У��������б�־�����͸���ͬ������
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
	//�й�����
	if(g_Bank.BankUnit[i].iBankID==BANK_ZGYH)
	{
		memset(zgyh_req.head.Ret,0x20,sizeof(zgyh_req.head.Ret));					//������; ��0000Ϊ���ɹ�
		memcpy(zgyh_req.head.TranCode,BANK_ZGYH_TRADE_CODE_DETRANS,4);			//������; DXRB:ת��,DXRV:����
		memset(zgyh_req.head.BrnId,0x20,sizeof(zgyh_req.head.BrnId));				//�����; �ո�
		memset(zgyh_req.head.TmlId,0x20,sizeof(zgyh_req.head.TmlId));				//�ն˺�; �ո�
		memset(zgyh_req.head.TelId,0x20,sizeof(zgyh_req.head.TelId));				//��Ա��; �ո�
		memset(zgyh_req.head.Filer1,0x20,sizeof(zgyh_req.head.Filer1));				//Ԥ����;
		zgyh_req.head.Mchno_len=0x08;				//�̶�ֵ; 0x08
		memcpy(zgyh_req.head.Merch_no,BANK_ZGYH_MERCH_NO,8);			//��λ����;  ����
		memset(zgyh_req.head.Mch_name,0x20,sizeof(zgyh_req.head.Mch_name));			//��λ����;�ո�
		memset(zgyh_req.head.Errcd,0x20,sizeof(zgyh_req.head.Errcd));				//�������;
		memset(zgyh_req.head.ErrMsg,0x20,sizeof(zgyh_req.head.ErrMsg));				//������Ϣ;
		sprintf(zgyh_req.head.LocalNo,"%d",pNode->SendNo);			//������ˮ��;
		memset(zgyh_req.head.BankNo,0x20,sizeof(zgyh_req.head.BankNo));				//������ˮ��;
		memset(zgyh_req.head.Filer2,0x20,sizeof(zgyh_req.head.Filer2));				//Ԥ��;

		memcpy(zgyh_req.GDCAccount,pNode->CardNo,12);			//У԰���ʺ�
		memcpy(zgyh_req.BankCard,pNode->BankCardNo,20);			//���п���
		zgyh_req.CardType='D';				//�����ͣ�C���ÿ�,D��ǿ�
		memcpy(zgyh_req.TranMoney,pNode->TransMoney,9);			//���׽��
		memset(zgyh_req.PinBlock,0x20,sizeof(zgyh_req.PinBlock));			//Ԥ��
		memset(zgyh_req.TpkUdlmk,0x20,sizeof(zgyh_req.TpkUdlmk));			//Ԥ��
		memset(zgyh_req.XykSqh,0x20,sizeof(zgyh_req.XykSqh));		//���ÿ���Ȩ��
		sprintf(zgyh_req.OldLocalNo,"%d",pNode->RecvNo);		//ԭ������ˮ��
		
		//Trace_Bank_Package_ZGYH_R(&zgyh_req,"Send query bank package:�й�����");
		ret=send_to_and_recv_from_bank(BANK_ZGYH,(char*)&zgyh_req,sizeof(zgyh_req),(char*)&zgyh_ans,sizeof(zgyh_ans),&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		//Trace_Bank_Package_ZGYH_A(&zgyh_ans,"Receivce query bank package:�й�����");
		if(0!=strncmp(zgyh_ans.head.Ret,"0000",4))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%4.4s] ",zgyh_ans.head.Ret);
			memcpy(temp,zgyh_ans.head.Ret,4);
			temp[4]=0;
			switch(atoi(temp))
			{
				case 1:		//���п���ʧ
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
					return	E_TRANS_BANKCARD_LOST;
				case 2:		//���п�״̬����
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
					return	E_TRANS_BANKACC_STATERR;
				case 3:		//���п�����
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
					return	E_TRANS_BANKACC_NOMONEY;
				case 4:		//�����������
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_BANKCARD_PWDERR;
				case 98:		//���д���ʱ
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
					return	E_TRANS_BANK_NOANSWER;
				case 99:		//��������
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_UNKNOW_ERROR;
				default:		//����δ֪����
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_UNKNOW_ERROR;
			}
		}
	}
	//��������
	else if(g_Bank.BankUnit[i].iBankID==BANK_GSYH)
	{
		memcpy(gsyh_req.ZoneNo,BANK_GSYH_ZONE_NO_GZ,4); //�������;����:3602,�麣:2002;
		memcpy(gsyh_req.BusiType,BANK_GSYH_TYPE_SCHOOL,2);//�������ͣ��̶�11
		memcpy(gsyh_req.TranCode,BANK_GSYH_TRADE_CODE_DETRANS,2);////��������;1:ת��,2:ȡ��,3:����ѯ
		gsyh_req.TranFlag[0]='0';						//���ױ�־;0:������,1:������
		memcpy(gsyh_req.BankCardNo,pNode->BankCardNo,sizeof(pNode->BankCardNo));//���п���;�跽�ʺţ�����ʱΪѧУ�ʺ�
		memcpy(gsyh_req.TranMoney,pNode->TransMoney,9);//���׽��;
		memcpy(gsyh_req.MoneyType,"001",3);//��������;001:�����
		memcpy(gsyh_req.TranDate,pNode->TradeDate,8); //��������;YYYY-MM-DD
		memcpy(gsyh_req.TranTime,pNode->TradeTime,6);//����ʱ��;HHMMSS
		gsyh_req.PwdFlag[0]='0';
		gsyh_req.PwdType[0]='0';							
		sprintf(gsyh_req.LocalSn,"%d",pNode->SendNo);			//������ˮ��
		sprintf(gsyh_req.LocalDetranSn,"%d",pNode->RecvNo);		//����ʱ�����ԭת�ʽ�����ˮ��
		memcpy(gsyh_req.BankSn,"000000",6);			//������ˮ��
		memcpy(gsyh_req.MercAccount,BANK_GSYH_MERCH_NO,5);	//Ȧ��ʱΪ��ɽ��ѧ�̻���,����ʱΪ�̻����̻���
		memcpy(gsyh_req.MercAccountCode,"01",2);		//�����ţ�ָ�̻����ж�������ʺ�ʱ�����ֶ�ָʾ����һ���ʺţ��ȹ̶�Ϊ01;
		memcpy(gsyh_req.GDCAccount,pNode->CardNo,10);			//У԰����;
		memcpy(gsyh_req.PosNo,pNode->TerminalId,5);				//Ȧ�����;
		memcpy(gsyh_req.AgentPercent,"000000000",9);		//����ʱ�Ĵ�����ɰٷֱ�
		memcpy(gsyh_req.AgentType,"01",2);			//ҵ������,01:Ȧ��,02:����;
		memset(gsyh_req.Filter,0x20,sizeof(gsyh_req.Filter));				//�ո�λ
		Trace_Bank_Package_GSYH(&gsyh_req,"Send query bank package:��������");
		ret=send_to_and_recv_from_bank(BANK_GSYH,(char*)&gsyh_req,sizeof(gsyh_req),(char*)&gsyh_ans,sizeof(gsyh_ans),&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		Trace_Bank_Package_GSYH(&gsyh_ans,"Send query bank package:��������");
		if(0!=strncmp(gsyh_ans.RetCode,"00",2))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s] ",gsyh_ans.RetCode);
			memcpy(temp,gsyh_ans.RetCode,2);
			temp[2]=0;
			switch(atoi(temp))
			{
				case 1:		//���п���ʧ
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
					return	E_TRANS_BANKCARD_LOST;
				case 2:		//���п�״̬����
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
					return	E_TRANS_BANKACC_STATERR;
				case 3:		//���п�����
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
					return	E_TRANS_BANKACC_NOMONEY;
				case 4:		//�����������
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_BANKCARD_PWDERR;
				case 98:		//���д���ʱ
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
					return	E_TRANS_BANK_NOANSWER;
				case 99:		//��������
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_UNKNOW_ERROR;
				default:		//����δ֪����
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_UNKNOW_ERROR;
			}
		}

		//���Ӧ���
		//sprintf(pNode->RetCode,"%d",SUCCEED);
		//memcpy(pNode->Balance,gsyh_ans.TranMoney,sizeof(pNode->Balance));
		//writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%9s]",gsyh_ans.TranMoney);
	}
	else if ((BANK_YNXH == g_Bank.BankUnit[i].iBankID))
	{
		// 3. ��Ϸ������ݱ���
		ret = Packet_Buf_Transform(packet_send_buf, &ynxh_req, PACKET_TO_BUF, 
								   BANK_YNXH, BANK_TRADE_CODE_DETRANS, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_BANK_NOANSWER;
		}

		// 4. ����������ݱ���
		Trace_Bank_Package_YNXH(&ynxh_req, "send detrans bank package");
			
		// 5. �������ݱ��ĺͽ���Ӧ�����ݱ���
		ret = send_to_and_recv_from_bank(BANK_YNXH, packet_send_buf, atoi(ynxh_req.head.packet_length) + 4, packet_recv_buf, ans_packet_length, &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_YNXH,ret);
			return E_TRANS_BANK_NOANSWER;
		}

		// 6. ���Ӧ�����ݱ���
		ret = Packet_Buf_Transform(packet_recv_buf + 4, &ynxh_ans, BUF_TO_PACKET, BANK_YNXH, BANK_TRADE_CODE_DETRANS, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_BANK_NOANSWER;
		}

		// 7. ���Ӧ�����ݱ���
		Trace_Bank_Package_YNXH(&ynxh_ans,"receivce detrans bank package");

		// 8. �жϴ�����
		ret = Get_Bank_Error_Code(&ynxh_ans, BANK_YNXH);
		if (ret)
		{
			writelog(LOG_ERR, "bank_no=[%s]--errcode=[%d]--card_id=[%s]", g_Bank.BankUnit[i].szBankAccountNO, ret, pNode->CardNo);
			return ret;
		}
	}
	// ����ũ��
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
	// �����ź�ʹ��
	int packet_length = 0;
	int packet_head_length = 0;
	char str_packet_length[5] = "";

	des2src(bank_ip,pBank->BankUnit[pBank->cur_bankid].szBankIP);
	bank_port=pBank->BankUnit[pBank->cur_bankid].iBankPort;
	delay_time=pBank->BankUnit[pBank->cur_bankid].iBankTimeout;
	//����signal����ֹ����ģʽ��socket

	alarm(delay_time/1000);
	//��������
	ret=SockNode.hSock.ConnectTcp(bank_ip,bank_port);
	if(!ret)
	{	
		alarm(0);
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],bank_ip[%s],port[%d] ",ret,bank_ip,bank_port);
		return E_TRANS_BANK_NETERR;
	}
	alarm(0);
	//�������ݵ�����
	writelog(LOG_ERR,"Send to Bank--Buf[%s]--Length[%d]", pSend, send_len);
	if (BANK_YNXH == bank_id || BANK_HRBZH == bank_id) 
	{
		// �������� = ���ĳ���(4�ֽ�) + �����ܳ���
		Trace_8583_Package(pSend, send_len, 0, "send msg");
	}
	
	ret = SockNode.hSock.Send(pSend, send_len);
	if (ret < 0)
	{
	      	// ����ʱ���˿������⣬�������ر�
		writelog(LOG_ERR,"Send to bank error,ret = [%d] ",ret);
		return E_TRANS_BANK_NETERR;
	}
	else if (0==ret)
	{
		// ��Ӧ�ó����������
	    writelog(LOG_ERR,"Send to bank error,CTcpSocket.Send should not return this error,error code is[%d]!\n",errno);
	    return	E_TRANS_BANK_NETERR;
	}
	
	writelog(LOG_ERR,"Send to Bank Ret=[%d]", ret);
	system("sleep 1");

	// �����źϷ�����Ϣ
	if (BANK_YNXH == bank_id)
	{
		// ������ź�Ȧ���豸, �հ����Ȳ�ȷ��, �Ƚ�ͷ����46���ֽ�, ��ȡ�������ĳ���
		packet_head_length = 50;
		ret = SockNode.hSock.Recv(pRecv, packet_head_length, delay_time);
		if (ret != packet_head_length)
		{
			writelog(LOG_ERR,"Receive packet head from bank error,ret= [%d]--packet_head_length=[%d]", ret, packet_head_length);
			return	E_TRANS_BANK_NOANSWER;  // ����ʱ�������ʱ
		}

		memcpy(str_packet_length, pRecv, 4);
		packet_length = atoi(str_packet_length);
		
		// ��ȡ�����峤��
		printf("�����峤��	=[%4.4s]\n", str_packet_length);
		ret = SockNode.hSock.Recv(pRecv + packet_head_length, packet_length + 4 - packet_head_length , delay_time);
		if (ret != packet_length + 4 - packet_head_length)
		{
			writelog(LOG_ERR,"Receive packet from bank error,ret= [%d]--packet_length=[%d]", ret, packet_length - 46);
			return	E_TRANS_BANK_NOANSWER;  // ����ʱ�������ʱ
		}

		Trace_8583_Package(pRecv, packet_length + 4, 0, "recv msg");
	}
	else if (BANK_HRBZH == bank_id)
	{
		//sleep(1);
		usleep(TIME_OUT1);
		// ���������Ȧ���豸, �հ����Ȳ�ȷ��, �Ƚ�ͷ����88���ֽ�, ��ȡ�������ĳ���
		packet_head_length = 88;
		ret = SockNode.hSock.Recv(pRecv, packet_head_length, delay_time);
		if (ret != packet_head_length)
		{
			writelog(LOG_ERR,"Receive packet head from bank error,ret= [%d]--packet_head_length=[%d]", ret, packet_head_length);
			return	E_TRANS_BANK_NOANSWER;  // ����ʱ�������ʱ
		}

		memcpy(str_packet_length, pRecv + packet_head_length - 4, 4);	// from 85 to 88, 4 byte packet length
		packet_length = atoi(str_packet_length);
		
		ret = SockNode.hSock.Recv(pRecv + packet_head_length, packet_length, delay_time);
		if (ret != packet_length)
		{
			writelog(LOG_ERR,"Receive packet from bank error,ret= [%d]--packet_length=[%d]", ret, packet_length - 46);
			return	E_TRANS_BANK_NOANSWER;  // ����ʱ�������ʱ
		}

		Trace_8583_Package(pRecv, packet_length + packet_head_length, 0, "recv msg");
	}
	else
	{		
		ret = SockNode.hSock.Recv(pRecv,recv_len,delay_time);
		if (ret != recv_len)
		{
			writelog(LOG_ERR,"Receive from bank error,ret= [%d] ",ret);
			return	E_TRANS_BANK_NOANSWER;  // ����ʱ�������ʱ
		}
		Trace_8583_Package(pRecv, recv_len, 10, "recv msg");
	}
	
	SockNode.hSock.Close();
	return 0;
}

