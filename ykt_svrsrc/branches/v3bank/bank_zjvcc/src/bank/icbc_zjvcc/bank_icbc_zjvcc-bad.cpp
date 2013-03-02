/* ----------------------------------------------------------
 * �������ƣ�bank_icbc_zjvcc.cpp
 * �������ڣ�2011-09-08
 * �������ߣ�������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ���������-����ְ�ӿ�
 * ----------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include "assert.h"

#include "shem.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "d3des.h"
#include "mac.h"
#include "bank.h"
#include "bank_interface.h"
#include "tcp_update.h"


static void GenMsgHead(char *msghead,ST_PACK *rPack)
{
	char buf[1024]="";
	AddXmlItemStr(buf,"AreaNo","");								//��������
	AddXmlItemStr(buf,"ChanNo","");								//��������
	AddXmlItemInt(buf, "TerminalNo", rPack->lvol6);					//�ն˱��
	AddXmlItemStr(buf,"TransNo",rPack->sholder_ac_no);			//������ˮ��
	AddXmlItemStr(buf,"TransDate",rPack->sdate0);				//��������
	AddXmlItemStr(buf,"TransTime",rPack->stime0);					//����ʱ��
	AddXmlItemStr(buf,"BankNo","");								//��������
	AddXmlItemStr(buf,"TellerNo","");								//��Ա����
	AddXmlItemInt(buf, "FuncTionFlag", 1);							//�����־
	AddXmlItemStr(msghead, "MsgHead", buf);						// ȫ������MsgHead ��	
	writelog(LOG_DEBUG,"msghead[%s] ",msghead);
}

// ��ֵ����
static void GenMsgBodyTrans(char *msgbody,ST_PACK *rPack)	
{
	char buf[1024]="";
	AddXmlItemStr(buf, "SchoolCode", SCHOOLCODE_AHUT);			//ѧУ����
	AddXmlItemStr(buf, "IcCard", rPack->sphone);					//У԰������(ʹ��ѧ����)
	AddXmlItemStr(buf, "CusName", rPack->scust_limit);				//�ͻ�����
	AddXmlItemInt(buf, "SignFlag", 1);								//ǩԼ��־
	AddXmlItemStr(buf, "ActNo", rPack->scust_limit2);				// ���п���
	AddXmlItemDbl(buf, "Amount", rPack->damt0);					// ���׽��

	AddXmlItemStr(msgbody, "MsgBody", buf);						//ȫ������MsgBody ��	
	writelog(LOG_DEBUG,"msgbody[%s] ",msgbody);
}

// ��������
static void GenMsgBodyTransRev(char *msgbody,ST_PACK *rPack)
{
	char buf[1024]="";
	AddXmlItemStr(buf, "SchoolCode", SCHOOLCODE_AHUT);			//ѧУ����
	AddXmlItemStr(buf, "IcCard", rPack->sphone);					//У԰������(ʹ��ѧ����)
	AddXmlItemDbl(buf, "Amount", rPack->damt0);					// ���׽��
	AddXmlItemStr(buf, "RSeqNo", rPack->sholder_ac_no);			//������ˮ��

	AddXmlItemStr(msgbody, "MsgBody", buf);						//ȫ������MsgBody ��	
	writelog(LOG_DEBUG,"msgbody[%s] ",msgbody);
}

static void GenMsgBodyQuery(char *msgbody,ST_PACK *rPack)
{
	char buf[1024]="";
	AddXmlItemStr(buf, "SchoolCode", SCHOOLCODE_AHUT);			//ѧУ����
	AddXmlItemStr(buf, "IcCard", rPack->sphone);					//У԰������(ʹ��ѧ����)
	AddXmlItemInt(buf, "SignFlag", 1);								//ǩԼ��־
	AddXmlItemStr(buf, "ActNo", rPack->scust_limit2);				// ���п���

	AddXmlItemStr(msgbody, "MsgBody", buf);						//ȫ������MsgBody ��	
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
	memcpy(msg,len_buf,8);											// 8λ����
	memcpy(msg+8,transcode,4);										// 4λ������
	memcpy(msg+12,XML_HEAD,xmlhead_len);							// xml ͷ
	memcpy(msg + xmlhead_len +12,transcont,transcont_len);				// ��������(msghead + msgbody)
	writelog(LOG_DEBUG,"msg[%s] ",msg);
}





// ��ӡ������Ϣ
#define set_msg(buf, fmt, ...)\
{\
	sprintf(buf, fmt, ## __VA_ARGS__);\
	printf(buf);\
}

//static void set_msg_log(char *szMsg,int ret)

//��ӡ��д��־������Ϣ
#define set_msg_log(buf, fmt, ...)\
{\
	set_msg(buf, fmt, ## __VA_ARGS__);\
	writelog(LOG_ERR,buf);\
}





#define MAX 2048
typedef struct
{
	char campus_no[12+1];	//1   ѧУ��� aaaaaaaaaaaaaaaaaaaaaa
	char txcode[5+1]; //2        ���״���      
	char userno[12+1]; //3        �ͻ���ţ�ÿ��ת�ʵ�Ψһ��ʶ�������У���ѧ�ţ� 
	char usernoalias[18+1];//4  ���֤��
	char acctperi[5+1];//5 ����
	char acctno[20+1];//6	�����˺Ż򿨺�
	char due_amount[10+1];//7	���׽���ʽ��180.00��
	char pay_amount[10+1]; //8�ɹ�������� 
	char custname[20+1]; //9/////�ͻ���
	char site[5+1]; //10��������	111111111xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	char teller[5+1];	//11	���׹�Ա 1111111111xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	char time[14+1];//12	����ʱ��,���ڣ�ʱ��
	char comporder[8+1];	//13��˾����ˮ  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	char bankorder[8+1];	//14���з���ˮ
	char comp_o_order[8+1];//15��˾��ԭ������ˮ  
	char bank_o_order[8+1];//16���з�ԭ������ˮ  	
	char note[50+1];	//17������Ϣ  
	char result[3+1];//18	���׳ɹ���ʧ��	00���ɹ�	01��ʧ��   
	char retmessage[50+1];	//19������Ϣ 
}Message;


static void print_msg(Message *Msg)
{
	printf("ѧУ��� campus_no:    [%s]\n", Msg->campus_no);
	printf("���״��� txcode:       [%s]\n", Msg->txcode);
	printf("�ͻ���� userno:       [%s]\n", Msg->userno);
	printf("�ͻ��ӱ�� usernoalias:[%s]\n", Msg->usernoalias);
	printf("���� acctperi:         [%s]\n", Msg->acctperi);
	printf("�˺� acctno:           [%s]\n", Msg->acctno);
	printf("���׽�� due_amount:   [%s]\n", Msg->due_amount);
	printf("��� pay_amount:       [%s]\n", Msg->pay_amount);
	printf("�ͻ����� custname:     [%s]\n", Msg->custname);
	printf("�������� site:         [%s]\n", Msg->site);
	printf("���׹�Ա teller:       [%s]\n", Msg->teller);
	printf("�������ڣ�ʱ�� time:   [%s]\n", Msg->time);
	printf("��˾����ˮ comporder:  [%s]\n", Msg->comporder);
	printf("���з���ˮ bankorder:  [%s]\n", Msg->bankorder);
	printf("��˾��ԭ������ˮ comp_o_order: [%s]\n", Msg->comp_o_order);
	printf("���з�ԭ������ˮ bank_o_order: [%s]\n", Msg->bank_o_order);
	printf("������Ϣ note:         [%s]\n", Msg->note);
	printf("��Ӧ�� result:         [%s]\n", Msg->result);
	printf("������Ϣ retmessage:   [%s]\n", Msg->retmessage);
	return;
}



static void print_send_msg(Message *Msg)
{
	printf("\n==================== ���ͱ��Ŀ�ʼ =====================\n");
	print_msg(Msg);
	printf("====================== ���ͱ��Ľ��� ======================\n");
	return; 
}

static void print_recv_msg(Message *Msg)
{
	printf("===================== ���з��ر��Ŀ�ʼ =====================\n");
	print_msg(Msg);
	printf("===================== ���з��ر��Ľ��� ======================\n");
	return; 
}


static void getdata(Message *Msg,ST_PACK *rPack)
{
// 	char trade_date[9]={0}; // �������� 
// 	char trade_time[7]={0}; // ����ʱ��
	//set_msg(Msg->campus_no,"%s","001");	//1ѧУ���
	//des2src(Msg->txcode,"20200"); //2���״���
// 	des2src(Msg->userno, rPack->sphone);	//3 ѧ����
// 	des2src(Msg->usernoalias, rPack->scust_auth2);// 4���֤��
// 	des2src(Msg->acctperi, rPack->vsmess); //5 ��������
// 	des2src(Msg->acctno, rPack->scust_limit2);//6 ���п���
// 	set_msg(Msg->due_amount,"%0.2f",rPack->damt0); //7���׽���ʽ��180.00��x
// 	//8
// 	des2src(Msg->custname, rPack->scust_limit );//9 �ͻ���
// 	set_msg(Msg->site,"%d",rPack->lvol6);  //10
// 	set_msg(Msg->teller,"%d",rPack->lvol6); //11
// 	des2src(trade_date, rPack->sdate0); //12 ��������
// 	des2src(trade_time, rPack->stime0); //12 ����ʱ��
// 	set_msg(Msg->time,"%s%s",trade_date,trade_time); //12	����ʱ��,���ڣ�ʱ��
// 	des2src(Msg->comporder, rPack->sholder_ac_no); //13

	snprintf(Msg->userno, sizeof(Msg->userno), "%d", rPack->lvol2); //3 �ͻ���
	snprintf(Msg->usernoalias, sizeof(Msg->usernoalias), "%s", rPack->scust_auth2); // ���֤��
	snprintf(Msg->acctno, sizeof(Msg->acctno), "%s", rPack->scust_limit2); // ���п���
	snprintf(Msg->custname, sizeof(Msg->custname), "%s", rPack->scust_limit); // �ͻ���
	snprintf(Msg->acctperi, sizeof(Msg->acctperi), "%s", rPack->sdate0); // ��������
	if(strlen(Msg->acctperi) == 0)// û���ṩ����
		getsysdate(Msg->acctperi);
	snprintf(Msg->due_amount, sizeof(Msg->due_amount), "%.2f", rPack->damt0);// ���׽��
	snprintf(Msg->site, sizeof(Msg->site), "%d", rPack->lvol6);// �ն�ID
	getsysdatetime(Msg->time); // �������ڣ�ʱ��
	if(strlen(rPack->sholder_ac_no) > 8) // һ��ͨ���ײο���
	{
		// һ��ͨ���ײο��� ȥ�� yyMMDD, ��Ϊϵͳ���ٺ�
		int serial = atoi(&rPack->sholder_ac_no[8]);
		snprintf(Msg->comporder, sizeof(Msg->comporder), "%06d", serial); // ��˾����ˮ
		snprintf(Msg->comp_o_order, sizeof(Msg->comp_o_order), "%06d", serial); // ��˾����ˮ
	}
	snprintf(Msg->bankorder, sizeof(Msg->bankorder), rPack->sname); // ���з���ˮ
	snprintf(Msg->bank_o_order, sizeof(Msg->bank_o_order), rPack->sname); // ���з�ԭ������ˮ
	//print_send_msg(Msg); // ��ӡ���ͱ���

}


static void struct2str(Message *j,char *buf)  //ƴװ
{
	sprintf(buf,"&|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|#",		
		j->campus_no, //1
		j->txcode, //2
		j->userno, //3
		j->usernoalias, //4
		j->acctperi, //5
		j->acctno, //6
		j->due_amount, //7
		j->pay_amount, //8
		j->custname, //9
		j->site, //10
		j->teller, //11
		j->time, //12
		j->comporder, //13
		j->bankorder, //14
		j->comp_o_order, //15
		j->bank_o_order, //16
		j->note, //17
		j->result, //18
		j->retmessage); //19

}


void str2struct(char *buf,Message *j)
{
	int len,i;
	char *p,*q,*str[20];
	len=strlen(buf);
	//q=strstr(buf,"&")+1;
	q=buf+1;
	for(i=1;q<buf+len-1;i++)
	{
		p=strstr(q,"|");
		*p++=0;
		str[i]=p;
		q=p;
	}
	strcpy(j->campus_no,str[1]);	//1   ѧУ��� aaaaaaaaaaaaaaaaaaaaaa
	strcpy(j->txcode,str[2]); //2        ���״���      
	strcpy(j->userno,str[3]); //3        �ͻ���ţ�ÿ��ת�ʵ�Ψһ��ʶ�������У���ѧ�ţ� 
	strcpy(j->usernoalias,str[4]);//4  ���֤��
	strcpy(j->acctperi,str[5]);//5 ����
	strcpy(j->acctno,str[6]);//6	�����˺Ż򿨺�
	strcpy(j->due_amount,str[7]);//7	���׽���ʽ��180.00��
	strcpy(j->pay_amount,str[8]); //8�ɹ�������� 
	strcpy(j->custname,str[9]); //9/////�ͻ���
	strcpy(j->site,str[10]); //10��������	111111111xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	strcpy(j->teller,str[11]);	//11	���׹�Ա 1111111111xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	strcpy(j->time,str[12]);//12	����ʱ��,���ڣ�ʱ��
	strcpy(j->comporder,str[13]);	//13��˾����ˮ  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	strcpy(j->bankorder,str[14]);	//14���з���ˮ
	strcpy(j->comp_o_order,str[15]);//15��˾��ԭ������ˮ  
	strcpy(j->bank_o_order,str[16]);//16���з�ԭ������ˮ  	
	strcpy(j->note,str[17]);	//17������Ϣ  
	strcpy(j->result,str[18]);//18	���׳ɹ���ʧ��	00���ɹ�	01��ʧ��   
	strcpy(j->retmessage,str[19]);	//19������Ϣ 
}


static bool send(CTcpSocket *SockNode,char *send_buf,char *szMsg)
{
	int ret=0;
	int send_len=strlen(send_buf);
	char buf[2048]={0};
	ret=SockNode->Send(send_buf,send_len);
	if (ret<=0)
	{
		SockNode->Close();
		set_msg_log(szMsg,"�������������г���,�������[%d]\n",ret);
		return false;
	}
	set_msg_log(buf, "�������ݵ�����, ����[%d] ����[%s]\n", send_len, send_buf);
	return true;
}


static bool connect(CTcpSocket *SockNode,char *bank_ip,int bank_port,int bank_delay,char *szMsg)
{
	char buf[2048]={0};
	int ret=0;
	alarm(bank_delay/1000);
	ret=SockNode->ConnectTcp(bank_ip, bank_port);
	if(!ret)
	{
		alarm(0);
		SockNode->Close();
		set_msg_log(szMsg,"�������з�����ʧ��,�������[%d],����IP[%s],����PORT[%d]\n",ret,bank_ip, bank_port);
		return false;
	}
	alarm(0);
	set_msg_log(buf, "�������з������ɹ�\n");
	return true;
}



static void get_ip_port(char *ip,int *port,ST_PACK *rPack)
{
	sprintf(ip, "%s",rPack->scust_auth); // ���з�����IP
	*port = rPack->lvol0; // ���з�����Port     
}

static void initialize(char *type,char *bank_ip,int *bank_port,Message *send_Msg,ST_PACK *rPack,char *send_buf)
{
	get_ip_port(bank_ip,bank_port,rPack); //���з�����IP�����з�����Port 
	getdata(send_Msg,rPack); //��ȡ����
	strcpy(send_Msg->txcode,type); //��ʼ���������ݽ��״���
	struct2str(send_Msg,send_buf);  //ƴװ
	print_send_msg(send_Msg); // ��ӡ���ͱ���
}



static bool receive(CTcpSocket *SockNode,char *recv_buf,int max_len,int bank_delay,char *szMsg)
{
	 	int ret=0;
		int recv_len = 0;
		char buf[2048]={0};
		// ��������
		while(1)
		{
			ret= SockNode->RecvDesignedLen(recv_buf,max_len,bank_delay);
			if (ret<=0)
			{
				SockNode->Close();
				set_msg_log(szMsg,"�������з������ݳ����ʱ,�������[%d]\n",ret);
				return false; // ����ʱ�������ʱ
			}
			max_len -= ret;
			recv_len += ret; // �ѽ������ݳ���
			if(recv_buf[recv_len -1] == '#')
			{
				SockNode->Close();
				break;
			}
		}
		recv_buf[recv_len] = 0; // �ַ�������
		set_msg_log(buf, "���յ����з�������, ����[%d] ����[%s]\n", recv_len, recv_buf);
		if(recv_buf[0] != '&') // �����ʼ��־
		{
			set_msg_log(szMsg,"���з������ݸ�ʽ����ʼ��־����\n");
			return false; // ���ĸ�ʽ����
		}
		return true;
}


static bool is_success(char *recv_buf,Message *recv_Msg,char *szMsg)
{
	str2struct(recv_buf,recv_Msg);   // �������з��ص�����	
	print_recv_msg(recv_Msg);
	if(strcmp(recv_Msg->result,"00")!=0)
	{
		set_msg(szMsg,"���з��ؽ���ʧ�ܣ�����[%s] ������Ϣ[%s]\n",recv_Msg->result, recv_Msg->retmessage);
		return false;
	}
	set_msg(szMsg,"���з��ؽ��׳ɹ�\n");	
	return true;
}


static bool result(char *type,Message *recv_Msg,TRUSERID *handle,int *pRetCode,char *szMsg)
{
	double amt;
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	if(strcmp(type,"20210")==0) //20210����˾�������ѯ�����
	{
		SetCol(handle,F_LVOL1,F_DAMT0,F_DAMT1,F_SALL_NAME, F_VSMESS,0);
		amt = atof(recv_Msg->pay_amount);// ȡ�������
		out_pack->damt0=amt;// ȡ�������
		out_pack->damt1=amt;// 
		out_pack->lvol1=1; // ��������
		des2src(out_pack->sall_name, recv_Msg->acctno); // �����ʺ�
		des2src(out_pack->vsmess, szMsg);
		PutRow(handle,out_pack,pRetCode,szMsg);
	}
	else if(strcmp(type,"20200")==0||strcmp(type,"20201")==0) //20200����˾��������ת�˿ۿ�  20201����˾��������ת�˿ۿ����
	{
		SetCol(handle,F_LVOL1,F_SPHONE, F_VSMESS,0);
		out_pack->lvol1=1; // ��������
		des2src(out_pack->vsmess, szMsg);
		des2src(out_pack->sphone, recv_Msg->bankorder);// ���ж���ˮ��
		PutRow(handle,out_pack,pRetCode,szMsg);
	}
	else if(strcmp(type,"10000")==0||strcmp(type,"10001")==0) //10000������ί�й�ϵ  10001������ί�й�ϵ
	{
		SetCol(handle,F_SCARD0, F_VSMESS,F_VSVARSTR0, F_LSAFE_LEVEL, 0);
		out_pack->lsafe_level = 0;
		des2src(out_pack->scard0, recv_Msg->acctno);
		des2src(out_pack->vsmess, szMsg);
		des2src(out_pack->vsvarstr0, szMsg);
		PutRow(handle,out_pack,pRetCode,szMsg);
	}	
	else
	{
		set_msg(szMsg,"����δʵ��, ����[%d]\n",type);
		writelog(LOG_ERR,szMsg);
		return false;
	}
	return true;
}

static int Bank_Process(char *type , TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char bank_ip[20]={0}; // ����IP
	int bank_port=0;
	Message send_Msg={"0005",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	Message recv_Msg={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	char send_buf[MAX]={0};
	char recv_buf[MAX]={0};
	CTcpSocket  SockNode;
	int	bank_delay = 40000; // ��������ʱ����Ҫ���ܽϳ�
	initialize(type,bank_ip,&bank_port,&send_Msg,rPack,send_buf);  //��ʼ����������
	
	//���ɰ�ͷ
	GenMsgHead(msghead,rPack);

	//���ɲ�ѯ����
	GenMsgBodyQuery(msgbody,rPack);

	// ���ɲ�ѯ����
	GenTransReqMSG(msg,QUERY_BALA,msghead,msgbody);
	
	
	
	
	if(connect(&SockNode,bank_ip,bank_port,bank_delay,szMsg)==false){return E_TRANS_BANK_NETERR;}; //��������
	if(send(&SockNode,send_buf,szMsg)==false){return E_TRANS_BANK_NETERR;} //�������ݵ�����
	if(receive(&SockNode,recv_buf,sizeof(recv_buf),bank_delay,szMsg)==false){return E_TRANS_BANK_NOANSWER;} //�������з�����Ϣ
	if(is_success(recv_buf,&recv_Msg,szMsg)==false){return E_TRANS_BANK_RECVERR;}  //�ж����з��ؽ����Ƿ�ɹ�
	if(result(type,&recv_Msg,handle,pRetCode,szMsg)==false){return E_TRANS_FUNC_NONSUPPORT;}  //���ؽ��
	return 0;
}

// ��ѯ���
int Bank_Querybala(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char* msg = "�յ� ��ѯ��� ����\n";
	printf(msg);
	writelog(LOG_INFO,msg);
	//return Bank_Process(0 ,handle,rPack,pRetCode,szMsg);
	return Bank_Process("20210",handle,rPack,pRetCode,szMsg);
}

// ת��
int Bank_Trans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char* msg = "�յ� Ȧ��ת�� ����\n";
	printf(msg);
	writelog(LOG_INFO,msg);
	//return Bank_Process(1, handle,rPack,pRetCode,szMsg);
	return Bank_Process("20200",handle,rPack,pRetCode,szMsg);
}




// ����
int Bank_Reverse(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char* msg = "�յ� ת�˳��� ����\n";
	printf(msg);
	writelog(LOG_INFO,msg);
	//return Bank_Process(2, handle,rPack,pRetCode,szMsg);
	return Bank_Process("20201",handle,rPack,pRetCode,szMsg);
}

// ǩԼ
/*
int Bank_Bind(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char* msg = "�յ� ǩԼ ����\n";
	printf(msg);
	writelog(LOG_INFO,msg);
	// return Bank_Process(3, handle,rPack,pRetCode,szMsg);
	return Bank_Process("10000",handle,rPack,pRetCode,szMsg);
}
*/
// ��Լ
/*
int Bank_UnBind(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char* msg = "�յ� ��Լ ����\n";
	printf(msg);
	writelog(LOG_INFO,msg);
	//return Bank_Process(4, handle,rPack,pRetCode,szMsg);
	return Bank_Process("10001",handle,rPack,pRetCode,szMsg);
}
*/
// �޸�У����
int Bank_ChangePin(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char* msg = "�յ� �޸�У���� ����\n";
	printf(msg);
	writelog(LOG_INFO,msg);
	//return Bank_Process(5, handle,rPack,pRetCode,szMsg);
	return Bank_Process("00000",handle,rPack,pRetCode,szMsg);
}

// ����У����
int Bank_ResetPin(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char* msg = "�յ� ����У���� ����\n";
	printf(msg);
	writelog(LOG_INFO,msg);
	//return Bank_Process(6, handle,rPack,pRetCode,szMsg);
	return Bank_Process("00000",handle,rPack,pRetCode,szMsg);
}

// ����
int Bank_Checkacc(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char* msg = "�յ� ���� ����\n";
	printf(msg);
	writelog(LOG_INFO,msg);
	//return Bank_Process(7, handle,rPack,pRetCode,szMsg);
	return Bank_Process("00000",handle,rPack,pRetCode,szMsg);
}


// ��ѯ��
int Bank_Querybind(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	set_msg(szMsg,"Bank_Querybind ����δʵ��, ����[%c]\n",rPack->sstatus0[0] );
	writelog(LOG_ERR,szMsg);
	//return E_TRANS_FUNC_NONSUPPORT;
	return Bank_Process("00000",handle,rPack,pRetCode,szMsg);
}

int Bank_Transfer(INNER_TRANS_REQUEST*, int)
{
	return E_TRANS_FUNC_NONSUPPORT;

}

int Bank_QueryBalance(INNER_TRANS_REQUEST*, double*)
{
	return E_TRANS_FUNC_NONSUPPORT;
}

