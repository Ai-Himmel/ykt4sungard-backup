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


//void TRACE_BANK_TRANS(BANK_TRANS_REQUEST *pTransPak, char *stage);
void Trace_Bank_Package_GSYH(BANK_GSYH_TRADE_STRUCT *pTransPak, char *stage);
void Trace_Bank_Package_ZGYH_R(BANK_ZGYH_TRADE_STRUCT_TRANS_REQ *pTransPak, char *stage);
void Trace_Bank_Package_ZGYH_A(BANK_ZGYH_TRADE_STRUCT_TRANS_ANS *pTransPak, char *stage);
int send_to_and_recv_from_bank(int const bank_id,char* pSend, int send_len,char* pRecv,int recv_len,ST_BANK_CONFIG *pBank);
void Trace_Bank_Package_YNXH(BANK_YNXH_TRADE_STRUCT_PACKET *pTransPak, char *stage);
void Trace_Bank_Package_YNNH(BANK_YNNH_TRADE_STRUCT_PACKET *pTransPak, char *stage);
//int Trace_Bank_Package_YNXH(BANK_YNXH_TRADE_STRUCT_PACKET *pTransPak, char *stage);
int Get_Bank_Error_Code(void *pTransPak, int bank_id);

/*================================================================ 
* ������:      Trade_Package_YNXH
* ����1:       [in or out] (BANK_YNXH_TRADE_STRUCT_PACKET *pTransPak)
*			   ��ȡ�������õı�������
* ����2:	   [in or out] (int trade_type) ��������: ��ѯ,����,����,����
* ����3:	   [in] (int packet_flag) ���ױ�ʶ: ��ȡ����(0), ���ñ���(1)
* ����4:       [in] (ST_BANK_CONFIG *pBank) ����ȫ�����ò����ṹ
* ����5:       [in] (INNER_TRANS_REQUEST * pNode) ��������ṹ
* ��������:    �����źϽ��ױ��Ļ��߻�ȡ�źϽ��ױ���
* ����ֵ��     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int Trade_Package_YNXH(BANK_YNXH_TRADE_STRUCT_PACKET *pTransPak, int trade_type, int packet_flag, 
							  ST_BANK_CONFIG *pBank, INNER_TRANS_REQUEST * pNode);

/*================================================================ 
* ������:      Packet_Buf_Transform
* ����1:       [in or out] (char *buf) ת����buf������
* ����2:	   [in or out] (void *packet) ���еı��ĸ�ʽ
* ����3:	   [in] (int change_flag) ѹ���ͽ����־: ����0��ʾѹ��
* 			   (packet to buf), 1��ʾ���(buf to packet)
* ����4:       [in] (int bank_id) �������: �����й�����, ũҵ���е�
* ����5:       [in] (int trade_type) ��������: ��ѯ, ����, ����, ���˵�
* ����6:       [in] (INNER_TRANS_REQUEST * pNode) ���洫��Ľṹ����
* ����7:       [in] (int serial_no) ת�ʻ��߳���ʹ�õ���ˮ��
* ��������:    �Է������ж����ݽ���ѹ�����յ������ж����ݽ��н��
* ����ֵ��     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int Packet_Buf_Transform(char *buf, void *packet, int change_flag, 
							  int bank_id, int trade_type, 
							  INNER_TRANS_REQUEST * pNode, int serial_no); 

void Trace_8583_Package(char *_8583_buf, int _8583_length, int format, char *msg);

int debug=2;

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
	char packet_send_buf[1892] = "";		// �źϷ��ͱ���buf
	char packet_recv_buf[1892] = "";		// �źϽ��ܱ���buf
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

		recv_length = sizeof(ynnh_req.ynnh_head) + sizeof(ynnh_req.bank_account) + sizeof(ynnh_req.bank_pin);
		
		ret = send_to_and_recv_from_bank(BANK_YNNH, packet_send_buf, strlen(packet_send_buf), packet_recv_buf, recv_length, &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_YNXH,ret);
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
	
	BANK_ZGYH_TRADE_STRUCT_TRANS_REQ 	zgyh_req;
	BANK_ZGYH_TRADE_STRUCT_TRANS_ANS 	zgyh_ans;

	BANK_GSYH_TRADE_STRUCT 			gsyh_req;
	BANK_GSYH_TRADE_STRUCT 			gsyh_ans;

	memset(&zgyh_req,0x20,sizeof zgyh_req);
	memset(&zgyh_ans,0x20,sizeof zgyh_ans);

	memset(&gsyh_ans,0x20,sizeof gsyh_ans);
	memset(&gsyh_req,0x20,sizeof gsyh_req);
	
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
	
	BANK_ZGYH_TRADE_STRUCT_DETRANS_REQ 	zgyh_req;
	BANK_ZGYH_TRADE_STRUCT_DETRANS_ANS 	zgyh_ans;

	BANK_GSYH_TRADE_STRUCT 			gsyh_req;
	BANK_GSYH_TRADE_STRUCT 			gsyh_ans;

	memset(&zgyh_req,0x20,sizeof zgyh_req);
	memset(&zgyh_ans,0x20,sizeof zgyh_ans);

	memset(&gsyh_ans,0x20,sizeof gsyh_ans);
	memset(&gsyh_req,0x20,sizeof gsyh_req);

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
	int delay_time=5000;
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
	if (BANK_YNXH == bank_id) 
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
	else
	{
		ret = SockNode.hSock.Recv(pRecv,recv_len,delay_time);
		if (ret != recv_len)
		{
			writelog(LOG_ERR,"Receive from bank error,ret= [%d] ",ret);
			return	E_TRANS_BANK_NOANSWER;  // ����ʱ�������ʱ
		}
	}
	
	SockNode.hSock.Close();
	return 0;
}

void Trace_Bank_Package_GSYH(BANK_GSYH_TRADE_STRUCT *pTransPak, char *stage)
{
	if(debug == 0)
		return;
	printf("----------%s----------\n",stage);
	printf("----------ip=[%s],port=[%d]-----------\n",g_Bank.BankUnit[g_Bank.cur_bankid].szBankIP,g_Bank.BankUnit[g_Bank.cur_bankid].iBankPort);

	if(debug < 2)
		return;
	printf("���״���	=[%2.2s]\n",pTransPak->TranCode);
	printf("���׽��	=[%2.2s]\n",pTransPak->RetCode);
	printf("��������	=[%8.8s]\n",pTransPak->TranDate);
	printf("����ʱ��	=[%6.6s]\n",pTransPak->TranTime);
	printf("У԰���ʺ�	=[%10.10s]\n",pTransPak->GDCAccount);
	printf("���п���	=[%20.20s]\n",pTransPak->BankCardNo);
	printf("�̻��� 		=[%8.8s]\n",pTransPak->MercAccount);
	printf("ת�˽��	=[%9.9s]\n",pTransPak->TranMoney);
	printf("��ǿ����	=[%9.9s]\n",pTransPak->TranMoney);
	printf("У԰����ˮ��	=[%8.8s]\n",pTransPak->LocalSn);
	printf("������ˮ��	=[%20.20s]\n",pTransPak->BankSn);
	printf("�ն��豸��	=[%5.5s]\n",pTransPak->PosNo);
}

void Trace_Bank_Package_ZGYH_R(BANK_ZGYH_TRADE_STRUCT_TRANS_REQ *pTransPak, char *stage)
{
	if(debug == 0)
		return;
	printf("----------%s----------\n",stage);
	printf("----------ip=[%s],port=[%d]-----------\n",g_Bank.BankUnit[g_Bank.cur_bankid].szBankIP,g_Bank.BankUnit[g_Bank.cur_bankid].iBankPort);
	if(debug < 2)
		return;
	printf("���״���	=[%4.4s]\n",pTransPak->head.TranCode);
	printf("���׽��	=[%4.4s]\n",pTransPak->head.Ret);
	//printf("��������	=[%8.8s]\n",pTransPak->head.);
	//printf("����ʱ��	=[%6.6s]\n",pTransPak->TranTime);
	printf("У԰���ʺ�	=[%10.10s]\n",pTransPak->GDCAccount);
	printf("���п���	=[%20.20s]\n",pTransPak->BankCard);
	printf("�̻��� 		=[%8.8s]\n",pTransPak->head.Merch_no);
	printf("ת�˽��	=[%13.13s]\n",pTransPak->TranMoney);
	//printf("��ǿ����	=[%9.9s]\n",pTransPak->TranMoney);
	printf("У԰����ˮ��	=[%20.20s]\n",pTransPak->head.LocalNo);
	printf("������ˮ��	=[%8.8s]\n",pTransPak->head.BankNo);
	printf("�ն��豸��	=[%2.2s]\n",pTransPak->head.TmlId);
}

void Trace_Bank_Package_ZGYH_A(BANK_ZGYH_TRADE_STRUCT_TRANS_ANS *pTransPak, char *stage)
{
	if(debug == 0)
		return;
	printf("----------%s----------\n",stage);
	printf("----------ip=[%s],port=[%d]-----------\n",g_Bank.BankUnit[g_Bank.cur_bankid].szBankIP,g_Bank.BankUnit[g_Bank.cur_bankid].iBankPort);
	if(debug < 2)
		return;
	printf("���״���	=[%4.4s]\n",pTransPak->head.TranCode);
	printf("���׽��	=[%4.4s]\n",pTransPak->head.Ret);
	//printf("��������	=[%8.8s]\n",pTransPak->head.);
	//printf("����ʱ��	=[%6.6s]\n",pTransPak->TranTime);
	printf("У԰���ʺ�	=[%10.10s]\n",pTransPak->GDCAccount);
	printf("���п���	=[%20.20s]\n",pTransPak->BankCard);
	printf("�̻��� 		=[%8.8s]\n",pTransPak->head.Merch_no);
	printf("ת�˽��	=[%9.9s]\n",pTransPak->TranMoney);
	printf("��ǿ����	=[%9.9s]\n",pTransPak->TranMoney);
	printf("У԰����ˮ��	=[%20.20s]\n",pTransPak->head.LocalNo);
	printf("������ˮ��	=[%8.8s]\n",pTransPak->head.BankNo);
	printf("�ն��豸��	=[%2.2s]\n",pTransPak->head.TmlId);

}

void Trace_Bank_Package_YNXH(BANK_YNXH_TRADE_STRUCT_PACKET *pTransPak, char *stage)
{
	if(debug == 0)
		return;
	printf("----------%s----------\n",stage);
	printf("----------ip=[%s],port=[%d]-----------\n",g_Bank.BankUnit[g_Bank.cur_bankid].szBankIP,g_Bank.BankUnit[g_Bank.cur_bankid].iBankPort);
	if(debug < 2)
		return;
	
	printf("����ͷ����	=[%d]\n", pTransPak->head.packet_head_length[0]);
	printf("���׽��	=[%X]\n", pTransPak->head.head_flag[0]);
	printf("�����ܳ���	=[%4.4s]\n", pTransPak->head.packet_length);
	printf("Ŀ��ID	=[%11.11s]\n", pTransPak->head.dest_id);
	printf("ԴID 		=[%11.11s]\n", pTransPak->head.src_id);
	printf("����λ	=[%X:%X:%X]\n", pTransPak->head.reserve_1[0],pTransPak->head.reserve_1[1],pTransPak->head.reserve_1[2]);
	printf("���κ�	=[%X]\n", pTransPak->head.batch_no[0]);
	printf("������Ϣ	=[%8.8s]\n", pTransPak->head.trade_info);
	printf("�û���Ϣ	=[%X]\n", pTransPak->head.user_info[0]);
	printf("�ܾ���	=[%5.5s]\n", pTransPak->head.reject_code);
	printf("��Ϣ����  =[%4.4s]\n", pTransPak->msg_type);
	printf("λͼ  =[%X:%X:%X:%X:%X:%X:%X:%X:%X:%X:%X:%X:%X:%X:%X:%X]\n", pTransPak->bit[0], pTransPak->bit[1], pTransPak->bit[2], pTransPak->bit[3], pTransPak->bit[4], pTransPak->bit[5],pTransPak->bit[6], pTransPak->bit[7], pTransPak->bit[8], pTransPak->bit[9], pTransPak->bit[10], pTransPak->bit[11], pTransPak->bit[12], pTransPak->bit[13], pTransPak->bit[14], pTransPak->bit[15]);
	printf("���ʺ�  =[%21.21s]\n", pTransPak->main_account);
	printf("���״�����  =[%6.6s]\n", pTransPak->trade_deal_code);
	printf("���״���ʱ��  =[%10.10s]\n", pTransPak->trade_deal_time);
	printf("ϵͳ���ٺ�  =[%6.6s]\n", pTransPak->system_id);
	printf("�ܿ������ڵ�ʱ��  =[%6.6s]\n", pTransPak->accept_card_time);
	printf("�ܿ������ڵ�����  =[%4.4s]\n", pTransPak->accept_card_date);
	printf("�̻�����  =[%4.4s]\n", pTransPak->shop_type);
	printf("�������뷽ʽ��  =[%3.3s]\n", pTransPak->service_input_code);
	printf("����������  =[%2.2s]\n", pTransPak->service_terms_code);
	printf("����ڵ����  =[%13.13s]\n", pTransPak->proxy_node_code);
	printf("���ͽڵ����  =[%13.13s]\n", pTransPak->send_node_code);
	printf("�ڶ��ŵ�����  =[%39.39s]\n", pTransPak->second_mag_tune);
	printf("�����ŵ�����  =[%107.107s]\n", pTransPak->third_mag_tune);
	printf("�����ο���  =[%12.12s]\n", pTransPak->check_code);
	printf("�ܿ����ն˱�ʶ��  =[%8.8s]\n", pTransPak->device_phy);
	printf("�ܿ�����ʶ  =[%15.15s]\n", pTransPak->mark);
	printf("�ܿ�����ַ����  =[%40.40s]\n", pTransPak->address);
	printf("��������  =[%515.515s]\n", pTransPak->append_data);
	printf("���׻��Ҵ���  =[%3.3s]\n", pTransPak->trade_money_code);
	printf("���˱�ʶ������  =[%X:%X:%X:%X:%X:%X:%X:%X]\n", pTransPak->personal_mark[0], pTransPak->personal_mark[1],
		pTransPak->personal_mark[2], pTransPak->personal_mark[3], pTransPak->personal_mark[4], pTransPak->personal_mark[5],
		pTransPak->personal_mark[6], pTransPak->personal_mark[7]);
	printf("�Զ�����  =[%33.33s]\n", pTransPak->defalut_area);
	printf("���ܽڵ��ʶ��  =[%13.13s]\n", pTransPak->accept_node_code);
	printf("���ļ�����  =[%X:%X:%X:%X:%X:%X:%X:%X]\n", pTransPak->packet_identity_code[0], pTransPak->packet_identity_code[1],
		pTransPak->packet_identity_code[2], pTransPak->packet_identity_code[3], pTransPak->packet_identity_code[4],
		pTransPak->packet_identity_code[5], pTransPak->packet_identity_code[6], pTransPak->packet_identity_code[7]);
	printf("Ӧ����  =[%2.2s]\n", pTransPak->answser_code);
	printf("ʵ�����  =[%43.43s]\n", pTransPak->cur_balance);
	printf("��������  =[%4.4s]\n", pTransPak->liquidate_date);
	printf("���׽��  =[%12.12s]\n", pTransPak->trade_money);
	printf("ԭʼ����  =[%42.42s]\n", pTransPak->inital_data);
	printf("������Ҵ���  =[%3.3s]\n", pTransPak->liq_cur_code);
	printf("������Ϣ����  =[%3.3s]\n", pTransPak->net_info_code);
	printf("���ӽ�����Ϣ  =[%103.103s]\n", pTransPak->append_trade_info);
	printf("ת�ʱ���  =[%10.10s]\n", pTransPak->transfer_count);
	printf("��ȫ������Ϣ  =[%16.16s]\n", pTransPak->security_info_control);
	printf("���׿���  =[%30.30s]\n", pTransPak->card_id);
	printf("������  =[%12.12s]\n", pTransPak->liq_money);
}

void Trace_Bank_Package_YNNH(BANK_YNNH_TRADE_STRUCT_PACKET *pTransPak, char *stage)
{
	if(debug == 0)
		return;
	printf("----------%s----------\n",stage);
	printf("----------ip=[%s],port=[%d]-----------\n",g_Bank.BankUnit[g_Bank.cur_bankid].szBankIP,g_Bank.BankUnit[g_Bank.cur_bankid].iBankPort);
	if(debug < 2)
		return;
	
	printf("�汾��Ϣ��	=[%2.2s]\n", pTransPak->ynnh_head.bank_version);
	printf("���ݰ���С	=[%5.5]\n", pTransPak->ynnh_head.packet_length);
	printf("���𷽱�ʶ	=[%2.2s]\n", pTransPak->ynnh_head.lanuch_mark);
	printf("�����㷨	=[%1.1s]\n", pTransPak->ynnh_head.algorithm);
	printf("��Կ�ֶ� 	=[%10.10s]\n", pTransPak->ynnh_head.secret_seg);
	printf("MACУ����	=[%8.8s]\n", pTransPak->ynnh_head.mac_check);
	printf("��������	=[%4.4s]\n", pTransPak->ynnh_head.trade_type);
	printf("��������	=[%8.8s]\n", pTransPak->ynnh_head.trade_date);
	printf("����ʱ��	=[%6.6s]\n", pTransPak->ynnh_head.trade_time);
	printf("�����¼��	=[%5.5s]\n", pTransPak->ynnh_head.packet_count);
	printf("��ˮ��	=[%20.20s]\n", pTransPak->ynnh_head.trade_serial);
	printf("�豸��	=[%8.8s]\n", pTransPak->ynnh_head.device_id);
	printf("�ɹ���־	=[%1.1s]\n", pTransPak->ynnh_head.success_flag);
	printf("������	=[%4.4s]\n", pTransPak->ynnh_head.error_code);
	printf("������־	=[%1.1s]\n", pTransPak->ynnh_head.follow_flag);
	printf("�����	=[%5.5s]\n", pTransPak->ynnh_head.packet_id);
	printf("��������	=[%2.2s]\n", pTransPak->ynnh_head.request_type);
	printf("��������ID	=[%8.8s]\n", pTransPak->ynnh_head.channel_id);
	
}

int Packet_Buf_Transform(char *buf, void *packet, int change_flag, 
							  int bank_id, int trade_type, 
							  INNER_TRANS_REQUEST * pNode, int serial_no)
{
	BANK_YNXH_TRADE_STRUCT_PACKET *packet_point = NULL;
	BANK_YNNH_TRADE_STRUCT_PACKET *packet_point2 = NULL;
	
	int _length = 0;						// �䳤����
	int packet_length = 0;					// ÿ�����ĵ����ݳ���
	int buf_length = 0;						// �����ܵ�buf����
	char prs_next[516] = "";				// �źϼ��ܺ����Կ
	char mac[9] = "";						// �źϼ�����mac��Կ
	char packet_str[516] = "";				// �źϱ������ 
	int req_packet_length = 0;				// �ź��������ܳ���
	int ans_packet_length = 0;				// �ź�Ӧ�����ܳ���
	char str_length[6] = "";
	char msg[25] = "";
	double second = 0.0;
	char forward_date[10]="";			    // ����ʱ����ļ�����ȡ��
	int ret = 0;
	
	if (NULL == buf) { return -2; }

	writelog(LOG_ERR,"��������־[%d]--���б�־[%d]--��������[%d]",change_flag, bank_id, trade_type);
	// ������ѹ��������
	if (PACKET_TO_BUF == change_flag)
	{
		// �ź�����
		if (BANK_YNXH == bank_id)
		{		
			packet_point = (BANK_YNXH_TRADE_STRUCT_PACKET *)packet;
			// 1. ����ͷ���������, ��ѯ, ����, ����, ����ͨ��
			packet_point->head.packet_head_length[0] = 46;
			packet_point->head.head_flag[0] = 1;			//bit:10000001
			memcpy(packet_point->head.dest_id, "14097310   ", sizeof(packet_point->head.dest_id) - 1);
			memcpy(packet_point->head.src_id, "00010000   ", sizeof(packet_point->head.dest_id) - 1);	// ����ʱ���ṩ
			memcpy(packet_point->head.reserve_1, "000", sizeof(packet_point->head.reserve_1) - 1);
			packet_point->head.batch_no[0] = 0x30;
			memcpy(packet_point->head.trade_info, "00000000", sizeof(packet_point->head.trade_info) - 1);
			packet_point->head.user_info[0] = 0x30;
			memcpy(packet_point->head.reject_code, "00000", sizeof(packet_point->head.reject_code) - 1);
			sprintf(packet_point->main_account, "%02d", strlen(pNode->BankCardNo));
			memcpy(packet_point->main_account + 2, pNode->BankCardNo, strlen(pNode->BankCardNo));
			strncpy(packet_point->trade_deal_time, pNode->TradeDate + 4, sizeof(pNode->TradeDate) - 4);		// Ȧ�������
			strncpy(packet_point->trade_deal_time + 4, pNode->TradeTime, sizeof(pNode->TradeTime));			// Ȧ���ʱ��
			memcpy(packet_point->accept_card_time, pNode->TradeDate + 4, sizeof(packet_point->accept_card_time) - 1);
			memcpy(packet_point->accept_card_date, pNode->TradeTime, sizeof(pNode->TradeDate) - 4);
			memcpy(packet_point->shop_type, "8220", sizeof(packet_point->shop_type) - 1);
			memcpy(packet_point->service_input_code, "021", sizeof(packet_point->service_input_code) - 1);
			memcpy(packet_point->service_terms_code, "00", sizeof(packet_point->service_terms_code) - 1);
			sprintf(packet_point->proxy_node_code, "%02d", strlen("99990000"));
			memcpy(packet_point->proxy_node_code + 2, "99990000", strlen("99990000")); // �豸ID��
			sprintf(packet_point->send_node_code, "%02d", strlen("99990000"));	// �󳤶�
			memcpy(packet_point->send_node_code + 2, "99990000", strlen("99990000")); 
			sprintf(packet_point->second_mag_tune, "%02d", strlen(pNode->SencodMagTune));	// �󳤶�
			memcpy(packet_point->second_mag_tune + 2, pNode->SencodMagTune, strlen(pNode->SencodMagTune));
			sprintf(packet_point->third_mag_tune, "%03d", strlen(pNode->ThirdMagTune));	// �󳤶�
			memcpy(packet_point->third_mag_tune + 3, pNode->ThirdMagTune, strlen(pNode->ThirdMagTune));
			strncpy(packet_point->check_code, "9999", 4);		
			strncpy(packet_point->check_code + 4, "00", 2);
			sprintf(packet_point->check_code + 6, "%06d", 0);
			memcpy(packet_point->device_phy, "00000000", 8);
			memcpy(packet_point->device_phy + 8 - strlen(pNode->TerminalId), pNode->TerminalId, strlen(pNode->TerminalId));
			memcpy(packet_point->mark, "822010689000001", sizeof(packet_point->mark) - 1);
			memcpy(packet_point->address, "���ϲƴ���ȪУ��", sizeof(packet_point->address) - 1);
			strncpy(prs_next, pNode->Reserve1, strlen(pNode->Reserve1));
			strncpy(prs_next + strlen(pNode->Reserve1), pNode->Reserve2, strlen(pNode->Reserve2));
			strncpy(prs_next + strlen(pNode->Reserve1) + strlen(pNode->Reserve2), pNode->Reserve3, 2);
			sprintf(packet_point->append_data, "%03d", strlen(prs_next));		// 48���ֵ
			memcpy(packet_point->append_data + 3, prs_next, strlen(prs_next));
			memcpy(packet_point->trade_money_code, "156", sizeof(packet_point->trade_money_code) - 1);
			memcpy(packet_point->personal_mark, pNode->BankCardPwd, 8);			// 52���ֵ, �˴�Ϊ��������
			sprintf(packet_point->defalut_area, "%03d", strlen("000002000100"));
			memcpy(packet_point->defalut_area + 3, "000002000100", sizeof(packet_point->defalut_area) - 1);
			memcpy(packet_point->accept_node_code, "1101999999999", sizeof(packet_point->accept_node_code) - 1);
			sprintf(packet_point->system_id, "%06d", 0);				// ϵͳ��ˮ��
			
			// ��ѯ�������
			if (BANK_TRADE_CODE_QUERYBALANCE == trade_type)
			{	
				// 2. ��������������
				memcpy(packet_point->msg_type, BANK_YNXH_TRADE_CODE_QUERYBALANCE, sizeof(packet_point->msg_type) - 1);
				packet_point->bit[0] = 0xE2;
				packet_point->bit[1] = 0x38;
				packet_point->bit[2] = 0x44;
				packet_point->bit[3] = 0x81;
				packet_point->bit[4] = 0xB8;
				packet_point->bit[5] = 0xE1;
				packet_point->bit[6] = 0x90;
				packet_point->bit[7] = 0x10;
				packet_point->bit[8] = 0x00;
				packet_point->bit[9] = 0x00;
				packet_point->bit[10] = 0x00;
				packet_point->bit[11] = 0x00;
				packet_point->bit[12] = 0x10;
				packet_point->bit[13] = 0x00;
				packet_point->bit[14] = 0x00;
				packet_point->bit[15] = 0x01;
				memcpy(packet_point->trade_deal_code, "300000", sizeof(packet_point->trade_deal_code) - 1);
				// ����MACֵ
//				strncpy(packet_str, BANK_YNXH_TRADE_CODE_QUERYBALANCE, 4);
//				strcat(packet_str, SPLIT_VL);
				PACKETSTR(packet_str, BANK_YNXH_TRADE_CODE_QUERYBALANCE, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->main_account + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_time, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->system_id, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->shop_type, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->service_terms_code , SPLIT_VL);
				PACKETSTR(packet_str, packet_point->proxy_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->send_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->device_phy, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->mark, SPLIT_VL);

				Caculate_Session_MAC(pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);				
				printf("ACCOUNT=[%s]--PFIRST=[%s]--PNEXT=[%s]--����ֶ�=[%s]--MAC=[%s]\n", pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);
								writelog(LOG_ERR,"ACCOUNT=[%s]--PFIRST=[%s]--PNEXT=[%s]--����ֶ�=[%s]--MAC=[%s]", pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);
				memcpy(packet_point->packet_identity_code, mac, 8);
				// ��������ĳ���
				req_packet_length = strlen(packet_point->main_account) + strlen(packet_point->proxy_node_code) + strlen(packet_point->send_node_code)
				                    + strlen(packet_point->second_mag_tune) + strlen(packet_point->third_mag_tune) + strlen(packet_point->append_data) 
				                    + strlen(packet_point->defalut_area) + strlen(packet_point->accept_node_code) + 201;
				sprintf(packet_point->head.packet_length, "%04d", req_packet_length);
				
				// ��packet���İ���buf��
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->head.packet_length, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.packet_head_length, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.head_flag, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->head.packet_length, packet_length);
				buf_length += packet_length;
				packet_length = 11;
				memcpy(buf + buf_length, packet_point->head.dest_id, packet_length);
				buf_length += packet_length;
				packet_length = 11;
				memcpy(buf + buf_length, packet_point->head.src_id, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->head.reserve_1, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.batch_no, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->head.trade_info, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.user_info, packet_length);
				buf_length += packet_length;
				packet_length = 5;
				memcpy(buf + buf_length, packet_point->head.reject_code, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->msg_type, packet_length);
				buf_length += packet_length;
				packet_length = 16;
				memcpy(buf + buf_length, packet_point->bit, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->main_account);
				memcpy(buf + buf_length, packet_point->main_account, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->trade_deal_code, packet_length);
				buf_length += packet_length;
				packet_length = 10;
				memcpy(buf + buf_length, packet_point->trade_deal_time, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->system_id, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->accept_card_time, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->accept_card_date, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->shop_type, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->service_input_code, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(buf + buf_length, packet_point->service_terms_code, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->proxy_node_code);
				memcpy(buf + buf_length, packet_point->proxy_node_code, packet_length);
				buf_length += packet_length;
				packet_length =strlen(packet_point->send_node_code);
				memcpy(buf + buf_length, packet_point->send_node_code, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->second_mag_tune);
				memcpy(buf + buf_length, packet_point->second_mag_tune, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->third_mag_tune);
				memcpy(buf + buf_length, packet_point->third_mag_tune, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(buf + buf_length, packet_point->check_code, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->device_phy, packet_length);
				buf_length += packet_length;
				packet_length = 15;
				memcpy(buf + buf_length, packet_point->mark, packet_length);
				buf_length += packet_length;
				packet_length = 40;
				memcpy(buf + buf_length, packet_point->address, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->append_data);
				memcpy(buf + buf_length, packet_point->append_data, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->trade_money_code, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->personal_mark, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->defalut_area);
				memcpy(buf + buf_length, packet_point->defalut_area, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->accept_node_code);
				memcpy(buf + buf_length, packet_point->accept_node_code, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->packet_identity_code, packet_length);
			}
			// ��������
			else if (BANK_TRADE_CODE_TRANS == trade_type)
			{
				// 2. ��������������
				memcpy(packet_point->msg_type, BANK_YNXH_TRADE_CODE_TRANS, sizeof(packet_point->msg_type));
				packet_point->bit[0] = 0xF2;
				packet_point->bit[1] = 0x3A;
				packet_point->bit[2] = 0x44;
				packet_point->bit[3] = 0x81;
				packet_point->bit[4] = 0xB8;
				packet_point->bit[5] = 0xE1;
				packet_point->bit[6] = 0x98;
				packet_point->bit[7] = 0x10;
				packet_point->bit[8] = 0x00;
				packet_point->bit[9] = 0x00;
				packet_point->bit[10] = 0x00;
				packet_point->bit[11] = 0x00;
				packet_point->bit[12] = 0x12;	// ����103��Ľ��׿���
				packet_point->bit[13] = 0x00;
				packet_point->bit[14] = 0x00;
				packet_point->bit[15] = 0x01;
				memcpy(packet_point->trade_deal_code, "400000", sizeof(packet_point->trade_deal_code) - 1);
				mempcpy(packet_point->trade_money, "000000000000", sizeof(packet_point->trade_money) - 1);
				memcpy(packet_point->trade_money + 12 - strlen(pNode->TransMoney), pNode->TransMoney, strlen(pNode->TransMoney));
				sprintf(packet_point->system_id, "%06d", serial_no);				// ϵͳ��ˮ��
				memcpy(packet_point->liquidate_date, pNode->TradeDate + 4, sizeof(pNode->TradeDate) - 4); // MMDD
				sprintf(packet_point->check_code + 6, "%06d", serial_no);				// �ܿ����ն˺ź�4λ + 00 + ϵͳ��ˮ��
				_length = strlen(trim(pNode->CardNo));
				sprintf(packet_point->card_id, "%02d", _length);
				memcpy(packet_point->card_id + 2, pNode->CardNo, _length);
				
				// ����MACֵ
//				strncpy(packet_str, BANK_YNXH_TRADE_CODE_TRANS, 4);
//				strcat(packet_str, SPLIT_VL);
				PACKETSTR(packet_str, BANK_YNXH_TRADE_CODE_TRANS, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->main_account + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_money, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_time, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->system_id, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->liquidate_date, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->shop_type, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->service_terms_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->proxy_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->send_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->device_phy, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->mark, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->card_id + 2, SPLIT_VL);
				
				memcpy(pNode->BankCardPwd, packet_point->personal_mark, sizeof(packet_point->personal_mark));
				Caculate_Session_MAC(pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);
				printf("ACCOUNT=[%s]--PFIRST=[%s]--PNEXT=[%s]--����ֶ�=[%s]--MAC=[%s]\n", pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);
				writelog(LOG_ERR,"ACCOUNT=[%s]--PFIRST=[%s]--PNEXT=[%s]--����ֶ�=[%s]--MAC=[%s]", pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);

				memcpy(packet_point->packet_identity_code, mac, 8);
				// ��������ĺ�Ӧ���ĳ���
				req_packet_length = strlen(packet_point->main_account) + strlen(packet_point->proxy_node_code) + strlen(packet_point->send_node_code)
				                    + strlen(packet_point->second_mag_tune) + strlen(packet_point->third_mag_tune) + strlen(packet_point->append_data) 
				                    + strlen(packet_point->defalut_area) + strlen(packet_point->accept_node_code) + strlen(packet_point->card_id) + 233;
				sprintf(packet_point->head.packet_length, "%04d", req_packet_length);

				// ��packet���İ���buf��
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->head.packet_length, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.packet_head_length, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.head_flag, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->head.packet_length, packet_length);
				buf_length += packet_length;
				packet_length = 11;
				memcpy(buf + buf_length, packet_point->head.dest_id, packet_length);
				buf_length += packet_length;
				packet_length = 11;
				memcpy(buf + buf_length, packet_point->head.src_id, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->head.reserve_1, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.batch_no, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->head.trade_info, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.user_info, packet_length);
				buf_length += packet_length;
				packet_length = 5;
				memcpy(buf + buf_length, packet_point->head.reject_code, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->msg_type, packet_length);
				buf_length += packet_length;
				packet_length = 16;
				memcpy(buf + buf_length, packet_point->bit, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->main_account);
				memcpy(buf + buf_length, packet_point->main_account, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->trade_deal_code, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(buf + buf_length, packet_point->trade_money, packet_length);
				buf_length += packet_length;
				packet_length = 10;
				memcpy(buf + buf_length, packet_point->trade_deal_time, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->system_id, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->accept_card_time, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->accept_card_date, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->liquidate_date, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->shop_type, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->service_input_code, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(buf + buf_length, packet_point->service_terms_code, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->proxy_node_code);
				memcpy(buf + buf_length, packet_point->proxy_node_code, packet_length);
				buf_length += packet_length;
				packet_length =strlen(packet_point->send_node_code);
				memcpy(buf + buf_length, packet_point->send_node_code, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->second_mag_tune);
				memcpy(buf + buf_length, packet_point->second_mag_tune, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->third_mag_tune);
				memcpy(buf + buf_length, packet_point->third_mag_tune, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(buf + buf_length, packet_point->check_code, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->device_phy, packet_length);
				buf_length += packet_length;
				packet_length = 15;
				memcpy(buf + buf_length, packet_point->mark, packet_length);
				buf_length += packet_length;
				packet_length = 40;
				memcpy(buf + buf_length, packet_point->address, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->append_data);
				memcpy(buf + buf_length, packet_point->append_data, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->trade_money_code, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->personal_mark, packet_length);
				buf_length += packet_length;
				packet_length = 16;
				memcpy(buf + buf_length, packet_point->security_info_control, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->defalut_area);
				memcpy(buf + buf_length, packet_point->defalut_area, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->accept_node_code);
				memcpy(buf + buf_length, packet_point->accept_node_code, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->card_id);
				memcpy(buf + buf_length, packet_point->card_id, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->packet_identity_code, packet_length);
			}
			else if (BANK_TRADE_CODE_DETRANS == trade_type)
			{
				// 3. ������������
				memcpy(packet_point->msg_type, BANK_YNXH_TRADE_CODE_DETRANS, sizeof(packet_point->msg_type));
				packet_point->bit[0] = 0xF2;
				packet_point->bit[1] = 0x3A;
				packet_point->bit[2] = 0x44;
				packet_point->bit[3] = 0x81;
				packet_point->bit[4] = 0x88;
				packet_point->bit[5] = 0xE1;
				packet_point->bit[6] = 0x80;
				packet_point->bit[7] = 0x10;
				packet_point->bit[8] = 0x00;
				packet_point->bit[9] = 0x00;
				packet_point->bit[10] = 0x00;
				packet_point->bit[11] = 0x40;
				packet_point->bit[12] = 0x12;			// ����103��
				packet_point->bit[13] = 0x00;
				packet_point->bit[14] = 0x00;
				packet_point->bit[15] = 0x01;
				getsysdate(pNode->BankDate);
				getsystime(pNode->BankTime);
				memcpy(packet_point->trade_deal_code, "400000", sizeof(packet_point->trade_deal_code) - 1);
				strncpy(packet_point->trade_deal_time, pNode->BankDate + 4, sizeof(pNode->BankDate) - 4);		// ��ǰ��������(MMDD)	
				strncpy(packet_point->trade_deal_time + 4, pNode->BankTime, sizeof(pNode->TradeTime));			// ��ǰ����ʱ��(HHMMSS)
				_length = strlen(trim(pNode->TransMoney));
				sprintf(pNode->TransMoney, "%d", atoi(pNode->TransMoney) * 100);
				writelog(LOG_INFO,"TransMoney=[%s], Length=[%d]", pNode->TransMoney, _length);
				memcpy(packet_point->trade_money, "000000000000", sizeof(packet_point->trade_money) - 1);		// �ź�12λ, һ��ͨ9λ			
				memcpy(packet_point->trade_money + 12 - strlen(pNode->TransMoney), pNode->TransMoney, strlen(pNode->TransMoney));
				sprintf(packet_point->system_id, "%06d", pNode->RecvNo);				// ������ˮ��
				memcpy(packet_point->liquidate_date, pNode->TradeDate + 4, sizeof(pNode->TradeDate) - 4); // MMDD, ����ʱ��(��Ҫ������ˮ�Ľ���ʱ��)
				sprintf(packet_point->check_code + 6, "%06d", pNode->RecvNo);				// �ܿ����ն˺ź�4λ + 00 + ϵͳ��ˮ��
				memcpy(packet_point->inital_data, BANK_YNXH_TRADE_CODE_TRANS, 4);
				memcpy(packet_point->inital_data + 4, packet_point->system_id, 6);			// ԭʼ��¼: ������ˮ�� + ��������ʱ�� + ����ԭʼ����ڵ� + ����ԭʼ���ͽڵ�
				memcpy(packet_point->inital_data + 10, pNode->TradeDate + 4, 4);			// pNode->TradeDate + 4
				memcpy(packet_point->inital_data + 14, pNode->TradeTime, 6);				// pNode->TradeTime
				memcpy(packet_point->inital_data + 20, "0000000000000000000000", 22);
				memcpy(packet_point->inital_data + 20 + 11 - strlen(packet_point->proxy_node_code + 2), packet_point->proxy_node_code + 2, strlen(packet_point->proxy_node_code + 2));
				memcpy(packet_point->inital_data + 31 + 11 - strlen(packet_point->send_node_code + 2), packet_point->send_node_code + 2, strlen(packet_point->send_node_code + 2));
				_length = strlen(trim(pNode->CardNo));
				sprintf(packet_point->card_id, "%02d", _length);
				memcpy(packet_point->card_id + 2, pNode->CardNo, _length);
				
				// ����MACֵ
//				strncpy(packet_str, BANK_YNXH_TRADE_CODE_DETRANS, 4);
//				strcat(packet_str, SPLIT_VL);
				PACKETSTR(packet_str, BANK_YNXH_TRADE_CODE_DETRANS, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->main_account + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_money, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_time, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->system_id, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->liquidate_date, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->shop_type, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->service_terms_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->proxy_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->send_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->device_phy, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->mark, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->inital_data, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->card_id + 2, SPLIT_VL);
		
				Caculate_String_MAC(packet_str, prs_next, mac);	// prs_next��Ϊ��������
				printf("ACCOUNT=[%s]--PFIRST=[%s]--PNEXT=[%s]--����ֶ�=[%s]--MAC=[%s]\n", pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);
				writelog(LOG_ERR,"ACCOUNT=[%s]--PFIRST=[%s]--PNEXT=[%s]--����ֶ�=[%s]--MAC=[%s]", pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);
				memcpy(packet_point->packet_identity_code, mac, 8);
				sprintf(packet_point->append_data, "%03d", strlen(prs_next));
				memcpy(packet_point->append_data + 3, prs_next, strlen(prs_next));

				// ��������ĺ�Ӧ���ĳ���
				req_packet_length = strlen(packet_point->main_account) + strlen(packet_point->proxy_node_code) + strlen(packet_point->send_node_code)
				                    + strlen(packet_point->append_data) + strlen(packet_point->defalut_area) + strlen(packet_point->accept_node_code) 
				                    + strlen(packet_point->card_id) + 251;
				sprintf(packet_point->head.packet_length, "%04d", req_packet_length);

				// ��packet���İ���buf��
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->head.packet_length, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.packet_head_length, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.head_flag, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->head.packet_length, packet_length);
				buf_length += packet_length;
				packet_length = 11;
				memcpy(buf + buf_length, packet_point->head.dest_id, packet_length);
				buf_length += packet_length;
				packet_length = 11;
				memcpy(buf + buf_length, packet_point->head.src_id, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->head.reserve_1, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.batch_no, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->head.trade_info, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.user_info, packet_length);
				buf_length += packet_length;
				packet_length = 5;
				memcpy(buf + buf_length, packet_point->head.reject_code, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->msg_type, packet_length);
				buf_length += packet_length;
				packet_length = 16;
				memcpy(buf + buf_length, packet_point->bit, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->main_account);
				memcpy(buf + buf_length, packet_point->main_account, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->trade_deal_code, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(buf + buf_length, packet_point->trade_money, packet_length);
				buf_length += packet_length;
				packet_length = 10;
				memcpy(buf + buf_length, packet_point->trade_deal_time, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->system_id, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->accept_card_time, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->accept_card_date, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->liquidate_date, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->shop_type, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->service_input_code, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(buf + buf_length, packet_point->service_terms_code, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->proxy_node_code);
				memcpy(buf + buf_length, packet_point->proxy_node_code, packet_length);
				buf_length += packet_length;
				packet_length =strlen(packet_point->send_node_code);
				memcpy(buf + buf_length, packet_point->send_node_code, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(buf + buf_length, packet_point->check_code, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->device_phy, packet_length);
				buf_length += packet_length;
				packet_length = 15;
				memcpy(buf + buf_length, packet_point->mark, packet_length);
				buf_length += packet_length;
				packet_length = 40;
				memcpy(buf + buf_length, packet_point->address, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->append_data);
				memcpy(buf + buf_length, packet_point->append_data, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->trade_money_code, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->defalut_area);
				memcpy(buf + buf_length, packet_point->defalut_area, packet_length);
				buf_length += packet_length;
				packet_length = 42;
				memcpy(buf + buf_length, packet_point->inital_data, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->accept_node_code);
				memcpy(buf + buf_length, packet_point->accept_node_code, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->card_id);
				memcpy(buf + buf_length, packet_point->card_id, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->packet_identity_code, packet_length);
			}
			else if (BANK_TRADE_CODE_COMPARE == trade_type)
			{
				// 4. ���˱�������
				memcpy(packet_point->msg_type, BANK_YNXH_TRADE_CODE_COMPARE, sizeof(packet_point->msg_type));
				packet_point->bit[0] = 0x82;
				packet_point->bit[1] = 0x22;
				packet_point->bit[2] = 0x40;
				packet_point->bit[3] = 0x01;
				packet_point->bit[4] = 0x88;
				packet_point->bit[5] = 0xE1;
				packet_point->bit[6] = 0x40;
				packet_point->bit[7] = 0x00;
				packet_point->bit[8] = 0x04;
				packet_point->bit[9] = 0x00;
				packet_point->bit[10] = 0x00;
				packet_point->bit[11] = 0x00;
				packet_point->bit[12] = 0x10;
				packet_point->bit[13] = 0x00;
				packet_point->bit[14] = 0x00;
				packet_point->bit[15] = 0x01;
				getsysdate(pNode->BankDate);
				getsystime(pNode->BankTime);
				strncpy(packet_point->trade_deal_time, pNode->BankDate + 4, sizeof(pNode->BankDate) - 4);		// ��ǰ��������(MMDD)	
				strncpy(packet_point->trade_deal_time + 4, pNode->BankTime, sizeof(pNode->TradeTime));	
				sprintf(packet_point->system_id, "%06d", 0);
				ret = datetime2second(pNode->BankDate, "YYYYMMDD", &second);
				if (ret)
				{
					writelog(LOG_ERR,"datetime2second error,errcode=[%d]",ret);
					return ret;
				}

				second = second - 24 * 60 * 60;
				ret = second2datetime(second, forward_date, "YYYYMMDD");
				if(ret)
				{
					writelog(LOG_ERR,"second2datetime error,errcode=[%d]",ret);
					return 	ret;
				}
				memcpy(packet_point->liquidate_date, forward_date + 4, sizeof(pNode->BankDate) - 4);	// ��������, ���ն���
				sprintf(packet_point->check_code + 6, "%06d", 0);		// ����û����ˮ��
				memcpy(packet_point->liq_cur_code, "156", 3);
				memcpy(packet_point->net_info_code, "272", 3);
				
				// ����MACֵ
//				strncpy(packet_str, BANK_YNXH_TRADE_CODE_COMPARE, 4);
//				strcat(packet_str, SPLIT_VL);
				PACKETSTR(packet_str, BANK_YNXH_TRADE_CODE_COMPARE, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_time, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->system_id, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->liquidate_date, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->shop_type, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->proxy_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->send_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->device_phy, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->mark, SPLIT_VL);
		
				Caculate_String_MAC(packet_str, prs_next, mac);	// prs_next��Ϊ��������
				printf("ACCOUNT=[%s]--PFIRST=[%s]--PNEXT=[%s]--����ֶ�=[%s]--MAC=[%s]\n", pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);
				writelog(LOG_ERR,"ACCOUNT=[%s]--PFIRST=[%s]--PNEXT=[%s]--����ֶ�=[%s]--MAC=[%s]", pNode->BankCardNo, pNode->BankCardPwd, prs_next, packet_str, mac);
				memcpy(packet_point->packet_identity_code, mac, 8);
				sprintf(packet_point->append_data, "%03d", strlen(prs_next));
				memcpy(packet_point->append_data + 3, prs_next, strlen(prs_next));

				// ��������ĺ�Ӧ���ĳ���
				req_packet_length = strlen(packet_point->proxy_node_code) + strlen(packet_point->send_node_code)
				                    + strlen(packet_point->append_data) + strlen(packet_point->accept_node_code) 
				                    + 179;
				sprintf(packet_point->head.packet_length, "%04d", req_packet_length);

				// ��packet���İ���buf��
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->head.packet_length, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.packet_head_length, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.head_flag, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->head.packet_length, packet_length);
				buf_length += packet_length;
				packet_length = 11;
				memcpy(buf + buf_length, packet_point->head.dest_id, packet_length);
				buf_length += packet_length;
				packet_length = 11;
				memcpy(buf + buf_length, packet_point->head.src_id, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->head.reserve_1, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.batch_no, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->head.trade_info, packet_length);
				buf_length += packet_length;
				packet_length = 1;
				memcpy(buf + buf_length, packet_point->head.user_info, packet_length);
				buf_length += packet_length;
				packet_length = 5;
				memcpy(buf + buf_length, packet_point->head.reject_code, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->msg_type, packet_length);
				buf_length += packet_length;
				packet_length = 16;
				memcpy(buf + buf_length, packet_point->bit, packet_length);
				buf_length += packet_length;
				packet_length = 10;
				memcpy(buf + buf_length, packet_point->trade_deal_time, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(buf + buf_length, packet_point->system_id, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->liquidate_date, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(buf + buf_length, packet_point->shop_type, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->proxy_node_code);
				memcpy(buf + buf_length, packet_point->proxy_node_code, packet_length);
				buf_length += packet_length;
				packet_length =strlen(packet_point->send_node_code);
				memcpy(buf + buf_length, packet_point->send_node_code, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(buf + buf_length, packet_point->check_code, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->device_phy, packet_length);
				buf_length += packet_length;
				packet_length = 15;
				memcpy(buf + buf_length, packet_point->mark, packet_length);
				buf_length += packet_length;
				packet_length = 40;
				memcpy(buf + buf_length, packet_point->address, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->append_data);
				memcpy(buf + buf_length, packet_point->append_data, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->liq_cur_code, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(buf + buf_length, packet_point->net_info_code, packet_length);
				buf_length += packet_length;
				packet_length = strlen(packet_point->accept_node_code);
				memcpy(buf + buf_length, packet_point->accept_node_code, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(buf + buf_length, packet_point->packet_identity_code, packet_length);
			}
			else 
			{
				NULL;
			}
		}
		// ����ũҵ����
		else if (BANK_YNNH == bank_id)
		{
			// ��ѯ���, ���ð�ͷ
			packet_point2 = (BANK_YNNH_TRADE_STRUCT_PACKET *)packet;
			memcpy(packet_point2->ynnh_head.bank_version, "01", sizeof(packet_point2->ynnh_head.bank_version));
			memcpy(packet_point2->ynnh_head.lanuch_mark, "03", sizeof(packet_point2->ynnh_head.lanuch_mark));
			memcpy(packet_point2->ynnh_head.algorithm, "1", sizeof(packet_point2->ynnh_head.algorithm));
			memset(packet_point2->ynnh_head.secret_seg, 0x20, sizeof(packet_point2->ynnh_head.secret_seg));
			memset(packet_point2->ynnh_head.mac_check, 0x20, sizeof(packet_point2->ynnh_head.mac_check));
			memcpy(packet_point2->ynnh_head.trade_type, "9529", sizeof(packet_point2->ynnh_head.trade_type));
			memcpy(packet_point2->ynnh_head.trade_date, pNode->TradeDate, sizeof(packet_point2->ynnh_head.trade_date));
			memcpy(packet_point2->ynnh_head.trade_time, pNode->TradeTime, sizeof(packet_point2->ynnh_head.trade_time));
			memset(packet_point2->ynnh_head.packet_count, 0x20, sizeof(packet_point2->ynnh_head.packet_count));
			memset(packet_point2->ynnh_head.trade_serial, 0x20, sizeof(packet_point2->ynnh_head.trade_serial));
			memset(packet_point2->ynnh_head.device_id, 0x20, sizeof(packet_point2->ynnh_head.device_id));
			memcpy(packet_point2->ynnh_head.device_id, pNode->TerminalId, strlen(pNode->TerminalId));
			memset(packet_point2->ynnh_head.success_flag, 0x20, sizeof(packet_point2->ynnh_head.success_flag));
			memcpy(packet_point2->ynnh_head.error_code, "0000", sizeof(packet_point2->ynnh_head.error_code));
			memcpy(packet_point2->ynnh_head.follow_flag, "0", sizeof(packet_point2->ynnh_head.follow_flag));
			memset(packet_point2->ynnh_head.packet_id, 0x20, sizeof(packet_point2->ynnh_head.packet_id));
			memcpy(packet_point2->ynnh_head.request_type, "01", sizeof(packet_point2->ynnh_head.request_type));
			memcpy(packet_point2->ynnh_head.channel_id, "10000311", sizeof(packet_point2->ynnh_head.channel_id));
			
			if (BANK_TRADE_CODE_QUERYBALANCE == trade_type)
			{
				memcpy(packet_point2->bank_account, pNode->BankCardNo, sizeof(packet_point2->bank_account));
				memcpy(packet_point2->bank_pin, pNode->BankCardPwd, sizeof(packet_point2->bank_pin));
				// ������ĳ���
				req_packet_length = sizeof(packet_point2->ynnh_head) + sizeof(packet_point2->bank_account) + sizeof(packet_point2->bank_pin);

				memset(packet_point2->ynnh_head.packet_length, 0x20, sizeof(packet_point2->ynnh_head.packet_length));
				sprintf(str_length, "%d", req_packet_length);
				memcpy(packet_point2->ynnh_head.packet_length, str_length, strlen(str_length));

				// ѹ���ͷ����
				_length = sizeof(packet_point2->ynnh_head);
				memcpy(buf + buf_length, &(packet_point2->ynnh_head), _length);
				/*
				_length = sizeof(packet_point2->ynnh_head.bank_version);
				memcpy(buf + buf_length, packet_point2->ynnh_head.bank_version, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->ynnh_head.packet_length);
				memcpy(buf + buf_length, packet_point2->ynnh_head.packet_length, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->ynnh_head.lanuch_mark);
				memcpy(buf + buf_length, packet_point2->ynnh_head.lanuch_mark, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->ynnh_head.algorithm);
				memcpy(buf + buf_length, packet_point2->ynnh_head.algorithm, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->ynnh_head.secret_seg);
				memcpy(buf + buf_length, packet_point2->ynnh_head.secret_seg, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->ynnh_head.mac_check);
				memcpy(buf + buf_length, packet_point2->ynnh_head.mac_check, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->ynnh_head.trade_type);
				memcpy(buf + buf_length, packet_point2->ynnh_head.trade_type, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->ynnh_head.trade_date);
				memcpy(buf + buf_length, packet_point2->ynnh_head.trade_date, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->ynnh_head.trade_time);
				memcpy(buf + buf_length, packet_point2->ynnh_head.trade_time, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->ynnh_head.packet_count);
				memcpy(buf + buf_length, packet_point2->ynnh_head.packet_count, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->ynnh_head.trade_serial);
				memcpy(buf + buf_length, packet_point2->ynnh_head.trade_serial, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->ynnh_head.device_id);
				memcpy(buf + buf_length, packet_point2->ynnh_head.device_id, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->ynnh_head.success_flag);
				memcpy(buf + buf_length, packet_point2->ynnh_head.success_flag, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->ynnh_head.error_code);
				memcpy(buf + buf_length, packet_point2->ynnh_head.error_code, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->ynnh_head.follow_flag);
				memcpy(buf + buf_length, packet_point2->ynnh_head.follow_flag, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->ynnh_head.packet_id);
				memcpy(buf + buf_length, packet_point2->ynnh_head.packet_id, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->ynnh_head.request_type);
				memcpy(buf + buf_length, packet_point2->ynnh_head.request_type, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->ynnh_head.channel_id);
				memcpy(buf + buf_length, packet_point2->ynnh_head.channel_id, _length);
				*/
				// ѹ���������
				buf_length += _length;
				_length = sizeof(packet_point2->bank_account);
				memcpy(buf + buf_length, packet_point2->bank_account, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->bank_pin);
				memcpy(buf + buf_length, packet_point2->bank_pin, _length);
			}
			// ת��
			else if (BANK_TRADE_CODE_TRANS == trade_type)
			{
			
			}
			else
			{
				NULL;
			}
			
			return 0;
		}
		else
		{
			return 0;
		}
	}
	// �����������������
	else if (BUF_TO_PACKET == change_flag)
	{
		// �ź�����
		if (BANK_YNXH == bank_id)
		{
			packet_point = (BANK_YNXH_TRADE_STRUCT_PACKET *)packet;
			buf_length = 0;
			packet_length = 1;
			memcpy(packet_point->head.packet_head_length, buf + buf_length, packet_length);
			buf_length += packet_length;
			packet_length = 1;
			memcpy(packet_point->head.head_flag, buf + buf_length, packet_length);
			buf_length += packet_length;
			packet_length = 4;
			memcpy(packet_point->head.packet_length, buf + buf_length, packet_length);
			buf_length += packet_length;
			packet_length = 11;
			memcpy(packet_point->head.dest_id, buf + buf_length, packet_length);			// buf + 6
			buf_length += packet_length;
			packet_length = 11;
			memcpy(packet_point->head.src_id, buf + buf_length, packet_length);			// buf + 17
			buf_length += packet_length;
			packet_length = 3;
			memcpy(packet_point->head.reserve_1, buf + buf_length, packet_length);
			buf_length += packet_length;
			packet_length = 1;
			memcpy(packet_point->head.batch_no, buf + buf_length, packet_length);
			buf_length += packet_length;
			packet_length = 8;
			memcpy(packet_point->head.trade_info, buf + buf_length, packet_length);
			buf_length += packet_length;
			packet_length = 1;
			memcpy(packet_point->head.user_info, buf + buf_length, packet_length);
			buf_length += packet_length;
			packet_length = 5;
			memcpy(packet_point->head.reject_code, buf + buf_length, packet_length);
			buf_length += packet_length;
			packet_length = 4;
			memcpy(packet_point->msg_type, buf + buf_length, packet_length);
			buf_length += packet_length;
			packet_length = 16;
			memcpy(packet_point->bit, buf + buf_length, packet_length);
			buf_length += packet_length;
			// ��ѯ���Ӧ��
			if (BANK_TRADE_CODE_QUERYBALANCE == trade_type)
			{
				// ��Ҫͨ��λͼ�����
				if ((unsigned char)packet_point->bit[0] != 0xE2)
				{
					writelog(LOG_ERR,"error byte0--[%d]\n", packet_point->bit[0]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[1] != 0x38)
				{
					writelog(LOG_ERR,"error byte1--[%d]\n", packet_point->bit[1]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[2] != 0x44)
				{
					writelog(LOG_ERR,"error byte2--[%d]\n", packet_point->bit[2]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[3] != 0x81)
				{
					writelog(LOG_ERR,"error byte3--[%d]\n", packet_point->bit[3]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[4] != 0x8A)
				{
					writelog(LOG_ERR,"error byte4--[%d]\n", packet_point->bit[4]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[5] != 0xE1)
				{
					writelog(LOG_ERR,"error byte5--[%d]\n", packet_point->bit[5]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[6] != 0x84)
				{
					writelog(LOG_ERR,"error byte6--[%d]\n", packet_point->bit[6]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[7] != 0x10)
				{
					writelog(LOG_ERR,"error byte7--[%d]\n", packet_point->bit[7]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[8] != 0x00)
				{
					writelog(LOG_ERR,"error byte8--[%d]\n", packet_point->bit[8]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[9] != 0x00)
				{
					writelog(LOG_ERR,"error byte9--[%d]\n", packet_point->bit[9]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[10] != 0x00)
				{
					writelog(LOG_ERR,"error byte10--[%d]\n", packet_point->bit[10]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[11] != 0x00)
				{
					writelog(LOG_ERR,"error byte11--[%d]\n", packet_point->bit[11]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[12] != 0x10)		
				{
					writelog(LOG_ERR,"error byte12--[%d]\n", packet_point->bit[12]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[13] != 0x00)
				{
					writelog(LOG_ERR,"error byte13--[%d]\n", packet_point->bit[13]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[14] != 0x00)
				{
					writelog(LOG_ERR,"error byte14--[%d]\n", packet_point->bit[14]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[15] != 0x01)
				{
					writelog(LOG_ERR,"error byte15--[%d]\n", packet_point->bit[15]);
					return E_TRANS_BANK_RECVERR;
				}

				memcpy(str_length, buf + 66, 2);	// ���ֶεĳ���
				printf("main_account head length[%d]\n", atoi(str_length));
				memcpy(packet_point->main_account, buf + 66, atoi(str_length) + 2);
				_length = strlen(packet_point->main_account);
				memcpy(packet_point->trade_deal_code, buf + 66 + _length, 6);
				memcpy(packet_point->trade_deal_time, buf + 72 + _length, 10);
				memcpy(packet_point->system_id, buf + 82 + _length, 6);
				memcpy(packet_point->accept_card_time, buf + 88 + _length, 6);
				memcpy(packet_point->accept_card_date, buf + 94 + _length, 4);
				memcpy(packet_point->shop_type, buf + 98 + _length, 4);
				memcpy(packet_point->service_input_code, buf + 102 + _length, 3);
				memcpy(packet_point->service_terms_code, buf + 105 + _length, 2);
				memcpy(str_length, buf + 107 + _length, 2);	// ���ֶεĳ���
				printf("proxy_node_code head length[%d]\n", atoi(str_length));
				memcpy(packet_point->proxy_node_code, buf + 107 + _length, atoi(str_length) + 2);
				_length += strlen(packet_point->proxy_node_code);
				memcpy(str_length, buf + 107 + _length, 2);	// ���ֶεĳ���
				printf("send_node_code head length[%d]\n", atoi(str_length));
				memcpy(packet_point->send_node_code, buf + 107 + _length, atoi(str_length) + 2);
				_length += strlen(packet_point->send_node_code);
				memcpy(packet_point->check_code, buf + 107 + _length, 12);
				memcpy(packet_point->answser_code, buf + 119 + _length, 2);
				memcpy(packet_point->device_phy, buf + 121 + _length, 8);
				memcpy(packet_point->mark, buf + 129 + _length, 15);
				memcpy(packet_point->address, buf + 144 + _length, 40);
				memcpy(str_length, buf + 184 + _length, 3);	// ���ֶεĳ���
				printf("append_data head length[%d]\n", atoi(str_length));
				memcpy(packet_point->append_data, buf + 184 + _length, atoi(str_length) + 3);
				_length += strlen(packet_point->append_data);
				memcpy(packet_point->trade_money_code, buf + 184 + _length, 3);
//				memcpy(str_length, buf + 187 + _length, 3);	// ���ֶεĳ���
//				printf("cur_balance length[%d]\n", atoi(str_length));
				memcpy(packet_point->cur_balance, buf + 187 + _length, 43);
				memcpy(str_length, buf + 230 + _length, 3);	// ���ֶεĳ���
				printf("defalult_area head length[%d]\n", atoi(str_length));
				memcpy(packet_point->defalut_area, buf + 230 + _length, atoi(str_length) + 3);
				_length += strlen(packet_point->defalut_area);
				memset(str_length, 0, sizeof(str_length));
				memcpy(str_length, buf + 230 + _length, 2);	// ���ֶεĳ���
				printf("accpet_node_code head length[%d]\n", atoi(str_length));
				memcpy(packet_point->accept_node_code, buf + 230 + _length, atoi(str_length) + 2);
				_length += strlen(packet_point->accept_node_code);
				memcpy(packet_point->packet_identity_code, buf + 230 + _length, 8);

				Trace_Bank_Package_YNXH(packet_point, "receivce query bank package");		// ������
				// ��ȡӦ���, �ж�MACֵ
				memset(packet_str, 0, sizeof(packet_str));
	//			strncpy(packet_str, BANK_YNXH_TRADE_CODE_ANS_QUERYBALANCE, 4);
	//			strcat(packet_str, SPLIT_VL);
				PACKETSTR(packet_str, BANK_YNXH_TRADE_CODE_ANS_QUERYBALANCE, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->main_account + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_time, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->system_id, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->shop_type, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->service_terms_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->proxy_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->send_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->answser_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->device_phy, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->mark, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->cur_balance, SPLIT_VL);
				
				Caculate_String_MAC(packet_str, prs_next, mac);
				printf("����ֶ� =[%s]--�����ֶ� =[%s]\n", packet_str, prs_next);
				if (0 != strncmp(packet_point->packet_identity_code, mac, 8))
				{
					writelog(LOG_INFO,"MAC=[%8s]--packet_identity_code=[%8s]", mac, packet_point->packet_identity_code);
					return E_TRANS_BANK_RECVERR;
				}
				
				sprintf(packet_point->append_data, "%03d", strlen(prs_next));
				memcpy(packet_point->append_data + 3, prs_next, strlen(prs_next));
			}
			// ����Ӧ��
			else if (BANK_TRADE_CODE_TRANS == trade_type)
			{
				// ��Ҫͨ��λͼ�����
				if ((unsigned char)packet_point->bit[0] != 0xF2)
				{
					writelog(LOG_ERR,"error byte0--[%d]", packet_point->bit[0]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[1] != 0x38)
				{
					writelog(LOG_ERR,"error byte1--[%d]", packet_point->bit[1]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[2] != 0x44)
				{
					writelog(LOG_ERR,"error byte2--[%d]", packet_point->bit[2]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[3] != 0x81)
				{
					writelog(LOG_ERR,"error byte3--[%d]", packet_point->bit[3]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[4] != 0x8A)
				{
					writelog(LOG_ERR,"error byte4--[%d]", packet_point->bit[4]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[5] != 0xE1)
				{
					writelog(LOG_ERR,"error byte5--[%d]", packet_point->bit[5]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[6] != 0x80)
				{
					writelog(LOG_ERR,"error byte6--[%d]", packet_point->bit[6]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[7] != 0x10)
				{
					writelog(LOG_ERR,"error byte7--[%d]", packet_point->bit[7]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[8] != 0x00)
				{
					writelog(LOG_ERR,"error byte8--[%d]", packet_point->bit[8]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[9] != 0x00)
				{
					writelog(LOG_ERR,"error byte9--[%d]", packet_point->bit[9]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[10] != 0x00)
				{
					writelog(LOG_ERR,"error byte10--[%d]", packet_point->bit[10]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[11] != 0x00)
				{
					writelog(LOG_ERR,"error byte11--[%d]", packet_point->bit[11]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[12] != 0x10)
				{
					writelog(LOG_ERR,"error byte12--[%d]", packet_point->bit[12]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[13] != 0x00)
				{
					writelog(LOG_ERR,"error byte13--[%d]", packet_point->bit[13]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[14] != 0x00)
				{
					writelog(LOG_ERR,"error byte14--[%d]", packet_point->bit[14]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[15] != 0x01)
				{
					writelog(LOG_ERR,"error byte15--[%d]", packet_point->bit[15]);
					return E_TRANS_BANK_RECVERR;
				}
		
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("main_account head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->main_account, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(packet_point->trade_deal_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(packet_point->trade_money, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 10;
				memcpy(packet_point->trade_deal_time, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(packet_point->system_id, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(packet_point->accept_card_time, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(packet_point->accept_card_date, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(packet_point->shop_type, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(packet_point->service_input_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(packet_point->service_terms_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("proxy_node_code head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->proxy_node_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("send_node_code head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->send_node_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(packet_point->check_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(packet_point->answser_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(packet_point->device_phy, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 15;
				memcpy(packet_point->mark, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 40;
				memcpy(packet_point->address, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("append_data head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->append_data, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(packet_point->trade_money_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("defalult_area head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->defalut_area, buf + buf_length, packet_length);
				memset(str_length, 0, sizeof(str_length));
				buf_length += packet_length;
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("accpet_node_code head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->accept_node_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(packet_point->packet_identity_code, buf + buf_length, packet_length);

				// �ж�MACֵ
				memset(packet_str, 0, sizeof(packet_str));
//				strncpy(packet_str, BANK_YNXH_TRADE_CODE_ANS_TRANS, 4);
//				strcat(packet_str, SPLIT_VL);
				PACKETSTR(packet_str, BANK_YNXH_TRADE_CODE_ANS_TRANS, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->main_account + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_money, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_time, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->system_id, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->shop_type, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->service_terms_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->proxy_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->send_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->answser_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->device_phy, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->mark, SPLIT_VL);
		
				Caculate_String_MAC(packet_str, prs_next, mac);
				printf("����ֶ� =[%s]--�����ֶ� =[%s]\n", packet_str, prs_next);
				if (0 != strncmp(packet_point->packet_identity_code, mac, 8))
				{
					writelog(LOG_INFO,"MAC=[%8s]--packet_identity_code=[%8s]", mac, packet_point->packet_identity_code);
					return E_TRANS_BANK_RECVERR;
				}

				sprintf(packet_point->append_data, "%03d", strlen(prs_next));
				memcpy(packet_point->append_data + 3, prs_next, strlen(prs_next));
			}
			// ����Ӧ��
			else if (BANK_TRADE_CODE_DETRANS == trade_type)
			{
				// ��Ҫͨ��λͼ�����
				if ((unsigned char)packet_point->bit[0] != 0xF2)
				{
					writelog(LOG_ERR,"error byte0--[%d]", packet_point->bit[0]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[1] != 0x38)
				{
					writelog(LOG_ERR,"error byte1--[%d]", packet_point->bit[1]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[2] != 0x44)
				{
					writelog(LOG_ERR,"error byte2--[%d]", packet_point->bit[2]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[3] != 0x81)
				{
					writelog(LOG_ERR,"error byte3--[%d]", packet_point->bit[3]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[4] != 0x8A)
				{
					writelog(LOG_ERR,"error byte4--[%d]", packet_point->bit[4]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[5] != 0xE1)
				{
					writelog(LOG_ERR,"error byte5--[%d]", packet_point->bit[5]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[6] != 0x80)
				{
					writelog(LOG_ERR,"error byte6--[%d]", packet_point->bit[6]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[7] != 0x10)
				{
					writelog(LOG_ERR,"error byte7--[%d]", packet_point->bit[7]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[8] != 0x00)
				{
					writelog(LOG_ERR,"error byte8--[%d]", packet_point->bit[8]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[9] != 0x00)
				{
					writelog(LOG_ERR,"error byte9--[%d]", packet_point->bit[9]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[10] != 0x00)
				{
					writelog(LOG_ERR,"error byte10--[%d]", packet_point->bit[10]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[11] != 0x00)
				{
					writelog(LOG_ERR,"error byte11--[%d]", packet_point->bit[11]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[12] != 0x10)
				{
					writelog(LOG_ERR,"error byte12--[%d]", packet_point->bit[12]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[13] != 0x00)
				{
					writelog(LOG_ERR,"error byte13--[%d]", packet_point->bit[13]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[14] != 0x00)
				{
					writelog(LOG_ERR,"error byte14--[%d]", packet_point->bit[14]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[15] != 0x01)
				{
					writelog(LOG_ERR,"error byte15--[%d]", packet_point->bit[15]);
					return E_TRANS_BANK_RECVERR;
				}
				
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("main_account head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->main_account, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(packet_point->trade_deal_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(packet_point->trade_money, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 10;
				memcpy(packet_point->trade_deal_time, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(packet_point->system_id, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(packet_point->accept_card_time, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(packet_point->accept_card_date, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(packet_point->shop_type, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(packet_point->service_input_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(packet_point->service_terms_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("proxy_node_code head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->proxy_node_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("send_node_code head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->send_node_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(packet_point->check_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(packet_point->answser_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(packet_point->device_phy, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 15;
				memcpy(packet_point->mark, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 40;
				memcpy(packet_point->address, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("append_data head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->append_data, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(packet_point->trade_money_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("defalult_area head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->defalut_area, buf + buf_length, packet_length);
				memset(str_length, 0, sizeof(str_length));
				buf_length += packet_length;
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("accpet_node_code head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->accept_node_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(packet_point->packet_identity_code, buf + buf_length, packet_length);			
				
				// �ж�MACֵ
				memset(packet_str, 0, sizeof(packet_str));
//				strncpy(packet_str, BANK_YNXH_TRADE_CODE_ANS_DETRANS, 4);
//				strcat(packet_str, SPLIT_VL);
				PACKETSTR(packet_str, BANK_YNXH_TRADE_CODE_ANS_DETRANS, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->main_account + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_money, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->trade_deal_time, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->system_id, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->shop_type, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->service_terms_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->proxy_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->send_node_code + 2, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->answser_code, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->device_phy, SPLIT_VL);
				PACKETSTR(packet_str, packet_point->mark, SPLIT_VL);
				
				printf("����ֶ� =[%s]--�����ֶ� =[%s]\n", packet_str, prs_next);
				Caculate_String_MAC(packet_str, prs_next, mac);
				if (0 != strncmp(packet_point->packet_identity_code, mac, 8))
				{
					writelog(LOG_ERR,"MAC=[%8s]--packet_identity_code=[%8s]", mac, packet_point->packet_identity_code);
					return E_TRANS_BANK_RECVERR;
				}

				sprintf(packet_point->append_data, "%03d", strlen(prs_next));
				memcpy(packet_point->append_data + 3, prs_next, strlen(prs_next));	
			}
			// ����Ӧ��
			else if (BANK_TRADE_CODE_COMPARE == trade_type)
			{
				if ((unsigned char)packet_point->bit[0] != 0x8A)
				{
					writelog(LOG_ERR,"error byte0--[%d]", packet_point->bit[0]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[1] != 0x22)
				{
					writelog(LOG_ERR,"error byte1--[%d]", packet_point->bit[1]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[2] != 0x40)
				{
					writelog(LOG_ERR,"error byte2--[%d]", packet_point->bit[2]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[3] != 0x01)
				{
					writelog(LOG_ERR,"error byte3--[%d]", packet_point->bit[3]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[4] != 0x8A)
				{
					writelog(LOG_ERR,"error byte4--[%d]", packet_point->bit[4]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[5] != 0xE1)
				{
					writelog(LOG_ERR,"error byte5--[%d]", packet_point->bit[5]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[6] != 0x40)
				{
					writelog(LOG_ERR,"error byte6--[%d]", packet_point->bit[6]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[7] != 0x80)
				{
					writelog(LOG_ERR,"error byte7--[%d]", packet_point->bit[7]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[8] != 0x00)
				{
					writelog(LOG_ERR,"error byte8--[%d]", packet_point->bit[8]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[9] != 0x04)
				{
					writelog(LOG_ERR,"error byte9--[%d]", packet_point->bit[9]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[10] != 0x00)
				{
					writelog(LOG_ERR,"error byte10--[%d]", packet_point->bit[10]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[11] != 0x00)
				{
					writelog(LOG_ERR,"error byte11--[%d]", packet_point->bit[11]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[12] != 0x10)
				{
					writelog(LOG_ERR,"error byte12--[%d]", packet_point->bit[12]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[13] != 0x00)
				{
					writelog(LOG_ERR,"error byte13--[%d]", packet_point->bit[13]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[14] != 0x00)
				{
					writelog(LOG_ERR,"error byte14--[%d]", packet_point->bit[14]);
					return E_TRANS_BANK_RECVERR;
				}

				if ((unsigned char)packet_point->bit[15] != 0x01)
				{
					writelog(LOG_ERR,"error byte15--[%d]", packet_point->bit[15]);
					return E_TRANS_BANK_RECVERR;
				}
				
				packet_length = 12;
				memcpy(packet_point->liq_money, buf + buf_length, packet_length);			// ������
				buf_length += packet_length;
				packet_length = 10;
				memcpy(packet_point->trade_deal_time, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 6;
				memcpy(packet_point->system_id, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(packet_point->liquidate_date, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 4;
				memcpy(packet_point->shop_type, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("proxy_node_code head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->proxy_node_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("send_node_code head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->send_node_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 12;
				memcpy(packet_point->check_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 2;
				memcpy(packet_point->answser_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(packet_point->device_phy, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 15;
				memcpy(packet_point->mark, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 40;
				memcpy(packet_point->address, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("append_data head length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->append_data, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(packet_point->liq_cur_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 3;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("append_trade_info length[%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->append_trade_info, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 10;
				memcpy(packet_point->transfer_count, buf + buf_length, packet_length);		// ת�ʱ���
				memset(str_length, 0, sizeof(str_length));
				buf_length += packet_length;
				packet_length = 2;
				memcpy(str_length, buf + buf_length, packet_length);	// ���ֶεĳ���
				printf("accpet_node_code [%d]\n", atoi(str_length));
				packet_length += atoi(str_length);
				memcpy(packet_point->accept_node_code, buf + buf_length, packet_length);
				buf_length += packet_length;
				packet_length = 8;
				memcpy(packet_point->packet_identity_code, buf + buf_length, packet_length);
			}
			else 
			{
				NULL;
			}
		}
		// ����ũ�в�ѯ����
		else if (BANK_YNNH == bank_id)
		{
			// ��ѯ���, ���ð�ͷ
			packet_point2 = (BANK_YNNH_TRADE_STRUCT_PACKET *)packet;
			// ����ͷ��
			memcpy(&(packet_point2->ynnh_head), buf, sizeof(packet_point2->ynnh_head));
			buf_length += sizeof(packet_point2->ynnh_head);
			
			if (BANK_TRADE_CODE_QUERYBALANCE == trade_type)
			{
				// ����ĸ���
				_length = sizeof(packet_point2->account_money);
				memcpy(packet_point2->bank_account, buf + buf_length, _length);
				buf_length += _length;
				_length = sizeof(packet_point2->trade_money);
				memcpy(packet_point2->remain_money, buf + buf_length, _length);
			}
		}
		else
		{
			NULL;
		}
	}
	else 
	{
		NULL;
	}
	
	return 0;
}

int Get_Bank_Error_Code(void *pTransPak, int bank_id)
{
	
	BANK_YNXH_TRADE_STRUCT_PACKET *point = NULL;
	BANK_YNNH_TRADE_STRUCT_PACKET *point2 = NULL;

	// �����ź�
	if (BANK_YNXH == bank_id)
	{
		point = (BANK_YNXH_TRADE_STRUCT_PACKET *)pTransPak;
		// ��Щ������δ���ṩ, �Ժ�̨��־Ϊ׼
		writelog(LOG_ERR,"reject_code[%s]--answser_code[%s]",point->head.reject_code,point->answser_code);
		if (0 == strcmp(point->answser_code, "00"))
		{
			return 0;
		}
		else if (0 == strcmp(point->answser_code, "01"))
		{
			return E_CONNECT_PUBLISH_BANK;	// ���뷢������ϵ
		}
		else if (0 == strcmp(point->answser_code, "03"))
		{
			return E_INVALID_SHOP;	// ��Ч�̻�
		}
		else if (0 == strcmp(point->answser_code, "05"))
		{
			return E_CVN_FAILED;	// �������
		}
		else if (0 == strcmp(point->answser_code, "06"))
		{
			return E_TRADE_FAILED;	// ���׳���
		}
		else if (0 == strcmp(point->answser_code, "12"))
		{
			return E_INVALIED_TRADE;	// ��Ч����
		}
		else if (0 == strcmp(point->answser_code, "13"))
		{
			return E_INVALIED_MONEY; // ��Ч���
		}
		else if (0 == strcmp(point->answser_code, "56"))
		{
			return E_INVALIED_CARD;	// ��Ч����
		}
		else if (0 == strcmp(point->answser_code, "22"))
		{
			return E_TROUBLE_DOUBT;	// ���ϻ���
		}
		else if (0 == strcmp(point->answser_code, "25"))
		{
			return E_FIND_INIT_TRADE;	// �Ҳ���ԭʼ����
		}
		else if (0 == strcmp(point->answser_code, "40"))
		{
			return E_TRANS_FUNC_NONSUPPORT;	// �����ܲ�֧��
		}
		else if (0 == strcmp(point->answser_code, "41"))
		{
			return E_TRANS_BANKCARD_LOST;	// ��ʧ��
		}
		else if (0 == strcmp(point->answser_code, "42"))
		{
			return E_NO_BANK_ACCOUNT;	// �޴��˻�
		}
		else if (0 == strcmp(point->answser_code, "51"))
		{
			return E_TRANS_BANKACC_NOMONEY;	// �ʽ���
		}
		else if (0 == strcmp(point->answser_code, "54"))
		{
			return E_CARD_OUTOFDATE;	// ���ڿ�
		}
		else if (0 == strcmp(point->answser_code, "55"))
		{
			return E_INVALID_PIN;	// ����ȷ��PIN
		}
		else if (0 == strcmp(point->answser_code, "57"))
		{
			return E_CARDHOLDER_TRADE;	// ������ֿ��˽��н���
		}
		else if (0 == strcmp(point->answser_code, "61"))
		{
			return E_TRANS_TRANSMONEY_OUTRANGE;	// �����������
		}
		else if (0 == strcmp(point->answser_code, "65"))
		{
			return E_OUTOF_TRADE_COUNTS;	// �������״���
		}
		else if (0 == strcmp(point->answser_code, "75"))
		{
			return E_OUTOFPIN_INPUT;	// �������״���
		}
		else if (0 == strcmp(point->answser_code, "90"))
		{
			return E_BANK_SETTLE_ACCOUNTS;	// �������ս���
		}
		else if (0 == strcmp(point->answser_code, "A0"))
		{
			return E_TRANS_BANK_RECVERR;		// ���з������ݳ���
		}
		else
		{
			return E_TRANS_UNKNOW_ERROR;	// ��ʱ��֧�ִ˹���
		}
	}
	// ����ũ��
	else if (BANK_YNNH == bank_id)
	{
		point2 = (BANK_YNNH_TRADE_STRUCT_PACKET *)pTransPak;
		// ��Щ������δ���ṩ, �Ժ�̨��־Ϊ׼
		writelog(LOG_ERR,"error_code[%4.4s]", point2->ynnh_head.error_code);
		if (0 == strcmp(point2->ynnh_head.error_code, "0000"))
		{
			return 0;
		}
		else
		{
			return E_TRANS_UNKNOW_ERROR;	// ��ʱ��֧�ִ˹���
		}
	}
	
	return 0;
}

int Trade_Package_YNXH(BANK_YNXH_TRADE_STRUCT_PACKET *pTransPak, int trade_type, int packet_flag, 
							  ST_BANK_CONFIG *pBank, INNER_TRANS_REQUEST * pNode)
{	
	if (BANK_TRADE_CODE_QUERYBALANCE == trade_type)
	{
		// ���������
		if (0 == packet_flag)
		{
		}
		else	
		{
			NULL;				// Ӧ���ڴ�ʵ��
		}
	}
	
	return 0;
}

void Trace_8583_Package(char *_8583_buf, int _8583_length, int format, char *msg)
{
	int count = 1;
	printf("%s\n", msg);
	printf("---------------------------------------------------------------------------\n");
	for	(int jj = 0; jj < _8583_length; jj += 16)
	{
		printf("[%d] BYTE 16 bit %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X\n", count,
			_8583_buf[jj], _8583_buf[jj + 1], _8583_buf[jj + 2], _8583_buf[jj + 3], _8583_buf[jj + 4], _8583_buf[jj + 5], 
			_8583_buf[jj + 6], _8583_buf[jj + 7], _8583_buf[jj + 8], _8583_buf[jj + 9], _8583_buf[jj + 10], _8583_buf[jj + 11], 
			_8583_buf[jj + 12], _8583_buf[jj + 13], _8583_buf[jj + 14], _8583_buf[jj + 15]);
		count++;
	}
	printf("---------------------------------------------------------------------------\n");

	return ;
}

int Bank_AdjustCompareFile(INNER_TRANS_REQUEST *pNode, ST_BANK *bank, void *var_object1, void *var_object2, void *var_object3)
{
	char path_name[256]="";
	char file_name[256]="";
	char packet_str[516] = "";					// �źϱ����������
	char prs_next[516] = "";					// �źϼ��ܺ����Կ
	char mac[9] = "";							// �źϼ�����mac��Կ
	int ret=0;
	int cnt=0;
	int i=0;
	
	if (BANK_YNXH == bank->iBankID)
	{
		// 1. �Ӵ����bank�л�ȡ�����ļ�·��
		BANK_FILE_ADJUST *file_adjust = (BANK_FILE_ADJUST *)var_object2;
		writelog(LOG_INFO,"comp_file_path=[%s]", file_adjust->file_path_name);

		// 2. �ж�MACֵ, Ч���ļ�
		memset(packet_str, 0, sizeof(packet_str));
//		strncpy(packet_str, BANK_YNXH_TRADE_CODE_ANS_COMPARE, 4);
//		strcat(packet_str, SPLIT_VL);
		PACKETSTR(packet_str, BANK_YNXH_TRADE_CODE_ANS_COMPARE, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->liq_money, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->trade_deal_time, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->system_id, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->shop_type, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->service_terms_code, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->proxy_node_code + 2, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->send_node_code + 2, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->answser_code, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->device_phy, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->mark, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->append_trade_info + 3, SPLIT_VL);
		PACKETSTR(packet_str, file_adjust->transfer_count, SPLIT_VL);
				
		Caculate_FS_MAC(packet_str, file_adjust->file_path_name, prs_next, mac);		// Ч���Ŀ¼�е��ļ�
		printf("����ֶ�=[%s]--�����ֶ�=[%s]--�ļ�·��=[%s]\n", packet_str, prs_next, file_adjust->file_path_name);
		if (0 != strncmp(file_adjust->packet_identity_code, mac, 8))
		{
			writelog(LOG_INFO,"MAC=[%8s]--packet_identity_code=[%8s]", mac, file_adjust->packet_identity_code);
			return E_TRANS_BANK_RECVERR;
		}
	}

	return 0;
}

int Bank_GetRecvPacket(INNER_TRANS_REQUEST * pNode, ST_BANK *bank, void *recv_packet)
{
	int ret=0;
	char temp[6]="";
	int flag=0;
	int i=0;

	// �������ú�����
	int req_packet_length = 0;					// �ź��������ܳ���
	int ans_packet_length = 0;					// �ź�Ӧ�����ܳ���
	char prs_next[516] = "";					// �źϼ��ܺ����Կ
	char mac[9] = "";							// �źϼ�����mac��Կ
	char packet_str[516] = "";					// �źϱ������ 
	char packet_send_buf[1892] = "";			// ���ͱ���buf
	char packet_recv_buf[1892] = "";			// ���ܱ���buf
	BANK_FILE_ADJUST *file_adjust;				// ��ҪЧ��Ķ����ļ�����
	BANK_YNXH_TRADE_STRUCT_PACKET 	ynxh_req;	// ������
	BANK_YNXH_TRADE_STRUCT_PACKET 	ynxh_ans;	// Ӧ����
	file_adjust = (BANK_FILE_ADJUST*)recv_packet;
	
	if (BANK_YNXH == bank->iBankID)
	{
		// ��Ϸ������ݱ���
		ret = Packet_Buf_Transform(packet_send_buf, &ynxh_req, PACKET_TO_BUF, 
								   BANK_YNXH, BANK_TRADE_CODE_COMPARE, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_BANK_NOANSWER;
		}

		// ����������ݱ���
		Trace_Bank_Package_YNXH(&ynxh_req, "send compare file bank package");
			
		// �������ݱ��ĺͽ���Ӧ�����ݱ���
		ret = send_to_and_recv_from_bank(BANK_YNXH, packet_send_buf, atoi(ynxh_req.head.packet_length) + 4, packet_recv_buf, ans_packet_length, &g_Bank);
		if (ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_YNXH,ret);
			return E_TRANS_BANK_NOANSWER;
		}

		// ���Ӧ�����ݱ���
		ret = Packet_Buf_Transform(packet_recv_buf + 4, &ynxh_ans, BUF_TO_PACKET, BANK_YNXH, BANK_TRADE_CODE_COMPARE, pNode, 0);
		if (ret) 
		{
			writelog(LOG_ERR,"packet to buf--errcode=[%d]",ret);
			return E_TRANS_BANK_NOANSWER;
		}

		// ���Ӧ�����ݱ���
		Trace_Bank_Package_YNXH(&ynxh_ans,"receivce compare file bank package");

		// �жϴ�����
		ret = Get_Bank_Error_Code(&ynxh_ans, BANK_YNXH);
		if (ret)
		{
			writelog(LOG_ERR, "bank_no=[%s]--errcode=[%d]--card_id=[%s]", g_Bank.BankUnit[i].szBankAccountNO, ret, pNode->CardNo);
			return ret;
		}

		// ���˵�ʱ�����ݰ�, �ȴ�ȡ���ļ������Ч��Ͷ���
		memcpy(file_adjust->liq_money, ynxh_ans.liq_money, sizeof(file_adjust->liq_money) - 1);
		writelog(LOG_ERR, "file_adjust_time=[%s], trade_deal_time=[%s]", file_adjust->trade_deal_time, ynxh_ans.trade_deal_time);
		memcpy(file_adjust->trade_deal_time, ynxh_ans.trade_deal_time, sizeof(file_adjust->trade_deal_time) - 1);
		memcpy(file_adjust->system_id, ynxh_ans.system_id, sizeof(file_adjust->system_id) - 1);
		memcpy(file_adjust->shop_type, ynxh_ans.shop_type, sizeof(file_adjust->shop_type) - 1);
		memcpy(file_adjust->service_terms_code, ynxh_ans.service_terms_code, sizeof(file_adjust->service_terms_code) - 1);
		memcpy(file_adjust->proxy_node_code, ynxh_ans.proxy_node_code, sizeof(file_adjust->proxy_node_code) - 1);
		memcpy(file_adjust->send_node_code, ynxh_ans.send_node_code, sizeof(file_adjust->send_node_code) - 1);
		memcpy(file_adjust->answser_code, ynxh_ans.answser_code, sizeof(file_adjust->answser_code) - 1);
		memcpy(file_adjust->device_phy, ynxh_ans.device_phy, sizeof(file_adjust->device_phy) - 1);
		memcpy(file_adjust->mark, ynxh_ans.mark, sizeof(file_adjust->mark) - 1);
		memcpy(file_adjust->append_trade_info, ynxh_ans.append_trade_info, sizeof(file_adjust->append_trade_info) - 1);	
		memcpy(file_adjust->transfer_count, ynxh_ans.transfer_count, sizeof(file_adjust->transfer_count) - 1);
		memcpy(file_adjust->packet_identity_code, ynxh_ans.packet_identity_code, sizeof(file_adjust->packet_identity_code) - 1);
		memcpy(file_adjust->file_path_name, bank->comp_file_path, sizeof(file_adjust->file_path_name) - 1);
		strcat(file_adjust->file_path_name, file_adjust->append_trade_info + 3);			// �ļ�·�� + �ļ�����
	}
	else
	{
		return 0;
	}

	return 0;
}

