#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tcp.h>
#include "profile.h"
#include <signal.h>
#include <yktclt.h>
#include <pubfunc.h>
#include <bank_gateway.h>

#define STRLENCPY(des,src,len) strncpy(des,src,strlen(src)>len?len:strlen(src))

CONFIG_PARA g_para;

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

static void print_recv_msg(Message *Msg)
{
	printf("===================== ���з��ر��Ŀ�ʼ =====================\n");
	print_msg(Msg);
	printf("===================== ���з��ر��Ľ��� ======================\n");
	return; 
}

static void print_send_msg(Message *Msg)
{
	printf("\n==================== ���ͱ��Ŀ�ʼ =====================\n");
	print_msg(Msg);
	printf("====================== ���ͱ��Ľ��� ======================\n");
	return; 
}

bool ReadIni(char *inifile)
{
   TIniFile tf;
  
   char szBuf[256];
  
   memset(&g_para,0,sizeof(g_para));
   printf("Begin to read ini-file:%s...\n",inifile);
   if (!tf.Open(inifile))
   {
      sprintf(szBuf,"���ܴ������ļ�<%s>\n",inifile);
      return false;
   }
   tf.ReadString("DRTP","drtp_ip","127.0.0.1",g_para.drtp_ip,sizeof(g_para.drtp_ip)-1);
   g_para.drtp_port = tf.ReadInt("DRTP","drtp_port",4000);
   g_para.main_funcno = tf.ReadInt("DRTP","main_func",9000);
   g_para.drtp_timeout = tf.ReadInt("DRTP","time_out",5000);
   
   g_para.bank_lisnport = tf.ReadInt("BANK","listen_port",4001);
   g_para.bank_timeout = tf.ReadInt("BANK","time_out",3000);
    g_para.term_id= tf.ReadInt("BANK","term_id",3000);
   tf.Close();
   return true;   
}

static void GenResMsgHead(char *msghead,char *refno,int errcode,char *errmsg)
{
	char buf[1024]="";
	char sysdate[9]="";
	char systime[7]="";
	getsysdate(sysdate);
	getsystime(systime);
	AddXmlItemStr(buf,"AreaNo","");								//��������
	AddXmlItemStr(buf,"ChanNo","");								//��������
	if(refno != NULL)
		AddXmlItemStr(buf,"TransNo",refno);						//������ˮ��
	else
		AddXmlItemStr(buf,"TransNo","");							
	AddXmlItemStr(buf,"TransDate",sysdate);						//��������
	AddXmlItemStr(buf,"TransTime",systime);						//����ʱ��
	AddXmlItemStr(buf,"BankNo","");								//��������
	AddXmlItemStr(buf,"TellerNo","");								//��Ա����
	AddXmlItemInt(buf, "FuncTionFlag", 1);							//�����־
	if(errcode!=0)
		AddXmlItemInt(buf, "ResultCode", errcode);
	else
		AddXmlItemStr(buf, "ResultCode", "0000");
	AddXmlItemStr(buf, "Err_Info", errmsg);
	AddXmlItemStr(msghead, "MsgHead", buf);						// ȫ������MsgHead ��	
}
static void GenBindResMsgBody(char *msgbody,INFO_BIND &info_bind)
{
	char buf[1024]="";
	AddXmlItemStr(buf, "SchoolCode", info_bind.SchoolCode);
	AddXmlItemStr(buf, "TrType", info_bind.TrType);
	AddXmlItemStr(buf, "CusName", info_bind.CusName);
	AddXmlItemStr(buf, "IcCard", info_bind.IcCard);
	AddXmlItemStr(buf, "ReMark","");
	AddXmlItemStr(msgbody, "MsgBody", buf);						// ȫ������MsgBody ��		
}

static void GenTradeResMsgBody(char *msgbody,INFO_TRADE &info_trade)
{
	char buf[1024]="";
	AddXmlItemStr(buf, "SchoolCode", info_trade.SchoolCode);
	AddXmlItemStr(buf, "CusName", info_trade.CusName);
	AddXmlItemDbl(buf, "ICCardNotWrt", info_trade.ICCardNotWrt);
	AddXmlItemStr(buf, "ReMark","");
	AddXmlItemStr(msgbody, "MsgBody", buf);						// ȫ������MsgBody ��		
}

static void GenTransResMSG(char *msg,char *transcode,char *msghead,char *msgbody)
{
	char len_buf[16]="";
	char transcont[2048]="";
	char *trans_head="<TranResponse>";
	char *trans_tail="</TranResponse>";

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
	
}


int doBind(KS_YKT_Clt &ykt_clt,INFO_BIND &info_bind,Message &recv_msg)
{
	printf("\n **********doBind************** \n");
	int ret=0;
	char errmsg[256]="";
	//writelog(LOG_INFO,"�� userno[%s],acctno[%s]\n", recv_msg.userno, recv_msg.acctno);
	printf("\n�� userno[%s]  acctno[%s]\n", recv_msg.userno, recv_msg.acctno);
	ykt_clt.SetStringFieldByName("sstatus0", "A");		
    ykt_clt.SetStringFieldByName("scust_auth2", recv_msg.userno);		
    ykt_clt.SetStringFieldByName("sname", recv_msg.usernoalias);		
    ykt_clt.SetStringFieldByName("scard1" ,recv_msg.acctno);		
    ykt_clt.SetStringFieldByName("scust_no", recv_msg.bankorder);	
    //ykt_clt.SetStringFieldByName("sbank_code", BANKCODE);	
	ykt_clt.SetStringFieldByName("sbank_code","00");	
// 	ykt_clt.SetIntFieldByName("lwithdraw_flag", recv_msg.result);
    	if(!ykt_clt.SendRequest(841602, g_para.drtp_timeout))
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_bind.ReMark,errmsg);
    		writelog(LOG_ERR,"���̨��������ʧ��[%s]\n",errmsg);
    		return 	-1;
    	}
    	if(ret = ykt_clt.GetReturnCode())
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_bind.ReMark,errmsg);
    		writelog(LOG_ERR,"��̨����ִ��ʧ��,retcode[%d],msg[%s]\n",ret,errmsg);
    		return  ret;
    	}
 	des2src(info_bind.TrType,"01");
	des2src(info_bind.IcCard, recv_msg.userno);
// 	des2src(info_bind.IcCard, stuemp_no);
 	des2src(info_bind.SchoolCode,SCHOOLCODE_AHUT);
 	des2src(info_bind.ReMark,"ǩԼ�ɹ�");
	return 0;
}
int doUnbind(KS_YKT_Clt &ykt_clt,INFO_BIND &info_bind,Message &recv_msg)
{
	int ret=0;
	char errmsg[256]="";
	printf("\n **********doUnbind************** \n");
	//writelog(LOG_INFO,"��ɾ�� stuempno[%s],acctno[%s]\n",stuemp_no,bank_no);
	writelog(LOG_INFO,"��ɾ�� userno[%s],bankno[%s]\n", recv_msg.userno, recv_msg.acctno);       
	ykt_clt.SetStringFieldByName("sstatus0", "D");		
        ykt_clt.SetStringFieldByName("scust_auth2", recv_msg.userno);		       
        ykt_clt.SetStringFieldByName("scard0", recv_msg.acctno);		
        // ykt_clt.SetIntFieldByName("lwithdraw_flag", g_para.term_id);
		 
    	if(!ykt_clt.SendRequest(841602, g_para.drtp_timeout))
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_bind.ReMark,errmsg);
    		writelog(LOG_ERR,"���̨��������ʧ��[%s]\n",errmsg);
    		return 	-1;
    	}
    	if(ret = ykt_clt.GetReturnCode())
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_bind.ReMark,errmsg);
    		writelog(LOG_ERR,"��̨����ִ��ʧ��,retcode[%d],msg[%s]\n",ret,errmsg);
    		return  ret;
    	}
	des2src(info_bind.TrType,"03");
	//des2src(info_bind.IcCard, stuemp_no);
	des2src(info_bind.IcCard, recv_msg.userno);
	des2src(info_bind.SchoolCode,SCHOOLCODE_AHUT);
	des2src(info_bind.ReMark,"��Լ�ɹ�");

	return 0;
}

// �󶨹�ϵ�޸�
int doUpbing(KS_YKT_Clt &ykt_clt,INFO_BIND &info_bind,char *recv_buf)
{
	int ret=0;
	char errmsg[256]="";
	char stuemp_no[32]="";						//ѧ����
	char bank_no[21]="";						// ���п���
	char bankseri[21]="";						// ���ж���ˮ��
	ret = GetXmlValue(stuemp_no, 32, "IcCard", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡIcCard �Ŵ���");
		return ret;
	}
	trim(stuemp_no);
	
	ret = GetXmlValue(bank_no, 21, "ActNo", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡActNo �Ŵ���");
		return ret;
	}
	trim(bank_no);
	ret = GetXmlValue(bankseri, 21, "TransNo", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡTransNo �Ŵ���");
		return ret;
	}
	trim(bankseri);
	
	writelog(LOG_INFO,"���޸� stuempno[%s],bankno[%s]\n",stuemp_no,bank_no);
        ykt_clt.SetStringFieldByName("sstatus0", "U");		
        ykt_clt.SetStringFieldByName("scust_auth2", stuemp_no);		
        ykt_clt.SetStringFieldByName("scard1", bank_no);		
        ykt_clt.SetStringFieldByName("scust_no", bankseri);	
        ykt_clt.SetStringFieldByName("sbank_code", BANKCODE);	
        ykt_clt.SetIntFieldByName("lwithdraw_flag", g_para.term_id);
		
    	if(!ykt_clt.SendRequest(841602, g_para.drtp_timeout))
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_bind.ReMark,errmsg);
    		writelog(LOG_ERR,"���̨��������ʧ��[%s]\n",errmsg);
    		return 	-1;
    	}
    	if(ret = ykt_clt.GetReturnCode())
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_bind.ReMark,errmsg);
    		writelog(LOG_ERR,"��̨����ִ��ʧ��,retcode[%d],msg[%s]\n",ret,errmsg);
    		return  ret;
    	}
	des2src(info_bind.TrType,"02");
	des2src(info_bind.IcCard, stuemp_no);
	des2src(info_bind.SchoolCode,SCHOOLCODE_AHUT);
	des2src(info_bind.ReMark,"�޸ĳɹ�");
	return 0;
}
int doCkbing(KS_YKT_Clt &ykt_clt,INFO_BIND &info_bind,char *recv_buf)
{
	int ret=0;
	char errmsg[256]="";
	char stuemp_no[32]="";						//ѧ����
	ret = GetXmlValue(stuemp_no, 32, "IcCard", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡIcCard �Ŵ���");
		return ret;
	}
	trim(stuemp_no);
	ykt_clt.SetStringFieldByName("sstatus0", "R");		
        ykt_clt.SetStringFieldByName("spager", stuemp_no);		
        ykt_clt.SetStringFieldByName("sbank_code", BANKCODE);	
	ykt_clt.SetStringFieldByName("sstatus1", "1");	
	ykt_clt.SetIntFieldByName("lwithdraw_flag", g_para.term_id);
         
    	if(!ykt_clt.SendRequest(841602, g_para.drtp_timeout))
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_bind.ReMark,errmsg);
    		writelog(LOG_ERR,"���̨��������ʧ��[%s]\n",errmsg);
    		return 	-1;
    	}
    	if(ret = ykt_clt.GetReturnCode())
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_bind.ReMark,errmsg);
    		writelog(LOG_ERR,"��̨����ִ��ʧ��,retcode[%d],msg[%s]\n",ret,errmsg);
    		return  ret;
    	}
	else
	{
		ykt_clt.GetStringFieldByName("sall_name",info_bind.CusName, sizeof(info_bind.CusName));		
		des2src(info_bind.TrType,"04");
		des2src(info_bind.IcCard, stuemp_no);
		des2src(info_bind.SchoolCode,SCHOOLCODE_AHUT);
		des2src(info_bind.ReMark,"��ѯ�ɹ�");
		return 0;
	}
	return 0;
}

//�޿���ֵ��ѯ
int doCkbala(KS_YKT_Clt &ykt_clt,INFO_TRADE &info_trade,char *recv_buf)
{
	int ret=0;
	char errmsg[256]="";
	char stuemp_no[32]="";						//ѧ����
		
	ret = GetXmlValue(stuemp_no, 32, "IcCard", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡIcCard �Ŵ���");
		return ret;
	}
	trim(stuemp_no);
	
	ykt_clt.SetStringFieldByName("spager", stuemp_no);		
	ykt_clt.SetStringFieldByName("sstatus1", "C");				// ���ױ�־
	ykt_clt.SetIntFieldByName("lwithdraw_flag", g_para.term_id);

	if(!ykt_clt.SendRequest(847133, g_para.drtp_timeout))
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_trade.ReMark,errmsg);
    		writelog(LOG_ERR,"���̨��������ʧ��[%s]\n",errmsg);
    		return 	-1;
    	}
    	if(ret = ykt_clt.GetReturnCode())
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_trade.ReMark,errmsg);
    		writelog(LOG_ERR,"��̨����ִ��ʧ��,retcode[%d],msg[%s]\n",ret,errmsg);
    		return  ret;
    	}
	else
	{
		ykt_clt.GetStringFieldByName("sall_name",info_trade.CusName, sizeof(info_trade.CusName));		// ����
		ykt_clt.GetDoubleFieldByName("damt0", &info_trade.ICCardNotWrt);							//δ��ֵ���
		ykt_clt.GetDoubleFieldByName("damt1", &info_trade.IcCardBal);								//�ʻ����
	}
	
	return 0;
}

//�޿���ֵ,����
int doTrade(KS_YKT_Clt &ykt_clt,INFO_TRADE &info_trade,char *recv_buf,bool bRev)
{
	int ret=0;
	char errmsg[256]="";
	char stuemp_no[32]="";						//ѧ����
	char samount[32]="";						//���
	double damount = 0;
	char RSeqNo[21]="";						// ������ˮ��
	char TransNo[21]="";
	char transflag[2]="";

	ret = GetXmlValue(TransNo, 21, "TransNo", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡTransNo �Ŵ���");
		return ret;
	}
	ret = GetXmlValue(stuemp_no, 32, "IcCard", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡIcCard �Ŵ���");
		return ret;
	}
	ret = GetXmlValue(samount, 32, "Amount", recv_buf);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡAmount ����");
		return ret;
	}

	transflag[0]='T';				// ��ֵ
	if(bRev)					// ����
	{
		ret = GetXmlValue(RSeqNo, 21, "RSeqNo", recv_buf);
		if(ret)
		{
			writelog(LOG_ERR,"��ȡRSeqNo ����");
			return ret;
		}
		trim(RSeqNo);
		transflag[0]='R';				// ����
		ykt_clt.SetStringFieldByName("scust_auth", RSeqNo);			// ������ˮ��
		
	}
	trim(stuemp_no);
	trim(samount);
	damount = atof(samount);	

	ykt_clt.SetStringFieldByName("sstatus1", transflag);				// ���ױ�־
	ykt_clt.SetStringFieldByName("scust_auth2", TransNo);		
        ykt_clt.SetStringFieldByName("spager", stuemp_no);		
        ykt_clt.SetDoubleFieldByName("damt0", damount);	
	ykt_clt.SetIntFieldByName("lwithdraw_flag", g_para.term_id);
         
    	if(!ykt_clt.SendRequest(847133, g_para.drtp_timeout))
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_trade.ReMark,errmsg);
    		writelog(LOG_ERR,"���̨��������ʧ��[%s]\n",errmsg);
    		return 	-1;
    	}
    	if(ret = ykt_clt.GetReturnCode())
    	{
    		ykt_clt.GetStringFieldByName("vsmess",errmsg,sizeof errmsg);       
    		trim(errmsg);
		des2src(info_trade.ReMark,errmsg);
    		writelog(LOG_ERR,"��̨����ִ��ʧ��,retcode[%d],msg[%s]\n",ret,errmsg);
    		return  ret;
    	}
	else
	{
		ykt_clt.GetStringFieldByName("sall_name",info_trade.CusName, sizeof(info_trade.CusName));			// ����
		ykt_clt.GetDoubleFieldByName("damt0", &info_trade.ICCardNotWrt);								//δ��ֵ���
		ykt_clt.GetStringFieldByName("sname2", info_trade.Refno, sizeof(info_trade.Refno));				// ��ˮ��
	}
	return 0;
}


int doResponse(char *recv_buf,int recv_len,char *send_buf,int &send_len)
{
	printf("\n -----------doResponse--------- \n");
	KS_YKT_Clt ykt_clt;
	int retcode = 0;
	Message recv_msg;
	INFO_BIND info_bind;
	str2struct(recv_buf,&recv_msg);
	print_recv_msg(&recv_msg);
	if(strcmp(recv_msg.txcode,"10000")==0)  //10000������ί�й�ϵ
	{
		retcode = doBind(ykt_clt,info_bind,recv_msg);

	}
	else if(strcmp(recv_msg.txcode,"10001")==0) //  10001������ί�й�ϵ
	{
		retcode = doUnbind(ykt_clt,info_bind,recv_msg);
	}
	else
	{
		return E_TRANS_NONSUPPORT;
	}
	struct2str(&recv_msg,send_buf);
	send_len=strlen(send_buf);
	print_send_msg(&recv_msg);  
	return 0;
  }
    
int doProcess(CTcpSocket &acpsocket)
{
    printf("\n doProcess3  \n");
	
	
	int ret = 0;
    int pack_len = 0;
    int send_len = 0;
    char recv_buf[4096] = "";
    char send_buf[4096] = "";
	//ret = acpsocket.Recv(recv_buf, HEAD_LEN, g_para.bank_timeout);
    //ret = acpsocket.Recv(recv_buf, 2048, g_para.bank_timeout);
	//ret = acpsocket.Recv(recv_buf, sizeof(recv_buf), g_para.bank_timeout);
	acpsocket.Recv(recv_buf, sizeof(recv_buf), g_para.bank_timeout);
	ret=strlen(recv_buf);
	printf("\n recv_buf[%s] \n len[%d] ret[%d]\n",recv_buf,strlen(recv_buf),ret);
// 	if(ret != HEAD_LEN)
//     {
//         writelog(LOG_ERR,"�����������ݰ�ͷ����\n");
//         return -1;
//     }
//     pack_len = atoi(recv_buf);
//     ret = acpsocket.Recv(recv_buf, pack_len, g_para.bank_timeout);
//     if(ret != pack_len)
//     {
//         writelog(LOG_ERR,"�����������ݰ������\n");
//         return -1;
//     }
 //   recv_buf[pack_len]=0;
    writelog(LOG_INFO,"len[%d],recv_buf[%s]\n",ret,recv_buf);
    ret = doResponse(recv_buf,strlen(recv_buf),send_buf,send_len);
    if(ret)
    {
        if(ret>0)
            return ret;
    }    
    
    send_buf[send_len]=0;
    writelog(LOG_INFO,"len[%d],send_buf[%s]\n",send_len,send_buf);
    printf("\n xxxxxxxxxxxxxxxxx \nsend_buf[%s]\nsend_len[%d]\n   xxxxxxxxxxxxxxxx\n",send_buf);
	ret = acpsocket.Send(send_buf,send_len);
	//ret = acpsocket.Send("1234",4);
	
/*
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

*/





   
	
	if(ret != send_len)
    {
        writelog(LOG_ERR,"�������ݴ���\n");
        return -1;
    }
    return 0;
}
int main()
{
 //   int ret = 0;
//	printf("\naaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
	
	
	bool flag = false;
	int childpid = 0;
	char *inifile = "transconfig.ini";
	CTcpSocket tcpsocket ;
	CTcpSocket sockettmp ;
	
	openlog("yktbank_gateway",LOG_PID|LOG_CONS|LOG_NDELAY,LOG_LOCAL3);
	
	if( !ReadIni(inifile))
	{
	    printf("��ȡ�����ļ�[%s]ʧ��\n",inifile);
	    return -1;
	}
	
	writelog(LOG_DEBUG,"drtp_ip[%s],drtp_port[%d],mainfuncno[%d],list_port[%d]",g_para.drtp_ip, g_para.drtp_port, g_para.main_funcno,g_para.bank_lisnport);
	printf("\n drtp_ip[%s],drtp_port[%d],mainfuncno[%d],list_port[%d]\n",g_para.drtp_ip, g_para.drtp_port, g_para.main_funcno,g_para.bank_lisnport);
	if(!KS_YKT_Clt::Initialize(g_para.drtp_ip, g_para.drtp_port, g_para.main_funcno))
	{
		printf("----------��ʼ��ͨѶƽ̨ʧ��----------\n");
		return 	-1;
	}
		
	signal(SIGCHLD,SIG_IGN);
	signal(SIGINT,SIG_DFL);
	flag = tcpsocket.Create();
	if(!flag)
		exit(1);
	flag = tcpsocket.Listen(g_para.bank_lisnport);
	if(!flag)
		exit(1);
	while(1)
	{
			flag = tcpsocket.Accept(sockettmp);
			
			if(!flag)
				continue;
			if ((childpid = fork()) == 0)		/* �ӽ��� */
			{   
				tcpsocket.Close();  
				
				doProcess(sockettmp);     /* �������� */  
				
				sockettmp.Close();
				exit(0);  
			}  
			else if(childpid < 0)
			{
                		printf("�����ӽ���ʧ��\n");
			}
			sockettmp.Close(); 		/* ������ */  
	}
	tcpsocket.Close();
	KS_YKT_Clt::Uninitialize();
	closelog();
	return 0;
}

