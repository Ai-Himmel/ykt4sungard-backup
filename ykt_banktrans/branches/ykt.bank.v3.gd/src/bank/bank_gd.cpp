/* ----------------------------------------------------------
 * �������ƣ�bank_gd.cpp
 * �������ڣ�2007-07-27 14:58
 * �������ߣ�������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ�ͨ�ýӿڹ淶�ķ�װ
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bank.h"
#include "bank_gd.h"
#include "mac.h"
#include "typdef.h"
#include "iso8583.h"


//void TRACE_BANK_TRANS(BANK_TRANS_REQUEST *pTransPak, char *stage);
void Trace_Bank_Package_GSYH(BANK_GSYH_TRADE_STRUCT *pTransPak, char *stage);
void Trace_Bank_Package_ZGYH_R(BANK_ZGYH_TRADE_STRUCT_TRANS_REQ *pTransPak, char *stage);
void Trace_Bank_Package_ZGYH_A(BANK_ZGYH_TRADE_STRUCT_TRANS_ANS *pTransPak, char *stage);
int send_to_and_recv_from_bank(int const bank_id,char* pSend, int send_len,char* pRecv,int recv_len,ST_BANK_CONFIG *pBank);
void WriteBufferLog(char *pBuffer,int Buffer_len,int colum_num);
int debug=2;

//����ͨ�ýӿڹ淶���з�װ�������еĽӿ�
int Bank_QueryBalance(INNER_TRANS_REQUEST * pNode,double *balance)
{

	int ret=0;
	char temp[6]="";
	int i=0;
	int flag=0;

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
	//�������в�֧�ֲ�ѯ���п�����
	else if(g_Bank.BankUnit[i].iBankID==BANK_JSYH)
	{
		return E_TRANS_BANK_FUNC_NONSUPPORT;
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

	BANK_ZGYH_TRADE_STRUCT_TRANS_REQ 	zgyh_req;
	BANK_ZGYH_TRADE_STRUCT_TRANS_ANS 	zgyh_ans;

	BANK_GSYH_TRADE_STRUCT 			gsyh_req;
	BANK_GSYH_TRADE_STRUCT 			gsyh_ans;

	MSG8583 jsyh_req,jsyh_ans;
	H_MSG8583 head_jsyh_req,head_jsyh_ans;

	ISO_MSG iso_jsyh_req,iso_jsyh_ans;
	iso8583_init(&iso_jsyh_req);
	iso8583_init(&iso_jsyh_ans);
	char jsyh_sbuf[2048]="";
	char jsyh_abuf[2048]="";
	

	memset(&zgyh_req,0x20,sizeof zgyh_req);
	memset(&zgyh_ans,0x20,sizeof zgyh_ans);

	memset(&gsyh_ans,0x20,sizeof gsyh_ans);
	memset(&gsyh_req,0x20,sizeof gsyh_req);

	memset(&jsyh_req,0x20,sizeof jsyh_req);
	memset(&jsyh_ans,0x20,sizeof jsyh_ans);
	memset(&head_jsyh_req,0x20,sizeof jsyh_req);
	memset(&head_jsyh_ans,0x20,sizeof jsyh_ans);
	

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
	//��������
	else if(g_Bank.BankUnit[i].iBankID==BANK_JSYH)
	{
		char buf[2048]="";
		char bitmap[16]={0x70,0x18,0x00,0x01,0x08,0x80,0x00,0x00};
		ret=iso8583_set(&iso_jsyh_req, 0, (unsigned char*)BANK_JSYH_TRADE_CODE_TRANS_REQ, 4);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		//memcpy(jsyh_req.msgType,BANK_JSYH_TRADE_CODE_TRANS_REQ,4);
		ret=iso8583_set(&iso_jsyh_req, 1, (unsigned char*)bitmap,8);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		//memcpy(jsyh_req.priActNum,pNode->BankCardNo,strlen(pNode->BankCardNo));
		ret=iso8583_set(&iso_jsyh_req, 2, (unsigned char*)pNode->BankCardNo,strlen(pNode->BankCardNo));
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		//memcpy(jsyh_req.procCode,"000000",6);
		ret=iso8583_set(&iso_jsyh_req, 3, (unsigned char*)"000000", 6);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		//memcpy(jsyh_req.txnAmunt,pNode->TransMoney,strlen(pNode->TransMoney));
		sprintf(buf,"%012s",pNode->TransMoney);
		ret=iso8583_set(&iso_jsyh_req, 4,(unsigned char*)buf , 12);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		//memcpy(jsyh_req.txnDatTim,"0000000000",10);
		//memset(jsyh_req.tracAudNum,'0',sizeof jsyh_req.tracAudNum);
		//memcpy(jsyh_req.txnLocDat,pNode->TradeDate,8);
		ret=iso8583_set(&iso_jsyh_req,13,(unsigned char*)pNode->TradeDate,8);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}

		//memcpy(jsyh_req.txnLocTim,pNode->TradeTime,6);
		ret=iso8583_set(&iso_jsyh_req,12,(unsigned char*)pNode->TradeTime,6);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		//memcpy(jsyh_req.bala_date,"0000",4);
		//memcpy(jsyh_req.trade_fee,"00000000",9);
		//memcpy(jsyh_req.acqInstID,BANK_JSYH_MERCH_NO,6);
		ret=iso8583_set(&iso_jsyh_req,32,(unsigned char*)BANK_JSYH_MERCH_NO,6);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		sprintf(sSerialno,"%020d",serial_no);
		//memcpy(jsyh_req.field37,sSerialno,strlen(sSerialno));
		ret=iso8583_set(&iso_jsyh_req,37,(unsigned char*)sSerialno,20);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		//memcpy(jsyh_req.termID,pNode->TerminalId,strlen(pNode->TerminalId));
		memset(buf,0,sizeof buf);
		sprintf(buf,"%8s",pNode->TerminalId);
		ret=iso8583_set(&iso_jsyh_req,41,(unsigned char*)buf,8);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		//memset(jsyh_req.field48,'0',20);
		//memcpy(jsyh_req.pinDat,"00000000",8);
		//memcpy(jsyh_req.bankCode,BANK_JSYH_MERCH_NO,6);
		//memcpy(jsyh_req.englishNam,"T",2);
		//memcpy(jsyh_req.mac,"000000",6);
		
		//ret=Pack8583((unsigned char*)head_jsyh_req.msg, jsyh_req, 2);
		ret=iso8583_pack(&iso_jsyh_req, jsyh_sbuf);
		if(ret<=0)
		{
			writelog(LOG_ERR,"Pack8583 error,errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}

		ret=send_to_and_recv_from_bank(BANK_JSYH,(char *)jsyh_sbuf,ret,(char*)jsyh_abuf,200,&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		
		//ret=UnPack8583((unsigned char*)head_jsyh_ans.msg,&jsyh_ans,2);
		ret=iso8583_unpack(&iso_jsyh_ans, jsyh_abuf);
		if(ret<0)
		{
			writelog(LOG_ERR,"UnPack8583 error,errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		if(0!=strncmp((char *)iso_jsyh_ans.fld[39].buf,"00",2))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s] ",iso_jsyh_ans.fld[39].buf);
			memcpy(temp,iso_jsyh_ans.fld[39].buf,2);
			temp[2]=0;
			switch(atoi(temp))
			{
				case 41:		//���п���ʧ
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
					return	E_TRANS_BANKCARD_LOST;
				case 36:		//���п�״̬����
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
					return	E_TRANS_BANKACC_STATERR;
				case 51:		//���п�����
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
					return	E_TRANS_BANKACC_NOMONEY;
				case 75:		//�����������
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_BANKCARD_PWDERR;
				case 96:		//���д���ʱ
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
					return	E_TRANS_BANK_NOANSWER;
				case 22:		//��������
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_UNKNOW_ERROR;
				default:		//����δ֪����
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_UNKNOW_ERROR;
			}
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

	char sMoney[32]="";
	char sSerialno[32]="";

	BANK_ZGYH_TRADE_STRUCT_DETRANS_REQ 	zgyh_req;
	BANK_ZGYH_TRADE_STRUCT_DETRANS_ANS 	zgyh_ans;

	BANK_GSYH_TRADE_STRUCT 			gsyh_req;
	BANK_GSYH_TRADE_STRUCT 			gsyh_ans;

	MSG8583 jsyh_req,jsyh_ans;
	H_MSG8583 head_jsyh_req,head_jsyh_ans;

	ISO_MSG iso_jsyh_req,iso_jsyh_ans;
	iso8583_init(&iso_jsyh_req);
	iso8583_init(&iso_jsyh_ans);
	char jsyh_sbuf[2048]="";
	char jsyh_abuf[2048]="";


	memset(&zgyh_req,0x20,sizeof zgyh_req);
	memset(&zgyh_ans,0x20,sizeof zgyh_ans);

	memset(&gsyh_ans,0x20,sizeof gsyh_ans);
	memset(&gsyh_req,0x20,sizeof gsyh_req);

	memset(&jsyh_req,0x20,sizeof jsyh_req);
	memset(&jsyh_ans,0x20,sizeof jsyh_ans);
	
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

		sprintf(sSerialno,"%d",pNode->SendNo);
		memcpy(zgyh_req.head.LocalNo,sSerialno,strlen(sSerialno));			//������ˮ��

		//sprintf(zgyh_req.head.LocalNo,"%d",pNode->SendNo);			//������ˮ��;
		memset(zgyh_req.head.BankNo,0x20,sizeof(zgyh_req.head.BankNo));				//������ˮ��;
		memset(zgyh_req.head.Filer2,0x20,sizeof(zgyh_req.head.Filer2));				//Ԥ��;

		memcpy(zgyh_req.GDCAccount,pNode->CardNo,strlen(pNode->CardNo));			//У԰���ʺ�
		memcpy(zgyh_req.BankCard,pNode->BankCardNo,strlen(pNode->BankCardNo));	//���п���
		zgyh_req.CardType='D';				//�����ͣ�C���ÿ�,D��ǿ�
		sprintf(sMoney,"%013d",atoi(pNode->TransMoney)*100);
		memcpy(zgyh_req.TranMoney,sMoney,sizeof(zgyh_req.TranMoney));	//���׽��

		//memset(zgyh_req.PinBlock,0x20,sizeof(zgyh_req.PinBlock));			//Ԥ��
		//memset(zgyh_req.TpkUdlmk,0x20,sizeof(zgyh_req.TpkUdlmk));			//Ԥ��
		//memset(zgyh_req.XykSqh,0x20,sizeof(zgyh_req.XykSqh));		//���ÿ���Ȩ��
		sprintf(sSerialno,"%d",pNode->RecvNo);
		memcpy(zgyh_req.OldLocalNo,sSerialno,strlen(sSerialno));			//������ˮ��
		//sprintf(zgyh_req.OldLocalNo,"%d",pNode->RecvNo);		//ԭ������ˮ��

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
		gsyh_req.TranFlag[0]='1';						//���ױ�־;0:������,1:������
		memcpy(gsyh_req.BankCardNo,pNode->BankCardNo,strlen(pNode->BankCardNo));//���п���;�跽�ʺţ�����ʱΪѧУ�ʺ�			
		sprintf(sMoney,"%010d",atoi(pNode->TransMoney)*100);
		memcpy(gsyh_req.TranMoney,sMoney,sizeof(gsyh_req.TranMoney));	//���׽��
		memcpy(gsyh_req.MoneyType,"001",3);//��������;001:�����
		memcpy(gsyh_req.TranDate,pNode->TradeDate,8); //��������;YYYY-MM-DD
		memcpy(gsyh_req.TranTime,pNode->TradeTime,6);//����ʱ��;HHMMSS
		gsyh_req.PwdFlag[0]='0';
		gsyh_req.PwdType[0]='0';	
		sprintf(sSerialno,"%d",pNode->SendNo);
		memcpy(gsyh_req.LocalSn,sSerialno,strlen(sSerialno));			//������ˮ��
		//sprintf(gsyh_req.LocalSn,"%d",pNode->SendNo);			//������ˮ��
		sprintf(sSerialno,"%d",pNode->RecvNo);
		memcpy(gsyh_req.LocalDetranSn,sSerialno,strlen(sSerialno));			//����ʱ�����ԭת�ʽ�����ˮ��
		//sprintf(gsyh_req.LocalDetranSn,"%d",pNode->RecvNo);	//����ʱ�����ԭת�ʽ�����ˮ��
		//memcpy(gsyh_req.BankSn,"000000",6);			//������ˮ��
		memcpy(gsyh_req.MercAccount,BANK_GSYH_MERCH_NO,5);	//Ȧ��ʱΪ��ɽ��ѧ�̻���,����ʱΪ�̻����̻���
		memcpy(gsyh_req.MercAccountCode,"01",2);		//�����ţ�ָ�̻����ж�������ʺ�ʱ�����ֶ�ָʾ����һ���ʺţ��ȹ̶�Ϊ01;
		memcpy(gsyh_req.GDCAccount,pNode->CardNo,10);			//У԰����;
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
	//��������
	else if(g_Bank.BankUnit[i].iBankID==BANK_JSYH)
	{
		char buf[2048]="";
		char bitmap[16]={0x70,0x38,0x00,0x01,0x08,0x80,0x00,0x00};
		ret=iso8583_set(&iso_jsyh_req, 0, (unsigned char*)BANK_JSYH_TRADE_CODE_DETRANS_REQ, 4);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		ret=iso8583_set(&iso_jsyh_req, 1, (unsigned char*)bitmap,8);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		ret=iso8583_set(&iso_jsyh_req, 2, (unsigned char*)pNode->BankCardNo,strlen(pNode->BankCardNo));
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		ret=iso8583_set(&iso_jsyh_req, 3, (unsigned char*)"000000", 6);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		sprintf(buf,"%012d",atoi(pNode->TransMoney)*100);
		ret=iso8583_set(&iso_jsyh_req, 4,(unsigned char*)buf , 12);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		memset(buf,0,sizeof buf);
		sprintf(buf,"%020d",pNode->RecvNo);
		ret=iso8583_set(&iso_jsyh_req, 11,(unsigned char*)buf , 20);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		ret=iso8583_set(&iso_jsyh_req,13,(unsigned char*)pNode->TradeDate,8);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}

		ret=iso8583_set(&iso_jsyh_req,12,(unsigned char*)pNode->TradeTime,6);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		ret=iso8583_set(&iso_jsyh_req,32,(unsigned char*)BANK_JSYH_MERCH_NO,6);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		sprintf(sSerialno,"%020d",pNode->SendNo);
		ret=iso8583_set(&iso_jsyh_req,37,(unsigned char*)sSerialno,20);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		memset(buf,0,sizeof buf);
		sprintf(buf,"%8s",pNode->TerminalId);
		ret=iso8583_set(&iso_jsyh_req,41,(unsigned char*)buf,8);
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error");
			return E_TRANS_UNKNOW_ERROR;
		}
		ret=iso8583_pack(&iso_jsyh_req, jsyh_sbuf);
		if(ret<=0)
		{
			writelog(LOG_ERR,"Pack8583 error,errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}

		ret=send_to_and_recv_from_bank(BANK_JSYH,(char *)jsyh_sbuf,ret,(char*)jsyh_abuf,200,&g_Bank);
		if(ret)
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
			return E_TRANS_BANK_NOANSWER;
		}
		
		//ret=UnPack8583((unsigned char*)head_jsyh_ans.msg,&jsyh_ans,2);
		ret=iso8583_unpack(&iso_jsyh_ans, jsyh_abuf);
		if(ret<0)
		{
			writelog(LOG_ERR,"UnPack8583 error,errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		if(0!=strncmp((char *)iso_jsyh_ans.fld[39].buf,"00",2))
		{
			writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s] ",iso_jsyh_ans.fld[39].buf);
			memcpy(temp,iso_jsyh_ans.fld[39].buf,2);
			temp[2]=0;
			switch(atoi(temp))
			{
				case 41:		//���п���ʧ
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
					return	E_TRANS_BANKCARD_LOST;
				case 36:		//���п�״̬����
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
					return	E_TRANS_BANKACC_STATERR;
				case 51:		//���п�����
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
					return	E_TRANS_BANKACC_NOMONEY;
				case 75:		//�����������
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_BANKCARD_PWDERR;
				case 96:		//���д���ʱ
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
					return	E_TRANS_BANK_NOANSWER;
				case 22:		//��������
					//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
					return	E_TRANS_UNKNOW_ERROR;
				default:		//����δ֪����
					//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
					return	E_TRANS_UNKNOW_ERROR;
			}
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

	if(g_Bank.LOG_MODE==1)	WriteBufferLog(pSend,send_len,16);
	
	//�������ݵ�����
	ret=SockNode.hSock.Send(pSend, send_len);
	if (ret<0)
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

	system("sleep 1");

	//�������з�����Ϣ
	ret=	SockNode.hSock.RecvDesignedLen(pRecv,recv_len,delay_time);
	if(g_Bank.LOG_MODE==1)	WriteBufferLog(pRecv,ret,16);
	if (ret<=0)
	{
		writelog(LOG_ERR,"Receive from bank error,ret= [%d] ",ret);
		return	E_TRANS_BANK_NOANSWER;  // ����ʱ�������ʱ
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
void WriteBufferLog(char *pBuffer,int Buffer_len,int colum_num)
{
	int i=0;
	int j=0;
	char buffer[10240]="";
	char hex_buffer[1024]="";
	char char_buffer[1024]="";
	char tmp_char[2+1]="";
	for(i=0;i<Buffer_len;i++)
	{
		sprintf(tmp_char,"%02X ",(unsigned char)pBuffer[i]);
		strcat(hex_buffer,tmp_char);
		if ((unsigned char)pBuffer[i]<32||(unsigned char)pBuffer[i]>128)
		{
			strcat(char_buffer,".");
		}
		else
		{
			sprintf(tmp_char,"%c",(unsigned char)pBuffer[i]);
			strcat(char_buffer,tmp_char);
		}
		if((i%colum_num+1==colum_num&&i>0))
		{ 
			strcat(buffer,hex_buffer);
			strcat(buffer," ; ");
			strcat(buffer,char_buffer);
			strcat(buffer,"\r\n");
			hex_buffer[0]=0;
			char_buffer[0]=0;
		}
	}
	memset(&hex_buffer[(i%colum_num)*3],' ',colum_num*3-(i%colum_num)*3);
	hex_buffer[colum_num*3]=0;
	strcat(buffer,hex_buffer);
	strcat(buffer," ; ");
	strcat(buffer,char_buffer);
	strcat(buffer,"\r\n");
	
	//writelog(LOG_DEBUG,"%s",buffer);
	printf(buffer);
}

